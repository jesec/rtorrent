// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <torrent/data/file.h>
#include <torrent/data/file_list.h>
#include <torrent/data/file_list_iterator.h>
#include <torrent/utils/error_number.h>
#include <torrent/utils/path.h>

#include "core/manager.h"

#include "command_helpers.h"
#include "control.h"
#include "globals.h"

void
apply_f_set_priority(torrent::File* file, uint32_t value) {
  if (value > torrent::PRIORITY_HIGH)
    throw torrent::input_error("Invalid value.");

  file->set_priority((torrent::priority_t)value);
}

// TODO: Redundant.
torrent::Object
apply_f_path(torrent::File* file) {
  if (file->path()->empty())
    return std::string();

  torrent::Object               resultRaw(*file->path()->begin());
  torrent::Object::string_type& result = resultRaw.as_string();

  for (torrent::Path::const_iterator itr  = ++file->path()->begin(),
                                     last = file->path()->end();
       itr != last;
       itr++)
    result += '/' + *itr;

  return resultRaw;
}

torrent::Object
apply_f_path_components(torrent::File* file) {
  torrent::Object             resultRaw = torrent::Object::create_list();
  torrent::Object::list_type& result    = resultRaw.as_list();

  for (torrent::Path::const_iterator itr  = file->path()->begin(),
                                     last = file->path()->end();
       itr != last;
       itr++)
    result.push_back(*itr);

  return resultRaw;
}

torrent::Object
apply_f_path_depth(torrent::File* file) {
  return (int64_t)file->path()->size();
}

torrent::Object
apply_fi_filename_last(torrent::FileListIterator* itr) {
  if (itr->file()->path()->empty())
    return "EMPTY";

  if (itr->depth() >= itr->file()->path()->size())
    return "ERROR";

  return itr->file()->path()->at(itr->depth());
}

void
initialize_command_file() {
  CMD2_FILE("f.is_created",
            [](const auto& file, const auto&) { return file->is_created(); });
  CMD2_FILE("f.is_open",
            [](const auto& file, const auto&) { return file->is_open(); });

  CMD2_FILE("f.is_create_queued", [](const auto& file, const auto&) {
    return file->is_create_queued();
  });
  CMD2_FILE("f.is_resize_queued", [](const auto& file, const auto&) {
    return file->is_resize_queued();
  });

  CMD2_FILE_VALUE_V("f.set_create_queued", [](const auto& file, const auto&) {
    return file->set_flags(torrent::File::flag_create_queued);
  });
  CMD2_FILE_VALUE_V("f.set_resize_queued", [](const auto& file, const auto&) {
    return file->set_flags(torrent::File::flag_resize_queued);
  });
  CMD2_FILE_VALUE_V("f.unset_create_queued", [](const auto& file, const auto&) {
    return file->unset_flags(torrent::File::flag_create_queued);
  });
  CMD2_FILE_VALUE_V("f.unset_resize_queued", [](const auto& file, const auto&) {
    return file->unset_flags(torrent::File::flag_resize_queued);
  });

  CMD2_FILE("f.prioritize_first", [](const auto& file, const auto&) {
    return file->has_flags(torrent::File::flag_prioritize_first);
  });
  CMD2_FILE_V("f.prioritize_first.enable", [](const auto& file, const auto&) {
    return file->set_flags(torrent::File::flag_prioritize_first);
  });
  CMD2_FILE_V("f.prioritize_first.disable", [](const auto& file, const auto&) {
    return file->unset_flags(torrent::File::flag_prioritize_first);
  });
  CMD2_FILE("f.prioritize_last", [](const auto& file, const auto&) {
    return file->has_flags(torrent::File::flag_prioritize_last);
  });
  CMD2_FILE_V("f.prioritize_last.enable", [](const auto& file, const auto&) {
    return file->set_flags(torrent::File::flag_prioritize_last);
  });
  CMD2_FILE_V("f.prioritize_last.disable", [](const auto& file, const auto&) {
    return file->unset_flags(torrent::File::flag_prioritize_last);
  });

  CMD2_FILE("f.size_bytes",
            [](const auto& file, const auto&) { return file->size_bytes(); });
  CMD2_FILE("f.size_chunks",
            [](const auto& file, const auto&) { return file->size_chunks(); });
  CMD2_FILE("f.completed_chunks", [](const auto& file, const auto&) {
    return file->completed_chunks();
  });

  CMD2_FILE("f.offset",
            [](const auto& file, const auto&) { return file->offset(); });
  CMD2_FILE("f.range_first",
            [](const auto& file, const auto&) { return file->range_first(); });
  CMD2_FILE("f.range_second",
            [](const auto& file, const auto&) { return file->range_second(); });

  CMD2_FILE("f.priority",
            [](const auto& file, const auto&) { return file->priority(); });
  CMD2_FILE_VALUE_V("f.priority.set", [](const auto& file, const auto& v) {
    return apply_f_set_priority(file, v);
  });

  CMD2_FILE("f.path",
            [](const auto& file, const auto&) { return apply_f_path(file); });
  CMD2_FILE("f.path_components", [](const auto& file, const auto&) {
    return apply_f_path_components(file);
  });
  CMD2_FILE("f.path_depth", [](const auto& file, const auto&) {
    return apply_f_path_depth(file);
  });
  CMD2_FILE("f.frozen_path",
            [](const auto& file, const auto&) { return file->frozen_path(); });

  CMD2_FILE("f.match_depth_prev", [](const auto& file, const auto&) {
    return file->match_depth_prev();
  });
  CMD2_FILE("f.match_depth_next", [](const auto& file, const auto&) {
    return file->match_depth_next();
  });

  CMD2_FILE("f.last_touched",
            [](const auto& file, const auto&) { return file->last_touched(); });

  CMD2_FILEITR("fi.filename_last", [](const auto& file, const auto&) {
    return apply_fi_filename_last(file);
  });
  CMD2_FILEITR("fi.is_file",
               [](const auto& file, const auto&) { return file->is_file(); });
}
