// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_RPC_COMMAND_IMPL_H
#define RTORRENT_RPC_COMMAND_IMPL_H

namespace rpc {

// template <> struct target_type_id<command_base::generic_slot>       { static
// constexpr int value = command_base::target_generic; };
template<>
struct target_type_id<command_base::cleaned_slot> {
  static constexpr int value = command_base::target_generic;
};
template<>
struct target_type_id<command_base::any_slot> {
  static constexpr int value = command_base::target_any;
};
template<>
struct target_type_id<command_base::download_slot> {
  static constexpr int value = command_base::target_download;
};
template<>
struct target_type_id<command_base::peer_slot> {
  static constexpr int value = command_base::target_peer;
};
template<>
struct target_type_id<command_base::tracker_slot> {
  static constexpr int value = command_base::target_tracker;
};
template<>
struct target_type_id<command_base::file_slot> {
  static constexpr int value = command_base::target_file;
};
template<>
struct target_type_id<command_base::file_itr_slot> {
  static constexpr int value = command_base::target_file_itr;
};

template<>
struct target_type_id<command_base::download_pair_slot> {
  static constexpr int value = command_base::target_download_pair;
};

template<>
struct target_type_id<> {
  static constexpr int value = command_base::target_generic;
};
template<>
struct target_type_id<target_type> {
  static constexpr int value       = command_base::target_any;
  static constexpr int proper_type = 1;
};
template<>
struct target_type_id<core::Download*> {
  static constexpr int value       = command_base::target_download;
  static constexpr int proper_type = 1;
};
template<>
struct target_type_id<torrent::Peer*> {
  static constexpr int value       = command_base::target_peer;
  static constexpr int proper_type = 1;
};
template<>
struct target_type_id<torrent::Tracker*> {
  static constexpr int value       = command_base::target_tracker;
  static constexpr int proper_type = 1;
};
template<>
struct target_type_id<torrent::File*> {
  static constexpr int value       = command_base::target_file;
  static constexpr int proper_type = 1;
};
template<>
struct target_type_id<torrent::FileListIterator*> {
  static constexpr int value       = command_base::target_file_itr;
  static constexpr int proper_type = 1;
};

template<>
struct target_type_id<core::Download*, core::Download*> {
  static constexpr int value = command_base::target_download_pair;
};

template<>
inline bool
is_target_compatible<target_type>(const target_type&) {
  return true;
}
template<>
inline bool
is_target_compatible<torrent::File*>(const target_type& target) {
  return std::get<0>(target) == command_base::target_file ||
         command_base::target_file_itr;
}

template<>
inline target_type
get_target_cast<target_type>(target_type target, int) {
  return target;
}

template<>
inline torrent::File*
get_target_cast<torrent::File*>(target_type target, int) {
  if (std::get<0>(target) == command_base::target_file_itr)
    return static_cast<torrent::FileListIterator*>(std::get<1>(target))->file();
  else
    return static_cast<torrent::File*>(std::get<1>(target));
}

inline torrent::Object*
command_base::push_stack(const torrent::Object* first_arg,
                         const torrent::Object* last_arg,
                         stack_type*            stack) {
  unsigned int idx = 0;

  while (first_arg != last_arg && idx < command_base::max_arguments) {
    new (&(*stack)[idx]) torrent::Object(*first_arg++);
    (*stack)[idx].swap(*command_base::argument(idx));

    idx++;
  }

  return stack->begin() + idx;
}

inline torrent::Object*
command_base::push_stack(const torrent::Object::list_type& args,
                         stack_type*                       stack) {
  return push_stack(args.data(), args.data() + args.size(), stack);
}

inline void
command_base::pop_stack(stack_type* stack, torrent::Object* last_stack) {
  while (last_stack-- != stack->begin()) {
    last_stack->swap(
      *command_base::argument(std::distance(stack->begin(), last_stack)));
    last_stack->~Object();

    // To ensure we catch errors:
    std::memset(static_cast<void*>(last_stack), 0xAA, sizeof(torrent::Object));
  }
}

}

#endif
