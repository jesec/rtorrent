// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <torrent/exceptions.h>
#include <torrent/hash_string.h>
#include <torrent/peer/connection_list.h>
#include <torrent/peer/peer_info.h>
#include <torrent/rate.h>

#include "control.h"
#include "display/frame.h"
#include "display/manager.h"
#include "display/text_element_string.h"
#include "display/utils.h"
#include "display/window_peer_list.h"
#include "input/manager.h"
#include "ui/element_text.h"

#include "ui/element_peer_list.h"

namespace ui {

ElementPeerList::ElementPeerList(core::Download* d)
  : m_download(d)
  , m_state(DISPLAY_MAX_SIZE) {

  m_listItr = m_list.end();

  for (const auto& peer : *m_download->download()->connection_list()) {
    m_list.push_back(peer);
  }

  torrent::ConnectionList* connection_list =
    m_download->download()->connection_list();

  m_peer_connected = connection_list->signal_connected().insert(
    connection_list->signal_connected().end(),
    std::bind(
      &ElementPeerList::receive_peer_connected, this, std::placeholders::_1));
  m_peer_disconnected = connection_list->signal_disconnected().insert(
    connection_list->signal_disconnected().end(),
    std::bind(&ElementPeerList::receive_peer_disconnected,
              this,
              std::placeholders::_1));

  m_windowList  = new display::WindowPeerList(m_download, &m_list, &m_listItr);
  m_elementInfo = create_info();

  m_elementInfo->slot_exit(
    std::bind(&ElementPeerList::activate_display, this, DISPLAY_LIST));

  m_bindings['k'] = std::bind(&ElementPeerList::receive_disconnect_peer, this);
  m_bindings['*'] = std::bind(&ElementPeerList::receive_snub_peer, this);
  m_bindings['B'] = std::bind(&ElementPeerList::receive_ban_peer, this);
  m_bindings[KEY_LEFT] = m_bindings['B' - '@'] =
    std::bind(&slot_type::operator(), &m_slot_exit);
  m_bindings[KEY_RIGHT] = m_bindings['F' - '@'] =
    std::bind(&ElementPeerList::activate_display, this, DISPLAY_INFO);

  m_bindings[KEY_UP] = m_bindings['P' - '@'] =
    std::bind(&ElementPeerList::receive_prev, this);
  m_bindings[KEY_DOWN] = m_bindings['N' - '@'] =
    std::bind(&ElementPeerList::receive_next, this);
}

ElementPeerList::~ElementPeerList() {
  torrent::ConnectionList* connection_list =
    m_download->download()->connection_list();

  connection_list->signal_connected().erase(m_peer_connected);
  connection_list->signal_disconnected().erase(m_peer_disconnected);

  delete m_windowList;
  delete m_elementInfo;
}

inline ElementText*
ElementPeerList::create_info() {
  using namespace display::helpers;

  ElementText* element = new ElementText(rpc::make_target());

  element->set_column(1);
  element->set_interval(1);

  element->push_back("Peer info:");

  element->push_back("");
  element->push_column("Address:", te_command("cat=$p.address=,:,$p.port="));
  element->push_column("Id:", te_command("p.id_html="));
  element->push_column("Client:", te_command("p.client_version="));
  element->push_column("Options:", te_command("p.options_str="));
  element->push_column("Connected:",
                       te_command("if=$p.is_incoming=,incoming,outgoing"));
  element->push_column(
    "Encrypted:",
    te_command("if=$p.is_encrypted=,yes,$p.is_obfuscated=,handshake,no"));

  element->push_back("");
  element->push_column("Snubbed:", te_command("if=$p.is_snubbed=,yes,no"));
  element->push_column("Done:", te_command("p.completed_percent="));
  element->push_column(
    "Rate:",
    te_command("cat=$convert.xb=$p.up_rate=,\\ ,$convert.xb=$p.down_rate="));
  element->push_column(
    "Total:",
    te_command("cat=$convert.xb=$p.up_total=,\\ ,$convert.xb=$p.down_total="));

  element->set_column_width(element->column_width() + 1);
  element->set_error_handler(
    new display::TextElementCString("No peer selected."));

  return element;
}

void
ElementPeerList::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error(
      "ui::ElementPeerList::activate(...) is_active().");

  if (focus)
    control->input()->push_back(&m_bindings);

  m_frame = frame;
  m_focus = focus;

  activate_display(DISPLAY_LIST);
}

void
ElementPeerList::disable() {
  if (!is_active())
    throw torrent::internal_error(
      "ui::ElementPeerList::disable(...) !is_active().");

  control->input()->erase(&m_bindings);

  activate_display(DISPLAY_MAX_SIZE);

  m_frame->clear();
  m_frame = nullptr;
}

void
ElementPeerList::activate_display(Display display) {
  if (display == m_state)
    return;

  switch (m_state) {
    case DISPLAY_INFO:
      m_elementInfo->disable();
      break;

    case DISPLAY_LIST:
      m_windowList->set_active(false);
      m_frame->clear();
      break;

    case DISPLAY_MAX_SIZE:
      break;
  }

  m_state = display;

  switch (m_state) {
    case DISPLAY_INFO:
      m_elementInfo->activate(m_frame, true);
      break;

    case DISPLAY_LIST:
      m_windowList->set_active(true);
      m_frame->initialize_window(m_windowList);
      break;

    case DISPLAY_MAX_SIZE:
      break;
  }

  control->display()->adjust_layout();
}

void
ElementPeerList::receive_next() {
  if (m_listItr != m_list.end())
    ++m_listItr;
  else
    m_listItr = m_list.begin();

  update_itr();
}

void
ElementPeerList::receive_prev() {
  if (m_listItr != m_list.begin())
    --m_listItr;
  else
    m_listItr = m_list.end();

  update_itr();
}

void
ElementPeerList::receive_disconnect_peer() {
  if (m_listItr == m_list.end())
    return;

  m_download->connection_list()->erase(*m_listItr, 0);
}

void
ElementPeerList::receive_peer_connected(torrent::Peer* p) {
  m_list.push_back(p);
}

void
ElementPeerList::receive_peer_disconnected(torrent::Peer* p) {
  PList::iterator itr = std::find(m_list.begin(), m_list.end(), p);

  if (itr == m_list.end())
    throw torrent::internal_error(
      "ElementPeerList::receive_peer_disconnected(...) itr == m_list.end().");

  if (itr == m_listItr)
    m_listItr = m_list.erase(itr);
  else
    m_list.erase(itr);

  update_itr();
}

void
ElementPeerList::receive_snub_peer() {
  if (m_listItr == m_list.end())
    return;

  (*m_listItr)->set_snubbed(!(*m_listItr)->is_snubbed());

  update_itr();
}

void
ElementPeerList::receive_ban_peer() {
  if (m_listItr == m_list.end())
    return;

  (*m_listItr)->set_banned(true);
  m_download->download()->connection_list()->erase(
    *m_listItr, torrent::ConnectionList::disconnect_quick);

  update_itr();
}

void
ElementPeerList::update_itr() {
  m_windowList->mark_dirty();
  m_elementInfo->set_target(m_listItr != m_list.end()
                              ? rpc::make_target(*m_listItr)
                              : rpc::make_target());
}

}
