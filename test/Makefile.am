TESTS = rtorrentTest

check_PROGRAMS = $(TESTS)
rtorrentTest_LDADD = ../src/libsub_root.a

rtorrentTest_SOURCES = \
	rpc/command_test.cc \
	rpc/command_map_test.cc \
	rpc/command_slot_test.cc \
	rpc/object_storage_test.cc \
	rpc/test_parse_options.cc \
	src/command_dynamic_test.cc \
	main.cc

rtorrentTest_CXXFLAGS = $(CPPUNIT_CFLAGS)
rtorrentTest_LDFLAGS = $(CPPUNIT_LIBS)  -ldl

AM_CPPFLAGS = -I$(top_srcdir)/include
