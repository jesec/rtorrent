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
            std::bind(&torrent::File::is_created, std::placeholders::_1));
  CMD2_FILE("f.is_open",
            std::bind(&torrent::File::is_open, std::placeholders::_1));

  CMD2_FILE("f.is_create_queued",
            std::bind(&torrent::File::is_create_queued, std::placeholders::_1));
  CMD2_FILE("f.is_resize_queued",
            std::bind(&torrent::File::is_resize_queued, std::placeholders::_1));

  CMD2_FILE_VALUE_V("f.set_create_queued",
                    std::bind(&torrent::File::set_flags,
                              std::placeholders::_1,
                              torrent::File::flag_create_queued));
  CMD2_FILE_VALUE_V("f.set_resize_queued",
                    std::bind(&torrent::File::set_flags,
                              std::placeholders::_1,
                              torrent::File::flag_resize_queued));
  CMD2_FILE_VALUE_V("f.unset_create_queued",
                    std::bind(&torrent::File::unset_flags,
                              std::placeholders::_1,
                              torrent::File::flag_create_queued));
  CMD2_FILE_VALUE_V("f.unset_resize_queued",
                    std::bind(&torrent::File::unset_flags,
                              std::placeholders::_1,
                              torrent::File::flag_resize_queued));

  CMD2_FILE("f.prioritize_first",
            std::bind(&torrent::File::has_flags,
                      std::placeholders::_1,
                      torrent::File::flag_prioritize_first));
  CMD2_FILE_V("f.prioritize_first.enable",
              std::bind(&torrent::File::set_flags,
                        std::placeholders::_1,
                        torrent::File::flag_prioritize_first));
  CMD2_FILE_V("f.prioritize_first.disable",
              std::bind(&torrent::File::unset_flags,
                        std::placeholders::_1,
                        torrent::File::flag_prioritize_first));
  CMD2_FILE("f.prioritize_last",
            std::bind(&torrent::File::has_flags,
                      std::placeholders::_1,
                      torrent::File::flag_prioritize_last));
  CMD2_FILE_V("f.prioritize_last.enable",
              std::bind(&torrent::File::set_flags,
                        std::placeholders::_1,
                        torrent::File::flag_prioritize_last));
  CMD2_FILE_V("f.prioritize_last.disable",
              std::bind(&torrent::File::unset_flags,
                        std::placeholders::_1,
                        torrent::File::flag_prioritize_last));

  CMD2_FILE("f.size_bytes",
            std::bind(&torrent::File::size_bytes, std::placeholders::_1));
  CMD2_FILE("f.size_chunks",
            std::bind(&torrent::File::size_chunks, std::placeholders::_1));
  CMD2_FILE("f.completed_chunks",
            std::bind(&torrent::File::completed_chunks, std::placeholders::_1));

  CMD2_FILE("f.offset",
            std::bind(&torrent::File::offset, std::placeholders::_1));
  CMD2_FILE("f.range_first",
            std::bind(&torrent::File::range_first, std::placeholders::_1));
  CMD2_FILE("f.range_second",
            std::bind(&torrent::File::range_second, std::placeholders::_1));

  CMD2_FILE("f.priority",
            std::bind(&torrent::File::priority, std::placeholders::_1));
  CMD2_FILE_VALUE_V("f.priority.set",
                    std::bind(&apply_f_set_priority,
                              std::placeholders::_1,
                              std::placeholders::_2));

  CMD2_FILE("f.path", std::bind(&apply_f_path, std::placeholders::_1));
  CMD2_FILE("f.path_components",
            std::bind(&apply_f_path_components, std::placeholders::_1));
  CMD2_FILE("f.path_depth",
            std::bind(&apply_f_path_depth, std::placeholders::_1));
  CMD2_FILE("f.frozen_path",
            std::bind(&torrent::File::frozen_path, std::placeholders::_1));

  CMD2_FILE("f.match_depth_prev",
            std::bind(&torrent::File::match_depth_prev, std::placeholders::_1));
  CMD2_FILE("f.match_depth_next",
            std::bind(&torrent::File::match_depth_next, std::placeholders::_1));

  CMD2_FILE("f.last_touched",
            std::bind(&torrent::File::last_touched, std::placeholders::_1));

  CMD2_FILEITR("fi.filename_last",
               std::bind(&apply_fi_filename_last, std::placeholders::_1));
  CMD2_FILEITR(
    "fi.is_file",
    std::bind(&torrent::FileListIterator::is_file, std::placeholders::_1));
}
