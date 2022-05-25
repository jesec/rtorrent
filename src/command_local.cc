// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "buildinfo.h"

#include <fcntl.h>
#include <functional>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <torrent/chunk_manager.h>
#include <torrent/data/chunk_utils.h>
#include <torrent/data/file_manager.h>
#include <torrent/torrent.h>
#include <torrent/utils/error_number.h>
#include <torrent/utils/option_strings.h>
#include <torrent/utils/path.h>
#include <torrent/utils/string_manip.h>
#include <unistd.h>

#include "core/download.h"
#include "core/download_list.h"
#include "core/download_store.h"
#include "core/manager.h"
#include "rpc/parse_commands.h"
#include "rpc/scgi.h"
#include "utils/file_status_cache.h"

#include "command_helpers.h"
#include "control.h"
#include "globals.h"

using CM_t = torrent::ChunkManager;
using FM_t = torrent::FileManager;

torrent::Object
apply_pieces_stats_total_size() {
  uint64_t            size   = 0;
  core::DownloadList* d_list = control->core()->download_list();

  for (core::DownloadList::iterator itr = d_list->begin(), last = d_list->end();
       itr != last;
       itr++)
    if ((*itr)->is_active())
      size += (*itr)->file_list()->size_bytes();

  return size;
}

torrent::Object
system_env(const torrent::Object::string_type& arg) {
  if (arg.empty())
    throw torrent::input_error("system.env: Missing variable name.");

  char* val = getenv(arg.c_str());
  return std::string(val ? val : "");
}

torrent::Object
system_hostname() {
  char buffer[1024];

  if (gethostname(buffer, 1023) == -1)
    throw torrent::input_error("Unable to read hostname.");

  //   if (shorten)
  //     *std::find(buffer, buffer + 1023, '.') = '\0';

  return std::string(buffer);
}

torrent::Object
system_get_cwd() {
  char* buffer = getcwd(nullptr, 0);

  if (buffer == nullptr)
    throw torrent::input_error("Unable to read cwd.");

  torrent::Object result = torrent::Object(std::string(buffer));
  free(buffer);

  return result;
}

torrent::Object
system_set_cwd(const torrent::Object::string_type& rawArgs) {
  if (::chdir(rawArgs.c_str()) != 0)
    throw torrent::input_error("Could not change current working directory.");

  return torrent::Object();
}

inline torrent::Object::list_const_iterator
post_increment(torrent::Object::list_const_iterator&       itr,
               const torrent::Object::list_const_iterator& last) {
  if (itr == last)
    throw torrent::input_error("Invalid number of arguments.");

  return itr++;
}

inline const std::string&
check_name(const std::string& str) {
  if (!torrent::utils::is_all_name(str))
    throw torrent::input_error("Non-alphanumeric characters found.");

  return str;
}

torrent::Object
group_insert(const torrent::Object::list_type& args) {
  torrent::Object::list_const_iterator itr  = args.begin();
  torrent::Object::list_const_iterator last = args.end();

  const std::string& name = check_name(post_increment(itr, last)->as_string());
  const std::string& view = check_name(post_increment(itr, last)->as_string());

  rpc::commands.call("method.insert",
                     rpc::create_object_list("group." + name + ".ratio.enable",
                                             "simple",
                                             "schedule2=group." + name +
                                               ".ratio,5,60,on_ratio=" + name));
  rpc::commands.call(
    "method.insert",
    rpc::create_object_list("group." + name + ".ratio.disable",
                            "simple",
                            "schedule_remove2=group." + name + ".ratio"));
  rpc::commands.call(
    "method.insert",
    rpc::create_object_list("group." + name + ".ratio.command",
                            "simple",
                            "d.try_close= ;d.ignore_commands.set=1"));
  rpc::commands.call(
    "method.insert",
    rpc::create_object_list("group2." + name + ".view", "string", view));
  rpc::commands.call("method.insert",
                     rpc::create_object_list(
                       "group2." + name + ".ratio.min", "value", (int64_t)200));
  rpc::commands.call("method.insert",
                     rpc::create_object_list(
                       "group2." + name + ".ratio.max", "value", (int64_t)300));
  rpc::commands.call("method.insert",
                     rpc::create_object_list("group2." + name + ".ratio.upload",
                                             "value",
                                             (int64_t)20 << 20));

  return name;
}

static constexpr int file_print_use_space   = 0x1;
static constexpr int file_print_delim_space = 0x2;

void
file_print_list(torrent::Object::list_const_iterator first,
                torrent::Object::list_const_iterator last,
                FILE*                                output,
                int                                  flags) {
  while (first != last) {
    switch (first->type()) {
      case torrent::Object::TYPE_STRING:
        fprintf(output,
                (const char*)" %s" + !(flags & file_print_use_space),
                first->as_string().c_str());
        break;
      case torrent::Object::TYPE_VALUE:
        fprintf(output,
                (const char*)" %" PRIi64 + !(flags & file_print_use_space),
                first->as_value());
        break;
      case torrent::Object::TYPE_LIST:
        file_print_list(
          first->as_list().begin(), first->as_list().end(), output, 0);
        break;
      case torrent::Object::TYPE_NONE:
        break;
      default:
        throw torrent::input_error("Invalid type.");
    }

    flags |= (flags & file_print_delim_space) >> 1;
    first++;
  }
}

torrent::Object
cmd_file_append(const torrent::Object::list_type& args) {
  if (args.empty())
    throw torrent::input_error("Invalid number of arguments.");

  FILE* output = fopen(args.front().as_string().c_str(), "a");

  if (output == nullptr)
    throw torrent::input_error(
      "Could not append to file '" + args.front().as_string() +
      "': " + torrent::utils::error_number::current().message());

  file_print_list(++args.begin(), args.end(), output, file_print_delim_space);

  fprintf(output, "\n");
  fclose(output);
  return torrent::Object();
}

void
initialize_command_local() {
  core::DownloadList*    dList        = control->core()->download_list();
  core::DownloadStore*   dStore       = control->core()->download_store();
  torrent::ChunkManager* chunkManager = torrent::chunk_manager();
  torrent::FileManager*  fileManager  = torrent::file_manager();

  CMD2_ANY("system.hostname",
           [](const auto&, const auto&) { return system_hostname(); });
  CMD2_ANY("system.pid", [](const auto&, const auto&) { return getpid(); });

  CMD2_VAR_C_STRING("system.api_version", (int64_t)RT_API_VERSION);
  CMD2_VAR_C_STRING("system.client_version", RT_VERSION);
  CMD2_VAR_C_STRING("system.library_version", torrent::version());
  CMD2_VAR_VALUE("system.file.allocate", 0);
  CMD2_VAR_VALUE("system.file.max_size", (int64_t)512 << 30);
  CMD2_VAR_VALUE("system.file.split_size", -1);
  CMD2_VAR_STRING("system.file.split_suffix", ".part");

  CMD2_ANY("system.file_status_cache.size", [](const auto&, const auto&) {
    return control->core()->file_status_cache()->size();
  });
  CMD2_ANY_V("system.file_status_cache.prune", [](const auto&, const auto&) {
    return control->core()->file_status_cache()->prune();
  });

  CMD2_VAR_BOOL("file.prioritize_toc", 0);
  CMD2_VAR_LIST("file.prioritize_toc.first");
  CMD2_VAR_LIST("file.prioritize_toc.last");

  CMD2_ANY("system.files.opened_counter",
           [fileManager](const auto&, const auto&) {
             return fileManager->files_opened_counter();
           });
  CMD2_ANY("system.files.closed_counter",
           [fileManager](const auto&, const auto&) {
             return fileManager->files_closed_counter();
           });
  CMD2_ANY("system.files.failed_counter",
           [fileManager](const auto&, const auto&) {
             return fileManager->files_failed_counter();
           });

  CMD2_ANY_STRING("system.env",
                  [](const auto&, const auto& arg) { return system_env(arg); });

  CMD2_ANY("system.time",
           [](const auto&, const auto&) { return cachedTime.seconds(); });
  CMD2_ANY("system.time_seconds", [](const auto&, const auto&) {
    return torrent::utils::timer::current_seconds();
  });
  CMD2_ANY("system.time_usec", [](const auto&, const auto&) {
    return torrent::utils::timer::current_usec();
  });

  CMD2_ANY_VALUE_V("system.umask.set",
                   [](const auto&, const auto& mode) { return umask(mode); });

  CMD2_VAR_BOOL("system.daemon", false);

  CMD2_ANY_V("system.shutdown.normal", [](const auto&, const auto&) {
    return control->receive_normal_shutdown();
  });
  CMD2_ANY_V("system.shutdown.quick", [](const auto&, const auto&) {
    return control->receive_quick_shutdown();
  });
  CMD2_REDIRECT_GENERIC_NO_EXPORT("system.shutdown", "system.shutdown.normal");

  CMD2_ANY("system.cwd",
           [](const auto&, const auto&) { return system_get_cwd(); });
  CMD2_ANY_STRING("system.cwd.set", [](const auto&, const auto& rawArgs) {
    return system_set_cwd(rawArgs);
  });

  CMD2_ANY("pieces.sync.always_safe", [chunkManager](const auto&, const auto&) {
    return chunkManager->safe_sync();
  });
  CMD2_ANY_VALUE_V("pieces.sync.always_safe.set",
                   [chunkManager](const auto&, const auto& state) {
                     return chunkManager->set_safe_sync(state);
                   });
  CMD2_ANY("pieces.sync.safe_free_diskspace",
           [chunkManager](const auto&, const auto&) {
             return chunkManager->safe_free_diskspace();
           });
  CMD2_ANY("pieces.sync.timeout", [chunkManager](const auto&, const auto&) {
    return chunkManager->timeout_sync();
  });
  CMD2_ANY_VALUE_V("pieces.sync.timeout.set",
                   [chunkManager](const auto&, const auto& seconds) {
                     return chunkManager->set_timeout_sync(seconds);
                   });
  CMD2_ANY("pieces.sync.timeout_safe",
           [chunkManager](const auto&, const auto&) {
             return chunkManager->timeout_safe_sync();
           });
  CMD2_ANY_VALUE_V("pieces.sync.timeout_safe.set",
                   [chunkManager](const auto&, const auto& seconds) {
                     return chunkManager->set_timeout_safe_sync(seconds);
                   });
  CMD2_ANY("pieces.sync.queue_size", [chunkManager](const auto&, const auto&) {
    return chunkManager->sync_queue_size();
  });

  CMD2_ANY("pieces.preload.type", [chunkManager](const auto&, const auto&) {
    return chunkManager->preload_type();
  });
  CMD2_ANY_VALUE_V("pieces.preload.type.set",
                   [chunkManager](const auto&, const auto& t) {
                     return chunkManager->set_preload_type(t);
                   });
  CMD2_ANY("pieces.preload.min_size", [chunkManager](const auto&, const auto&) {
    return chunkManager->preload_min_size();
  });
  CMD2_ANY_VALUE_V("pieces.preload.min_size.set",
                   [chunkManager](const auto&, const auto& bytes) {
                     return chunkManager->set_preload_min_size(bytes);
                   });
  CMD2_ANY("pieces.preload.min_rate", [chunkManager](const auto&, const auto&) {
    return chunkManager->preload_required_rate();
  });
  CMD2_ANY_VALUE_V("pieces.preload.min_rate.set",
                   [chunkManager](const auto&, const auto& bytes) {
                     return chunkManager->set_preload_required_rate(bytes);
                   });

  CMD2_ANY("pieces.memory.current", [chunkManager](const auto&, const auto&) {
    return chunkManager->memory_usage();
  });
  CMD2_ANY("pieces.memory.sync_queue",
           [chunkManager](const auto&, const auto&) {
             return chunkManager->sync_queue_memory_usage();
           });
  CMD2_ANY("pieces.memory.block_count",
           [chunkManager](const auto&, const auto&) {
             return chunkManager->memory_block_count();
           });
  CMD2_ANY("pieces.memory.max", [chunkManager](const auto&, const auto&) {
    return chunkManager->max_memory_usage();
  });
  CMD2_ANY_VALUE_V("pieces.memory.max.set",
                   [chunkManager](const auto&, const auto& bytes) {
                     return chunkManager->set_max_memory_usage(bytes);
                   });
  CMD2_ANY("pieces.stats_preloaded", [chunkManager](const auto&, const auto&) {
    return chunkManager->stats_preloaded();
  });
  CMD2_ANY("pieces.stats_not_preloaded",
           [chunkManager](const auto&, const auto&) {
             return chunkManager->stats_not_preloaded();
           });

  CMD2_ANY("pieces.stats.total_size", [](const auto&, const auto&) {
    return apply_pieces_stats_total_size();
  });

  CMD2_ANY("pieces.hash.queue_size",
           [](const auto&, const auto&) { return torrent::hash_queue_size(); });
  CMD2_VAR_BOOL("pieces.hash.on_completion", false);

  CMD2_VAR_STRING("directory.default", "./");

  CMD2_VAR_STRING("session.name", "");
  CMD2_VAR_BOOL("session.use_lock", true);
  CMD2_VAR_BOOL("session.on_completion", true);

  CMD2_ANY("session.path",
           [dStore](const auto&, const auto&) { return dStore->path(); });
  CMD2_ANY_STRING_V(
    "session.path.set",
    [dStore](const auto&, const auto& path) { return dStore->set_path(path); });

  CMD2_ANY_V("session.save", [dList](const auto&, const auto&) {
    return dList->session_save();
  });

#define CMD2_EXECUTE(key, flags)                                               \
  CMD2_ANY(key, [](const auto&, const auto& rawArgs) {                         \
    return rpc::execFile.execute_object(rawArgs, flags);                       \
  });

  CMD2_EXECUTE("execute2",
               rpc::ExecFile::flag_expand_tilde | rpc::ExecFile::flag_throw);
  CMD2_EXECUTE("execute.throw",
               rpc::ExecFile::flag_expand_tilde | rpc::ExecFile::flag_throw);
  CMD2_EXECUTE("execute.throw.bg",
               rpc::ExecFile::flag_expand_tilde | rpc::ExecFile::flag_throw |
                 rpc::ExecFile::flag_background);
  CMD2_EXECUTE("execute.nothrow", rpc::ExecFile::flag_expand_tilde);
  CMD2_EXECUTE("execute.nothrow.bg",
               rpc::ExecFile::flag_expand_tilde |
                 rpc::ExecFile::flag_background);
  CMD2_EXECUTE("execute.raw", rpc::ExecFile::flag_throw);
  CMD2_EXECUTE("execute.raw.bg",
               rpc::ExecFile::flag_throw | rpc::ExecFile::flag_background);
  CMD2_EXECUTE("execute.raw_nothrow", 0);
  CMD2_EXECUTE("execute.raw_nothrow.bg", rpc::ExecFile::flag_background);
  CMD2_EXECUTE("execute.capture",
               rpc::ExecFile::flag_throw | rpc::ExecFile::flag_expand_tilde |
                 rpc::ExecFile::flag_capture);
  CMD2_EXECUTE("execute.capture_nothrow",
               rpc::ExecFile::flag_expand_tilde | rpc::ExecFile::flag_capture);

  CMD2_ANY_LIST("file.append", [](const auto&, const auto& args) {
    return cmd_file_append(args);
  });

  // TODO: Convert to new command types:
  *rpc::command_base::argument(0) = "placeholder.0";
  *rpc::command_base::argument(1) = "placeholder.1";
  *rpc::command_base::argument(2) = "placeholder.2";
  *rpc::command_base::argument(3) = "placeholder.3";
  CMD2_ANY_P("argument.0", [](const auto&, const auto&) {
    return rpc::command_base::argument_ref(0);
  });
  CMD2_ANY_P("argument.1", [](const auto&, const auto&) {
    return rpc::command_base::argument_ref(1);
  });
  CMD2_ANY_P("argument.2", [](const auto&, const auto&) {
    return rpc::command_base::argument_ref(2);
  });
  CMD2_ANY_P("argument.3", [](const auto&, const auto&) {
    return rpc::command_base::argument_ref(3);
  });

  CMD2_ANY_LIST("group.insert", [](const auto&, const auto& args) {
    return group_insert(args);
  });
}
