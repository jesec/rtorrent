AC_DEFUN([TORRENT_WITH_XMLRPC_C], [
  AC_MSG_CHECKING(for XMLRPC-C)

  AC_ARG_WITH(xmlrpc-c,
    AC_HELP_STRING([--with-xmlrpc-c=PATH], [enable XMLRPC-C support]),
  [
    if test "$withval" = "no"; then
      AC_MSG_RESULT(no)

    else
      if test "$withval" = "yes"; then
        xmlrpc_cc_prg="xmlrpc-c-config"
      else
        xmlrpc_cc_prg="$withval"
      fi
      
      if eval $xmlrpc_cc_prg --version 2>/dev/null >/dev/null; then
        CXXFLAGS="$CXXFLAGS `$xmlrpc_cc_prg --cflags server-util`"
        LIBS="$LIBS `$xmlrpc_cc_prg server-util --libs`"

        AC_TRY_LINK(
        [ #include <xmlrpc-c/server.h>
        ],[ xmlrpc_registry_new(NULL); ],
        [
          AC_MSG_RESULT(ok)
        ], [
          AC_MSG_RESULT(failed)
          AC_MSG_ERROR(Could not compile XMLRPC-C test.)
        ])

        AC_DEFINE(HAVE_XMLRPC_C, 1, Support for XMLRPC-C.)

      else
        AC_MSG_RESULT(failed)
        AC_MSG_ERROR(Could not compile XMLRPC-C test.)
      fi
    fi

  ],[
    AC_MSG_RESULT(ignored)
  ])
])
