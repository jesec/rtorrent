noinst_LIBRARIES = libsub_root.a
bin_PROGRAMS = rtorrent

rtorrent_LDADD = libsub_root.a @PTHREAD_LIBS@
rtorrent_SOURCES = main.cc

libsub_root_a_SOURCES = \
	core/curl_get.cc \
	core/curl_socket.cc \
	core/curl_stack.cc \
	core/dht_manager.cc \
	core/download.cc \
	core/download_factory.cc \
	core/download_list.cc \
	core/download_store.cc \
	core/http_queue.cc \
	core/manager.cc \
	core/poll_manager.cc \
	core/view.cc \
	core/view_manager.cc \
	\
	display/canvas.cc \
	display/frame.cc \
	display/manager.cc \
	display/utils.cc \
	display/text_element_list.cc \
	display/text_element_string.cc \
	display/text_element_value.cc \
	display/window.cc \
	display/window_download_chunks_seen.cc \
	display/window_download_list.cc \
	display/window_download_statusbar.cc \
	display/window_download_transfer_list.cc \
	display/window_file_list.cc \
	display/window_http_queue.cc \
	display/window_input.cc \
	display/window_log.cc \
	display/window_log_complete.cc \
	display/window_peer_list.cc \
	display/window_statusbar.cc \
	display/window_string_list.cc \
	display/window_text.cc \
	display/window_title.cc \
	display/window_tracker_list.cc \
	\
	input/bindings.cc \
	input/input_event.cc \
	input/manager.cc \
	input/path_input.cc \
	input/text_input.cc \
	\
	rpc/command.cc \
	rpc/command_map.cc \
	rpc/command_scheduler.cc \
	rpc/command_scheduler_item.cc \
	rpc/exec_file.cc \
	rpc/object_storage.cc \
	rpc/parse.cc \
	rpc/parse_commands.cc \
	rpc/parse_options.cc \
	rpc/scgi.cc \
	rpc/scgi_task.cc \
	rpc/xmlrpc.cc \
	\
	ui/download.cc \
	ui/download_list.cc \
	ui/element_base.cc \
	ui/element_chunks_seen.cc \
	ui/element_download_list.cc \
	ui/element_file_list.cc \
	ui/element_log_complete.cc \
	ui/element_menu.cc \
	ui/element_peer_list.cc \
	ui/element_string_list.cc \
	ui/element_text.cc \
	ui/element_tracker_list.cc \
	ui/element_transfer_list.cc \
	ui/root.cc \
	\
	utils/directory.cc \
	utils/file_status_cache.cc \
	utils/lockfile.cc \
	utils/socket_fd.cc \
	\
	command_download.cc \
	command_dynamic.cc \
	command_events.cc \
	command_file.cc \
	command_ip.cc \
	command_helpers.cc \
	command_groups.cc \
	command_local.cc \
	command_logging.cc \
	command_network.cc \
	command_peer.cc \
	command_throttle.cc \
	command_tracker.cc \
	command_scheduler.cc \
	command_ui.cc \
	control.cc \
	globals.cc \
	option_parser.cc \
	signal_handler.cc \
	thread_base.cc \
	thread_worker.cc

AM_CPPFLAGS = -I$(top_srcdir)/include
