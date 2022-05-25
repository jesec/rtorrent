// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "command_helpers.h"
#include "control.h"
#include "core/manager.h"
#include "core/view_manager.h"
#include "rpc/command.h"
#include "rpc/parse.h"
#include "ui/root.h"

using view_event_slot = std::function<
  void(core::ViewManager*, const std::string&, const torrent::Object&)>;

torrent::Object
apply_view_filter_on(const torrent::Object::list_type& args) {
  if (args.size() < 1)
    throw torrent::input_error("Too few arguments.");

  const std::string& name = args.front().as_string();

  if (name.empty())
    throw torrent::input_error("First argument must be a string.");

  core::ViewManager::filter_args filterArgs;

  for (torrent::Object::list_const_iterator itr  = ++args.begin(),
                                            last = args.end();
       itr != last;
       itr++)
    filterArgs.push_back(itr->as_string());

  control->view_manager()->set_filter_on(name, filterArgs);

  return torrent::Object();
}

torrent::Object
apply_view_event(const view_event_slot&            viewFilterSlot,
                 const torrent::Object::list_type& args) {
  if (args.size() != 2)
    throw torrent::input_error("Wrong argument count.");

  viewFilterSlot(
    control->view_manager(), args.front().as_string(), args.back());

  return torrent::Object();
}

torrent::Object
apply_view_sort(const torrent::Object::list_type& args) {
  if (args.size() <= 0 || args.size() > 2)
    throw torrent::input_error("Wrong argument count.");

  const std::string& name = args.front().as_string();

  if (name.empty())
    throw torrent::input_error("First argument must be a string.");

  int32_t value = 0;

  if (args.size() == 2)
    value = rpc::convert_to_value(args.back());

  control->view_manager()->sort(name, value);

  return torrent::Object();
}

torrent::Object
apply_view_list() {
  torrent::Object             rawResult = torrent::Object::create_list();
  torrent::Object::list_type& result    = rawResult.as_list();

  for (core::ViewManager::const_iterator itr = control->view_manager()->begin(),
                                         last = control->view_manager()->end();
       itr != last;
       itr++)
    result.push_back((*itr)->name());

  return rawResult;
}

torrent::Object
apply_view_set(const torrent::Object::list_type& args) {
  if (args.size() != 2)
    throw torrent::input_error("Wrong argument count.");

  core::ViewManager::iterator itr =
    control->view_manager()->find(args.back().as_string());

  if (itr == control->view_manager()->end())
    throw torrent::input_error("Could not find view \"" +
                               args.back().as_string() + "\".");

  //   if (args.front().as_string() == "main")
  //     control->ui()->download_list()->set_view(*itr);
  //   else
  throw torrent::input_error("No such target.");
}

torrent::Object
apply_print(rpc::target_type, const torrent::Object& rawArgs) {
  char buffer[1024];
  rpc::print_object(buffer, buffer + 1024, &rawArgs, 0);

  control->core()->push_log(buffer);
  return torrent::Object();
}

torrent::Object
cmd_view_size(const torrent::Object::string_type& args) {
  return (*control->view_manager()->find_throw(args))->size_visible();
}

torrent::Object
cmd_view_size_not_visible(const torrent::Object::string_type& args) {
  return (*control->view_manager()->find_throw(args))->size_not_visible();
}

torrent::Object
cmd_view_persistent(const torrent::Object::string_type& args) {
  core::View* view = *control->view_manager()->find_throw(args);

  if (!view->get_filter().is_empty() || !view->event_added().is_empty() ||
      !view->event_removed().is_empty())
    throw torrent::input_error("Cannot set modified views as persitent.");

  view->set_filter("d.views.has=" + args);
  view->set_event_added("d.views.push_back_unique=" + args);
  view->set_event_removed("d.views.remove=" + args);

  return torrent::Object();
}

// TODO: These don't need wrapper functions anymore...
torrent::Object
cmd_ui_set_view(const torrent::Object::string_type& args) {
  control->ui()->download_list()->set_current_view(args);
  return torrent::Object();
}

torrent::Object
cmd_ui_current_view() {
  return control->ui()->download_list()->current_view()->name();
}

torrent::Object
cmd_ui_unfocus_download(core::Download* download) {
  control->ui()->download_list()->unfocus_download(download);

  return torrent::Object();
}

torrent::Object
cmd_view_filter_download(core::Download*                     download,
                         const torrent::Object::string_type& args) {
  (*control->view_manager()->find_throw(args))->filter_download(download);

  return torrent::Object();
}

torrent::Object
cmd_view_set_visible(core::Download*                     download,
                     const torrent::Object::string_type& args) {
  (*control->view_manager()->find_throw(args))->set_visible(download);

  return torrent::Object();
}

torrent::Object
cmd_view_set_not_visible(core::Download*                     download,
                         const torrent::Object::string_type& args) {
  (*control->view_manager()->find_throw(args))->set_not_visible(download);

  return torrent::Object();
}

torrent::Object
cmd_status_throttle_names(bool up, const torrent::Object::list_type& args) {
  if (args.size() == 0)
    return torrent::Object();

  std::vector<std::string> throttle_name_list;

  for (torrent::Object::list_const_iterator itr  = args.begin(),
                                            last = args.end();
       itr != last;
       itr++) {
    if (itr->is_string())
      throttle_name_list.push_back(itr->as_string());
  }

  if (up)
    control->ui()->set_status_throttle_up_names(throttle_name_list);
  else
    control->ui()->set_status_throttle_down_names(throttle_name_list);

  return torrent::Object();
}

void
initialize_command_ui() {
  CMD2_VAR_STRING("keys.layout", "qwerty");

  CMD2_ANY_STRING("view.add",
                  object_convert_void([](const auto&, const auto& name) {
                    return control->view_manager()->insert_throw(name);
                  }));

  CMD2_ANY_L("view.list",
             [](const auto&, const auto&) { return apply_view_list(); });
  CMD2_ANY_LIST("view.set", [](const auto&, const auto& args) {
    return apply_view_set(args);
  });

  CMD2_ANY_LIST("view.filter", [](const auto&, const auto& args) {
    return apply_view_event(&core::ViewManager::set_filter, args);
  });
  CMD2_ANY_LIST("view.filter_on", [](const auto&, const auto& args) {
    return apply_view_filter_on(args);
  });
  CMD2_ANY_LIST("view.filter.temp", [](const auto&, const auto& args) {
    return apply_view_event(&core::ViewManager::set_filter_temp, args);
  });
  CMD2_VAR_STRING("view.filter.temp.excluded", "default,started,stopped");
  CMD2_VAR_BOOL("view.filter.temp.log", 0);

  CMD2_ANY_LIST("view.sort", [](const auto&, const auto& args) {
    return apply_view_sort(args);
  });
  CMD2_ANY_LIST("view.sort_new", [](const auto&, const auto& args) {
    return apply_view_event(&core::ViewManager::set_sort_new, args);
  });
  CMD2_ANY_LIST("view.sort_current", [](const auto&, const auto& args) {
    return apply_view_event(&core::ViewManager::set_sort_current, args);
  });

  CMD2_ANY_LIST("view.event_added", [](const auto&, const auto& args) {
    return apply_view_event(&core::ViewManager::set_event_added, args);
  });
  CMD2_ANY_LIST("view.event_removed", [](const auto&, const auto& args) {
    return apply_view_event(&core::ViewManager::set_event_removed, args);
  });

  // Cleanup and add . to view.

  CMD2_ANY_STRING("view.size", [](const auto&, const auto& args) {
    return cmd_view_size(args);
  });
  CMD2_ANY_STRING("view.size_not_visible", [](const auto&, const auto& args) {
    return cmd_view_size_not_visible(args);
  });
  CMD2_ANY_STRING("view.persistent", [](const auto&, const auto& args) {
    return cmd_view_persistent(args);
  });

  CMD2_ANY_STRING_V("view.filter_all", [](const auto&, const auto& args) {
    control->view_manager()->find_ptr_throw(args)->filter();
  });

  CMD2_DL_STRING("view.filter_download",
                 [](const auto& download, const auto& args) {
                   return cmd_view_filter_download(download, args);
                 });
  CMD2_DL_STRING("view.set_visible",
                 [](const auto& download, const auto& args) {
                   return cmd_view_set_visible(download, args);
                 });
  CMD2_DL_STRING("view.set_not_visible",
                 [](const auto& download, const auto& args) {
                   return cmd_view_set_not_visible(download, args);
                 });

  // Commands that affect the default rtorrent UI.
  CMD2_DL("ui.unfocus_download", [](const auto& download, const auto&) {
    return cmd_ui_unfocus_download(download);
  });
  CMD2_ANY("ui.current_view",
           [](const auto&, const auto&) { return cmd_ui_current_view(); });
  CMD2_ANY_STRING("ui.current_view.set", [](const auto&, const auto& args) {
    return cmd_ui_set_view(args);
  });

  CMD2_ANY("ui.input.history.size", [](const auto&, const auto&) {
    return control->ui()->get_input_history_size();
  });
  CMD2_ANY_VALUE_V("ui.input.history.size.set",
                   [](const auto&, const auto& size) {
                     return control->ui()->set_input_history_size(size);
                   });
  CMD2_ANY_V("ui.input.history.clear", [](const auto&, const auto&) {
    return control->ui()->clear_input_history();
  });

  CMD2_VAR_VALUE("ui.throttle.global.step.small", 5);
  CMD2_VAR_VALUE("ui.throttle.global.step.medium", 50);
  CMD2_VAR_VALUE("ui.throttle.global.step.large", 500);

  CMD2_ANY_LIST("ui.status.throttle.up.set", [](const auto&, const auto& args) {
    return cmd_status_throttle_names(true, args);
  });
  CMD2_ANY_LIST("ui.status.throttle.down.set",
                [](const auto&, const auto& args) {
                  return cmd_status_throttle_names(false, args);
                });

  // TODO: Add 'option_string' for rtorrent-specific options.
  CMD2_VAR_STRING("ui.torrent_list.layout", "full");

  CMD2_ANY("print", &apply_print);
}
