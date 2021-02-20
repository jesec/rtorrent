// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_SIGNAL_HANDLER_H
#define RTORRENT_SIGNAL_HANDLER_H

#include <functional>
#include <signal.h>

class SignalHandler {
public:
  using slot_void = std::function<void()>;

  // typedef void (*handler_slot)(int, siginfo_t *info, ucontext_t *uap);
  using handler_slot = void (*)(int, siginfo_t*, void*);

#ifdef NSIG
  static constexpr unsigned int HIGHEST_SIGNAL = NSIG;
#else
  // Let's be on the safe side.
  static constexpr unsigned int HIGHEST_SIGNAL = 32;
#endif

  static void set_default(unsigned int signum);
  static void set_ignore(unsigned int signum);
  static void set_handler(unsigned int signum, slot_void slot);

  static void set_sigaction_handler(unsigned int signum, handler_slot slot);

  static const char* as_string(unsigned int signum);

private:
  static void caught(int signum);

  static slot_void m_handlers[HIGHEST_SIGNAL];
};

#endif
