# Copied from https://github.com/dropbox/dbx_build_tools/blob/master/thirdparty/ncurses/BUILD.ncurses
# ncurses is a real pain-in-the-neck to build in Bazel. Its uses a lot
# of ah-hoc generated code. We cheat here by using it native build system to
# generate that code then simply checking the generated artifacts as genrules.
# See generate.sh in this directory for how to recreate those files.

load("@rules_cc//cc:defs.bzl", "cc_library")

NCURSES_COPTS = [
    "-I",
    "external/ncurses/ncurses",
    "-I",
    "$(GENDIR)/external/ncurses/ncurses",
    "-I",
    "external/ncurses/include",
    "-I",
    "$(GENDIR)/external/ncurses/include",
    "-DNDEBUG",
    "-D_GNU_SOURCE",
    "-D_DEFAULT_SOURCE",
]

# This list was generated using convert_modules.py.
NCURSES_SRCS = [
    "ncurses/tty/hardscroll.c",
    "ncurses/tty/hashmap.c",
    "ncurses/base/lib_addch.c",
    "ncurses/base/lib_addstr.c",
    "ncurses/base/lib_beep.c",
    "ncurses/base/lib_bkgd.c",
    "ncurses/base/lib_box.c",
    "ncurses/base/lib_chgat.c",
    "ncurses/base/lib_clear.c",
    "ncurses/base/lib_clearok.c",
    "ncurses/base/lib_clrbot.c",
    "ncurses/base/lib_clreol.c",
    "ncurses/base/lib_color.c",
    "ncurses/base/lib_colorset.c",
    "ncurses/base/lib_delch.c",
    "ncurses/base/lib_delwin.c",
    "ncurses/base/lib_echo.c",
    "ncurses/base/lib_endwin.c",
    "ncurses/base/lib_erase.c",
    "ncurses/base/lib_flash.c",
    "ncurses/lib_gen.c",
    "ncurses/base/lib_getch.c",
    "ncurses/base/lib_getstr.c",
    "ncurses/base/lib_hline.c",
    "ncurses/base/lib_immedok.c",
    "ncurses/base/lib_inchstr.c",
    "ncurses/base/lib_initscr.c",
    "ncurses/base/lib_insch.c",
    "ncurses/base/lib_insdel.c",
    "ncurses/base/lib_insnstr.c",
    "ncurses/base/lib_instr.c",
    "ncurses/base/lib_isendwin.c",
    "ncurses/base/lib_leaveok.c",
    "ncurses/base/lib_mouse.c",
    "ncurses/base/lib_move.c",
    "ncurses/tty/lib_mvcur.c",
    "ncurses/base/lib_mvwin.c",
    "ncurses/base/lib_newterm.c",
    "ncurses/base/lib_newwin.c",
    "ncurses/base/lib_nl.c",
    "ncurses/base/lib_overlay.c",
    "ncurses/base/lib_pad.c",
    "ncurses/base/lib_printw.c",
    "ncurses/base/lib_redrawln.c",
    "ncurses/base/lib_refresh.c",
    "ncurses/base/lib_restart.c",
    "ncurses/base/lib_scanw.c",
    "ncurses/base/lib_screen.c",
    "ncurses/base/lib_scroll.c",
    "ncurses/base/lib_scrollok.c",
    "ncurses/base/lib_scrreg.c",
    "ncurses/base/lib_set_term.c",
    "ncurses/base/lib_slk.c",
    "ncurses/base/lib_slkatr_set.c",
    "ncurses/base/lib_slkatrof.c",
    "ncurses/base/lib_slkatron.c",
    "ncurses/base/lib_slkatrset.c",
    "ncurses/base/lib_slkattr.c",
    "ncurses/base/lib_slkclear.c",
    "ncurses/base/lib_slkcolor.c",
    "ncurses/base/lib_slkinit.c",
    "ncurses/base/lib_slklab.c",
    "ncurses/base/lib_slkrefr.c",
    "ncurses/base/lib_slkset.c",
    "ncurses/base/lib_slktouch.c",
    "ncurses/base/lib_touch.c",
    "ncurses/trace/lib_tracedmp.c",
    "ncurses/trace/lib_tracemse.c",
    "ncurses/tty/lib_tstp.c",
    "ncurses/base/lib_ungetch.c",
    "ncurses/tty/lib_vidattr.c",
    "ncurses/base/lib_vline.c",
    "ncurses/base/lib_wattroff.c",
    "ncurses/base/lib_wattron.c",
    "ncurses/base/lib_winch.c",
    "ncurses/base/lib_window.c",
    "ncurses/base/nc_panel.c",
    "ncurses/base/safe_sprintf.c",
    "ncurses/tty/tty_update.c",
    "ncurses/trace/varargs.c",
    "ncurses/base/vsscanf.c",
    "ncurses/base/lib_freeall.c",
    "ncurses/widechar/charable.c",
    "ncurses/widechar/lib_add_wch.c",
    "ncurses/widechar/lib_box_set.c",
    "ncurses/widechar/lib_cchar.c",
    "ncurses/widechar/lib_erasewchar.c",
    "ncurses/widechar/lib_get_wch.c",
    "ncurses/widechar/lib_get_wstr.c",
    "ncurses/widechar/lib_hline_set.c",
    "ncurses/widechar/lib_in_wch.c",
    "ncurses/widechar/lib_in_wchnstr.c",
    "ncurses/widechar/lib_ins_wch.c",
    "ncurses/widechar/lib_inwstr.c",
    "ncurses/widechar/lib_key_name.c",
    "ncurses/widechar/lib_pecho_wchar.c",
    "ncurses/widechar/lib_slk_wset.c",
    "ncurses/widechar/lib_unget_wch.c",
    "ncurses/widechar/lib_vid_attr.c",
    "ncurses/widechar/lib_vline_set.c",
    "ncurses/widechar/lib_wacs.c",
    "ncurses/widechar/lib_wunctrl.c",
    "ncurses/expanded.c",
    "ncurses/base/legacy_coding.c",
    "ncurses/base/lib_dft_fgbg.c",
    "ncurses/tinfo/lib_print.c",
    "ncurses/base/new_pair.c",
    "ncurses/base/resizeterm.c",
    "ncurses/trace/trace_xnames.c",
    "ncurses/tinfo/use_screen.c",
    "ncurses/base/use_window.c",
    "ncurses/base/wresize.c",
    "ncurses/tinfo/access.c",
    "ncurses/tinfo/add_tries.c",
    "ncurses/tinfo/alloc_ttype.c",
    "ncurses/codes.c",
    "ncurses/comp_captab.c",
    "ncurses/tinfo/comp_error.c",
    "ncurses/tinfo/comp_hash.c",
    "ncurses/comp_userdefs.c",
    "ncurses/tinfo/db_iterator.c",
    "ncurses/tinfo/doalloc.c",
    "ncurses/tinfo/entries.c",
    "ncurses/fallback.c",
    "ncurses/tinfo/free_ttype.c",
    "ncurses/tinfo/getenv_num.c",
    "ncurses/tinfo/home_terminfo.c",
    "ncurses/tinfo/init_keytry.c",
    "ncurses/tinfo/lib_acs.c",
    "ncurses/tinfo/lib_baudrate.c",
    "ncurses/tinfo/lib_cur_term.c",
    "ncurses/tinfo/lib_data.c",
    "ncurses/tinfo/lib_has_cap.c",
    "ncurses/tinfo/lib_kernel.c",
    "ncurses/lib_keyname.c",
    "ncurses/tinfo/lib_longname.c",
    "ncurses/tinfo/lib_napms.c",
    "ncurses/tinfo/lib_options.c",
    "ncurses/tinfo/lib_raw.c",
    "ncurses/tinfo/lib_setup.c",
    "ncurses/tinfo/lib_termcap.c",
    "ncurses/tinfo/lib_termname.c",
    "ncurses/tinfo/lib_tgoto.c",
    "ncurses/tinfo/lib_ti.c",
    "ncurses/tinfo/lib_tparm.c",
    "ncurses/tinfo/lib_tputs.c",
    "ncurses/trace/lib_trace.c",
    "ncurses/trace/lib_traceatr.c",
    "ncurses/trace/lib_tracebits.c",
    "ncurses/trace/lib_tracechr.c",
    "ncurses/tinfo/lib_ttyflags.c",
    "ncurses/tty/lib_twait.c",
    "ncurses/tinfo/name_match.c",
    "ncurses/names.c",
    "ncurses/tinfo/obsolete.c",
    "ncurses/tinfo/read_entry.c",
    "ncurses/tinfo/read_termcap.c",
    "ncurses/tinfo/strings.c",
    "ncurses/trace/trace_buf.c",
    "ncurses/trace/trace_tries.c",
    "ncurses/base/tries.c",
    "ncurses/tinfo/trim_sgr0.c",
    "ncurses/unctrl.c",
    "ncurses/trace/visbuf.c",
    "ncurses/tinfo/alloc_entry.c",
    "ncurses/tinfo/captoinfo.c",
    "ncurses/tinfo/comp_expand.c",
    "ncurses/tinfo/comp_parse.c",
    "ncurses/tinfo/comp_scan.c",
    "ncurses/tinfo/parse_entry.c",
    "ncurses/tinfo/write_entry.c",
    "ncurses/base/define_key.c",
    "ncurses/tinfo/hashed_db.c",
    "ncurses/base/key_defined.c",
    "ncurses/base/keybound.c",
    "ncurses/base/keyok.c",
    "ncurses/base/version.c",
]

PANEL_SRCS = [
    "panel/panel.c",
    "panel/p_above.c",
    "panel/p_below.c",
    "panel/p_bottom.c",
    "panel/p_delete.c",
    "panel/p_hide.c",
    "panel/p_hidden.c",
    "panel/p_move.c",
    "panel/p_new.c",
    "panel/p_replace.c",
    "panel/p_show.c",
    "panel/p_top.c",
    "panel/p_update.c",
    "panel/p_user.c",
    "panel/p_win.c",
]

cc_library(
    name = "textual-includes",
    textual_hdrs = [
        "ncurses/tinfo/doalloc.c",
        "ncurses/names.c",
        "include/capdefaults.c",
    ],
)

cc_library(
    name = "ncursesw",
    srcs = NCURSES_SRCS + [
        "include/hashed_db.h",
        "include/hashsize.h",
        "include/nc_alloc.h",
        "include/nc_panel.h",
        "include/nc_string.h",
        "include/nc_termios.h",
        "include/ncurses_cfg.h",
        "include/ncurses_def.h",
        "include/parametrized.h",
        "ncurses/SigAction.h",
        "ncurses/build.priv.h",
        "ncurses/curses.priv.h",
        "ncurses/fifo_defs.h",
        "ncurses/init_keytry.h",
        "ncurses/new_pair.h",
    ],
    hdrs = [
        "include/curses.h",
        "include/nc_tparm.h",
        "include/ncurses.h",
        "include/ncurses_dll.h",
        "include/term.h",
        "include/term_entry.h",
        "include/termcap.h",
        "include/tic.h",
        "include/unctrl.h",
    ],
    copts = NCURSES_COPTS,
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        ":textual-includes",
    ],
)

alias(
    name = "cursesw",
    actual = ":ncursesw",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "panel",
    srcs = PANEL_SRCS + [
        "ncurses/curses.priv.h",
        "panel/panel.priv.h",
    ],
    hdrs = ["panel/panel.h"],
    copts = NCURSES_COPTS,
    strip_include_prefix = "panel",
    visibility = ["//visibility:public"],
    deps = [
        ":ncursesw",
    ],
)

genrule(
    name = "symlink-ncurses",
    srcs = [":include/curses.h"],
    outs = ["include/ncurses.h"],
    cmd = "ln -s curses.h $@",
    local = True,  # emits a symlink
)

### BEGIN GENERATED RULES

genrule(
    name = "include/curses",
    outs = ["include/curses.h"],
    cmd = r"""
cat << 'EOF' > $@
/****************************************************************************
 * Copyright 2018-2019,2020 Thomas E. Dickey                                *
 * Copyright 1998-2016,2017 Free Software Foundation, Inc.                  *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

/****************************************************************************
 *  Author: Zeyd M. Ben-Halim <zmbenhal@netcom.com> 1992,1995               *
 *     and: Eric S. Raymond <esr@snark.thyrsus.com>                         *
 *     and: Thomas E. Dickey                        1996-on                 *
 ****************************************************************************/

/* $$Id: curses.h.in,v 1.266 2020/02/08 10:51:53 tom Exp $$ */

#ifndef __NCURSES_H
#define __NCURSES_H

#define CURSES 1
#define CURSES_H 1

/* These are defined only in curses.h, and are used for conditional compiles */
#define NCURSES_VERSION_MAJOR 6
#define NCURSES_VERSION_MINOR 2
#define NCURSES_VERSION_PATCH 20200212

/* This is defined in more than one ncurses header, for identification */
#undef  NCURSES_VERSION
#define NCURSES_VERSION "6.2"

/*
 * Identify the mouse encoding version.
 */
#define NCURSES_MOUSE_VERSION 2

/*
 * Definitions to facilitate DLL's.
 */
#include <ncurses_dll.h>

#if 1
#include <stdint.h>
#endif

/*
 * User-definable tweak to disable the include of <stdbool.h>.
 */
#ifndef NCURSES_ENABLE_STDBOOL_H
#define NCURSES_ENABLE_STDBOOL_H 1
#endif

/*
 * NCURSES_ATTR_T is used to quiet compiler warnings when building ncurses
 * configured using --disable-macros.
 */
#ifndef NCURSES_ATTR_T
#define NCURSES_ATTR_T int
#endif

/*
 * Expands to 'const' if ncurses is configured using --enable-const.  Note that
 * doing so makes it incompatible with other implementations of X/Open Curses.
 */
#undef  NCURSES_CONST
#define NCURSES_CONST const

#undef NCURSES_INLINE
#define NCURSES_INLINE inline

/*
 * The standard type used for color values, and for color-pairs.  The latter
 * allows the curses library to enumerate the combinations of foreground and
 * background colors used by an application, and is normally the product of the
 * total foreground and background colors.
 *
 * X/Open uses "short" for both of these types, ultimately because they are
 * numbers from the SVr4 terminal database, which uses 16-bit signed values.
 */
#undef	NCURSES_COLOR_T
#define	NCURSES_COLOR_T short

#undef	NCURSES_PAIRS_T
#define	NCURSES_PAIRS_T short

/*
 * Definitions used to make WINDOW and similar structs opaque.
 */
#ifndef NCURSES_INTERNALS
#define NCURSES_OPAQUE       0
#define NCURSES_OPAQUE_FORM  0
#define NCURSES_OPAQUE_MENU  0
#define NCURSES_OPAQUE_PANEL 0
#endif

/*
 * Definition used to optionally suppress wattr* macros to help with the
 * transition from ncurses5 to ncurses6 by allowing the header files to
 * be shared across development packages for ncursesw in both ABIs.
 */
#ifndef NCURSES_WATTR_MACROS
#define NCURSES_WATTR_MACROS 1
#endif

/*
 * The reentrant code relies on the opaque setting, but adds features.
 */
#ifndef NCURSES_REENTRANT
#define NCURSES_REENTRANT 0
#endif

/*
 * In certain environments, we must work around linker problems for data
 */
#undef NCURSES_BROKEN_LINKER
#if 0
#define NCURSES_BROKEN_LINKER 1
#endif

/*
 * Control whether bindings for interop support are added.
 */
#undef	NCURSES_INTEROP_FUNCS
#define	NCURSES_INTEROP_FUNCS 1

/*
 * The internal type used for window dimensions.
 */
#undef	NCURSES_SIZE_T
#define	NCURSES_SIZE_T short

/*
 * Control whether tparm() supports varargs or fixed-parameter list.
 */
#undef NCURSES_TPARM_VARARGS
#define NCURSES_TPARM_VARARGS 1

/*
 * Control type used for tparm's arguments.  While X/Open equates long and
 * char* values, this is not always workable for 64-bit platforms.
 */
#undef NCURSES_TPARM_ARG
#define NCURSES_TPARM_ARG intptr_t

/*
 * Control whether ncurses uses wcwidth() for checking width of line-drawing
 * characters.
 */
#undef NCURSES_WCWIDTH_GRAPHICS
#define NCURSES_WCWIDTH_GRAPHICS 1

/*
 * NCURSES_CH_T is used in building the library, but not used otherwise in
 * this header file, since that would make the normal/wide-character versions
 * of the header incompatible.
 */
#undef	NCURSES_CH_T
#define NCURSES_CH_T cchar_t

#if 1 && defined(_LP64)
typedef unsigned chtype;
typedef unsigned mmask_t;
#else
typedef unsigned long chtype;
typedef unsigned long mmask_t;
#endif

/*
 * We need FILE, etc.  Include this before checking any feature symbols.
 */
#include <stdio.h>

/*
 * With XPG4, you must define _XOPEN_SOURCE_EXTENDED, it is redundant (or
 * conflicting) when _XOPEN_SOURCE is 500 or greater.  If NCURSES_WIDECHAR is
 * not already defined, e.g., if the platform relies upon nonstandard feature
 * test macros, define it at this point if the standard feature test macros
 * indicate that it should be defined.
 */
#ifndef NCURSES_WIDECHAR
#if defined(_XOPEN_SOURCE_EXTENDED) || (defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE - 0 >= 500))
#define NCURSES_WIDECHAR 1
#else
#define NCURSES_WIDECHAR 0
#endif
#endif /* NCURSES_WIDECHAR */

#include <stdarg.h>	/* we need va_list */
#if NCURSES_WIDECHAR
#include <stddef.h>	/* we want wchar_t */
#endif

/* X/Open and SVr4 specify that curses implements 'bool'.  However, C++ may also
 * implement it.  If so, we must use the C++ compiler's type to avoid conflict
 * with other interfaces.
 *
 * A further complication is that <stdbool.h> may declare 'bool' to be a
 * different type, such as an enum which is not necessarily compatible with
 * C++.  If we have <stdbool.h>, make 'bool' a macro, so users may #undef it.
 * Otherwise, let it remain a typedef to avoid conflicts with other #define's.
 * In either case, make a typedef for NCURSES_BOOL which can be used if needed
 * from either C or C++.
 */

#undef TRUE
#define TRUE    1

#undef FALSE
#define FALSE   0

typedef unsigned char NCURSES_BOOL;

#if defined(__cplusplus)	/* __cplusplus, etc. */

/* use the C++ compiler's bool type */
#define NCURSES_BOOL bool

#else			/* c89, c99, etc. */

#if NCURSES_ENABLE_STDBOOL_H
#include <stdbool.h>
/* use whatever the C compiler decides bool really is */
#define NCURSES_BOOL bool
#else
/* there is no predefined bool - use our own */
#undef bool
#define bool NCURSES_BOOL
#endif

#endif /* !__cplusplus, etc. */

#ifdef __cplusplus
extern "C" {
#define NCURSES_CAST(type,value) static_cast<type>(value)
#else
#define NCURSES_CAST(type,value) (type)(value)
#endif

#define NCURSES_OK_ADDR(p) (0 != NCURSES_CAST(const void *, (p)))

/*
 * X/Open attributes.  In the ncurses implementation, they are identical to the
 * A_ attributes.
 */
#define WA_ATTRIBUTES	A_ATTRIBUTES
#define WA_NORMAL	A_NORMAL
#define WA_STANDOUT	A_STANDOUT
#define WA_UNDERLINE	A_UNDERLINE
#define WA_REVERSE	A_REVERSE
#define WA_BLINK	A_BLINK
#define WA_DIM		A_DIM
#define WA_BOLD		A_BOLD
#define WA_ALTCHARSET	A_ALTCHARSET
#define WA_INVIS	A_INVIS
#define WA_PROTECT	A_PROTECT
#define WA_HORIZONTAL	A_HORIZONTAL
#define WA_LEFT		A_LEFT
#define WA_LOW		A_LOW
#define WA_RIGHT	A_RIGHT
#define WA_TOP		A_TOP
#define WA_VERTICAL	A_VERTICAL

#if 1
#define WA_ITALIC	A_ITALIC	/* ncurses extension */
#endif

/* colors */
#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7

/* line graphics */

#if 0 || NCURSES_REENTRANT
NCURSES_WRAPPED_VAR(chtype*, acs_map);
#define acs_map NCURSES_PUBLIC_VAR(acs_map())
#else
extern NCURSES_EXPORT_VAR(chtype) acs_map[];
#endif

#define NCURSES_ACS(c)	(acs_map[NCURSES_CAST(unsigned char,(c))])

/* VT100 symbols begin here */
#define ACS_ULCORNER	NCURSES_ACS('l') /* upper left corner */
#define ACS_LLCORNER	NCURSES_ACS('m') /* lower left corner */
#define ACS_URCORNER	NCURSES_ACS('k') /* upper right corner */
#define ACS_LRCORNER	NCURSES_ACS('j') /* lower right corner */
#define ACS_LTEE	NCURSES_ACS('t') /* tee pointing right */
#define ACS_RTEE	NCURSES_ACS('u') /* tee pointing left */
#define ACS_BTEE	NCURSES_ACS('v') /* tee pointing up */
#define ACS_TTEE	NCURSES_ACS('w') /* tee pointing down */
#define ACS_HLINE	NCURSES_ACS('q') /* horizontal line */
#define ACS_VLINE	NCURSES_ACS('x') /* vertical line */
#define ACS_PLUS	NCURSES_ACS('n') /* large plus or crossover */
#define ACS_S1		NCURSES_ACS('o') /* scan line 1 */
#define ACS_S9		NCURSES_ACS('s') /* scan line 9 */
#define ACS_DIAMOND	NCURSES_ACS('`') /* diamond */
#define ACS_CKBOARD	NCURSES_ACS('a') /* checker board (stipple) */
#define ACS_DEGREE	NCURSES_ACS('f') /* degree symbol */
#define ACS_PLMINUS	NCURSES_ACS('g') /* plus/minus */
#define ACS_BULLET	NCURSES_ACS('~') /* bullet */
/* Teletype 5410v1 symbols begin here */
#define ACS_LARROW	NCURSES_ACS(',') /* arrow pointing left */
#define ACS_RARROW	NCURSES_ACS('+') /* arrow pointing right */
#define ACS_DARROW	NCURSES_ACS('.') /* arrow pointing down */
#define ACS_UARROW	NCURSES_ACS('-') /* arrow pointing up */
#define ACS_BOARD	NCURSES_ACS('h') /* board of squares */
#define ACS_LANTERN	NCURSES_ACS('i') /* lantern symbol */
#define ACS_BLOCK	NCURSES_ACS('0') /* solid square block */
/*
 * These aren't documented, but a lot of System Vs have them anyway
 * (you can spot pprryyzz{{||}} in a lot of AT&T terminfo strings).
 * The ACS_names may not match AT&T's, our source didn't know them.
 */
#define ACS_S3		NCURSES_ACS('p') /* scan line 3 */
#define ACS_S7		NCURSES_ACS('r') /* scan line 7 */
#define ACS_LEQUAL	NCURSES_ACS('y') /* less/equal */
#define ACS_GEQUAL	NCURSES_ACS('z') /* greater/equal */
#define ACS_PI		NCURSES_ACS('{') /* Pi */
#define ACS_NEQUAL	NCURSES_ACS('|') /* not equal */
#define ACS_STERLING	NCURSES_ACS('}') /* UK pound sign */

/*
 * Line drawing ACS names are of the form ACS_trbl, where t is the top, r
 * is the right, b is the bottom, and l is the left.  t, r, b, and l might
 * be B (blank), S (single), D (double), or T (thick).  The subset defined
 * here only uses B and S.
 */
#define ACS_BSSB	ACS_ULCORNER
#define ACS_SSBB	ACS_LLCORNER
#define ACS_BBSS	ACS_URCORNER
#define ACS_SBBS	ACS_LRCORNER
#define ACS_SBSS	ACS_RTEE
#define ACS_SSSB	ACS_LTEE
#define ACS_SSBS	ACS_BTEE
#define ACS_BSSS	ACS_TTEE
#define ACS_BSBS	ACS_HLINE
#define ACS_SBSB	ACS_VLINE
#define ACS_SSSS	ACS_PLUS

#undef	ERR
#define ERR     (-1)

#undef	OK
#define OK      (0)

/* values for the _flags member */
#define _SUBWIN         0x01	/* is this a sub-window? */
#define _ENDLINE        0x02	/* is the window flush right? */
#define _FULLWIN        0x04	/* is the window full-screen? */
#define _SCROLLWIN      0x08	/* bottom edge is at screen bottom? */
#define _ISPAD	        0x10	/* is this window a pad? */
#define _HASMOVED       0x20	/* has cursor moved since last refresh? */
#define _WRAPPED        0x40	/* cursor was just wrappped */

/*
 * this value is used in the firstchar and lastchar fields to mark
 * unchanged lines
 */
#define _NOCHANGE       -1

/*
 * this value is used in the oldindex field to mark lines created by insertions
 * and scrolls.
 */
#define _NEWINDEX	-1

typedef struct screen  SCREEN;
typedef struct _win_st WINDOW;

typedef	chtype	attr_t;		/* ...must be at least as wide as chtype */

#if NCURSES_WIDECHAR

#if 0
#ifdef mblen			/* libutf8.h defines it w/o undefining first */
#undef mblen
#endif
#include <libutf8.h>
#endif

#if 1
#include <wchar.h>		/* ...to get mbstate_t, etc. */
#endif

#if 0
typedef unsigned short wchar_t1;
#endif

#if 0
typedef unsigned int wint_t1;
#endif

/*
 * cchar_t stores an array of CCHARW_MAX wide characters.  The first is
 * normally a spacing character.  The others are non-spacing.  If those
 * (spacing and nonspacing) do not fill the array, a null L'\0' follows.
 * Otherwise, a null is assumed to follow when extracting via getcchar().
 */
#define CCHARW_MAX	5
typedef struct
{
    attr_t	attr;
    wchar_t	chars[CCHARW_MAX];
#if 1
#undef NCURSES_EXT_COLORS
#define NCURSES_EXT_COLORS 20200212
    int		ext_color;	/* color pair, must be more than 16-bits */
#endif
}
cchar_t;

#endif /* NCURSES_WIDECHAR */

#if !NCURSES_OPAQUE
struct ldat;

struct _win_st
{
	NCURSES_SIZE_T _cury, _curx; /* current cursor position */

	/* window location and size */
	NCURSES_SIZE_T _maxy, _maxx; /* maximums of x and y, NOT window size */
	NCURSES_SIZE_T _begy, _begx; /* screen coords of upper-left-hand corner */

	short   _flags;		/* window state flags */

	/* attribute tracking */
	attr_t  _attrs;		/* current attribute for non-space character */
	chtype  _bkgd;		/* current background char/attribute pair */

	/* option values set by user */
	bool	_notimeout;	/* no time out on function-key entry? */
	bool	_clear;		/* consider all data in the window invalid? */
	bool	_leaveok;	/* OK to not reset cursor on exit? */
	bool	_scroll;	/* OK to scroll this window? */
	bool	_idlok;		/* OK to use insert/delete line? */
	bool	_idcok;		/* OK to use insert/delete char? */
	bool	_immed;		/* window in immed mode? (not yet used) */
	bool	_sync;		/* window in sync mode? */
	bool	_use_keypad;	/* process function keys into KEY_ symbols? */
	int	_delay;		/* 0 = nodelay, <0 = blocking, >0 = delay */

	struct ldat *_line;	/* the actual line data */

	/* global screen state */
	NCURSES_SIZE_T _regtop;	/* top line of scrolling region */
	NCURSES_SIZE_T _regbottom; /* bottom line of scrolling region */

	/* these are used only if this is a sub-window */
	int	_parx;		/* x coordinate of this window in parent */
	int	_pary;		/* y coordinate of this window in parent */
	WINDOW	*_parent;	/* pointer to parent if a sub-window */

	/* these are used only if this is a pad */
	struct pdat
	{
	    NCURSES_SIZE_T _pad_y,      _pad_x;
	    NCURSES_SIZE_T _pad_top,    _pad_left;
	    NCURSES_SIZE_T _pad_bottom, _pad_right;
	} _pad;

	NCURSES_SIZE_T _yoffset; /* real begy is _begy + _yoffset */

#if NCURSES_WIDECHAR
	cchar_t  _bkgrnd;	/* current background char/attribute pair */
#if 1
	int	_color;		/* current color-pair for non-space character */
#endif
#endif
};
#endif /* NCURSES_OPAQUE */

/*
 * This is an extension to support events...
 */
#if 1
#ifdef NCURSES_WGETCH_EVENTS
#if !defined(__BEOS__) || defined(__HAIKU__)
   /* Fix _nc_timed_wait() on BEOS... */
#  define NCURSES_EVENT_VERSION	1
#endif	/* !defined(__BEOS__) */

/*
 * Bits to set in _nc_event.data.flags
 */
#  define _NC_EVENT_TIMEOUT_MSEC	1
#  define _NC_EVENT_FILE		2
#  define _NC_EVENT_FILE_READABLE	2
#  if 0					/* Not supported yet... */
#    define _NC_EVENT_FILE_WRITABLE	4
#    define _NC_EVENT_FILE_EXCEPTION	8
#  endif

typedef struct
{
    int type;
    union
    {
	long timeout_msec;	/* _NC_EVENT_TIMEOUT_MSEC */
	struct
	{
	    unsigned int flags;
	    int fd;
	    unsigned int result;
	} fev;				/* _NC_EVENT_FILE */
    } data;
} _nc_event;

typedef struct
{
    int count;
    int result_flags;	/* _NC_EVENT_TIMEOUT_MSEC or _NC_EVENT_FILE_READABLE */
    _nc_event *events[1];
} _nc_eventlist;

extern NCURSES_EXPORT(int) wgetch_events (WINDOW *, _nc_eventlist *);	/* experimental */
extern NCURSES_EXPORT(int) wgetnstr_events (WINDOW *,char *,int,_nc_eventlist *);/* experimental */

#endif /* NCURSES_WGETCH_EVENTS */
#endif /* NCURSES_EXT_FUNCS */

/*
 * GCC (and some other compilers) define '__attribute__'; we're using this
 * macro to alert the compiler to flag inconsistencies in printf/scanf-like
 * function calls.  Just in case '__attribute__' isn't defined, make a dummy.
 * Old versions of G++ do not accept it anyway, at least not consistently with
 * GCC.
 */
#if !(defined(__GNUC__) || defined(__GNUG__) || defined(__attribute__))
#define __attribute__(p) /* nothing */
#endif

/*
 * We cannot define these in ncurses_cfg.h, since they require parameters to be
 * passed (that is non-portable).  If you happen to be using gcc with warnings
 * enabled, define
 *	GCC_PRINTF
 *	GCC_SCANF
 * to improve checking of calls to printw(), etc.
 */
#ifndef GCC_PRINTFLIKE
#if defined(GCC_PRINTF) && !defined(printf)
#define GCC_PRINTFLIKE(fmt,var) __attribute__((format(printf,fmt,var)))
#else
#define GCC_PRINTFLIKE(fmt,var) /*nothing*/
#endif
#endif

#ifndef GCC_SCANFLIKE
#if defined(GCC_SCANF) && !defined(scanf)
#define GCC_SCANFLIKE(fmt,var)  __attribute__((format(scanf,fmt,var)))
#else
#define GCC_SCANFLIKE(fmt,var)  /*nothing*/
#endif
#endif

#ifndef	GCC_NORETURN
#define	GCC_NORETURN /* nothing */
#endif

#ifndef	GCC_UNUSED
#define	GCC_UNUSED /* nothing */
#endif

#undef  GCC_DEPRECATED
#if (__GNUC__ - 0 > 3 || (__GNUC__ - 0 == 3 && __GNUC_MINOR__ - 0 >= 2))
#define GCC_DEPRECATED(msg) __attribute__((deprecated))
#else
#define GCC_DEPRECATED(msg) /* nothing */
#endif

/*
 * Curses uses a helper function.  Define our type for this to simplify
 * extending it for the sp-funcs feature.
 */
typedef int (*NCURSES_OUTC)(int);

/*
 * Function prototypes.  This is the complete X/Open Curses list of required
 * functions.  Those marked `generated' will have sources generated from the
 * macro definitions later in this file, in order to satisfy XPG4.2
 * requirements.
 */

extern NCURSES_EXPORT(int) addch (const chtype);			/* generated */
extern NCURSES_EXPORT(int) addchnstr (const chtype *, int);		/* generated */
extern NCURSES_EXPORT(int) addchstr (const chtype *);			/* generated */
extern NCURSES_EXPORT(int) addnstr (const char *, int);			/* generated */
extern NCURSES_EXPORT(int) addstr (const char *);			/* generated */
extern NCURSES_EXPORT(int) attroff (NCURSES_ATTR_T);			/* generated */
extern NCURSES_EXPORT(int) attron (NCURSES_ATTR_T);			/* generated */
extern NCURSES_EXPORT(int) attrset (NCURSES_ATTR_T);			/* generated */
extern NCURSES_EXPORT(int) attr_get (attr_t *, NCURSES_PAIRS_T *, void *);	/* generated */
extern NCURSES_EXPORT(int) attr_off (attr_t, void *);			/* generated */
extern NCURSES_EXPORT(int) attr_on (attr_t, void *);			/* generated */
extern NCURSES_EXPORT(int) attr_set (attr_t, NCURSES_PAIRS_T, void *);		/* generated */
extern NCURSES_EXPORT(int) baudrate (void);				/* implemented */
extern NCURSES_EXPORT(int) beep  (void);				/* implemented */
extern NCURSES_EXPORT(int) bkgd (chtype);				/* generated */
extern NCURSES_EXPORT(void) bkgdset (chtype);				/* generated */
extern NCURSES_EXPORT(int) border (chtype,chtype,chtype,chtype,chtype,chtype,chtype,chtype);	/* generated */
extern NCURSES_EXPORT(int) box (WINDOW *, chtype, chtype);		/* generated */
extern NCURSES_EXPORT(bool) can_change_color (void);			/* implemented */
extern NCURSES_EXPORT(int) cbreak (void);				/* implemented */
extern NCURSES_EXPORT(int) chgat (int, attr_t, NCURSES_PAIRS_T, const void *);	/* generated */
extern NCURSES_EXPORT(int) clear (void);				/* generated */
extern NCURSES_EXPORT(int) clearok (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(int) clrtobot (void);				/* generated */
extern NCURSES_EXPORT(int) clrtoeol (void);				/* generated */
extern NCURSES_EXPORT(int) color_content (NCURSES_COLOR_T,NCURSES_COLOR_T*,NCURSES_COLOR_T*,NCURSES_COLOR_T*);	/* implemented */
extern NCURSES_EXPORT(int) color_set (NCURSES_PAIRS_T,void*);			/* generated */
extern NCURSES_EXPORT(int) COLOR_PAIR (int);				/* generated */
extern NCURSES_EXPORT(int) copywin (const WINDOW*,WINDOW*,int,int,int,int,int,int,int);	/* implemented */
extern NCURSES_EXPORT(int) curs_set (int);				/* implemented */
extern NCURSES_EXPORT(int) def_prog_mode (void);			/* implemented */
extern NCURSES_EXPORT(int) def_shell_mode (void);			/* implemented */
extern NCURSES_EXPORT(int) delay_output (int);				/* implemented */
extern NCURSES_EXPORT(int) delch (void);				/* generated */
extern NCURSES_EXPORT(void) delscreen (SCREEN *);			/* implemented */
extern NCURSES_EXPORT(int) delwin (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) deleteln (void);				/* generated */
extern NCURSES_EXPORT(WINDOW *) derwin (WINDOW *,int,int,int,int);	/* implemented */
extern NCURSES_EXPORT(int) doupdate (void);				/* implemented */
extern NCURSES_EXPORT(WINDOW *) dupwin (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(int) echo (void);					/* implemented */
extern NCURSES_EXPORT(int) echochar (const chtype);			/* generated */
extern NCURSES_EXPORT(int) erase (void);				/* generated */
extern NCURSES_EXPORT(int) endwin (void);				/* implemented */
extern NCURSES_EXPORT(char) erasechar (void);				/* implemented */
extern NCURSES_EXPORT(void) filter (void);				/* implemented */
extern NCURSES_EXPORT(int) flash (void);				/* implemented */
extern NCURSES_EXPORT(int) flushinp (void);				/* implemented */
extern NCURSES_EXPORT(chtype) getbkgd (WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) getch (void);				/* generated */
extern NCURSES_EXPORT(int) getnstr (char *, int);			/* generated */
extern NCURSES_EXPORT(int) getstr (char *);				/* generated */
extern NCURSES_EXPORT(WINDOW *) getwin (FILE *);			/* implemented */
extern NCURSES_EXPORT(int) halfdelay (int);				/* implemented */
extern NCURSES_EXPORT(bool) has_colors (void);				/* implemented */
extern NCURSES_EXPORT(bool) has_ic (void);				/* implemented */
extern NCURSES_EXPORT(bool) has_il (void);				/* implemented */
extern NCURSES_EXPORT(int) hline (chtype, int);				/* generated */
extern NCURSES_EXPORT(void) idcok (WINDOW *, bool);			/* implemented */
extern NCURSES_EXPORT(int) idlok (WINDOW *, bool);			/* implemented */
extern NCURSES_EXPORT(void) immedok (WINDOW *, bool);			/* implemented */
extern NCURSES_EXPORT(chtype) inch (void);				/* generated */
extern NCURSES_EXPORT(int) inchnstr (chtype *, int);			/* generated */
extern NCURSES_EXPORT(int) inchstr (chtype *);				/* generated */
extern NCURSES_EXPORT(WINDOW *) initscr (void);				/* implemented */
extern NCURSES_EXPORT(int) init_color (NCURSES_COLOR_T,NCURSES_COLOR_T,NCURSES_COLOR_T,NCURSES_COLOR_T);	/* implemented */
extern NCURSES_EXPORT(int) init_pair (NCURSES_PAIRS_T,NCURSES_COLOR_T,NCURSES_COLOR_T);		/* implemented */
extern NCURSES_EXPORT(int) innstr (char *, int);			/* generated */
extern NCURSES_EXPORT(int) insch (chtype);				/* generated */
extern NCURSES_EXPORT(int) insdelln (int);				/* generated */
extern NCURSES_EXPORT(int) insertln (void);				/* generated */
extern NCURSES_EXPORT(int) insnstr (const char *, int);			/* generated */
extern NCURSES_EXPORT(int) insstr (const char *);			/* generated */
extern NCURSES_EXPORT(int) instr (char *);				/* generated */
extern NCURSES_EXPORT(int) intrflush (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(bool) isendwin (void);				/* implemented */
extern NCURSES_EXPORT(bool) is_linetouched (WINDOW *,int);		/* implemented */
extern NCURSES_EXPORT(bool) is_wintouched (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(NCURSES_CONST char *) keyname (int);		/* implemented */
extern NCURSES_EXPORT(int) keypad (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(char) killchar (void);				/* implemented */
extern NCURSES_EXPORT(int) leaveok (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(char *) longname (void);				/* implemented */
extern NCURSES_EXPORT(int) meta (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(int) move (int, int);				/* generated */
extern NCURSES_EXPORT(int) mvaddch (int, int, const chtype);		/* generated */
extern NCURSES_EXPORT(int) mvaddchnstr (int, int, const chtype *, int);	/* generated */
extern NCURSES_EXPORT(int) mvaddchstr (int, int, const chtype *);	/* generated */
extern NCURSES_EXPORT(int) mvaddnstr (int, int, const char *, int);	/* generated */
extern NCURSES_EXPORT(int) mvaddstr (int, int, const char *);		/* generated */
extern NCURSES_EXPORT(int) mvchgat (int, int, int, attr_t, NCURSES_PAIRS_T, const void *);	/* generated */
extern NCURSES_EXPORT(int) mvcur (int,int,int,int);			/* implemented */
extern NCURSES_EXPORT(int) mvdelch (int, int);				/* generated */
extern NCURSES_EXPORT(int) mvderwin (WINDOW *, int, int);		/* implemented */
extern NCURSES_EXPORT(int) mvgetch (int, int);				/* generated */
extern NCURSES_EXPORT(int) mvgetnstr (int, int, char *, int);		/* generated */
extern NCURSES_EXPORT(int) mvgetstr (int, int, char *);			/* generated */
extern NCURSES_EXPORT(int) mvhline (int, int, chtype, int);		/* generated */
extern NCURSES_EXPORT(chtype) mvinch (int, int);			/* generated */
extern NCURSES_EXPORT(int) mvinchnstr (int, int, chtype *, int);	/* generated */
extern NCURSES_EXPORT(int) mvinchstr (int, int, chtype *);		/* generated */
extern NCURSES_EXPORT(int) mvinnstr (int, int, char *, int);		/* generated */
extern NCURSES_EXPORT(int) mvinsch (int, int, chtype);			/* generated */
extern NCURSES_EXPORT(int) mvinsnstr (int, int, const char *, int);	/* generated */
extern NCURSES_EXPORT(int) mvinsstr (int, int, const char *);		/* generated */
extern NCURSES_EXPORT(int) mvinstr (int, int, char *);			/* generated */
extern NCURSES_EXPORT(int) mvprintw (int,int, const char *,...)		/* implemented */
		GCC_PRINTFLIKE(3,4);
extern NCURSES_EXPORT(int) mvscanw (int,int, const char *,...)		/* implemented */
		GCC_SCANFLIKE(3,4);
extern NCURSES_EXPORT(int) mvvline (int, int, chtype, int);		/* generated */
extern NCURSES_EXPORT(int) mvwaddch (WINDOW *, int, int, const chtype);	/* generated */
extern NCURSES_EXPORT(int) mvwaddchnstr (WINDOW *, int, int, const chtype *, int);/* generated */
extern NCURSES_EXPORT(int) mvwaddchstr (WINDOW *, int, int, const chtype *);	/* generated */
extern NCURSES_EXPORT(int) mvwaddnstr (WINDOW *, int, int, const char *, int);	/* generated */
extern NCURSES_EXPORT(int) mvwaddstr (WINDOW *, int, int, const char *);	/* generated */
extern NCURSES_EXPORT(int) mvwchgat (WINDOW *, int, int, int, attr_t, NCURSES_PAIRS_T, const void *);/* generated */
extern NCURSES_EXPORT(int) mvwdelch (WINDOW *, int, int);		/* generated */
extern NCURSES_EXPORT(int) mvwgetch (WINDOW *, int, int);		/* generated */
extern NCURSES_EXPORT(int) mvwgetnstr (WINDOW *, int, int, char *, int);	/* generated */
extern NCURSES_EXPORT(int) mvwgetstr (WINDOW *, int, int, char *);	/* generated */
extern NCURSES_EXPORT(int) mvwhline (WINDOW *, int, int, chtype, int);	/* generated */
extern NCURSES_EXPORT(int) mvwin (WINDOW *,int,int);			/* implemented */
extern NCURSES_EXPORT(chtype) mvwinch (WINDOW *, int, int);			/* generated */
extern NCURSES_EXPORT(int) mvwinchnstr (WINDOW *, int, int, chtype *, int);	/* generated */
extern NCURSES_EXPORT(int) mvwinchstr (WINDOW *, int, int, chtype *);		/* generated */
extern NCURSES_EXPORT(int) mvwinnstr (WINDOW *, int, int, char *, int);		/* generated */
extern NCURSES_EXPORT(int) mvwinsch (WINDOW *, int, int, chtype);		/* generated */
extern NCURSES_EXPORT(int) mvwinsnstr (WINDOW *, int, int, const char *, int);	/* generated */
extern NCURSES_EXPORT(int) mvwinsstr (WINDOW *, int, int, const char *);	/* generated */
extern NCURSES_EXPORT(int) mvwinstr (WINDOW *, int, int, char *);		/* generated */
extern NCURSES_EXPORT(int) mvwprintw (WINDOW*,int,int, const char *,...)	/* implemented */
		GCC_PRINTFLIKE(4,5);
extern NCURSES_EXPORT(int) mvwscanw (WINDOW *,int,int, const char *,...)	/* implemented */
		GCC_SCANFLIKE(4,5);
extern NCURSES_EXPORT(int) mvwvline (WINDOW *,int, int, chtype, int);	/* generated */
extern NCURSES_EXPORT(int) napms (int);					/* implemented */
extern NCURSES_EXPORT(WINDOW *) newpad (int,int);			/* implemented */
extern NCURSES_EXPORT(SCREEN *) newterm (const char *,FILE *,FILE *);	/* implemented */
extern NCURSES_EXPORT(WINDOW *) newwin (int,int,int,int);		/* implemented */
extern NCURSES_EXPORT(int) nl (void);					/* implemented */
extern NCURSES_EXPORT(int) nocbreak (void);				/* implemented */
extern NCURSES_EXPORT(int) nodelay (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(int) noecho (void);				/* implemented */
extern NCURSES_EXPORT(int) nonl (void);					/* implemented */
extern NCURSES_EXPORT(void) noqiflush (void);				/* implemented */
extern NCURSES_EXPORT(int) noraw (void);				/* implemented */
extern NCURSES_EXPORT(int) notimeout (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(int) overlay (const WINDOW*,WINDOW *);		/* implemented */
extern NCURSES_EXPORT(int) overwrite (const WINDOW*,WINDOW *);		/* implemented */
extern NCURSES_EXPORT(int) pair_content (NCURSES_PAIRS_T,NCURSES_COLOR_T*,NCURSES_COLOR_T*);		/* implemented */
extern NCURSES_EXPORT(int) PAIR_NUMBER (int);				/* generated */
extern NCURSES_EXPORT(int) pechochar (WINDOW *, const chtype);		/* implemented */
extern NCURSES_EXPORT(int) pnoutrefresh (WINDOW*,int,int,int,int,int,int);/* implemented */
extern NCURSES_EXPORT(int) prefresh (WINDOW *,int,int,int,int,int,int);	/* implemented */
extern NCURSES_EXPORT(int) printw (const char *,...)			/* implemented */
		GCC_PRINTFLIKE(1,2);
extern NCURSES_EXPORT(int) putwin (WINDOW *, FILE *);			/* implemented */
extern NCURSES_EXPORT(void) qiflush (void);				/* implemented */
extern NCURSES_EXPORT(int) raw (void);					/* implemented */
extern NCURSES_EXPORT(int) redrawwin (WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) refresh (void);				/* generated */
extern NCURSES_EXPORT(int) resetty (void);				/* implemented */
extern NCURSES_EXPORT(int) reset_prog_mode (void);			/* implemented */
extern NCURSES_EXPORT(int) reset_shell_mode (void);			/* implemented */
extern NCURSES_EXPORT(int) ripoffline (int, int (*)(WINDOW *, int));	/* implemented */
extern NCURSES_EXPORT(int) savetty (void);				/* implemented */
extern NCURSES_EXPORT(int) scanw (const char *,...)			/* implemented */
		GCC_SCANFLIKE(1,2);
extern NCURSES_EXPORT(int) scr_dump (const char *);			/* implemented */
extern NCURSES_EXPORT(int) scr_init (const char *);			/* implemented */
extern NCURSES_EXPORT(int) scrl (int);					/* generated */
extern NCURSES_EXPORT(int) scroll (WINDOW *);				/* generated */
extern NCURSES_EXPORT(int) scrollok (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(int) scr_restore (const char *);			/* implemented */
extern NCURSES_EXPORT(int) scr_set (const char *);			/* implemented */
extern NCURSES_EXPORT(int) setscrreg (int,int);				/* generated */
extern NCURSES_EXPORT(SCREEN *) set_term (SCREEN *);			/* implemented */
extern NCURSES_EXPORT(int) slk_attroff (const chtype);			/* implemented */
extern NCURSES_EXPORT(int) slk_attr_off (const attr_t, void *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) slk_attron (const chtype);			/* implemented */
extern NCURSES_EXPORT(int) slk_attr_on (attr_t,void*);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) slk_attrset (const chtype);			/* implemented */
extern NCURSES_EXPORT(attr_t) slk_attr (void);				/* implemented */
extern NCURSES_EXPORT(int) slk_attr_set (const attr_t,NCURSES_PAIRS_T,void*);	/* implemented */
extern NCURSES_EXPORT(int) slk_clear (void);				/* implemented */
extern NCURSES_EXPORT(int) slk_color (NCURSES_PAIRS_T);				/* implemented */
extern NCURSES_EXPORT(int) slk_init (int);				/* implemented */
extern NCURSES_EXPORT(char *) slk_label (int);				/* implemented */
extern NCURSES_EXPORT(int) slk_noutrefresh (void);			/* implemented */
extern NCURSES_EXPORT(int) slk_refresh (void);				/* implemented */
extern NCURSES_EXPORT(int) slk_restore (void);				/* implemented */
extern NCURSES_EXPORT(int) slk_set (int,const char *,int);		/* implemented */
extern NCURSES_EXPORT(int) slk_touch (void);				/* implemented */
extern NCURSES_EXPORT(int) standout (void);				/* generated */
extern NCURSES_EXPORT(int) standend (void);				/* generated */
extern NCURSES_EXPORT(int) start_color (void);				/* implemented */
extern NCURSES_EXPORT(WINDOW *) subpad (WINDOW *, int, int, int, int);	/* implemented */
extern NCURSES_EXPORT(WINDOW *) subwin (WINDOW *, int, int, int, int);	/* implemented */
extern NCURSES_EXPORT(int) syncok (WINDOW *, bool);			/* implemented */
extern NCURSES_EXPORT(chtype) termattrs (void);				/* implemented */
extern NCURSES_EXPORT(char *) termname (void);				/* implemented */
extern NCURSES_EXPORT(void) timeout (int);				/* generated */
extern NCURSES_EXPORT(int) touchline (WINDOW *, int, int);		/* generated */
extern NCURSES_EXPORT(int) touchwin (WINDOW *);				/* generated */
extern NCURSES_EXPORT(int) typeahead (int);				/* implemented */
extern NCURSES_EXPORT(int) ungetch (int);				/* implemented */
extern NCURSES_EXPORT(int) untouchwin (WINDOW *);			/* generated */
extern NCURSES_EXPORT(void) use_env (bool);				/* implemented */
extern NCURSES_EXPORT(void) use_tioctl (bool);				/* implemented */
extern NCURSES_EXPORT(int) vidattr (chtype);				/* implemented */
extern NCURSES_EXPORT(int) vidputs (chtype, NCURSES_OUTC);		/* implemented */
extern NCURSES_EXPORT(int) vline (chtype, int);				/* generated */
extern NCURSES_EXPORT(int) vwprintw (WINDOW *, const char *,va_list) GCC_DEPRECATED(use vw_printw);	/* implemented */
extern NCURSES_EXPORT(int) vw_printw (WINDOW *, const char *,va_list);	/* implemented */
extern NCURSES_EXPORT(int) vwscanw (WINDOW *, const char *,va_list) GCC_DEPRECATED(use vw_scanw);	/* implemented */
extern NCURSES_EXPORT(int) vw_scanw (WINDOW *, const char *,va_list);	/* implemented */
extern NCURSES_EXPORT(int) waddch (WINDOW *, const chtype);		/* implemented */
extern NCURSES_EXPORT(int) waddchnstr (WINDOW *,const chtype *,int);	/* implemented */
extern NCURSES_EXPORT(int) waddchstr (WINDOW *,const chtype *);		/* generated */
extern NCURSES_EXPORT(int) waddnstr (WINDOW *,const char *,int);	/* implemented */
extern NCURSES_EXPORT(int) waddstr (WINDOW *,const char *);		/* generated */
extern NCURSES_EXPORT(int) wattron (WINDOW *, int);			/* generated */
extern NCURSES_EXPORT(int) wattroff (WINDOW *, int);			/* generated */
extern NCURSES_EXPORT(int) wattrset (WINDOW *, int);			/* generated */
extern NCURSES_EXPORT(int) wattr_get (WINDOW *, attr_t *, NCURSES_PAIRS_T *, void *);	/* generated */
extern NCURSES_EXPORT(int) wattr_on (WINDOW *, attr_t, void *);		/* implemented */
extern NCURSES_EXPORT(int) wattr_off (WINDOW *, attr_t, void *);	/* implemented */
extern NCURSES_EXPORT(int) wattr_set (WINDOW *, attr_t, NCURSES_PAIRS_T, void *);	/* generated */
extern NCURSES_EXPORT(int) wbkgd (WINDOW *, chtype);			/* implemented */
extern NCURSES_EXPORT(void) wbkgdset (WINDOW *,chtype);			/* implemented */
extern NCURSES_EXPORT(int) wborder (WINDOW *,chtype,chtype,chtype,chtype,chtype,chtype,chtype,chtype);	/* implemented */
extern NCURSES_EXPORT(int) wchgat (WINDOW *, int, attr_t, NCURSES_PAIRS_T, const void *);/* implemented */
extern NCURSES_EXPORT(int) wclear (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) wclrtobot (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(int) wclrtoeol (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(int) wcolor_set (WINDOW*,NCURSES_PAIRS_T,void*);		/* implemented */
extern NCURSES_EXPORT(void) wcursyncup (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(int) wdelch (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) wdeleteln (WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) wechochar (WINDOW *, const chtype);		/* implemented */
extern NCURSES_EXPORT(int) werase (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) wgetch (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) wgetnstr (WINDOW *,char *,int);		/* implemented */
extern NCURSES_EXPORT(int) wgetstr (WINDOW *, char *);			/* generated */
extern NCURSES_EXPORT(int) whline (WINDOW *, chtype, int);		/* implemented */
extern NCURSES_EXPORT(chtype) winch (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) winchnstr (WINDOW *, chtype *, int);		/* implemented */
extern NCURSES_EXPORT(int) winchstr (WINDOW *, chtype *);		/* generated */
extern NCURSES_EXPORT(int) winnstr (WINDOW *, char *, int);		/* implemented */
extern NCURSES_EXPORT(int) winsch (WINDOW *, chtype);			/* implemented */
extern NCURSES_EXPORT(int) winsdelln (WINDOW *,int);			/* implemented */
extern NCURSES_EXPORT(int) winsertln (WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) winsnstr (WINDOW *, const char *,int);	/* implemented */
extern NCURSES_EXPORT(int) winsstr (WINDOW *, const char *);		/* generated */
extern NCURSES_EXPORT(int) winstr (WINDOW *, char *);			/* generated */
extern NCURSES_EXPORT(int) wmove (WINDOW *,int,int);			/* implemented */
extern NCURSES_EXPORT(int) wnoutrefresh (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(int) wprintw (WINDOW *, const char *,...)		/* implemented */
		GCC_PRINTFLIKE(2,3);
extern NCURSES_EXPORT(int) wredrawln (WINDOW *,int,int);		/* implemented */
extern NCURSES_EXPORT(int) wrefresh (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) wscanw (WINDOW *, const char *,...)		/* implemented */
		GCC_SCANFLIKE(2,3);
extern NCURSES_EXPORT(int) wscrl (WINDOW *,int);			/* implemented */
extern NCURSES_EXPORT(int) wsetscrreg (WINDOW *,int,int);		/* implemented */
extern NCURSES_EXPORT(int) wstandout (WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) wstandend (WINDOW *);			/* generated */
extern NCURSES_EXPORT(void) wsyncdown (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(void) wsyncup (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(void) wtimeout (WINDOW *,int);			/* implemented */
extern NCURSES_EXPORT(int) wtouchln (WINDOW *,int,int,int);		/* implemented */
extern NCURSES_EXPORT(int) wvline (WINDOW *,chtype,int);		/* implemented */

/*
 * These are also declared in <term.h>:
 */
extern NCURSES_EXPORT(int) tigetflag (const char *);			/* implemented */
extern NCURSES_EXPORT(int) tigetnum (const char *);			/* implemented */
extern NCURSES_EXPORT(char *) tigetstr (const char *);			/* implemented */
extern NCURSES_EXPORT(int) putp (const char *);				/* implemented */

#if NCURSES_TPARM_VARARGS
extern NCURSES_EXPORT(char *) tparm (const char *, ...);		/* special */
#else
extern NCURSES_EXPORT(char *) tparm (const char *, NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG);	/* special */
extern NCURSES_EXPORT(char *) tparm_varargs (const char *, ...);	/* special */
#endif

extern NCURSES_EXPORT(char *) tiparm (const char *, ...);		/* special */

/*
 * These functions are not in X/Open, but we use them in macro definitions:
 */
extern NCURSES_EXPORT(int) getattrs (const WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) getcurx (const WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) getcury (const WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) getbegx (const WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) getbegy (const WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) getmaxx (const WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) getmaxy (const WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) getparx (const WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) getpary (const WINDOW *);			/* generated */

/*
 * vid_attr() was implemented originally based on a draft of X/Open curses.
 */
#if !NCURSES_WIDECHAR
#define vid_attr(a,pair,opts) vidattr(a)
#endif

/*
 * These functions are extensions - not in X/Open Curses.
 */
#if 1
#undef  NCURSES_EXT_FUNCS
#define NCURSES_EXT_FUNCS 20200212
typedef int (*NCURSES_WINDOW_CB)(WINDOW *, void *);
typedef int (*NCURSES_SCREEN_CB)(SCREEN *, void *);
extern NCURSES_EXPORT(bool) is_term_resized (int, int);
extern NCURSES_EXPORT(char *) keybound (int, int);
extern NCURSES_EXPORT(const char *) curses_version (void);
extern NCURSES_EXPORT(int) alloc_pair (int, int);
extern NCURSES_EXPORT(int) assume_default_colors (int, int);
extern NCURSES_EXPORT(int) define_key (const char *, int);
extern NCURSES_EXPORT(int) extended_color_content(int, int *, int *, int *);
extern NCURSES_EXPORT(int) extended_pair_content(int, int *, int *);
extern NCURSES_EXPORT(int) extended_slk_color(int);
extern NCURSES_EXPORT(int) find_pair (int, int);
extern NCURSES_EXPORT(int) free_pair (int);
extern NCURSES_EXPORT(int) get_escdelay (void);
extern NCURSES_EXPORT(int) init_extended_color(int, int, int, int);
extern NCURSES_EXPORT(int) init_extended_pair(int, int, int);
extern NCURSES_EXPORT(int) key_defined (const char *);
extern NCURSES_EXPORT(int) keyok (int, bool);
extern NCURSES_EXPORT(void) reset_color_pairs (void);
extern NCURSES_EXPORT(int) resize_term (int, int);
extern NCURSES_EXPORT(int) resizeterm (int, int);
extern NCURSES_EXPORT(int) set_escdelay (int);
extern NCURSES_EXPORT(int) set_tabsize (int);
extern NCURSES_EXPORT(int) use_default_colors (void);
extern NCURSES_EXPORT(int) use_extended_names (bool);
extern NCURSES_EXPORT(int) use_legacy_coding (int);
extern NCURSES_EXPORT(int) use_screen (SCREEN *, NCURSES_SCREEN_CB, void *);
extern NCURSES_EXPORT(int) use_window (WINDOW *, NCURSES_WINDOW_CB, void *);
extern NCURSES_EXPORT(int) wresize (WINDOW *, int, int);
extern NCURSES_EXPORT(void) nofilter(void);

/*
 * These extensions provide access to information stored in the WINDOW even
 * when NCURSES_OPAQUE is set:
 */
extern NCURSES_EXPORT(WINDOW *) wgetparent (const WINDOW *);	/* generated */
extern NCURSES_EXPORT(bool) is_cleared (const WINDOW *);	/* generated */
extern NCURSES_EXPORT(bool) is_idcok (const WINDOW *);		/* generated */
extern NCURSES_EXPORT(bool) is_idlok (const WINDOW *);		/* generated */
extern NCURSES_EXPORT(bool) is_immedok (const WINDOW *);	/* generated */
extern NCURSES_EXPORT(bool) is_keypad (const WINDOW *);		/* generated */
extern NCURSES_EXPORT(bool) is_leaveok (const WINDOW *);	/* generated */
extern NCURSES_EXPORT(bool) is_nodelay (const WINDOW *);	/* generated */
extern NCURSES_EXPORT(bool) is_notimeout (const WINDOW *);	/* generated */
extern NCURSES_EXPORT(bool) is_pad (const WINDOW *);		/* generated */
extern NCURSES_EXPORT(bool) is_scrollok (const WINDOW *);	/* generated */
extern NCURSES_EXPORT(bool) is_subwin (const WINDOW *);		/* generated */
extern NCURSES_EXPORT(bool) is_syncok (const WINDOW *);		/* generated */
extern NCURSES_EXPORT(int) wgetdelay (const WINDOW *);		/* generated */
extern NCURSES_EXPORT(int) wgetscrreg (const WINDOW *, int *, int *); /* generated */

#else
#define curses_version() NCURSES_VERSION
#endif

/*
 * Extra extension-functions, which pass a SCREEN pointer rather than using
 * a global variable SP.
 */
#if 1
#undef  NCURSES_SP_FUNCS
#define NCURSES_SP_FUNCS 20200212
#define NCURSES_SP_NAME(name) name##_sp

/* Define the sp-funcs helper function */
#define NCURSES_SP_OUTC NCURSES_SP_NAME(NCURSES_OUTC)
typedef int (*NCURSES_SP_OUTC)(SCREEN*, int);

extern NCURSES_EXPORT(SCREEN *) new_prescr (void); /* implemented:SP_FUNC */

extern NCURSES_EXPORT(int) NCURSES_SP_NAME(baudrate) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(beep) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(can_change_color) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(cbreak) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(curs_set) (SCREEN*, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(color_content) (SCREEN*, NCURSES_PAIRS_T, NCURSES_COLOR_T*, NCURSES_COLOR_T*, NCURSES_COLOR_T*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(def_prog_mode) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(def_shell_mode) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(delay_output) (SCREEN*, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(doupdate) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(echo) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(endwin) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(char) NCURSES_SP_NAME(erasechar) (SCREEN*);/* implemented:SP_FUNC */
extern NCURSES_EXPORT(void) NCURSES_SP_NAME(filter) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(flash) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(flushinp) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(WINDOW *) NCURSES_SP_NAME(getwin) (SCREEN*, FILE *);			/* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(halfdelay) (SCREEN*, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(has_colors) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(has_ic) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(has_il) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(init_color) (SCREEN*, NCURSES_COLOR_T, NCURSES_COLOR_T, NCURSES_COLOR_T, NCURSES_COLOR_T); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(init_pair) (SCREEN*, NCURSES_PAIRS_T, NCURSES_COLOR_T, NCURSES_COLOR_T); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(intrflush) (SCREEN*, WINDOW*, bool);	/* implemented:SP_FUNC */
extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(isendwin) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(NCURSES_CONST char *) NCURSES_SP_NAME(keyname) (SCREEN*, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(char) NCURSES_SP_NAME(killchar) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(char *) NCURSES_SP_NAME(longname) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(mvcur) (SCREEN*, int, int, int, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(napms) (SCREEN*, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(WINDOW *) NCURSES_SP_NAME(newpad) (SCREEN*, int, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(SCREEN *) NCURSES_SP_NAME(newterm) (SCREEN*, const char *, FILE *, FILE *); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(WINDOW *) NCURSES_SP_NAME(newwin) (SCREEN*, int, int, int, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(nl) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(nocbreak) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(noecho) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(nonl) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(void) NCURSES_SP_NAME(noqiflush) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(noraw) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(pair_content) (SCREEN*, NCURSES_PAIRS_T, NCURSES_COLOR_T*, NCURSES_COLOR_T*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(void) NCURSES_SP_NAME(qiflush) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(raw) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(reset_prog_mode) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(reset_shell_mode) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(resetty) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(ripoffline) (SCREEN*, int, int (*)(WINDOW *, int));	/* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(savetty) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(scr_init) (SCREEN*, const char *); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(scr_restore) (SCREEN*, const char *); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(scr_set) (SCREEN*, const char *); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_attroff) (SCREEN*, const chtype); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_attron) (SCREEN*, const chtype); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_attrset) (SCREEN*, const chtype); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(attr_t) NCURSES_SP_NAME(slk_attr) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_attr_set) (SCREEN*, const attr_t, NCURSES_PAIRS_T, void*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_clear) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_color) (SCREEN*, NCURSES_PAIRS_T); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_init) (SCREEN*, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(char *) NCURSES_SP_NAME(slk_label) (SCREEN*, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_noutrefresh) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_refresh) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_restore) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_set) (SCREEN*, int, const char *, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_touch) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(start_color) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(chtype) NCURSES_SP_NAME(termattrs) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(char *) NCURSES_SP_NAME(termname) (SCREEN*); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(typeahead) (SCREEN*, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(ungetch) (SCREEN*, int); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(void) NCURSES_SP_NAME(use_env) (SCREEN*, bool); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(void) NCURSES_SP_NAME(use_tioctl) (SCREEN*, bool); /* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(vidattr) (SCREEN*, chtype);	/* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(vidputs) (SCREEN*, chtype, NCURSES_SP_OUTC); /* implemented:SP_FUNC */
#if 1
extern NCURSES_EXPORT(char *) NCURSES_SP_NAME(keybound) (SCREEN*, int, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(alloc_pair) (SCREEN*, int, int); /* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(assume_default_colors) (SCREEN*, int, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(define_key) (SCREEN*, const char *, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(extended_color_content) (SCREEN*, int, int *, int *, int *);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(extended_pair_content) (SCREEN*, int, int *, int *);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(extended_slk_color) (SCREEN*, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(get_escdelay) (SCREEN*);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(find_pair) (SCREEN*, int, int); /* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(free_pair) (SCREEN*, int); /* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(init_extended_color) (SCREEN*, int, int, int, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(init_extended_pair) (SCREEN*, int, int, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(is_term_resized) (SCREEN*, int, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(key_defined) (SCREEN*, const char *);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(keyok) (SCREEN*, int, bool);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(void) NCURSES_SP_NAME(nofilter) (SCREEN*); /* implemented */	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(void) NCURSES_SP_NAME(reset_color_pairs) (SCREEN*); /* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(resize_term) (SCREEN*, int, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(resizeterm) (SCREEN*, int, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(set_escdelay) (SCREEN*, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(set_tabsize) (SCREEN*, int);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(use_default_colors) (SCREEN*);	/* implemented:EXT_SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(use_legacy_coding) (SCREEN*, int);	/* implemented:EXT_SP_FUNC */
#endif
#else
#undef  NCURSES_SP_FUNCS
#define NCURSES_SP_FUNCS 0
#define NCURSES_SP_NAME(name) name
#define NCURSES_SP_OUTC NCURSES_OUTC
#endif

/* attributes */

#define NCURSES_ATTR_SHIFT       8
#define NCURSES_BITS(mask,shift) (NCURSES_CAST(chtype,(mask)) << ((shift) + NCURSES_ATTR_SHIFT))

#define A_NORMAL	(1UL - 1UL)
#define A_ATTRIBUTES	NCURSES_BITS(~(1UL - 1UL),0)
#define A_CHARTEXT	(NCURSES_BITS(1UL,0) - 1UL)
#define A_COLOR		NCURSES_BITS(((1UL) << 8) - 1UL,0)
#define A_STANDOUT	NCURSES_BITS(1UL,8)
#define A_UNDERLINE	NCURSES_BITS(1UL,9)
#define A_REVERSE	NCURSES_BITS(1UL,10)
#define A_BLINK		NCURSES_BITS(1UL,11)
#define A_DIM		NCURSES_BITS(1UL,12)
#define A_BOLD		NCURSES_BITS(1UL,13)
#define A_ALTCHARSET	NCURSES_BITS(1UL,14)
#define A_INVIS		NCURSES_BITS(1UL,15)
#define A_PROTECT	NCURSES_BITS(1UL,16)
#define A_HORIZONTAL	NCURSES_BITS(1UL,17)
#define A_LEFT		NCURSES_BITS(1UL,18)
#define A_LOW		NCURSES_BITS(1UL,19)
#define A_RIGHT		NCURSES_BITS(1UL,20)
#define A_TOP		NCURSES_BITS(1UL,21)
#define A_VERTICAL	NCURSES_BITS(1UL,22)

#if 1
#define A_ITALIC	NCURSES_BITS(1UL,23)	/* ncurses extension */
#endif

/*
 * Most of the pseudo functions are macros that either provide compatibility
 * with older versions of curses, or provide inline functionality to improve
 * performance.
 */

/*
 * These pseudo functions are always implemented as macros:
 */

#define getyx(win,y,x)		(y = getcury(win), x = getcurx(win))
#define getbegyx(win,y,x)	(y = getbegy(win), x = getbegx(win))
#define getmaxyx(win,y,x)	(y = getmaxy(win), x = getmaxx(win))
#define getparyx(win,y,x)	(y = getpary(win), x = getparx(win))

#define getsyx(y,x) do { if (newscr) { \
			     if (is_leaveok(newscr)) \
				(y) = (x) = -1; \
			     else \
				 getyx(newscr,(y), (x)); \
			} \
		    } while(0)

#define setsyx(y,x) do { if (newscr) { \
			    if ((y) == -1 && (x) == -1) \
				leaveok(newscr, TRUE); \
			    else { \
				leaveok(newscr, FALSE); \
				wmove(newscr, (y), (x)); \
			    } \
			} \
		    } while(0)

#ifndef NCURSES_NOMACROS

/*
 * These miscellaneous pseudo functions are provided for compatibility:
 */

#define wgetstr(w, s)		wgetnstr(w, s, -1)
#define getnstr(s, n)		wgetnstr(stdscr, s, (n))

#define setterm(term)		setupterm(term, 1, (int *)0)

#define fixterm()		reset_prog_mode()
#define resetterm()		reset_shell_mode()
#define saveterm()		def_prog_mode()
#define crmode()		cbreak()
#define nocrmode()		nocbreak()
#define gettmode()

/* It seems older SYSV curses versions define these */
#if !NCURSES_OPAQUE
#define getattrs(win)		NCURSES_CAST(int, NCURSES_OK_ADDR(win) ? (win)->_attrs : A_NORMAL)
#define getcurx(win)		(NCURSES_OK_ADDR(win) ? (win)->_curx : ERR)
#define getcury(win)		(NCURSES_OK_ADDR(win) ? (win)->_cury : ERR)
#define getbegx(win)		(NCURSES_OK_ADDR(win) ? (win)->_begx : ERR)
#define getbegy(win)		(NCURSES_OK_ADDR(win) ? (win)->_begy : ERR)
#define getmaxx(win)		(NCURSES_OK_ADDR(win) ? ((win)->_maxx + 1) : ERR)
#define getmaxy(win)		(NCURSES_OK_ADDR(win) ? ((win)->_maxy + 1) : ERR)
#define getparx(win)		(NCURSES_OK_ADDR(win) ? (win)->_parx : ERR)
#define getpary(win)		(NCURSES_OK_ADDR(win) ? (win)->_pary : ERR)
#endif /* NCURSES_OPAQUE */

#define wstandout(win)		(wattrset(win,A_STANDOUT))
#define wstandend(win)		(wattrset(win,A_NORMAL))

#define wattron(win,at)		wattr_on(win, NCURSES_CAST(attr_t, at), NULL)
#define wattroff(win,at)	wattr_off(win, NCURSES_CAST(attr_t, at), NULL)

#if !NCURSES_OPAQUE
#if NCURSES_WATTR_MACROS
#if NCURSES_WIDECHAR && 1
#define wattrset(win,at) \
	(NCURSES_OK_ADDR(win) \
	  ? ((win)->_color = NCURSES_CAST(int, PAIR_NUMBER(at)), \
	     (win)->_attrs = NCURSES_CAST(attr_t, at), \
	     OK) \
	  : ERR)
#else
#define wattrset(win,at) \
	(NCURSES_OK_ADDR(win) \
	  ? ((win)->_attrs = NCURSES_CAST(attr_t, at), \
	     OK) \
	  : ERR)
#endif
#endif /* NCURSES_WATTR_MACROS */
#endif /* NCURSES_OPAQUE */

#define scroll(win)		wscrl(win,1)

#define touchwin(win)		wtouchln((win), 0, getmaxy(win), 1)
#define touchline(win, s, c)	wtouchln((win), s, c, 1)
#define untouchwin(win)		wtouchln((win), 0, getmaxy(win), 0)

#define box(win, v, h)		wborder(win, v, v, h, h, 0, 0, 0, 0)
#define border(ls, rs, ts, bs, tl, tr, bl, br)	wborder(stdscr, ls, rs, ts, bs, tl, tr, bl, br)
#define hline(ch, n)		whline(stdscr, ch, (n))
#define vline(ch, n)		wvline(stdscr, ch, (n))

#define winstr(w, s)		winnstr(w, s, -1)
#define winchstr(w, s)		winchnstr(w, s, -1)
#define winsstr(w, s)		winsnstr(w, s, -1)

#if !NCURSES_OPAQUE
#define redrawwin(win)		wredrawln(win, 0, (NCURSES_OK_ADDR(win) ? (win)->_maxy+1 : -1))
#endif /* NCURSES_OPAQUE */

#define waddstr(win,str)	waddnstr(win,str,-1)
#define waddchstr(win,str)	waddchnstr(win,str,-1)

/*
 * These apply to the first 256 color pairs.
 */
#define COLOR_PAIR(n)	(NCURSES_BITS((n), 0) & A_COLOR)
#define PAIR_NUMBER(a)	(NCURSES_CAST(int,((NCURSES_CAST(unsigned long,(a)) & A_COLOR) >> NCURSES_ATTR_SHIFT)))

/*
 * pseudo functions for standard screen
 */

#define addch(ch)		waddch(stdscr,(ch))
#define addchnstr(str,n)	waddchnstr(stdscr,(str),(n))
#define addchstr(str)		waddchstr(stdscr,(str))
#define addnstr(str,n)		waddnstr(stdscr,(str),(n))
#define addstr(str)		waddnstr(stdscr,(str),-1)
#define attr_get(ap,cp,o)	wattr_get(stdscr,(ap),(cp),(o))
#define attr_off(a,o)		wattr_off(stdscr,(a),(o))
#define attr_on(a,o)		wattr_on(stdscr,(a),(o))
#define attr_set(a,c,o)		wattr_set(stdscr,(a),(c),(o))
#define attroff(at)		wattroff(stdscr,(at))
#define attron(at)		wattron(stdscr,(at))
#define attrset(at)		wattrset(stdscr,(at))
#define bkgd(ch)		wbkgd(stdscr,(ch))
#define bkgdset(ch)		wbkgdset(stdscr,(ch))
#define chgat(n,a,c,o)		wchgat(stdscr,(n),(a),(c),(o))
#define clear()			wclear(stdscr)
#define clrtobot()		wclrtobot(stdscr)
#define clrtoeol()		wclrtoeol(stdscr)
#define color_set(c,o)		wcolor_set(stdscr,(c),(o))
#define delch()			wdelch(stdscr)
#define deleteln()		winsdelln(stdscr,-1)
#define echochar(c)		wechochar(stdscr,(c))
#define erase()			werase(stdscr)
#define getch()			wgetch(stdscr)
#define getstr(str)		wgetstr(stdscr,(str))
#define inch()			winch(stdscr)
#define inchnstr(s,n)		winchnstr(stdscr,(s),(n))
#define inchstr(s)		winchstr(stdscr,(s))
#define innstr(s,n)		winnstr(stdscr,(s),(n))
#define insch(c)		winsch(stdscr,(c))
#define insdelln(n)		winsdelln(stdscr,(n))
#define insertln()		winsdelln(stdscr,1)
#define insnstr(s,n)		winsnstr(stdscr,(s),(n))
#define insstr(s)		winsstr(stdscr,(s))
#define instr(s)		winstr(stdscr,(s))
#define move(y,x)		wmove(stdscr,(y),(x))
#define refresh()		wrefresh(stdscr)
#define scrl(n)			wscrl(stdscr,(n))
#define setscrreg(t,b)		wsetscrreg(stdscr,(t),(b))
#define standend()		wstandend(stdscr)
#define standout()		wstandout(stdscr)
#define timeout(delay)		wtimeout(stdscr,(delay))
#define wdeleteln(win)		winsdelln(win,-1)
#define winsertln(win)		winsdelln(win,1)

/*
 * mv functions
 */

#define mvwaddch(win,y,x,ch)		(wmove((win),(y),(x)) == ERR ? ERR : waddch((win),(ch)))
#define mvwaddchnstr(win,y,x,str,n)	(wmove((win),(y),(x)) == ERR ? ERR : waddchnstr((win),(str),(n)))
#define mvwaddchstr(win,y,x,str)	(wmove((win),(y),(x)) == ERR ? ERR : waddchnstr((win),(str),-1))
#define mvwaddnstr(win,y,x,str,n)	(wmove((win),(y),(x)) == ERR ? ERR : waddnstr((win),(str),(n)))
#define mvwaddstr(win,y,x,str)		(wmove((win),(y),(x)) == ERR ? ERR : waddnstr((win),(str),-1))
#define mvwchgat(win,y,x,n,a,c,o)	(wmove((win),(y),(x)) == ERR ? ERR : wchgat((win),(n),(a),(c),(o)))
#define mvwdelch(win,y,x)		(wmove((win),(y),(x)) == ERR ? ERR : wdelch(win))
#define mvwgetch(win,y,x)		(wmove((win),(y),(x)) == ERR ? ERR : wgetch(win))
#define mvwgetnstr(win,y,x,str,n)	(wmove((win),(y),(x)) == ERR ? ERR : wgetnstr((win),(str),(n)))
#define mvwgetstr(win,y,x,str)		(wmove((win),(y),(x)) == ERR ? ERR : wgetstr((win),(str)))
#define mvwhline(win,y,x,c,n)		(wmove((win),(y),(x)) == ERR ? ERR : whline((win),(c),(n)))
#define mvwinch(win,y,x)		(wmove((win),(y),(x)) == ERR ? NCURSES_CAST(chtype, ERR) : winch(win))
#define mvwinchnstr(win,y,x,s,n)	(wmove((win),(y),(x)) == ERR ? ERR : winchnstr((win),(s),(n)))
#define mvwinchstr(win,y,x,s)		(wmove((win),(y),(x)) == ERR ? ERR : winchstr((win),(s)))
#define mvwinnstr(win,y,x,s,n)		(wmove((win),(y),(x)) == ERR ? ERR : winnstr((win),(s),(n)))
#define mvwinsch(win,y,x,c)		(wmove((win),(y),(x)) == ERR ? ERR : winsch((win),(c)))
#define mvwinsnstr(win,y,x,s,n)		(wmove((win),(y),(x)) == ERR ? ERR : winsnstr((win),(s),(n)))
#define mvwinsstr(win,y,x,s)		(wmove((win),(y),(x)) == ERR ? ERR : winsstr((win),(s)))
#define mvwinstr(win,y,x,s)		(wmove((win),(y),(x)) == ERR ? ERR : winstr((win),(s)))
#define mvwvline(win,y,x,c,n)		(wmove((win),(y),(x)) == ERR ? ERR : wvline((win),(c),(n)))

#define mvaddch(y,x,ch)			mvwaddch(stdscr,(y),(x),(ch))
#define mvaddchnstr(y,x,str,n)		mvwaddchnstr(stdscr,(y),(x),(str),(n))
#define mvaddchstr(y,x,str)		mvwaddchstr(stdscr,(y),(x),(str))
#define mvaddnstr(y,x,str,n)		mvwaddnstr(stdscr,(y),(x),(str),(n))
#define mvaddstr(y,x,str)		mvwaddstr(stdscr,(y),(x),(str))
#define mvchgat(y,x,n,a,c,o)		mvwchgat(stdscr,(y),(x),(n),(a),(c),(o))
#define mvdelch(y,x)			mvwdelch(stdscr,(y),(x))
#define mvgetch(y,x)			mvwgetch(stdscr,(y),(x))
#define mvgetnstr(y,x,str,n)		mvwgetnstr(stdscr,(y),(x),(str),(n))
#define mvgetstr(y,x,str)		mvwgetstr(stdscr,(y),(x),(str))
#define mvhline(y,x,c,n)		mvwhline(stdscr,(y),(x),(c),(n))
#define mvinch(y,x)			mvwinch(stdscr,(y),(x))
#define mvinchnstr(y,x,s,n)		mvwinchnstr(stdscr,(y),(x),(s),(n))
#define mvinchstr(y,x,s)		mvwinchstr(stdscr,(y),(x),(s))
#define mvinnstr(y,x,s,n)		mvwinnstr(stdscr,(y),(x),(s),(n))
#define mvinsch(y,x,c)			mvwinsch(stdscr,(y),(x),(c))
#define mvinsnstr(y,x,s,n)		mvwinsnstr(stdscr,(y),(x),(s),(n))
#define mvinsstr(y,x,s)			mvwinsstr(stdscr,(y),(x),(s))
#define mvinstr(y,x,s)			mvwinstr(stdscr,(y),(x),(s))
#define mvvline(y,x,c,n)		mvwvline(stdscr,(y),(x),(c),(n))

/*
 * Some wide-character functions can be implemented without the extensions.
 */
#if !NCURSES_OPAQUE
#define getbkgd(win)                    (NCURSES_OK_ADDR(win) ? ((win)->_bkgd) : 0)
#endif /* NCURSES_OPAQUE */

#define slk_attr_off(a,v)		((v) ? ERR : slk_attroff(a))
#define slk_attr_on(a,v)		((v) ? ERR : slk_attron(a))

#if !NCURSES_OPAQUE
#if NCURSES_WATTR_MACROS
#if NCURSES_WIDECHAR && 1
#define wattr_set(win,a,p,opts) \
	(NCURSES_OK_ADDR(win) \
	 ? ((void)((win)->_attrs = ((a) & ~A_COLOR), \
		   (win)->_color = (opts) ? *(int *)(opts) : (p)), \
	    OK) \
	 : ERR)
#define wattr_get(win,a,p,opts) \
	(NCURSES_OK_ADDR(win) \
	 ? ((void)(NCURSES_OK_ADDR(a) \
		   ? (*(a) = (win)->_attrs) \
		   : OK), \
	    (void)(NCURSES_OK_ADDR(p) \
		   ? (*(p) = (NCURSES_PAIRS_T) (win)->_color) \
		   : OK), \
	    (void)(NCURSES_OK_ADDR(opts) \
		   ? (*(int *)(opts) = (win)->_color) \
		   : OK), \
	    OK) \
	 : ERR)
#else /* !(NCURSES_WIDECHAR && NCURSES_EXE_COLORS) */
#define wattr_set(win,a,p,opts) \
	 (NCURSES_OK_ADDR(win) \
	  ? ((void)((win)->_attrs = (((a) & ~A_COLOR) | \
				     (attr_t)COLOR_PAIR(p))), \
	     OK) \
	  : ERR)
#define wattr_get(win,a,p,opts) \
	(NCURSES_OK_ADDR(win) \
	 ? ((void)(NCURSES_OK_ADDR(a) \
		   ? (*(a) = (win)->_attrs) \
		   : OK), \
	    (void)(NCURSES_OK_ADDR(p) \
		   ? (*(p) = (NCURSES_PAIRS_T) PAIR_NUMBER((win)->_attrs)) \
		   : OK), \
	    OK) \
	 : ERR)
#endif /* (NCURSES_WIDECHAR && NCURSES_EXE_COLORS) */
#endif /* NCURSES_WATTR_MACROS */
#endif /* NCURSES_OPAQUE */

/*
 * X/Open curses deprecates SVr4 vwprintw/vwscanw, which are supposed to use
 * varargs.h.  It adds new calls vw_printw/vw_scanw, which are supposed to
 * use POSIX stdarg.h.  The ncurses versions of vwprintw/vwscanw already
 * use stdarg.h, so...
 */
/* define vw_printw		vwprintw */
/* define vw_scanw		vwscanw */

/*
 * Export fallback function for use in C++ binding.
 */
#if !1
#define vsscanf(a,b,c) _nc_vsscanf(a,b,c)
NCURSES_EXPORT(int) vsscanf(const char *, const char *, va_list);
#endif

/*
 * These macros are extensions - not in X/Open Curses.
 */
#if 1
#if !NCURSES_OPAQUE
#define is_cleared(win)		(NCURSES_OK_ADDR(win) ? (win)->_clear : FALSE)
#define is_idcok(win)		(NCURSES_OK_ADDR(win) ? (win)->_idcok : FALSE)
#define is_idlok(win)		(NCURSES_OK_ADDR(win) ? (win)->_idlok : FALSE)
#define is_immedok(win)		(NCURSES_OK_ADDR(win) ? (win)->_immed : FALSE)
#define is_keypad(win)		(NCURSES_OK_ADDR(win) ? (win)->_use_keypad : FALSE)
#define is_leaveok(win)		(NCURSES_OK_ADDR(win) ? (win)->_leaveok : FALSE)
#define is_nodelay(win)		(NCURSES_OK_ADDR(win) ? ((win)->_delay == 0) : FALSE)
#define is_notimeout(win)	(NCURSES_OK_ADDR(win) ? (win)->_notimeout : FALSE)
#define is_pad(win)		(NCURSES_OK_ADDR(win) ? ((win)->_flags & _ISPAD) != 0 : FALSE)
#define is_scrollok(win)	(NCURSES_OK_ADDR(win) ? (win)->_scroll : FALSE)
#define is_subwin(win)		(NCURSES_OK_ADDR(win) ? ((win)->_flags & _SUBWIN) != 0 : FALSE)
#define is_syncok(win)		(NCURSES_OK_ADDR(win) ? (win)->_sync : FALSE)
#define wgetdelay(win)		(NCURSES_OK_ADDR(win) ? (win)->_delay : 0)
#define wgetparent(win)		(NCURSES_OK_ADDR(win) ? (win)->_parent : 0)
#define wgetscrreg(win,t,b)	(NCURSES_OK_ADDR(win) ? (*(t) = (win)->_regtop, *(b) = (win)->_regbottom, OK) : ERR)
#endif
#endif

/*
 * X/Open says this returns a bool; SVr4 also checked for out-of-range line.
 * The macro provides compatibility:
 */
#define is_linetouched(w,l) ((!(w) || ((l) > getmaxy(w)) || ((l) < 0)) ? ERR : (is_linetouched)((w),(l)))

#endif /* NCURSES_NOMACROS */

/*
 * Public variables.
 *
 * Notes:
 *	a. ESCDELAY was an undocumented feature under AIX curses.
 *	   It gives the ESC expire time in milliseconds.
 *	b. ttytype is needed for backward compatibility
 */
#if NCURSES_REENTRANT

NCURSES_WRAPPED_VAR(WINDOW *, curscr);
NCURSES_WRAPPED_VAR(WINDOW *, newscr);
NCURSES_WRAPPED_VAR(WINDOW *, stdscr);
NCURSES_WRAPPED_VAR(char *, ttytype);
NCURSES_WRAPPED_VAR(int, COLORS);
NCURSES_WRAPPED_VAR(int, COLOR_PAIRS);
NCURSES_WRAPPED_VAR(int, COLS);
NCURSES_WRAPPED_VAR(int, ESCDELAY);
NCURSES_WRAPPED_VAR(int, LINES);
NCURSES_WRAPPED_VAR(int, TABSIZE);

#define curscr      NCURSES_PUBLIC_VAR(curscr())
#define newscr      NCURSES_PUBLIC_VAR(newscr())
#define stdscr      NCURSES_PUBLIC_VAR(stdscr())
#define ttytype     NCURSES_PUBLIC_VAR(ttytype())
#define COLORS      NCURSES_PUBLIC_VAR(COLORS())
#define COLOR_PAIRS NCURSES_PUBLIC_VAR(COLOR_PAIRS())
#define COLS        NCURSES_PUBLIC_VAR(COLS())
#define ESCDELAY    NCURSES_PUBLIC_VAR(ESCDELAY())
#define LINES       NCURSES_PUBLIC_VAR(LINES())
#define TABSIZE     NCURSES_PUBLIC_VAR(TABSIZE())

#else

extern NCURSES_EXPORT_VAR(WINDOW *) curscr;
extern NCURSES_EXPORT_VAR(WINDOW *) newscr;
extern NCURSES_EXPORT_VAR(WINDOW *) stdscr;
extern NCURSES_EXPORT_VAR(char) ttytype[];
extern NCURSES_EXPORT_VAR(int) COLORS;
extern NCURSES_EXPORT_VAR(int) COLOR_PAIRS;
extern NCURSES_EXPORT_VAR(int) COLS;
extern NCURSES_EXPORT_VAR(int) ESCDELAY;
extern NCURSES_EXPORT_VAR(int) LINES;
extern NCURSES_EXPORT_VAR(int) TABSIZE;

#endif

/*
 * Pseudo-character tokens outside ASCII range.  The curses wgetch() function
 * will return any given one of these only if the corresponding k- capability
 * is defined in your terminal's terminfo entry.
 *
 * Some keys (KEY_A1, etc) are arranged like this:
 *	a1     up    a3
 *	left   b2    right
 *	c1     down  c3
 *
 * A few key codes do not depend upon the terminfo entry.
 */
#define KEY_CODE_YES	0400		/* A wchar_t contains a key code */
#define KEY_MIN		0401		/* Minimum curses key */
#define KEY_BREAK	0401		/* Break key (unreliable) */
#define KEY_SRESET	0530		/* Soft (partial) reset (unreliable) */
#define KEY_RESET	0531		/* Reset or hard reset (unreliable) */
/*
 * These definitions were generated by ./MKkey_defs.sh thirdparty/ncurses/ncurses-6.2/include/Caps thirdparty/ncurses/ncurses-6.2/include/Caps-ncurses
 */
#define KEY_DOWN	0402		/* down-arrow key */
#define KEY_UP		0403		/* up-arrow key */
#define KEY_LEFT	0404		/* left-arrow key */
#define KEY_RIGHT	0405		/* right-arrow key */
#define KEY_HOME	0406		/* home key */
#define KEY_BACKSPACE	0407		/* backspace key */
#define KEY_F0		0410		/* Function keys.  Space for 64 */
#define KEY_F(n)	(KEY_F0+(n))	/* Value of function key n */
#define KEY_DL		0510		/* delete-line key */
#define KEY_IL		0511		/* insert-line key */
#define KEY_DC		0512		/* delete-character key */
#define KEY_IC		0513		/* insert-character key */
#define KEY_EIC		0514		/* sent by rmir or smir in insert mode */
#define KEY_CLEAR	0515		/* clear-screen or erase key */
#define KEY_EOS		0516		/* clear-to-end-of-screen key */
#define KEY_EOL		0517		/* clear-to-end-of-line key */
#define KEY_SF		0520		/* scroll-forward key */
#define KEY_SR		0521		/* scroll-backward key */
#define KEY_NPAGE	0522		/* next-page key */
#define KEY_PPAGE	0523		/* previous-page key */
#define KEY_STAB	0524		/* set-tab key */
#define KEY_CTAB	0525		/* clear-tab key */
#define KEY_CATAB	0526		/* clear-all-tabs key */
#define KEY_ENTER	0527		/* enter/send key */
#define KEY_PRINT	0532		/* print key */
#define KEY_LL		0533		/* lower-left key (home down) */
#define KEY_A1		0534		/* upper left of keypad */
#define KEY_A3		0535		/* upper right of keypad */
#define KEY_B2		0536		/* center of keypad */
#define KEY_C1		0537		/* lower left of keypad */
#define KEY_C3		0540		/* lower right of keypad */
#define KEY_BTAB	0541		/* back-tab key */
#define KEY_BEG		0542		/* begin key */
#define KEY_CANCEL	0543		/* cancel key */
#define KEY_CLOSE	0544		/* close key */
#define KEY_COMMAND	0545		/* command key */
#define KEY_COPY	0546		/* copy key */
#define KEY_CREATE	0547		/* create key */
#define KEY_END		0550		/* end key */
#define KEY_EXIT	0551		/* exit key */
#define KEY_FIND	0552		/* find key */
#define KEY_HELP	0553		/* help key */
#define KEY_MARK	0554		/* mark key */
#define KEY_MESSAGE	0555		/* message key */
#define KEY_MOVE	0556		/* move key */
#define KEY_NEXT	0557		/* next key */
#define KEY_OPEN	0560		/* open key */
#define KEY_OPTIONS	0561		/* options key */
#define KEY_PREVIOUS	0562		/* previous key */
#define KEY_REDO	0563		/* redo key */
#define KEY_REFERENCE	0564		/* reference key */
#define KEY_REFRESH	0565		/* refresh key */
#define KEY_REPLACE	0566		/* replace key */
#define KEY_RESTART	0567		/* restart key */
#define KEY_RESUME	0570		/* resume key */
#define KEY_SAVE	0571		/* save key */
#define KEY_SBEG	0572		/* shifted begin key */
#define KEY_SCANCEL	0573		/* shifted cancel key */
#define KEY_SCOMMAND	0574		/* shifted command key */
#define KEY_SCOPY	0575		/* shifted copy key */
#define KEY_SCREATE	0576		/* shifted create key */
#define KEY_SDC		0577		/* shifted delete-character key */
#define KEY_SDL		0600		/* shifted delete-line key */
#define KEY_SELECT	0601		/* select key */
#define KEY_SEND	0602		/* shifted end key */
#define KEY_SEOL	0603		/* shifted clear-to-end-of-line key */
#define KEY_SEXIT	0604		/* shifted exit key */
#define KEY_SFIND	0605		/* shifted find key */
#define KEY_SHELP	0606		/* shifted help key */
#define KEY_SHOME	0607		/* shifted home key */
#define KEY_SIC		0610		/* shifted insert-character key */
#define KEY_SLEFT	0611		/* shifted left-arrow key */
#define KEY_SMESSAGE	0612		/* shifted message key */
#define KEY_SMOVE	0613		/* shifted move key */
#define KEY_SNEXT	0614		/* shifted next key */
#define KEY_SOPTIONS	0615		/* shifted options key */
#define KEY_SPREVIOUS	0616		/* shifted previous key */
#define KEY_SPRINT	0617		/* shifted print key */
#define KEY_SREDO	0620		/* shifted redo key */
#define KEY_SREPLACE	0621		/* shifted replace key */
#define KEY_SRIGHT	0622		/* shifted right-arrow key */
#define KEY_SRSUME	0623		/* shifted resume key */
#define KEY_SSAVE	0624		/* shifted save key */
#define KEY_SSUSPEND	0625		/* shifted suspend key */
#define KEY_SUNDO	0626		/* shifted undo key */
#define KEY_SUSPEND	0627		/* suspend key */
#define KEY_UNDO	0630		/* undo key */
#define KEY_MOUSE	0631		/* Mouse event has occurred */
#define KEY_RESIZE	0632		/* Terminal resize event */
#define KEY_EVENT	0633		/* We were interrupted by an event */

#define KEY_MAX		0777		/* Maximum key value is 0633 */
/* $$Id: curses.wide,v 1.50 2017/03/26 16:05:21 tom Exp $$ */
/*
 * vile:cmode:
 * This file is part of ncurses, designed to be appended after curses.h.in
 * (see that file for the relevant copyright).
 */
#define _XOPEN_CURSES 1

#if NCURSES_WIDECHAR

extern NCURSES_EXPORT_VAR(cchar_t *) _nc_wacs;

#define NCURSES_WACS(c)	(&_nc_wacs[NCURSES_CAST(unsigned char,(c))])

#define WACS_BSSB	NCURSES_WACS('l')
#define WACS_SSBB	NCURSES_WACS('m')
#define WACS_BBSS	NCURSES_WACS('k')
#define WACS_SBBS	NCURSES_WACS('j')
#define WACS_SBSS	NCURSES_WACS('u')
#define WACS_SSSB	NCURSES_WACS('t')
#define WACS_SSBS	NCURSES_WACS('v')
#define WACS_BSSS	NCURSES_WACS('w')
#define WACS_BSBS	NCURSES_WACS('q')
#define WACS_SBSB	NCURSES_WACS('x')
#define WACS_SSSS	NCURSES_WACS('n')

#define WACS_ULCORNER	WACS_BSSB
#define WACS_LLCORNER	WACS_SSBB
#define WACS_URCORNER	WACS_BBSS
#define WACS_LRCORNER	WACS_SBBS
#define WACS_RTEE	WACS_SBSS
#define WACS_LTEE	WACS_SSSB
#define WACS_BTEE	WACS_SSBS
#define WACS_TTEE	WACS_BSSS
#define WACS_HLINE	WACS_BSBS
#define WACS_VLINE	WACS_SBSB
#define WACS_PLUS	WACS_SSSS

#define WACS_S1		NCURSES_WACS('o') /* scan line 1 */
#define WACS_S9 	NCURSES_WACS('s') /* scan line 9 */
#define WACS_DIAMOND	NCURSES_WACS('`') /* diamond */
#define WACS_CKBOARD	NCURSES_WACS('a') /* checker board */
#define WACS_DEGREE	NCURSES_WACS('f') /* degree symbol */
#define WACS_PLMINUS	NCURSES_WACS('g') /* plus/minus */
#define WACS_BULLET	NCURSES_WACS('~') /* bullet */

	/* Teletype 5410v1 symbols */
#define WACS_LARROW	NCURSES_WACS(',') /* arrow left */
#define WACS_RARROW	NCURSES_WACS('+') /* arrow right */
#define WACS_DARROW	NCURSES_WACS('.') /* arrow down */
#define WACS_UARROW	NCURSES_WACS('-') /* arrow up */
#define WACS_BOARD	NCURSES_WACS('h') /* board of squares */
#define WACS_LANTERN	NCURSES_WACS('i') /* lantern symbol */
#define WACS_BLOCK	NCURSES_WACS('0') /* solid square block */

	/* ncurses extensions */
#define WACS_S3		NCURSES_WACS('p') /* scan line 3 */
#define WACS_S7		NCURSES_WACS('r') /* scan line 7 */
#define WACS_LEQUAL	NCURSES_WACS('y') /* less/equal */
#define WACS_GEQUAL	NCURSES_WACS('z') /* greater/equal */
#define WACS_PI		NCURSES_WACS('{') /* Pi */
#define WACS_NEQUAL	NCURSES_WACS('|') /* not equal */
#define WACS_STERLING	NCURSES_WACS('}') /* UK pound sign */

	/* double lines */
#define WACS_BDDB	NCURSES_WACS('C')
#define WACS_DDBB	NCURSES_WACS('D')
#define WACS_BBDD	NCURSES_WACS('B')
#define WACS_DBBD	NCURSES_WACS('A')
#define WACS_DBDD	NCURSES_WACS('G')
#define WACS_DDDB	NCURSES_WACS('F')
#define WACS_DDBD	NCURSES_WACS('H')
#define WACS_BDDD	NCURSES_WACS('I')
#define WACS_BDBD	NCURSES_WACS('R')
#define WACS_DBDB	NCURSES_WACS('Y')
#define WACS_DDDD	NCURSES_WACS('E')

#define WACS_D_ULCORNER	WACS_BDDB
#define WACS_D_LLCORNER	WACS_DDBB
#define WACS_D_URCORNER	WACS_BBDD
#define WACS_D_LRCORNER	WACS_DBBD
#define WACS_D_RTEE	WACS_DBDD
#define WACS_D_LTEE	WACS_DDDB
#define WACS_D_BTEE	WACS_DDBD
#define WACS_D_TTEE	WACS_BDDD
#define WACS_D_HLINE	WACS_BDBD
#define WACS_D_VLINE	WACS_DBDB
#define WACS_D_PLUS	WACS_DDDD

	/* thick lines */
#define WACS_BTTB	NCURSES_WACS('L')
#define WACS_TTBB	NCURSES_WACS('M')
#define WACS_BBTT	NCURSES_WACS('K')
#define WACS_TBBT	NCURSES_WACS('J')
#define WACS_TBTT	NCURSES_WACS('U')
#define WACS_TTTB	NCURSES_WACS('T')
#define WACS_TTBT	NCURSES_WACS('V')
#define WACS_BTTT	NCURSES_WACS('W')
#define WACS_BTBT	NCURSES_WACS('Q')
#define WACS_TBTB	NCURSES_WACS('X')
#define WACS_TTTT	NCURSES_WACS('N')

#define WACS_T_ULCORNER	WACS_BTTB
#define WACS_T_LLCORNER	WACS_TTBB
#define WACS_T_URCORNER	WACS_BBTT
#define WACS_T_LRCORNER	WACS_TBBT
#define WACS_T_RTEE	WACS_TBTT
#define WACS_T_LTEE	WACS_TTTB
#define WACS_T_BTEE	WACS_TTBT
#define WACS_T_TTEE	WACS_BTTT
#define WACS_T_HLINE	WACS_BTBT
#define WACS_T_VLINE	WACS_TBTB
#define WACS_T_PLUS	WACS_TTTT

/*
 * Function prototypes for wide-character operations.
 *
 * "generated" comments should include ":WIDEC" to make the corresponding
 * functions ifdef'd in lib_gen.c
 *
 * "implemented" comments do not need this marker.
 */

extern NCURSES_EXPORT(int) add_wch (const cchar_t *);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) add_wchnstr (const cchar_t *, int);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) add_wchstr (const cchar_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) addnwstr (const wchar_t *, int);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) addwstr (const wchar_t *);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) bkgrnd (const cchar_t *);			/* generated:WIDEC */
extern NCURSES_EXPORT(void) bkgrndset (const cchar_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) border_set (const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*); /* generated:WIDEC */
extern NCURSES_EXPORT(int) box_set (WINDOW *, const cchar_t *, const cchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) echo_wchar (const cchar_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) erasewchar (wchar_t*);			/* implemented */
extern NCURSES_EXPORT(int) get_wch (wint_t *);				/* generated:WIDEC */
extern NCURSES_EXPORT(int) get_wstr (wint_t *);				/* generated:WIDEC */
extern NCURSES_EXPORT(int) getbkgrnd (cchar_t *);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) getcchar (const cchar_t *, wchar_t*, attr_t*, NCURSES_PAIRS_T*, void*);	/* implemented */
extern NCURSES_EXPORT(int) getn_wstr (wint_t *, int);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) hline_set (const cchar_t *, int);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) in_wch (cchar_t *);				/* generated:WIDEC */
extern NCURSES_EXPORT(int) in_wchnstr (cchar_t *, int);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) in_wchstr (cchar_t *);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) innwstr (wchar_t *, int);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) ins_nwstr (const wchar_t *, int);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) ins_wch (const cchar_t *);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) ins_wstr (const wchar_t *);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) inwstr (wchar_t *);				/* generated:WIDEC */
extern NCURSES_EXPORT(NCURSES_CONST char*) key_name (wchar_t);		/* implemented */
extern NCURSES_EXPORT(int) killwchar (wchar_t *);			/* implemented */
extern NCURSES_EXPORT(int) mvadd_wch (int, int, const cchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvadd_wchnstr (int, int, const cchar_t *, int);/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvadd_wchstr (int, int, const cchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvaddnwstr (int, int, const wchar_t *, int);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvaddwstr (int, int, const wchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvget_wch (int, int, wint_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvget_wstr (int, int, wint_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvgetn_wstr (int, int, wint_t *, int);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvhline_set (int, int, const cchar_t *, int);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvin_wch (int, int, cchar_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvin_wchnstr (int, int, cchar_t *, int);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvin_wchstr (int, int, cchar_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvinnwstr (int, int, wchar_t *, int);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvins_nwstr (int, int, const wchar_t *, int);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvins_wch (int, int, const cchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvins_wstr (int, int, const wchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvinwstr (int, int, wchar_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvvline_set (int, int, const cchar_t *, int);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwadd_wch (WINDOW *, int, int, const cchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwadd_wchnstr (WINDOW *, int, int, const cchar_t *, int); /* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwadd_wchstr (WINDOW *, int, int, const cchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwaddnwstr (WINDOW *, int, int, const wchar_t *, int);/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwaddwstr (WINDOW *, int, int, const wchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwget_wch (WINDOW *, int, int, wint_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwget_wstr (WINDOW *, int, int, wint_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwgetn_wstr (WINDOW *, int, int, wint_t *, int);/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwhline_set (WINDOW *, int, int, const cchar_t *, int);/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwin_wch (WINDOW *, int, int, cchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwin_wchnstr (WINDOW *, int,int, cchar_t *,int);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwin_wchstr (WINDOW *, int, int, cchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwinnwstr (WINDOW *, int, int, wchar_t *, int);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwins_nwstr (WINDOW *, int,int, const wchar_t *,int); /* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwins_wch (WINDOW *, int, int, const cchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwins_wstr (WINDOW *, int, int, const wchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwinwstr (WINDOW *, int, int, wchar_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) mvwvline_set (WINDOW *, int,int, const cchar_t *,int); /* generated:WIDEC */
extern NCURSES_EXPORT(int) pecho_wchar (WINDOW *, const cchar_t *);	/* implemented */
extern NCURSES_EXPORT(int) setcchar (cchar_t *, const wchar_t *, const attr_t, NCURSES_PAIRS_T, const void *);	/* implemented */
extern NCURSES_EXPORT(int) slk_wset (int, const wchar_t *, int);	/* implemented */
extern NCURSES_EXPORT(attr_t) term_attrs (void);			/* implemented */
extern NCURSES_EXPORT(int) unget_wch (const wchar_t);			/* implemented */
extern NCURSES_EXPORT(int) vid_attr (attr_t, NCURSES_PAIRS_T, void *);		/* implemented */
extern NCURSES_EXPORT(int) vid_puts (attr_t, NCURSES_PAIRS_T, void *, NCURSES_OUTC); /* implemented */
extern NCURSES_EXPORT(int) vline_set (const cchar_t *, int);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) wadd_wch (WINDOW *,const cchar_t *);		/* implemented */
extern NCURSES_EXPORT(int) wadd_wchnstr (WINDOW *,const cchar_t *,int);	/* implemented */
extern NCURSES_EXPORT(int) wadd_wchstr (WINDOW *,const cchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) waddnwstr (WINDOW *,const wchar_t *,int);	/* implemented */
extern NCURSES_EXPORT(int) waddwstr (WINDOW *,const wchar_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) wbkgrnd (WINDOW *,const cchar_t *);		/* implemented */
extern NCURSES_EXPORT(void) wbkgrndset (WINDOW *,const cchar_t *);	/* implemented */
extern NCURSES_EXPORT(int) wborder_set (WINDOW *,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*);	/* implemented */
extern NCURSES_EXPORT(int) wecho_wchar (WINDOW *, const cchar_t *);	/* implemented */
extern NCURSES_EXPORT(int) wget_wch (WINDOW *, wint_t *);		/* implemented */
extern NCURSES_EXPORT(int) wget_wstr (WINDOW *, wint_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) wgetbkgrnd (WINDOW *, cchar_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) wgetn_wstr (WINDOW *, wint_t *, int);	/* implemented */
extern NCURSES_EXPORT(int) whline_set (WINDOW *, const cchar_t *, int);	/* implemented */
extern NCURSES_EXPORT(int) win_wch (WINDOW *, cchar_t *);		/* implemented */
extern NCURSES_EXPORT(int) win_wchnstr (WINDOW *, cchar_t *, int);	/* implemented */
extern NCURSES_EXPORT(int) win_wchstr (WINDOW *, cchar_t *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) winnwstr (WINDOW *, wchar_t *, int);		/* implemented */
extern NCURSES_EXPORT(int) wins_nwstr (WINDOW *, const wchar_t *, int);	/* implemented */
extern NCURSES_EXPORT(int) wins_wch (WINDOW *, const cchar_t *);	/* implemented */
extern NCURSES_EXPORT(int) wins_wstr (WINDOW *, const wchar_t *);	/* generated:WIDEC */
extern NCURSES_EXPORT(int) winwstr (WINDOW *, wchar_t *);		/* implemented */
extern NCURSES_EXPORT(wchar_t*) wunctrl (cchar_t *);			/* implemented */
extern NCURSES_EXPORT(int) wvline_set (WINDOW *, const cchar_t *, int);	/* implemented */

#if NCURSES_SP_FUNCS
extern NCURSES_EXPORT(attr_t) NCURSES_SP_NAME(term_attrs) (SCREEN*);		/* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(unget_wch) (SCREEN*, const wchar_t);	/* implemented:SP_FUNC */
extern NCURSES_EXPORT(wchar_t*) NCURSES_SP_NAME(wunctrl) (SCREEN*, cchar_t *);	/* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(vid_attr) (SCREEN*, attr_t, NCURSES_PAIRS_T, void *);	/* implemented:SP_FUNC */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(vid_puts) (SCREEN*, attr_t, NCURSES_PAIRS_T, void *, NCURSES_SP_OUTC);	/* implemented:SP_FUNC */
#endif

#ifndef NCURSES_NOMACROS

/*
 * XSI curses macros for XPG4 conformance.
 */
#define add_wch(c)			wadd_wch(stdscr,(c))
#define add_wchnstr(str,n)		wadd_wchnstr(stdscr,(str),(n))
#define add_wchstr(str)			wadd_wchstr(stdscr,(str))
#define addnwstr(wstr,n)		waddnwstr(stdscr,(wstr),(n))
#define addwstr(wstr)			waddwstr(stdscr,(wstr))
#define bkgrnd(c)			wbkgrnd(stdscr,(c))
#define bkgrndset(c)			wbkgrndset(stdscr,(c))
#define border_set(l,r,t,b,tl,tr,bl,br) wborder_set(stdscr,(l),(r),(t),(b),tl,tr,bl,br)
#define box_set(w,v,h)			wborder_set((w),(v),(v),(h),(h),0,0,0,0)
#define echo_wchar(c)			wecho_wchar(stdscr,(c))
#define get_wch(c)			wget_wch(stdscr,(c))
#define get_wstr(t)			wget_wstr(stdscr,(t))
#define getbkgrnd(wch)			wgetbkgrnd(stdscr,(wch))
#define getn_wstr(t,n)			wgetn_wstr(stdscr,(t),(n))
#define hline_set(c,n)			whline_set(stdscr,(c),(n))
#define in_wch(c)			win_wch(stdscr,(c))
#define in_wchnstr(c,n)			win_wchnstr(stdscr,(c),(n))
#define in_wchstr(c)			win_wchstr(stdscr,(c))
#define innwstr(c,n)			winnwstr(stdscr,(c),(n))
#define ins_nwstr(t,n)			wins_nwstr(stdscr,(t),(n))
#define ins_wch(c)			wins_wch(stdscr,(c))
#define ins_wstr(t)			wins_wstr(stdscr,(t))
#define inwstr(c)			winwstr(stdscr,(c))
#define vline_set(c,n)			wvline_set(stdscr,(c),(n))
#define wadd_wchstr(win,str)		wadd_wchnstr((win),(str),-1)
#define waddwstr(win,wstr)		waddnwstr((win),(wstr),-1)
#define wget_wstr(w,t)			wgetn_wstr((w),(t),-1)
#define win_wchstr(w,c)			win_wchnstr((w),(c),-1)
#define wins_wstr(w,t)			wins_nwstr((w),(t),-1)

#if !NCURSES_OPAQUE
#define wgetbkgrnd(win,wch)		(NCURSES_OK_ADDR(wch) ? ((win) ? (*(wch) = (win)->_bkgrnd) : *(wch), OK) : ERR)
#endif

#define mvadd_wch(y,x,c)		mvwadd_wch(stdscr,(y),(x),(c))
#define mvadd_wchnstr(y,x,s,n)		mvwadd_wchnstr(stdscr,(y),(x),(s),(n))
#define mvadd_wchstr(y,x,s)		mvwadd_wchstr(stdscr,(y),(x),(s))
#define mvaddnwstr(y,x,wstr,n)		mvwaddnwstr(stdscr,(y),(x),(wstr),(n))
#define mvaddwstr(y,x,wstr)		mvwaddwstr(stdscr,(y),(x),(wstr))
#define mvget_wch(y,x,c)		mvwget_wch(stdscr,(y),(x),(c))
#define mvget_wstr(y,x,t)		mvwget_wstr(stdscr,(y),(x),(t))
#define mvgetn_wstr(y,x,t,n)		mvwgetn_wstr(stdscr,(y),(x),(t),(n))
#define mvhline_set(y,x,c,n)		mvwhline_set(stdscr,(y),(x),(c),(n))
#define mvin_wch(y,x,c)			mvwin_wch(stdscr,(y),(x),(c))
#define mvin_wchnstr(y,x,c,n)		mvwin_wchnstr(stdscr,(y),(x),(c),(n))
#define mvin_wchstr(y,x,c)		mvwin_wchstr(stdscr,(y),(x),(c))
#define mvinnwstr(y,x,c,n)		mvwinnwstr(stdscr,(y),(x),(c),(n))
#define mvins_nwstr(y,x,t,n)		mvwins_nwstr(stdscr,(y),(x),(t),(n))
#define mvins_wch(y,x,c)		mvwins_wch(stdscr,(y),(x),(c))
#define mvins_wstr(y,x,t)		mvwins_wstr(stdscr,(y),(x),(t))
#define mvinwstr(y,x,c)			mvwinwstr(stdscr,(y),(x),(c))
#define mvvline_set(y,x,c,n)		mvwvline_set(stdscr,(y),(x),(c),(n))

#define mvwadd_wch(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : wadd_wch((win),(c)))
#define mvwadd_wchnstr(win,y,x,s,n)	(wmove(win,(y),(x)) == ERR ? ERR : wadd_wchnstr((win),(s),(n)))
#define mvwadd_wchstr(win,y,x,s)	(wmove(win,(y),(x)) == ERR ? ERR : wadd_wchstr((win),(s)))
#define mvwaddnwstr(win,y,x,wstr,n)	(wmove(win,(y),(x)) == ERR ? ERR : waddnwstr((win),(wstr),(n)))
#define mvwaddwstr(win,y,x,wstr)	(wmove(win,(y),(x)) == ERR ? ERR : waddwstr((win),(wstr)))
#define mvwget_wch(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : wget_wch((win),(c)))
#define mvwget_wstr(win,y,x,t)		(wmove(win,(y),(x)) == ERR ? ERR : wget_wstr((win),(t)))
#define mvwgetn_wstr(win,y,x,t,n)	(wmove(win,(y),(x)) == ERR ? ERR : wgetn_wstr((win),(t),(n)))
#define mvwhline_set(win,y,x,c,n)	(wmove(win,(y),(x)) == ERR ? ERR : whline_set((win),(c),(n)))
#define mvwin_wch(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : win_wch((win),(c)))
#define mvwin_wchnstr(win,y,x,c,n)	(wmove(win,(y),(x)) == ERR ? ERR : win_wchnstr((win),(c),(n)))
#define mvwin_wchstr(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : win_wchstr((win),(c)))
#define mvwinnwstr(win,y,x,c,n)		(wmove(win,(y),(x)) == ERR ? ERR : winnwstr((win),(c),(n)))
#define mvwins_nwstr(win,y,x,t,n)	(wmove(win,(y),(x)) == ERR ? ERR : wins_nwstr((win),(t),(n)))
#define mvwins_wch(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : wins_wch((win),(c)))
#define mvwins_wstr(win,y,x,t)		(wmove(win,(y),(x)) == ERR ? ERR : wins_wstr((win),(t)))
#define mvwinwstr(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : winwstr((win),(c)))
#define mvwvline_set(win,y,x,c,n)	(wmove(win,(y),(x)) == ERR ? ERR : wvline_set((win),(c),(n)))

#endif /* NCURSES_NOMACROS */

#if defined(TRACE) || defined(NCURSES_TEST)
extern NCURSES_EXPORT(const char *) _nc_viswbuf(const wchar_t *);
extern NCURSES_EXPORT(const char *) _nc_viswibuf(const wint_t *);
#endif

#endif /* NCURSES_WIDECHAR */
/* $$Id: curses.tail,v 1.25 2019/12/14 22:28:39 tom Exp $$ */
/*
 * vile:cmode:
 * This file is part of ncurses, designed to be appended after curses.h.in
 * (see that file for the relevant copyright).
 */

/* mouse interface */

#if NCURSES_MOUSE_VERSION > 1
#define NCURSES_MOUSE_MASK(b,m) ((m) << (((b) - 1) * 5))
#else
#define NCURSES_MOUSE_MASK(b,m) ((m) << (((b) - 1) * 6))
#endif

#define	NCURSES_BUTTON_RELEASED	001L
#define	NCURSES_BUTTON_PRESSED	002L
#define	NCURSES_BUTTON_CLICKED	004L
#define	NCURSES_DOUBLE_CLICKED	010L
#define	NCURSES_TRIPLE_CLICKED	020L
#define	NCURSES_RESERVED_EVENT	040L

/* event masks */
#define	BUTTON1_RELEASED	NCURSES_MOUSE_MASK(1, NCURSES_BUTTON_RELEASED)
#define	BUTTON1_PRESSED		NCURSES_MOUSE_MASK(1, NCURSES_BUTTON_PRESSED)
#define	BUTTON1_CLICKED		NCURSES_MOUSE_MASK(1, NCURSES_BUTTON_CLICKED)
#define	BUTTON1_DOUBLE_CLICKED	NCURSES_MOUSE_MASK(1, NCURSES_DOUBLE_CLICKED)
#define	BUTTON1_TRIPLE_CLICKED	NCURSES_MOUSE_MASK(1, NCURSES_TRIPLE_CLICKED)

#define	BUTTON2_RELEASED	NCURSES_MOUSE_MASK(2, NCURSES_BUTTON_RELEASED)
#define	BUTTON2_PRESSED		NCURSES_MOUSE_MASK(2, NCURSES_BUTTON_PRESSED)
#define	BUTTON2_CLICKED		NCURSES_MOUSE_MASK(2, NCURSES_BUTTON_CLICKED)
#define	BUTTON2_DOUBLE_CLICKED	NCURSES_MOUSE_MASK(2, NCURSES_DOUBLE_CLICKED)
#define	BUTTON2_TRIPLE_CLICKED	NCURSES_MOUSE_MASK(2, NCURSES_TRIPLE_CLICKED)

#define	BUTTON3_RELEASED	NCURSES_MOUSE_MASK(3, NCURSES_BUTTON_RELEASED)
#define	BUTTON3_PRESSED		NCURSES_MOUSE_MASK(3, NCURSES_BUTTON_PRESSED)
#define	BUTTON3_CLICKED		NCURSES_MOUSE_MASK(3, NCURSES_BUTTON_CLICKED)
#define	BUTTON3_DOUBLE_CLICKED	NCURSES_MOUSE_MASK(3, NCURSES_DOUBLE_CLICKED)
#define	BUTTON3_TRIPLE_CLICKED	NCURSES_MOUSE_MASK(3, NCURSES_TRIPLE_CLICKED)

#define	BUTTON4_RELEASED	NCURSES_MOUSE_MASK(4, NCURSES_BUTTON_RELEASED)
#define	BUTTON4_PRESSED		NCURSES_MOUSE_MASK(4, NCURSES_BUTTON_PRESSED)
#define	BUTTON4_CLICKED		NCURSES_MOUSE_MASK(4, NCURSES_BUTTON_CLICKED)
#define	BUTTON4_DOUBLE_CLICKED	NCURSES_MOUSE_MASK(4, NCURSES_DOUBLE_CLICKED)
#define	BUTTON4_TRIPLE_CLICKED	NCURSES_MOUSE_MASK(4, NCURSES_TRIPLE_CLICKED)

/*
 * In 32 bits the version-1 scheme does not provide enough space for a 5th
 * button, unless we choose to change the ABI by omitting the reserved-events.
 */
#if NCURSES_MOUSE_VERSION > 1

#define	BUTTON5_RELEASED	NCURSES_MOUSE_MASK(5, NCURSES_BUTTON_RELEASED)
#define	BUTTON5_PRESSED		NCURSES_MOUSE_MASK(5, NCURSES_BUTTON_PRESSED)
#define	BUTTON5_CLICKED		NCURSES_MOUSE_MASK(5, NCURSES_BUTTON_CLICKED)
#define	BUTTON5_DOUBLE_CLICKED	NCURSES_MOUSE_MASK(5, NCURSES_DOUBLE_CLICKED)
#define	BUTTON5_TRIPLE_CLICKED	NCURSES_MOUSE_MASK(5, NCURSES_TRIPLE_CLICKED)

#define	BUTTON_CTRL		NCURSES_MOUSE_MASK(6, 0001L)
#define	BUTTON_SHIFT		NCURSES_MOUSE_MASK(6, 0002L)
#define	BUTTON_ALT		NCURSES_MOUSE_MASK(6, 0004L)
#define	REPORT_MOUSE_POSITION	NCURSES_MOUSE_MASK(6, 0010L)

#else

#define	BUTTON1_RESERVED_EVENT	NCURSES_MOUSE_MASK(1, NCURSES_RESERVED_EVENT)
#define	BUTTON2_RESERVED_EVENT	NCURSES_MOUSE_MASK(2, NCURSES_RESERVED_EVENT)
#define	BUTTON3_RESERVED_EVENT	NCURSES_MOUSE_MASK(3, NCURSES_RESERVED_EVENT)
#define	BUTTON4_RESERVED_EVENT	NCURSES_MOUSE_MASK(4, NCURSES_RESERVED_EVENT)

#define	BUTTON_CTRL		NCURSES_MOUSE_MASK(5, 0001L)
#define	BUTTON_SHIFT		NCURSES_MOUSE_MASK(5, 0002L)
#define	BUTTON_ALT		NCURSES_MOUSE_MASK(5, 0004L)
#define	REPORT_MOUSE_POSITION	NCURSES_MOUSE_MASK(5, 0010L)

#endif

#define	ALL_MOUSE_EVENTS	(REPORT_MOUSE_POSITION - 1)

/* macros to extract single event-bits from masks */
#define	BUTTON_RELEASE(e, x)		((e) & NCURSES_MOUSE_MASK(x, 001))
#define	BUTTON_PRESS(e, x)		((e) & NCURSES_MOUSE_MASK(x, 002))
#define	BUTTON_CLICK(e, x)		((e) & NCURSES_MOUSE_MASK(x, 004))
#define	BUTTON_DOUBLE_CLICK(e, x)	((e) & NCURSES_MOUSE_MASK(x, 010))
#define	BUTTON_TRIPLE_CLICK(e, x)	((e) & NCURSES_MOUSE_MASK(x, 020))
#define	BUTTON_RESERVED_EVENT(e, x)	((e) & NCURSES_MOUSE_MASK(x, 040))

typedef struct
{
    short id;		/* ID to distinguish multiple devices */
    int x, y, z;	/* event coordinates (character-cell) */
    mmask_t bstate;	/* button state bits */
}
MEVENT;

extern NCURSES_EXPORT(bool)    has_mouse(void);
extern NCURSES_EXPORT(int)     getmouse (MEVENT *);
extern NCURSES_EXPORT(int)     ungetmouse (MEVENT *);
extern NCURSES_EXPORT(mmask_t) mousemask (mmask_t, mmask_t *);
extern NCURSES_EXPORT(bool)    wenclose (const WINDOW *, int, int);
extern NCURSES_EXPORT(int)     mouseinterval (int);
extern NCURSES_EXPORT(bool)    wmouse_trafo (const WINDOW*, int*, int*, bool);
extern NCURSES_EXPORT(bool)    mouse_trafo (int*, int*, bool);              /* generated */

#if NCURSES_SP_FUNCS
extern NCURSES_EXPORT(bool)    NCURSES_SP_NAME(has_mouse) (SCREEN*);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(getmouse) (SCREEN*, MEVENT *);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(ungetmouse) (SCREEN*,MEVENT *);
extern NCURSES_EXPORT(mmask_t) NCURSES_SP_NAME(mousemask) (SCREEN*, mmask_t, mmask_t *);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(mouseinterval) (SCREEN*, int);
#endif

#ifndef NCURSES_NOMACROS
#define mouse_trafo(y,x,to_screen) wmouse_trafo(stdscr,y,x,to_screen)
#endif

/* other non-XSI functions */

extern NCURSES_EXPORT(int) mcprint (char *, int);	/* direct data to printer */
extern NCURSES_EXPORT(int) has_key (int);		/* do we have given key? */

#if NCURSES_SP_FUNCS
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(has_key) (SCREEN*, int);    /* do we have given key? */
extern NCURSES_EXPORT(int) NCURSES_SP_NAME(mcprint) (SCREEN*, char *, int);	/* direct data to printer */
#endif

/* Debugging : use with libncurses_g.a */

extern NCURSES_EXPORT(void) _tracef (const char *, ...) GCC_PRINTFLIKE(1,2);
extern NCURSES_EXPORT(char *) _traceattr (attr_t);
extern NCURSES_EXPORT(char *) _traceattr2 (int, chtype);
extern NCURSES_EXPORT(char *) _tracechar (int);
extern NCURSES_EXPORT(char *) _tracechtype (chtype);
extern NCURSES_EXPORT(char *) _tracechtype2 (int, chtype);
#if NCURSES_WIDECHAR
#define _tracech_t		_tracecchar_t
extern NCURSES_EXPORT(char *) _tracecchar_t (const cchar_t *);
#define _tracech_t2		_tracecchar_t2
extern NCURSES_EXPORT(char *) _tracecchar_t2 (int, const cchar_t *);
#else
#define _tracech_t		_tracechtype
#define _tracech_t2		_tracechtype2
#endif
extern NCURSES_EXPORT(void) trace (const unsigned) GCC_DEPRECATED("use curses_trace");
extern NCURSES_EXPORT(unsigned) curses_trace (const unsigned);

/* trace masks */
#define TRACE_DISABLE	0x0000	/* turn off tracing */
#define TRACE_TIMES	0x0001	/* trace user and system times of updates */
#define TRACE_TPUTS	0x0002	/* trace tputs calls */
#define TRACE_UPDATE	0x0004	/* trace update actions, old & new screens */
#define TRACE_MOVE	0x0008	/* trace cursor moves and scrolls */
#define TRACE_CHARPUT	0x0010	/* trace all character outputs */
#define TRACE_ORDINARY	0x001F	/* trace all update actions */
#define TRACE_CALLS	0x0020	/* trace all curses calls */
#define TRACE_VIRTPUT	0x0040	/* trace virtual character puts */
#define TRACE_IEVENT	0x0080	/* trace low-level input processing */
#define TRACE_BITS	0x0100	/* trace state of TTY control bits */
#define TRACE_ICALLS	0x0200	/* trace internal/nested calls */
#define TRACE_CCALLS	0x0400	/* trace per-character calls */
#define TRACE_DATABASE	0x0800	/* trace read/write of terminfo/termcap data */
#define TRACE_ATTRS	0x1000	/* trace attribute updates */

#define TRACE_SHIFT	13	/* number of bits in the trace masks */
#define TRACE_MAXIMUM	((1 << TRACE_SHIFT) - 1) /* maximum trace level */

#if defined(TRACE) || defined(NCURSES_TEST)
extern NCURSES_EXPORT_VAR(int) _nc_optimize_enable;		/* enable optimizations */
extern NCURSES_EXPORT(const char *) _nc_visbuf (const char *);
#define OPTIMIZE_MVCUR		0x01	/* cursor movement optimization */
#define OPTIMIZE_HASHMAP	0x02	/* diff hashing to detect scrolls */
#define OPTIMIZE_SCROLL		0x04	/* scroll optimization */
#define OPTIMIZE_ALL		0xff	/* enable all optimizations (dflt) */
#endif

extern NCURSES_EXPORT(void) exit_curses (int) GCC_NORETURN;

#include <unctrl.h>

#ifdef __cplusplus

#ifndef NCURSES_NOMACROS

/* these names conflict with STL */
#undef box
#undef clear
#undef erase
#undef move
#undef refresh

#endif /* NCURSES_NOMACROS */

}
#endif

#endif /* __NCURSES_H */

EOF
""",
)

genrule(
    name = "include/ncurses_cfg",
    outs = ["include/ncurses_cfg.h"],
    cmd = r"""
cat << 'EOF' > $@
/* include/ncurses_cfg.h.  Generated automatically by configure.  */
/****************************************************************************
 * Copyright 2020 Thomas E. Dickey                                          *
 * Copyright 1998-2016,2017 Free Software Foundation, Inc.                  *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

/****************************************************************************
 *  Author: Thomas E. Dickey      1997-on                                   *
 ****************************************************************************/
/*
 * $$Id: ncurses_cfg.hin,v 1.12 2020/02/02 23:34:34 tom Exp $$
 *
 * Both ncurses_cfg.h and ncurses_def.h are internal header-files used when
 * building ncurses.
 *
 * This is a template-file used to generate the "ncurses_cfg.h" file.
 *
 * Rather than list every definition, the configuration script substitutes the
 * definitions that it finds using 'sed'.  You need a patch (original date
 * 971222) to autoconf 2.12 or 2.13 to do this.
 *
 * See:
 *	http://invisible-island.net/autoconf/
 *	ftp://ftp.invisible-island.net/autoconf/
 */
#ifndef NC_CONFIG_H
#define NC_CONFIG_H

#define PACKAGE "ncurses"
#define NCURSES_VERSION "6.2"
#define NCURSES_PATCHDATE 20200212
#define SYSTEM_NAME "linux-gnu"
#define HAVE_LONG_FILE_NAMES 1
#define MIXEDCASE_FILENAMES 1
#define TERMINFO_DIRS "/etc/terminfo:/lib/terminfo:/usr/share/terminfo"
#define TERMINFO "/usr/share/terminfo"
#define HAVE_BIG_CORE 1
#define PURE_TERMINFO 1
#define USE_HOME_TERMINFO 1
#define USE_ROOT_ENVIRON 1
#define HAVE_UNISTD_H 1
#define HAVE_REMOVE 1
#define HAVE_UNLINK 1
#define HAVE_LINK 1
#define HAVE_SYMLINK 1
#define USE_LINKS 1
#define HAVE_LANGINFO_CODESET 1
#define USE_WIDEC_SUPPORT 1
#define NCURSES_WIDECHAR 1
#define HAVE_WCHAR_H 1
#define HAVE_WCTYPE_H 1
#define HAVE_PUTWC 1
#define HAVE_BTOWC 1
#define HAVE_WCTOB 1
#define HAVE_MBTOWC 1
#define HAVE_WCTOMB 1
#define HAVE_MBLEN 1
#define HAVE_MBRLEN 1
#define HAVE_MBRTOWC 1
#define HAVE_WCSRTOMBS 1
#define HAVE_MBSRTOWCS 1
#define HAVE_WCSTOMBS 1
#define HAVE_MBSTOWCS 1
#define NEED_WCHAR_H 1
#define HAVE_FSEEKO 1
#define RGB_PATH "/usr/lib64/X11/rgb.txt"
#define STDC_HEADERS 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_MEMORY_H 1
#define HAVE_STRINGS_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_STDINT_H 1
#define HAVE_UNISTD_H 1
#define SIZEOF_SIGNED_CHAR 1
#define NCURSES_EXT_FUNCS 1
#define HAVE_ASSUME_DEFAULT_COLORS 1
#define HAVE_CURSES_VERSION 1
#define HAVE_HAS_KEY 1
#define HAVE_RESIZETERM 1
#define HAVE_RESIZE_TERM 1
#define HAVE_TERM_ENTRY_H 1
#define HAVE_USE_DEFAULT_COLORS 1
#define HAVE_USE_EXTENDED_NAMES 1
#define HAVE_USE_SCREEN 1
#define HAVE_USE_WINDOW 1
#define HAVE_WRESIZE 1
#define NCURSES_SP_FUNCS 1
#define HAVE_TPUTS_SP 1
#define NCURSES_EXT_COLORS 1
#define HAVE_ALLOC_PAIR 1
#define HAVE_INIT_EXTENDED_COLOR 1
#define HAVE_RESET_COLOR_PAIRS 1
#define NCURSES_EXT_PUTWIN 1
#define NCURSES_NO_PADDING 1
#define USE_SIGWINCH 1
#define NCURSES_WRAP_PREFIX "_nc_"
#define USE_ASSUMED_COLOR 1
#define USE_HASHMAP 1
#define GCC_SCANF 1
#define GCC_SCANFLIKE(fmt,var) __attribute__((format(scanf,fmt,var)))
#define GCC_PRINTF 1
#define GCC_PRINTFLIKE(fmt,var) __attribute__((format(printf,fmt,var)))
#define GCC_UNUSED __attribute__((unused))
#define GCC_NORETURN __attribute__((noreturn))
#define HAVE_NC_ALLOC_H 1
#define HAVE_GETTIMEOFDAY 1
#define STDC_HEADERS 1
#define HAVE_DIRENT_H 1
#define TIME_WITH_SYS_TIME 1
#define HAVE_REGEX_H_FUNCS 1
#define HAVE_FCNTL_H 1
#define HAVE_GETOPT_H 1
#define HAVE_LIMITS_H 1
#define HAVE_LOCALE_H 1
#define HAVE_MATH_H 1
#define HAVE_POLL_H 1
#define HAVE_SYS_IOCTL_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_SYS_POLL_H 1
#define HAVE_SYS_SELECT_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TIMES_H 1
#define HAVE_TTYENT_H 1
#define HAVE_UNISTD_H 1
#define HAVE_WCTYPE_H 1
#define HAVE_UNISTD_H 1
#define HAVE_GETOPT_H 1
#define HAVE_GETOPT_HEADER 1
#define DECL_ENVIRON 1
#define HAVE_ENVIRON 1
#define HAVE_PUTENV 1
#define HAVE_SETENV 1
#define HAVE_STRDUP 1
#define HAVE_SYS_TIME_SELECT 1
#define SIG_ATOMIC_T volatile sig_atomic_t
#define HAVE_GETCWD 1
#define HAVE_GETEGID 1
#define HAVE_GETEUID 1
#define HAVE_GETOPT 1
#define HAVE_GETTTYNAM 1
#define HAVE_LOCALECONV 1
#define HAVE_POLL 1
#define HAVE_PUTENV 1
#define HAVE_REMOVE 1
#define HAVE_SELECT 1
#define HAVE_SETBUF 1
#define HAVE_SETBUFFER 1
#define HAVE_SETENV 1
#define HAVE_SETVBUF 1
#define HAVE_SIGACTION 1
#define HAVE_STRDUP 1
#define HAVE_STRSTR 1
#define HAVE_SYSCONF 1
#define HAVE_TCGETPGRP 1
#define HAVE_TIMES 1
#define HAVE_TSEARCH 1
#define HAVE_VSNPRINTF 1
#define HAVE_ISASCII 1
#define HAVE_NANOSLEEP 1
#define HAVE_TERMIO_H 1
#define HAVE_TERMIOS_H 1
#define HAVE_UNISTD_H 1
#define HAVE_SYS_IOCTL_H 1
#define HAVE_TCGETATTR 1
#define HAVE_VSSCANF 1
#define HAVE_UNISTD_H 1
#define HAVE_MKSTEMP 1
#define HAVE_SIZECHANGE 1
#define HAVE_WORKING_POLL 1
#define HAVE_VA_COPY 1
#define HAVE_UNISTD_H 1
#define HAVE_FORK 1
#define HAVE_VFORK 1
#define HAVE_WORKING_VFORK 1
#define HAVE_WORKING_FORK 1
#define USE_FOPEN_BIN_R 1
#define USE_OPENPTY_HEADER <pty.h>
#define USE_XTERM_PTY 1
#define SIZEOF_WCHAR_T 4
#define HAVE_SLK_COLOR 1
#define HAVE_PANEL_H 1
#define HAVE_LIBPANEL 1
#define HAVE_MENU_H 1
#define HAVE_LIBMENU 1
#define HAVE_FORM_H 1
#define HAVE_LIBFORM 1
#define NCURSES_PATHSEP ':'
#define NCURSES_VERSION_STRING "6.2.20200212"
#define NCURSES_OSPEED_COMPAT 1
#define HAVE_CURSES_DATA_BOOLNAMES 1

#include <ncurses_def.h>

	/* The C compiler may not treat these properly but C++ has to */
#ifdef __cplusplus
#undef const
#undef inline
#endif

	/* On HP-UX, the C compiler doesn't grok mbstate_t without
	   -D_XOPEN_SOURCE=500. However, this causes problems on
	   IRIX. So, we #define mbstate_t to int in configure.in
	   only for the C compiler if needed. */
#ifndef __cplusplus
#ifdef NEED_MBSTATE_T_DEF
#define mbstate_t int
#endif
#endif

/*
 * vile:cmode
 */
#endif /* NC_CONFIG_H */

EOF
""",
)

genrule(
    name = "include/ncurses_def",
    outs = ["include/ncurses_def.h"],
    cmd = r"""
cat << 'EOF' > $@
/*
 * This file is generated by thirdparty/ncurses/ncurses-6.2/include/MKncurses_def.sh
 */

#ifndef NC_DEFINE_H
#define NC_DEFINE_H 1

#ifndef BROKEN_LINKER
#define BROKEN_LINKER 0
#endif

#ifndef BSD_TPUTS
#define BSD_TPUTS 0
#endif

#ifndef CGETENT_CONST
#define CGETENT_CONST /* nothing */
#endif

#ifndef CPP_HAS_PARAM_INIT
#define CPP_HAS_PARAM_INIT 0
#endif

#ifndef CURSES_ACS_ARRAY
#define CURSES_ACS_ARRAY acs_map
#endif

#ifndef CURSES_WACS_ARRAY
#define CURSES_WACS_ARRAY _nc_wacs
#endif

#ifndef DECL_ERRNO
#define DECL_ERRNO 0
#endif

#ifndef ETIP_NEEDS_MATH_H
#define ETIP_NEEDS_MATH_H 0
#endif

#ifndef GCC_NORETURN
#define GCC_NORETURN /* nothing */
#endif

#ifndef GCC_UNUSED
#define GCC_UNUSED /* nothing */
#endif

#ifndef HAVE_ALLOC_PAIR
#define HAVE_ALLOC_PAIR 0
#endif

#ifndef HAVE_ASSUME_DEFAULT_COLORS
#define HAVE_ASSUME_DEFAULT_COLORS 0
#endif

#ifndef HAVE_BIG_CORE
#define HAVE_BIG_CORE 0
#endif

#ifndef HAVE_BSD_CGETENT
#define HAVE_BSD_CGETENT 0
#endif

#ifndef HAVE_BSD_SIGNAL_H
#define HAVE_BSD_SIGNAL_H 0
#endif

#ifndef HAVE_BSD_STRING_H
#define HAVE_BSD_STRING_H 0
#endif

#ifndef HAVE_BTOWC
#define HAVE_BTOWC 0
#endif

#ifndef HAVE_BUILTIN_H
#define HAVE_BUILTIN_H 0
#endif

#ifndef HAVE_CHGAT
#define HAVE_CHGAT 1
#endif

#ifndef HAVE_COLOR_CONTENT
#define HAVE_COLOR_CONTENT 1
#endif

#ifndef HAVE_COLOR_SET
#define HAVE_COLOR_SET 1
#endif

#ifndef HAVE_CONSISTENT_GETENV
#define HAVE_CONSISTENT_GETENV 0
#endif

#ifndef HAVE_COPYWIN
#define HAVE_COPYWIN 1
#endif

#ifndef HAVE_CURSCR
#define HAVE_CURSCR 1
#endif

#ifndef HAVE_CURSES_DATA_TABSIZE
#define HAVE_CURSES_DATA_TABSIZE 1
#endif

#ifndef HAVE_CURSES_DATA_TTYTYPE
#define HAVE_CURSES_DATA_TTYTYPE 1
#endif

#ifndef HAVE_DELSCREEN
#define HAVE_DELSCREEN 1
#endif

#ifndef HAVE_DERWIN
#define HAVE_DERWIN 1
#endif

#ifndef HAVE_DIRENT_H
#define HAVE_DIRENT_H 0
#endif

#ifndef HAVE_DUPWIN
#define HAVE_DUPWIN 1
#endif

#ifndef HAVE_ERRNO
#define HAVE_ERRNO 0
#endif

#ifndef HAVE_FCNTL_H
#define HAVE_FCNTL_H 0
#endif

#ifndef HAVE_FILTER
#define HAVE_FILTER 1
#endif

#ifndef HAVE_FORM_H
#define HAVE_FORM_H 0
#endif

#ifndef HAVE_GETBEGX
#define HAVE_GETBEGX 1
#endif

#ifndef HAVE_GETCURX
#define HAVE_GETCURX 1
#endif

#ifndef HAVE_GETCWD
#define HAVE_GETCWD 0
#endif

#ifndef HAVE_GETEGID
#define HAVE_GETEGID 0
#endif

#ifndef HAVE_GETEUID
#define HAVE_GETEUID 0
#endif

#ifndef HAVE_GETMAXX
#define HAVE_GETMAXX 1
#endif

#ifndef HAVE_GETNSTR
#define HAVE_GETNSTR 0
#endif

#ifndef HAVE_GETOPT_H
#define HAVE_GETOPT_H 0
#endif

#ifndef HAVE_GETPARX
#define HAVE_GETPARX 1
#endif

#ifndef HAVE_GETTIMEOFDAY
#define HAVE_GETTIMEOFDAY 0
#endif

#ifndef HAVE_GETTTYNAM
#define HAVE_GETTTYNAM 0
#endif

#ifndef HAVE_GETWIN
#define HAVE_GETWIN 1
#endif

#ifndef HAVE_GPM_H
#define HAVE_GPM_H 0
#endif

#ifndef HAVE_GPP_BUILTIN_H
#define HAVE_GPP_BUILTIN_H 0
#endif

#ifndef HAVE_GXX_BUILTIN_H
#define HAVE_GXX_BUILTIN_H 0
#endif

#ifndef HAVE_HALFDELAY
#define HAVE_HALFDELAY 1
#endif

#ifndef HAVE_HAS_KEY
#define HAVE_HAS_KEY 0
#endif

#ifndef HAVE_INIT_EXTENDED_COLOR
#define HAVE_INIT_EXTENDED_COLOR 0
#endif

#ifndef HAVE_INTTYPES_H
#define HAVE_INTTYPES_H 0
#endif

#ifndef HAVE_IOSTREAM
#define HAVE_IOSTREAM 0
#endif

#ifndef HAVE_ISASCII
#define HAVE_ISASCII 0
#endif

#ifndef HAVE_ISSETUGID
#define HAVE_ISSETUGID 0
#endif

#ifndef HAVE_LANGINFO_CODESET
#define HAVE_LANGINFO_CODESET 0
#endif

#ifndef HAVE_LIBC_H
#define HAVE_LIBC_H 0
#endif

#ifndef HAVE_LIBDBMALLOC
#define HAVE_LIBDBMALLOC 0
#endif

#ifndef HAVE_LIBDMALLOC
#define HAVE_LIBDMALLOC 0
#endif

#ifndef HAVE_LIBFORM
#define HAVE_LIBFORM 0
#endif

#ifndef HAVE_LIBGPM
#define HAVE_LIBGPM 0
#endif

#ifndef HAVE_LIBMENU
#define HAVE_LIBMENU 0
#endif

#ifndef HAVE_LIBMPATROL
#define HAVE_LIBMPATROL 0
#endif

#ifndef HAVE_LIBPANEL
#define HAVE_LIBPANEL 0
#endif

#ifndef HAVE_LIB_PCRE2
#define HAVE_LIB_PCRE2 0
#endif

#ifndef HAVE_LIMITS_H
#define HAVE_LIMITS_H 0
#endif

#ifndef HAVE_LINK
#define HAVE_LINK 0
#endif

#ifndef HAVE_LOCALECONV
#define HAVE_LOCALECONV 0
#endif

#ifndef HAVE_LOCALE_H
#define HAVE_LOCALE_H 0
#endif

#ifndef HAVE_LONG_FILE_NAMES
#define HAVE_LONG_FILE_NAMES 0
#endif

#ifndef HAVE_MATH_H
#define HAVE_MATH_H 0
#endif

#ifndef HAVE_MBLEN
#define HAVE_MBLEN 0
#endif

#ifndef HAVE_MBRLEN
#define HAVE_MBRLEN 0
#endif

#ifndef HAVE_MBRTOWC
#define HAVE_MBRTOWC 0
#endif

#ifndef HAVE_MBSRTOWCS
#define HAVE_MBSRTOWCS 0
#endif

#ifndef HAVE_MBSTOWCS
#define HAVE_MBSTOWCS 0
#endif

#ifndef HAVE_MBTOWC
#define HAVE_MBTOWC 0
#endif

#ifndef HAVE_MENU_H
#define HAVE_MENU_H 0
#endif

#ifndef HAVE_MKSTEMP
#define HAVE_MKSTEMP 0
#endif

#ifndef HAVE_MVDERWIN
#define HAVE_MVDERWIN 1
#endif

#ifndef HAVE_MVVLINE
#define HAVE_MVVLINE 1
#endif

#ifndef HAVE_MVWIN
#define HAVE_MVWIN 1
#endif

#ifndef HAVE_MVWVLINE
#define HAVE_MVWVLINE 1
#endif

#ifndef HAVE_NANOSLEEP
#define HAVE_NANOSLEEP 0
#endif

#ifndef HAVE_NC_ALLOC_H
#define HAVE_NC_ALLOC_H 0
#endif

#ifndef HAVE_NEWPAD
#define HAVE_NEWPAD 1
#endif

#ifndef HAVE_PANEL_H
#define HAVE_PANEL_H 0
#endif

#ifndef HAVE_PCRE2_POSIX_H
#define HAVE_PCRE2_POSIX_H 0
#endif

#ifndef HAVE_PCREPOSIX_H
#define HAVE_PCREPOSIX_H 0
#endif

#ifndef HAVE_POLL
#define HAVE_POLL 0
#endif

#ifndef HAVE_POLL_H
#define HAVE_POLL_H 0
#endif

#ifndef HAVE_PURIFY
#define HAVE_PURIFY 0
#endif

#ifndef HAVE_PUTENV
#define HAVE_PUTENV 0
#endif

#ifndef HAVE_PUTWC
#define HAVE_PUTWC 0
#endif

#ifndef HAVE_PUTWIN
#define HAVE_PUTWIN 1
#endif

#ifndef HAVE_REGEXPR_H_FUNCS
#define HAVE_REGEXPR_H_FUNCS 0
#endif

#ifndef HAVE_REGEXP_H_FUNCS
#define HAVE_REGEXP_H_FUNCS 0
#endif

#ifndef HAVE_REGEX_H_FUNCS
#define HAVE_REGEX_H_FUNCS 0
#endif

#ifndef HAVE_REMOVE
#define HAVE_REMOVE 0
#endif

#ifndef HAVE_RESET_COLOR_PAIRS
#define HAVE_RESET_COLOR_PAIRS 0
#endif

#ifndef HAVE_RESIZETERM
#define HAVE_RESIZETERM 0
#endif

#ifndef HAVE_RESIZE_TERM
#define HAVE_RESIZE_TERM 0
#endif

#ifndef HAVE_RESTARTTERM
#define HAVE_RESTARTTERM 1
#endif

#ifndef HAVE_RIPOFFLINE
#define HAVE_RIPOFFLINE 1
#endif

#ifndef HAVE_SCR_DUMP
#define HAVE_SCR_DUMP 1
#endif

#ifndef HAVE_SELECT
#define HAVE_SELECT 0
#endif

#ifndef HAVE_SETBUF
#define HAVE_SETBUF 0
#endif

#ifndef HAVE_SETBUFFER
#define HAVE_SETBUFFER 0
#endif

#ifndef HAVE_SETENV
#define HAVE_SETENV 0
#endif

#ifndef HAVE_SETUPTERM
#define HAVE_SETUPTERM 1
#endif

#ifndef HAVE_SETVBUF
#define HAVE_SETVBUF 0
#endif

#ifndef HAVE_SGTTY_H
#define HAVE_SGTTY_H 0
#endif

#ifndef HAVE_SIGACTION
#define HAVE_SIGACTION 0
#endif

#ifndef HAVE_SIGVEC
#define HAVE_SIGVEC 0
#endif

#ifndef HAVE_SIZECHANGE
#define HAVE_SIZECHANGE 0
#endif

#ifndef HAVE_SLK_COLOR
#define HAVE_SLK_COLOR 0
#endif

#ifndef HAVE_SLK_INIT
#define HAVE_SLK_INIT 1
#endif

#ifndef HAVE_SNPRINTF
#define HAVE_SNPRINTF 0
#endif

#ifndef HAVE_STDINT_H
#define HAVE_STDINT_H 0
#endif

#ifndef HAVE_STRDUP
#define HAVE_STRDUP 0
#endif

#ifndef HAVE_STRLCAT
#define HAVE_STRLCAT 0
#endif

#ifndef HAVE_STRLCPY
#define HAVE_STRLCPY 0
#endif

#ifndef HAVE_STRSTR
#define HAVE_STRSTR 0
#endif

#ifndef HAVE_SYMLINK
#define HAVE_SYMLINK 0
#endif

#ifndef HAVE_SYSCONF
#define HAVE_SYSCONF 0
#endif

#ifndef HAVE_SYS_BSDTYPES_H
#define HAVE_SYS_BSDTYPES_H 0
#endif

#ifndef HAVE_SYS_IOCTL_H
#define HAVE_SYS_IOCTL_H 0
#endif

#ifndef HAVE_SYS_PARAM_H
#define HAVE_SYS_PARAM_H 0
#endif

#ifndef HAVE_SYS_POLL_H
#define HAVE_SYS_POLL_H 0
#endif

#ifndef HAVE_SYS_SELECT_H
#define HAVE_SYS_SELECT_H 0
#endif

#ifndef HAVE_SYS_TERMIO_H
#define HAVE_SYS_TERMIO_H 0
#endif

#ifndef HAVE_SYS_TIMES_H
#define HAVE_SYS_TIMES_H 0
#endif

#ifndef HAVE_SYS_TIME_H
#define HAVE_SYS_TIME_H 0
#endif

#ifndef HAVE_SYS_TIME_SELECT
#define HAVE_SYS_TIME_SELECT 0
#endif

#ifndef HAVE_TCGETATTR
#define HAVE_TCGETATTR 0
#endif

#ifndef HAVE_TCGETPGRP
#define HAVE_TCGETPGRP 0
#endif

#ifndef HAVE_TELL
#define HAVE_TELL 0
#endif

#ifndef HAVE_TERMATTRS
#define HAVE_TERMATTRS 1
#endif

#ifndef HAVE_TERMCAP_H
#define HAVE_TERMCAP_H 1
#endif

#ifndef HAVE_TERMIOS_H
#define HAVE_TERMIOS_H 0
#endif

#ifndef HAVE_TERMIO_H
#define HAVE_TERMIO_H 0
#endif

#ifndef HAVE_TERMNAME
#define HAVE_TERMNAME 1
#endif

#ifndef HAVE_TERM_ENTRY_H
#define HAVE_TERM_ENTRY_H 1
#endif

#ifndef HAVE_TERM_H
#define HAVE_TERM_H 1
#endif

#ifndef HAVE_TGETENT
#define HAVE_TGETENT 1
#endif

#ifndef HAVE_TIGETNUM
#define HAVE_TIGETNUM 1
#endif

#ifndef HAVE_TIGETSTR
#define HAVE_TIGETSTR 1
#endif

#ifndef HAVE_TIMES
#define HAVE_TIMES 0
#endif

#ifndef HAVE_TPUTS_SP
#define HAVE_TPUTS_SP 0
#endif

#ifndef HAVE_TSEARCH
#define HAVE_TSEARCH 0
#endif

#ifndef HAVE_TTYENT_H
#define HAVE_TTYENT_H 0
#endif

#ifndef HAVE_TYPEAHEAD
#define HAVE_TYPEAHEAD 1
#endif

#ifndef HAVE_TYPEINFO
#define HAVE_TYPEINFO 0
#endif

#ifndef HAVE_TYPE_ATTR_T
#define HAVE_TYPE_ATTR_T 0
#endif

#ifndef HAVE_TYPE_SIGACTION
#define HAVE_TYPE_SIGACTION 0
#endif

#ifndef HAVE_UNCTRL_H
#define HAVE_UNCTRL_H 1
#endif

#ifndef HAVE_UNISTD_H
#define HAVE_UNISTD_H 0
#endif

#ifndef HAVE_UNLINK
#define HAVE_UNLINK 0
#endif

#ifndef HAVE_USE_DEFAULT_COLORS
#define HAVE_USE_DEFAULT_COLORS 0
#endif

#ifndef HAVE_USE_ENV
#define HAVE_USE_ENV 1
#endif

#ifndef HAVE_USE_EXTENDED_NAMES
#define HAVE_USE_EXTENDED_NAMES 0
#endif

#ifndef HAVE_USE_SCREEN
#define HAVE_USE_SCREEN 0
#endif

#ifndef HAVE_USE_WINDOW
#define HAVE_USE_WINDOW 0
#endif

#ifndef HAVE_VFSCANF
#define HAVE_VFSCANF 0
#endif

#ifndef HAVE_VIDPUTS
#define HAVE_VIDPUTS 1
#endif

#ifndef HAVE_VID_PUTS
#define HAVE_VID_PUTS 1
#endif

#ifndef HAVE_VSNPRINTF
#define HAVE_VSNPRINTF 0
#endif

#ifndef HAVE_VSSCANF
#define HAVE_VSSCANF 0
#endif

#ifndef HAVE_VW_PRINTW
#define HAVE_VW_PRINTW 1
#endif

#ifndef HAVE_WCHGAT
#define HAVE_WCHGAT 1
#endif

#ifndef HAVE_WCSRTOMBS
#define HAVE_WCSRTOMBS 0
#endif

#ifndef HAVE_WCSTOMBS
#define HAVE_WCSTOMBS 0
#endif

#ifndef HAVE_WCTOB
#define HAVE_WCTOB 0
#endif

#ifndef HAVE_WCTOMB
#define HAVE_WCTOMB 0
#endif

#ifndef HAVE_WCTYPE_H
#define HAVE_WCTYPE_H 0
#endif

#ifndef HAVE_WINSDELLN
#define HAVE_WINSDELLN 1
#endif

#ifndef HAVE_WINSSTR
#define HAVE_WINSSTR 1
#endif

#ifndef HAVE_WORKING_POLL
#define HAVE_WORKING_POLL 0
#endif

#ifndef HAVE_WRESIZE
#define HAVE_WRESIZE 0
#endif

#ifndef HAVE_WSYNCDOWN
#define HAVE_WSYNCDOWN 1
#endif

#ifndef HAVE__DOSCAN
#define HAVE__DOSCAN 0
#endif

#ifndef HAVE__TRACEF
#define HAVE__TRACEF 0
#endif

#ifndef MIXEDCASE_FILENAMES
#define MIXEDCASE_FILENAMES 0
#endif

#ifndef NCURSES_CHAR_EQ
#define NCURSES_CHAR_EQ 0
#endif

#ifndef NCURSES_EXPANDED
#define NCURSES_EXPANDED 0
#endif

#ifndef NCURSES_EXT_COLORS
#define NCURSES_EXT_COLORS 0
#endif

#ifndef NCURSES_EXT_FUNCS
#define NCURSES_EXT_FUNCS 0
#endif

#ifndef NCURSES_EXT_PUTWIN
#define NCURSES_EXT_PUTWIN 0
#endif

#ifndef NCURSES_NO_PADDING
#define NCURSES_NO_PADDING 0
#endif

#ifndef NCURSES_OSPEED_COMPAT
#define NCURSES_OSPEED_COMPAT 0
#endif

#ifndef NCURSES_PATHSEP
#define NCURSES_PATHSEP ':'
#endif

#ifndef NCURSES_WIDECHAR
#define NCURSES_WIDECHAR 0
#endif

#ifndef NEED_PTEM_H
#define NEED_PTEM_H 0
#endif

#ifndef NO_LEAKS
#define NO_LEAKS 0
#endif

#ifndef PURE_TERMINFO
#define PURE_TERMINFO 0
#endif

#ifndef STDC_HEADERS
#define STDC_HEADERS 0
#endif

#ifndef SVR4_ACTION
#define SVR4_ACTION 0
#endif

#ifndef SVR4_TERMIO
#define SVR4_TERMIO 0
#endif

#ifndef SYSTEM_NAME
#define SYSTEM_NAME "unknown"
#endif

#ifndef TERMINFO
#define TERMINFO "none"
#endif

#ifndef TERMPATH
#define TERMPATH "none"
#endif

#ifndef TIME_WITH_SYS_TIME
#define TIME_WITH_SYS_TIME 0
#endif

#ifndef TYPEOF_CHTYPE
#define TYPEOF_CHTYPE 0
#endif

#ifndef USE_COLORFGBG
#define USE_COLORFGBG 0
#endif

#ifndef USE_FOPEN_BIN_R
#define USE_FOPEN_BIN_R 0
#endif

#ifndef USE_GETCAP
#define USE_GETCAP 0
#endif

#ifndef USE_GETCAP_CACHE
#define USE_GETCAP_CACHE 0
#endif

#ifndef USE_HARD_TABS
#define USE_HARD_TABS 0
#endif

#ifndef USE_HASHED_DB
#define USE_HASHED_DB 0
#endif

#ifndef USE_HASHMAP
#define USE_HASHMAP 0
#endif

#ifndef USE_HOME_TERMINFO
#define USE_HOME_TERMINFO 0
#endif

#ifndef USE_LINKS
#define USE_LINKS 0
#endif

#ifndef USE_MY_MEMMOVE
#define USE_MY_MEMMOVE 0
#endif

#ifndef USE_OK_BCOPY
#define USE_OK_BCOPY 0
#endif

#ifndef USE_PTHREADS_EINTR
#define USE_PTHREADS_EINTR 0
#endif

#ifndef USE_RCS_IDS
#define USE_RCS_IDS 0
#endif

#ifndef USE_REENTRANT
#define USE_REENTRANT 0
#endif

#ifndef USE_SAFE_SPRINTF
#define USE_SAFE_SPRINTF 0
#endif

#ifndef USE_SCROLL_HINTS
#define USE_SCROLL_HINTS 0
#endif

#ifndef USE_SIGWINCH
#define USE_SIGWINCH 0
#endif

#ifndef USE_STRING_HACKS
#define USE_STRING_HACKS 0
#endif

#ifndef USE_SYMLINKS
#define USE_SYMLINKS 0
#endif

#ifndef USE_SYSMOUSE
#define USE_SYSMOUSE 0
#endif

#ifndef USE_WEAK_SYMBOLS
#define USE_WEAK_SYMBOLS 0
#endif

#ifndef USE_WIDEC_SUPPORT
#define USE_WIDEC_SUPPORT 0
#endif

#ifndef USE_XMC_SUPPORT
#define USE_XMC_SUPPORT 0
#endif

#endif /* NC_DEFINE_H */

EOF
""",
)

genrule(
    name = "include/ncurses_dll",
    outs = ["include/ncurses_dll.h"],
    cmd = r"""
cat << 'EOF' > $@
/****************************************************************************
 * Copyright 2018,2020 Thomas E. Dickey                                     *
 * Copyright 2009,2014 Free Software Foundation, Inc.                       *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/
/* $$Id: ncurses_dll.h.in,v 1.12 2020/02/02 23:34:34 tom Exp $$ */

#ifndef NCURSES_DLL_H_incl
#define NCURSES_DLL_H_incl 1

/*
 * MinGW gcc (unlike MSYS2 and Cygwin) should define _WIN32 and possibly _WIN64.
 */
#if defined(__MINGW64__)

#ifndef _WIN64
#define _WIN64 1
#endif

#elif defined(__MINGW32__)

#ifndef _WIN32
#define _WIN32 1
#endif

/* 2014-08-02 workaround for broken MinGW compiler.
 * Oddly, only TRACE is mapped to trace - the other -D's are okay.
 * suggest TDM as an alternative.
 */
#if (__GNUC__ == 4) && (__GNUC_MINOR__ == 8)

#ifdef trace
#undef trace
#define TRACE
#endif

#endif	/* broken compiler */

#endif	/* MingW */

/*
 * For reentrant code, we map the various global variables into SCREEN by
 * using functions to access them.
 */
#define NCURSES_PUBLIC_VAR(name) _nc_##name
#define NCURSES_WRAPPED_VAR(type,name) extern type NCURSES_PUBLIC_VAR(name)(void)

/* no longer needed on cygwin or mingw, thanks to auto-import       */
/* but this structure may be useful at some point for an MSVC build */
/* so, for now unconditionally define the important flags           */
/* "the right way" for proper static and dll+auto-import behavior   */
#undef NCURSES_DLL
#define NCURSES_STATIC

#if defined(__CYGWIN__) || defined(_WIN32)
#  if defined(NCURSES_DLL)
#    if defined(NCURSES_STATIC)
#      undef NCURSES_STATIC
#    endif
#  endif
#  undef NCURSES_IMPEXP
#  undef NCURSES_API
#  undef NCURSES_EXPORT
#  undef NCURSES_EXPORT_VAR
#  if defined(NCURSES_DLL)
/* building a DLL */
#    define NCURSES_IMPEXP __declspec(dllexport)
#  elif defined(NCURSES_STATIC)
/* building or linking to a static library */
#    define NCURSES_IMPEXP /* nothing */
#  else
/* linking to the DLL */
#    define NCURSES_IMPEXP __declspec(dllimport)
#  endif
#  define NCURSES_API __cdecl
#  define NCURSES_EXPORT(type) NCURSES_IMPEXP type NCURSES_API
#  define NCURSES_EXPORT_VAR(type) NCURSES_IMPEXP type
#endif

/* Take care of non-cygwin platforms */
#if !defined(NCURSES_IMPEXP)
#  define NCURSES_IMPEXP /* nothing */
#endif
#if !defined(NCURSES_API)
#  define NCURSES_API /* nothing */
#endif
#if !defined(NCURSES_EXPORT)
#  define NCURSES_EXPORT(type) NCURSES_IMPEXP type NCURSES_API
#endif
#if !defined(NCURSES_EXPORT_VAR)
#  define NCURSES_EXPORT_VAR(type) NCURSES_IMPEXP type
#endif

#endif /* NCURSES_DLL_H_incl */

EOF
""",
)

genrule(
    name = "include/term",
    outs = ["include/term.h"],
    cmd = r"""
cat << 'EOF' > $@
/****************************************************************************
 * Copyright 2018-2019,2020 Thomas E. Dickey                                *
 * Copyright 1998-2013,2017 Free Software Foundation, Inc.                  *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

/****************************************************************************/
/* Author: Zeyd M. Ben-Halim <zmbenhal@netcom.com> 1992,1995                */
/*    and: Eric S. Raymond <esr@snark.thyrsus.com>                          */
/*    and: Thomas E. Dickey                        1995-on                  */
/****************************************************************************/

/* $$Id: MKterm.h.awk.in,v 1.74 2020/02/02 23:34:34 tom Exp $$ */

/*
**	term.h -- Definition of struct term
*/

#ifndef NCURSES_TERM_H_incl
#define NCURSES_TERM_H_incl 1

#undef  NCURSES_VERSION
#define NCURSES_VERSION "6.2"

#include <ncurses_dll.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Make this file self-contained by providing defaults for the HAVE_TERMIO[S]_H
 * definition (based on the system for which this was configured).
 */

#undef  NCURSES_CONST
#define NCURSES_CONST const

#undef  NCURSES_SBOOL
#define NCURSES_SBOOL char

#undef  NCURSES_USE_DATABASE
#define NCURSES_USE_DATABASE 1

#undef  NCURSES_USE_TERMCAP
#define NCURSES_USE_TERMCAP 0

#undef  NCURSES_XNAMES
#define NCURSES_XNAMES 1

/* We will use these symbols to hide differences between
 * termios/termio/sgttyb interfaces.
 */
#undef  TTY
#undef  SET_TTY
#undef  GET_TTY

/* Assume POSIX termio if we have the header and function */
/* #if HAVE_TERMIOS_H && HAVE_TCGETATTR */
#if 1 && 1

#undef  TERMIOS
#define TERMIOS 1

#include <termios.h>
#define TTY struct termios

#else /* !HAVE_TERMIOS_H */

/* #if HAVE_TERMIO_H */
#if 1

#undef  TERMIOS
#define TERMIOS 1

#include <termio.h>
#define TTY struct termio

#else /* !HAVE_TERMIO_H */

#if _WIN32
#  include <ncurses_mingw.h>
#  define TTY struct termios
#else
#undef TERMIOS
#include <sgtty.h>
#include <sys/ioctl.h>
#define TTY struct sgttyb
#endif /* MINGW32 */
#endif /* HAVE_TERMIO_H */

#endif /* HAVE_TERMIOS_H */

#ifdef TERMIOS
#define GET_TTY(fd, buf) tcgetattr(fd, buf)
#define SET_TTY(fd, buf) tcsetattr(fd, TCSADRAIN, buf)
#else
#define GET_TTY(fd, buf) gtty(fd, buf)
#define SET_TTY(fd, buf) stty(fd, buf)
#endif

#ifndef	GCC_NORETURN
#define	GCC_NORETURN /* nothing */
#endif

#define NAMESIZE 256

/* The cast works because TERMTYPE is the first data in TERMINAL */
#define CUR ((TERMTYPE *)(cur_term))->

#define auto_left_margin               CUR Booleans[0]
#define auto_right_margin              CUR Booleans[1]
#define no_esc_ctlc                    CUR Booleans[2]
#define ceol_standout_glitch           CUR Booleans[3]
#define eat_newline_glitch             CUR Booleans[4]
#define erase_overstrike               CUR Booleans[5]
#define generic_type                   CUR Booleans[6]
#define hard_copy                      CUR Booleans[7]
#define has_meta_key                   CUR Booleans[8]
#define has_status_line                CUR Booleans[9]
#define insert_null_glitch             CUR Booleans[10]
#define memory_above                   CUR Booleans[11]
#define memory_below                   CUR Booleans[12]
#define move_insert_mode               CUR Booleans[13]
#define move_standout_mode             CUR Booleans[14]
#define over_strike                    CUR Booleans[15]
#define status_line_esc_ok             CUR Booleans[16]
#define dest_tabs_magic_smso           CUR Booleans[17]
#define tilde_glitch                   CUR Booleans[18]
#define transparent_underline          CUR Booleans[19]
#define xon_xoff                       CUR Booleans[20]
#define needs_xon_xoff                 CUR Booleans[21]
#define prtr_silent                    CUR Booleans[22]
#define hard_cursor                    CUR Booleans[23]
#define non_rev_rmcup                  CUR Booleans[24]
#define no_pad_char                    CUR Booleans[25]
#define non_dest_scroll_region         CUR Booleans[26]
#define can_change                     CUR Booleans[27]
#define back_color_erase               CUR Booleans[28]
#define hue_lightness_saturation       CUR Booleans[29]
#define col_addr_glitch                CUR Booleans[30]
#define cr_cancels_micro_mode          CUR Booleans[31]
#define has_print_wheel                CUR Booleans[32]
#define row_addr_glitch                CUR Booleans[33]
#define semi_auto_right_margin         CUR Booleans[34]
#define cpi_changes_res                CUR Booleans[35]
#define lpi_changes_res                CUR Booleans[36]
#define columns                        CUR Numbers[0]
#define init_tabs                      CUR Numbers[1]
#define lines                          CUR Numbers[2]
#define lines_of_memory                CUR Numbers[3]
#define magic_cookie_glitch            CUR Numbers[4]
#define padding_baud_rate              CUR Numbers[5]
#define virtual_terminal               CUR Numbers[6]
#define width_status_line              CUR Numbers[7]
#define num_labels                     CUR Numbers[8]
#define label_height                   CUR Numbers[9]
#define label_width                    CUR Numbers[10]
#define max_attributes                 CUR Numbers[11]
#define maximum_windows                CUR Numbers[12]
#define max_colors                     CUR Numbers[13]
#define max_pairs                      CUR Numbers[14]
#define no_color_video                 CUR Numbers[15]
#define buffer_capacity                CUR Numbers[16]
#define dot_vert_spacing               CUR Numbers[17]
#define dot_horz_spacing               CUR Numbers[18]
#define max_micro_address              CUR Numbers[19]
#define max_micro_jump                 CUR Numbers[20]
#define micro_col_size                 CUR Numbers[21]
#define micro_line_size                CUR Numbers[22]
#define number_of_pins                 CUR Numbers[23]
#define output_res_char                CUR Numbers[24]
#define output_res_line                CUR Numbers[25]
#define output_res_horz_inch           CUR Numbers[26]
#define output_res_vert_inch           CUR Numbers[27]
#define print_rate                     CUR Numbers[28]
#define wide_char_size                 CUR Numbers[29]
#define buttons                        CUR Numbers[30]
#define bit_image_entwining            CUR Numbers[31]
#define bit_image_type                 CUR Numbers[32]
#define back_tab                       CUR Strings[0]
#define bell                           CUR Strings[1]
#define carriage_return                CUR Strings[2]
#define change_scroll_region           CUR Strings[3]
#define clear_all_tabs                 CUR Strings[4]
#define clear_screen                   CUR Strings[5]
#define clr_eol                        CUR Strings[6]
#define clr_eos                        CUR Strings[7]
#define column_address                 CUR Strings[8]
#define command_character              CUR Strings[9]
#define cursor_address                 CUR Strings[10]
#define cursor_down                    CUR Strings[11]
#define cursor_home                    CUR Strings[12]
#define cursor_invisible               CUR Strings[13]
#define cursor_left                    CUR Strings[14]
#define cursor_mem_address             CUR Strings[15]
#define cursor_normal                  CUR Strings[16]
#define cursor_right                   CUR Strings[17]
#define cursor_to_ll                   CUR Strings[18]
#define cursor_up                      CUR Strings[19]
#define cursor_visible                 CUR Strings[20]
#define delete_character               CUR Strings[21]
#define delete_line                    CUR Strings[22]
#define dis_status_line                CUR Strings[23]
#define down_half_line                 CUR Strings[24]
#define enter_alt_charset_mode         CUR Strings[25]
#define enter_blink_mode               CUR Strings[26]
#define enter_bold_mode                CUR Strings[27]
#define enter_ca_mode                  CUR Strings[28]
#define enter_delete_mode              CUR Strings[29]
#define enter_dim_mode                 CUR Strings[30]
#define enter_insert_mode              CUR Strings[31]
#define enter_secure_mode              CUR Strings[32]
#define enter_protected_mode           CUR Strings[33]
#define enter_reverse_mode             CUR Strings[34]
#define enter_standout_mode            CUR Strings[35]
#define enter_underline_mode           CUR Strings[36]
#define erase_chars                    CUR Strings[37]
#define exit_alt_charset_mode          CUR Strings[38]
#define exit_attribute_mode            CUR Strings[39]
#define exit_ca_mode                   CUR Strings[40]
#define exit_delete_mode               CUR Strings[41]
#define exit_insert_mode               CUR Strings[42]
#define exit_standout_mode             CUR Strings[43]
#define exit_underline_mode            CUR Strings[44]
#define flash_screen                   CUR Strings[45]
#define form_feed                      CUR Strings[46]
#define from_status_line               CUR Strings[47]
#define init_1string                   CUR Strings[48]
#define init_2string                   CUR Strings[49]
#define init_3string                   CUR Strings[50]
#define init_file                      CUR Strings[51]
#define insert_character               CUR Strings[52]
#define insert_line                    CUR Strings[53]
#define insert_padding                 CUR Strings[54]
#define key_backspace                  CUR Strings[55]
#define key_catab                      CUR Strings[56]
#define key_clear                      CUR Strings[57]
#define key_ctab                       CUR Strings[58]
#define key_dc                         CUR Strings[59]
#define key_dl                         CUR Strings[60]
#define key_down                       CUR Strings[61]
#define key_eic                        CUR Strings[62]
#define key_eol                        CUR Strings[63]
#define key_eos                        CUR Strings[64]
#define key_f0                         CUR Strings[65]
#define key_f1                         CUR Strings[66]
#define key_f10                        CUR Strings[67]
#define key_f2                         CUR Strings[68]
#define key_f3                         CUR Strings[69]
#define key_f4                         CUR Strings[70]
#define key_f5                         CUR Strings[71]
#define key_f6                         CUR Strings[72]
#define key_f7                         CUR Strings[73]
#define key_f8                         CUR Strings[74]
#define key_f9                         CUR Strings[75]
#define key_home                       CUR Strings[76]
#define key_ic                         CUR Strings[77]
#define key_il                         CUR Strings[78]
#define key_left                       CUR Strings[79]
#define key_ll                         CUR Strings[80]
#define key_npage                      CUR Strings[81]
#define key_ppage                      CUR Strings[82]
#define key_right                      CUR Strings[83]
#define key_sf                         CUR Strings[84]
#define key_sr                         CUR Strings[85]
#define key_stab                       CUR Strings[86]
#define key_up                         CUR Strings[87]
#define keypad_local                   CUR Strings[88]
#define keypad_xmit                    CUR Strings[89]
#define lab_f0                         CUR Strings[90]
#define lab_f1                         CUR Strings[91]
#define lab_f10                        CUR Strings[92]
#define lab_f2                         CUR Strings[93]
#define lab_f3                         CUR Strings[94]
#define lab_f4                         CUR Strings[95]
#define lab_f5                         CUR Strings[96]
#define lab_f6                         CUR Strings[97]
#define lab_f7                         CUR Strings[98]
#define lab_f8                         CUR Strings[99]
#define lab_f9                         CUR Strings[100]
#define meta_off                       CUR Strings[101]
#define meta_on                        CUR Strings[102]
#define newline                        CUR Strings[103]
#define pad_char                       CUR Strings[104]
#define parm_dch                       CUR Strings[105]
#define parm_delete_line               CUR Strings[106]
#define parm_down_cursor               CUR Strings[107]
#define parm_ich                       CUR Strings[108]
#define parm_index                     CUR Strings[109]
#define parm_insert_line               CUR Strings[110]
#define parm_left_cursor               CUR Strings[111]
#define parm_right_cursor              CUR Strings[112]
#define parm_rindex                    CUR Strings[113]
#define parm_up_cursor                 CUR Strings[114]
#define pkey_key                       CUR Strings[115]
#define pkey_local                     CUR Strings[116]
#define pkey_xmit                      CUR Strings[117]
#define print_screen                   CUR Strings[118]
#define prtr_off                       CUR Strings[119]
#define prtr_on                        CUR Strings[120]
#define repeat_char                    CUR Strings[121]
#define reset_1string                  CUR Strings[122]
#define reset_2string                  CUR Strings[123]
#define reset_3string                  CUR Strings[124]
#define reset_file                     CUR Strings[125]
#define restore_cursor                 CUR Strings[126]
#define row_address                    CUR Strings[127]
#define save_cursor                    CUR Strings[128]
#define scroll_forward                 CUR Strings[129]
#define scroll_reverse                 CUR Strings[130]
#define set_attributes                 CUR Strings[131]
#define set_tab                        CUR Strings[132]
#define set_window                     CUR Strings[133]
#define tab                            CUR Strings[134]
#define to_status_line                 CUR Strings[135]
#define underline_char                 CUR Strings[136]
#define up_half_line                   CUR Strings[137]
#define init_prog                      CUR Strings[138]
#define key_a1                         CUR Strings[139]
#define key_a3                         CUR Strings[140]
#define key_b2                         CUR Strings[141]
#define key_c1                         CUR Strings[142]
#define key_c3                         CUR Strings[143]
#define prtr_non                       CUR Strings[144]
#define char_padding                   CUR Strings[145]
#define acs_chars                      CUR Strings[146]
#define plab_norm                      CUR Strings[147]
#define key_btab                       CUR Strings[148]
#define enter_xon_mode                 CUR Strings[149]
#define exit_xon_mode                  CUR Strings[150]
#define enter_am_mode                  CUR Strings[151]
#define exit_am_mode                   CUR Strings[152]
#define xon_character                  CUR Strings[153]
#define xoff_character                 CUR Strings[154]
#define ena_acs                        CUR Strings[155]
#define label_on                       CUR Strings[156]
#define label_off                      CUR Strings[157]
#define key_beg                        CUR Strings[158]
#define key_cancel                     CUR Strings[159]
#define key_close                      CUR Strings[160]
#define key_command                    CUR Strings[161]
#define key_copy                       CUR Strings[162]
#define key_create                     CUR Strings[163]
#define key_end                        CUR Strings[164]
#define key_enter                      CUR Strings[165]
#define key_exit                       CUR Strings[166]
#define key_find                       CUR Strings[167]
#define key_help                       CUR Strings[168]
#define key_mark                       CUR Strings[169]
#define key_message                    CUR Strings[170]
#define key_move                       CUR Strings[171]
#define key_next                       CUR Strings[172]
#define key_open                       CUR Strings[173]
#define key_options                    CUR Strings[174]
#define key_previous                   CUR Strings[175]
#define key_print                      CUR Strings[176]
#define key_redo                       CUR Strings[177]
#define key_reference                  CUR Strings[178]
#define key_refresh                    CUR Strings[179]
#define key_replace                    CUR Strings[180]
#define key_restart                    CUR Strings[181]
#define key_resume                     CUR Strings[182]
#define key_save                       CUR Strings[183]
#define key_suspend                    CUR Strings[184]
#define key_undo                       CUR Strings[185]
#define key_sbeg                       CUR Strings[186]
#define key_scancel                    CUR Strings[187]
#define key_scommand                   CUR Strings[188]
#define key_scopy                      CUR Strings[189]
#define key_screate                    CUR Strings[190]
#define key_sdc                        CUR Strings[191]
#define key_sdl                        CUR Strings[192]
#define key_select                     CUR Strings[193]
#define key_send                       CUR Strings[194]
#define key_seol                       CUR Strings[195]
#define key_sexit                      CUR Strings[196]
#define key_sfind                      CUR Strings[197]
#define key_shelp                      CUR Strings[198]
#define key_shome                      CUR Strings[199]
#define key_sic                        CUR Strings[200]
#define key_sleft                      CUR Strings[201]
#define key_smessage                   CUR Strings[202]
#define key_smove                      CUR Strings[203]
#define key_snext                      CUR Strings[204]
#define key_soptions                   CUR Strings[205]
#define key_sprevious                  CUR Strings[206]
#define key_sprint                     CUR Strings[207]
#define key_sredo                      CUR Strings[208]
#define key_sreplace                   CUR Strings[209]
#define key_sright                     CUR Strings[210]
#define key_srsume                     CUR Strings[211]
#define key_ssave                      CUR Strings[212]
#define key_ssuspend                   CUR Strings[213]
#define key_sundo                      CUR Strings[214]
#define req_for_input                  CUR Strings[215]
#define key_f11                        CUR Strings[216]
#define key_f12                        CUR Strings[217]
#define key_f13                        CUR Strings[218]
#define key_f14                        CUR Strings[219]
#define key_f15                        CUR Strings[220]
#define key_f16                        CUR Strings[221]
#define key_f17                        CUR Strings[222]
#define key_f18                        CUR Strings[223]
#define key_f19                        CUR Strings[224]
#define key_f20                        CUR Strings[225]
#define key_f21                        CUR Strings[226]
#define key_f22                        CUR Strings[227]
#define key_f23                        CUR Strings[228]
#define key_f24                        CUR Strings[229]
#define key_f25                        CUR Strings[230]
#define key_f26                        CUR Strings[231]
#define key_f27                        CUR Strings[232]
#define key_f28                        CUR Strings[233]
#define key_f29                        CUR Strings[234]
#define key_f30                        CUR Strings[235]
#define key_f31                        CUR Strings[236]
#define key_f32                        CUR Strings[237]
#define key_f33                        CUR Strings[238]
#define key_f34                        CUR Strings[239]
#define key_f35                        CUR Strings[240]
#define key_f36                        CUR Strings[241]
#define key_f37                        CUR Strings[242]
#define key_f38                        CUR Strings[243]
#define key_f39                        CUR Strings[244]
#define key_f40                        CUR Strings[245]
#define key_f41                        CUR Strings[246]
#define key_f42                        CUR Strings[247]
#define key_f43                        CUR Strings[248]
#define key_f44                        CUR Strings[249]
#define key_f45                        CUR Strings[250]
#define key_f46                        CUR Strings[251]
#define key_f47                        CUR Strings[252]
#define key_f48                        CUR Strings[253]
#define key_f49                        CUR Strings[254]
#define key_f50                        CUR Strings[255]
#define key_f51                        CUR Strings[256]
#define key_f52                        CUR Strings[257]
#define key_f53                        CUR Strings[258]
#define key_f54                        CUR Strings[259]
#define key_f55                        CUR Strings[260]
#define key_f56                        CUR Strings[261]
#define key_f57                        CUR Strings[262]
#define key_f58                        CUR Strings[263]
#define key_f59                        CUR Strings[264]
#define key_f60                        CUR Strings[265]
#define key_f61                        CUR Strings[266]
#define key_f62                        CUR Strings[267]
#define key_f63                        CUR Strings[268]
#define clr_bol                        CUR Strings[269]
#define clear_margins                  CUR Strings[270]
#define set_left_margin                CUR Strings[271]
#define set_right_margin               CUR Strings[272]
#define label_format                   CUR Strings[273]
#define set_clock                      CUR Strings[274]
#define display_clock                  CUR Strings[275]
#define remove_clock                   CUR Strings[276]
#define create_window                  CUR Strings[277]
#define goto_window                    CUR Strings[278]
#define hangup                         CUR Strings[279]
#define dial_phone                     CUR Strings[280]
#define quick_dial                     CUR Strings[281]
#define tone                           CUR Strings[282]
#define pulse                          CUR Strings[283]
#define flash_hook                     CUR Strings[284]
#define fixed_pause                    CUR Strings[285]
#define wait_tone                      CUR Strings[286]
#define user0                          CUR Strings[287]
#define user1                          CUR Strings[288]
#define user2                          CUR Strings[289]
#define user3                          CUR Strings[290]
#define user4                          CUR Strings[291]
#define user5                          CUR Strings[292]
#define user6                          CUR Strings[293]
#define user7                          CUR Strings[294]
#define user8                          CUR Strings[295]
#define user9                          CUR Strings[296]
#define orig_pair                      CUR Strings[297]
#define orig_colors                    CUR Strings[298]
#define initialize_color               CUR Strings[299]
#define initialize_pair                CUR Strings[300]
#define set_color_pair                 CUR Strings[301]
#define set_foreground                 CUR Strings[302]
#define set_background                 CUR Strings[303]
#define change_char_pitch              CUR Strings[304]
#define change_line_pitch              CUR Strings[305]
#define change_res_horz                CUR Strings[306]
#define change_res_vert                CUR Strings[307]
#define define_char                    CUR Strings[308]
#define enter_doublewide_mode          CUR Strings[309]
#define enter_draft_quality            CUR Strings[310]
#define enter_italics_mode             CUR Strings[311]
#define enter_leftward_mode            CUR Strings[312]
#define enter_micro_mode               CUR Strings[313]
#define enter_near_letter_quality      CUR Strings[314]
#define enter_normal_quality           CUR Strings[315]
#define enter_shadow_mode              CUR Strings[316]
#define enter_subscript_mode           CUR Strings[317]
#define enter_superscript_mode         CUR Strings[318]
#define enter_upward_mode              CUR Strings[319]
#define exit_doublewide_mode           CUR Strings[320]
#define exit_italics_mode              CUR Strings[321]
#define exit_leftward_mode             CUR Strings[322]
#define exit_micro_mode                CUR Strings[323]
#define exit_shadow_mode               CUR Strings[324]
#define exit_subscript_mode            CUR Strings[325]
#define exit_superscript_mode          CUR Strings[326]
#define exit_upward_mode               CUR Strings[327]
#define micro_column_address           CUR Strings[328]
#define micro_down                     CUR Strings[329]
#define micro_left                     CUR Strings[330]
#define micro_right                    CUR Strings[331]
#define micro_row_address              CUR Strings[332]
#define micro_up                       CUR Strings[333]
#define order_of_pins                  CUR Strings[334]
#define parm_down_micro                CUR Strings[335]
#define parm_left_micro                CUR Strings[336]
#define parm_right_micro               CUR Strings[337]
#define parm_up_micro                  CUR Strings[338]
#define select_char_set                CUR Strings[339]
#define set_bottom_margin              CUR Strings[340]
#define set_bottom_margin_parm         CUR Strings[341]
#define set_left_margin_parm           CUR Strings[342]
#define set_right_margin_parm          CUR Strings[343]
#define set_top_margin                 CUR Strings[344]
#define set_top_margin_parm            CUR Strings[345]
#define start_bit_image                CUR Strings[346]
#define start_char_set_def             CUR Strings[347]
#define stop_bit_image                 CUR Strings[348]
#define stop_char_set_def              CUR Strings[349]
#define subscript_characters           CUR Strings[350]
#define superscript_characters         CUR Strings[351]
#define these_cause_cr                 CUR Strings[352]
#define zero_motion                    CUR Strings[353]
#define char_set_names                 CUR Strings[354]
#define key_mouse                      CUR Strings[355]
#define mouse_info                     CUR Strings[356]
#define req_mouse_pos                  CUR Strings[357]
#define get_mouse                      CUR Strings[358]
#define set_a_foreground               CUR Strings[359]
#define set_a_background               CUR Strings[360]
#define pkey_plab                      CUR Strings[361]
#define device_type                    CUR Strings[362]
#define code_set_init                  CUR Strings[363]
#define set0_des_seq                   CUR Strings[364]
#define set1_des_seq                   CUR Strings[365]
#define set2_des_seq                   CUR Strings[366]
#define set3_des_seq                   CUR Strings[367]
#define set_lr_margin                  CUR Strings[368]
#define set_tb_margin                  CUR Strings[369]
#define bit_image_repeat               CUR Strings[370]
#define bit_image_newline              CUR Strings[371]
#define bit_image_carriage_return      CUR Strings[372]
#define color_names                    CUR Strings[373]
#define define_bit_image_region        CUR Strings[374]
#define end_bit_image_region           CUR Strings[375]
#define set_color_band                 CUR Strings[376]
#define set_page_length                CUR Strings[377]
#define display_pc_char                CUR Strings[378]
#define enter_pc_charset_mode          CUR Strings[379]
#define exit_pc_charset_mode           CUR Strings[380]
#define enter_scancode_mode            CUR Strings[381]
#define exit_scancode_mode             CUR Strings[382]
#define pc_term_options                CUR Strings[383]
#define scancode_escape                CUR Strings[384]
#define alt_scancode_esc               CUR Strings[385]
#define enter_horizontal_hl_mode       CUR Strings[386]
#define enter_left_hl_mode             CUR Strings[387]
#define enter_low_hl_mode              CUR Strings[388]
#define enter_right_hl_mode            CUR Strings[389]
#define enter_top_hl_mode              CUR Strings[390]
#define enter_vertical_hl_mode         CUR Strings[391]
#define set_a_attributes               CUR Strings[392]
#define set_pglen_inch                 CUR Strings[393]

#define BOOLWRITE 37
#define NUMWRITE  33
#define STRWRITE  394

/* older synonyms for some capabilities */
#define beehive_glitch	no_esc_ctlc
#define teleray_glitch	dest_tabs_magic_smso

/* HPUX-11 uses this name rather than the standard one */
#ifndef micro_char_size
#define micro_char_size micro_col_size
#endif

#ifdef __INTERNAL_CAPS_VISIBLE
#define termcap_init2                  CUR Strings[394]
#define termcap_reset                  CUR Strings[395]
#define magic_cookie_glitch_ul         CUR Numbers[33]
#define backspaces_with_bs             CUR Booleans[37]
#define crt_no_scrolling               CUR Booleans[38]
#define no_correctly_working_cr        CUR Booleans[39]
#define carriage_return_delay          CUR Numbers[34]
#define new_line_delay                 CUR Numbers[35]
#define linefeed_if_not_lf             CUR Strings[396]
#define backspace_if_not_bs            CUR Strings[397]
#define gnu_has_meta_key               CUR Booleans[40]
#define linefeed_is_newline            CUR Booleans[41]
#define backspace_delay                CUR Numbers[36]
#define horizontal_tab_delay           CUR Numbers[37]
#define number_of_function_keys        CUR Numbers[38]
#define other_non_function_keys        CUR Strings[398]
#define arrow_key_map                  CUR Strings[399]
#define has_hardware_tabs              CUR Booleans[42]
#define return_does_clr_eol            CUR Booleans[43]
#define acs_ulcorner                   CUR Strings[400]
#define acs_llcorner                   CUR Strings[401]
#define acs_urcorner                   CUR Strings[402]
#define acs_lrcorner                   CUR Strings[403]
#define acs_ltee                       CUR Strings[404]
#define acs_rtee                       CUR Strings[405]
#define acs_btee                       CUR Strings[406]
#define acs_ttee                       CUR Strings[407]
#define acs_hline                      CUR Strings[408]
#define acs_vline                      CUR Strings[409]
#define acs_plus                       CUR Strings[410]
#define memory_lock                    CUR Strings[411]
#define memory_unlock                  CUR Strings[412]
#define box_chars_1                    CUR Strings[413]
#endif /* __INTERNAL_CAPS_VISIBLE */


/*
 * Predefined terminfo array sizes
 */
#define BOOLCOUNT 44
#define NUMCOUNT  39
#define STRCOUNT  414

/* used by code for comparing entries */
#define acs_chars_index	 146

typedef struct termtype {	/* in-core form of terminfo data */
    char  *term_names;		/* str_table offset of term names */
    char  *str_table;		/* pointer to string table */
    NCURSES_SBOOL  *Booleans;	/* array of boolean values */
    short *Numbers;		/* array of integer values */
    char  **Strings;		/* array of string offsets */

#if NCURSES_XNAMES
    char  *ext_str_table;	/* pointer to extended string table */
    char  **ext_Names;		/* corresponding names */

    unsigned short num_Booleans;/* count total Booleans */
    unsigned short num_Numbers;	/* count total Numbers */
    unsigned short num_Strings;	/* count total Strings */

    unsigned short ext_Booleans;/* count extensions to Booleans */
    unsigned short ext_Numbers;	/* count extensions to Numbers */
    unsigned short ext_Strings;	/* count extensions to Strings */
#endif /* NCURSES_XNAMES */

} TERMTYPE;

/*
 * The only reason these structures are visible is for read-only use.
 * Programs which modify the data are not, never were, portable across
 * curses implementations.
 */
#ifdef NCURSES_INTERNALS

typedef struct termtype2 {	/* in-core form of terminfo data */
    char  *term_names;		/* str_table offset of term names */
    char  *str_table;		/* pointer to string table */
    NCURSES_SBOOL  *Booleans;	/* array of boolean values */
    int   *Numbers;		/* array of integer values */
    char  **Strings;		/* array of string offsets */

#if NCURSES_XNAMES
    char  *ext_str_table;	/* pointer to extended string table */
    char  **ext_Names;		/* corresponding names */

    unsigned short num_Booleans;/* count total Booleans */
    unsigned short num_Numbers;	/* count total Numbers */
    unsigned short num_Strings;	/* count total Strings */

    unsigned short ext_Booleans;/* count extensions to Booleans */
    unsigned short ext_Numbers;	/* count extensions to Numbers */
    unsigned short ext_Strings;	/* count extensions to Strings */
#endif /* NCURSES_XNAMES */

} TERMTYPE2;

typedef struct term {		/* describe an actual terminal */
    TERMTYPE	type;		/* terminal type description */
    short	Filedes;	/* file description being written to */
    TTY		Ottyb;		/* original state of the terminal */
    TTY		Nttyb;		/* current state of the terminal */
    int		_baudrate;	/* used to compute padding */
    char *	_termname;	/* used for termname() */
    TERMTYPE2	type2;		/* extended terminal type description */
} TERMINAL;
#else
typedef struct term TERMINAL;
#endif /* NCURSES_INTERNALS */


#if 0 && !0
extern NCURSES_EXPORT_VAR(TERMINAL *) cur_term;
#elif 0
NCURSES_WRAPPED_VAR(TERMINAL *, cur_term);
#define cur_term   NCURSES_PUBLIC_VAR(cur_term())
#else
extern NCURSES_EXPORT_VAR(TERMINAL *) cur_term;
#endif

#if 0 || 0
NCURSES_WRAPPED_VAR(NCURSES_CONST char * const *, boolnames);
NCURSES_WRAPPED_VAR(NCURSES_CONST char * const *, boolcodes);
NCURSES_WRAPPED_VAR(NCURSES_CONST char * const *, boolfnames);
NCURSES_WRAPPED_VAR(NCURSES_CONST char * const *, numnames);
NCURSES_WRAPPED_VAR(NCURSES_CONST char * const *, numcodes);
NCURSES_WRAPPED_VAR(NCURSES_CONST char * const *, numfnames);
NCURSES_WRAPPED_VAR(NCURSES_CONST char * const *, strnames);
NCURSES_WRAPPED_VAR(NCURSES_CONST char * const *, strcodes);
NCURSES_WRAPPED_VAR(NCURSES_CONST char * const *, strfnames);

#define boolnames  NCURSES_PUBLIC_VAR(boolnames())
#define boolcodes  NCURSES_PUBLIC_VAR(boolcodes())
#define boolfnames NCURSES_PUBLIC_VAR(boolfnames())
#define numnames   NCURSES_PUBLIC_VAR(numnames())
#define numcodes   NCURSES_PUBLIC_VAR(numcodes())
#define numfnames  NCURSES_PUBLIC_VAR(numfnames())
#define strnames   NCURSES_PUBLIC_VAR(strnames())
#define strcodes   NCURSES_PUBLIC_VAR(strcodes())
#define strfnames  NCURSES_PUBLIC_VAR(strfnames())

#else

extern NCURSES_EXPORT_VAR(NCURSES_CONST char * const ) boolnames[];
extern NCURSES_EXPORT_VAR(NCURSES_CONST char * const ) boolcodes[];
extern NCURSES_EXPORT_VAR(NCURSES_CONST char * const ) boolfnames[];
extern NCURSES_EXPORT_VAR(NCURSES_CONST char * const ) numnames[];
extern NCURSES_EXPORT_VAR(NCURSES_CONST char * const ) numcodes[];
extern NCURSES_EXPORT_VAR(NCURSES_CONST char * const ) numfnames[];
extern NCURSES_EXPORT_VAR(NCURSES_CONST char * const ) strnames[];
extern NCURSES_EXPORT_VAR(NCURSES_CONST char * const ) strcodes[];
extern NCURSES_EXPORT_VAR(NCURSES_CONST char * const ) strfnames[];

#endif

/*
 * These entrypoints are used only by the ncurses utilities such as tic.
 */
#ifdef NCURSES_INTERNALS

extern NCURSES_EXPORT(int) _nc_set_tty_mode (TTY *buf);
extern NCURSES_EXPORT(int) _nc_read_entry2 (const char * const, char * const, TERMTYPE2 *const);
extern NCURSES_EXPORT(int) _nc_read_file_entry (const char *const, TERMTYPE2 *);
extern NCURSES_EXPORT(int) _nc_read_termtype (TERMTYPE2 *, char *, int);
extern NCURSES_EXPORT(char *) _nc_first_name (const char *const);
extern NCURSES_EXPORT(int) _nc_name_match (const char *const, const char *const, const char *const);

#endif /* NCURSES_INTERNALS */


/*
 * These entrypoints are used by tack 1.07.
 */
extern NCURSES_EXPORT(const TERMTYPE *) _nc_fallback (const char *);
extern NCURSES_EXPORT(int) _nc_read_entry (const char * const, char * const, TERMTYPE *const);

/*
 * Normal entry points
 */
extern NCURSES_EXPORT(TERMINAL *) set_curterm (TERMINAL *);
extern NCURSES_EXPORT(int) del_curterm (TERMINAL *);

/* miscellaneous entry points */
extern NCURSES_EXPORT(int) restartterm (NCURSES_CONST char *, int, int *);
extern NCURSES_EXPORT(int) setupterm (const char *,int,int *);

/* terminfo entry points, also declared in curses.h */
#if !defined(__NCURSES_H)
extern NCURSES_EXPORT(char *) tigetstr (const char *);
extern NCURSES_EXPORT_VAR(char) ttytype[];
extern NCURSES_EXPORT(int) putp (const char *);
extern NCURSES_EXPORT(int) tigetflag (const char *);
extern NCURSES_EXPORT(int) tigetnum (const char *);

#if 1 /* NCURSES_TPARM_VARARGS */
extern NCURSES_EXPORT(char *) tparm (const char *, ...);	/* special */
#else
extern NCURSES_EXPORT(char *) tparm (const char *, long,long,long,long,long,long,long,long,long);	/* special */
extern NCURSES_EXPORT(char *) tparm_varargs (const char *, ...);	/* special */
#endif

extern NCURSES_EXPORT(char *) tiparm (const char *, ...);		/* special */

#endif /* __NCURSES_H */

/* termcap database emulation (XPG4 uses const only for 2nd param of tgetent) */
#if !defined(NCURSES_TERMCAP_H_incl)
extern NCURSES_EXPORT(char *) tgetstr (const char *, char **);
extern NCURSES_EXPORT(char *) tgoto (const char *, int, int);
extern NCURSES_EXPORT(int) tgetent (char *, const char *);
extern NCURSES_EXPORT(int) tgetflag (const char *);
extern NCURSES_EXPORT(int) tgetnum (const char *);
extern NCURSES_EXPORT(int) tputs (const char *, int, int (*)(int));
#endif /* NCURSES_TERMCAP_H_incl */

/*
 * Include curses.h before term.h to enable these extensions.
 */
#if defined(NCURSES_SP_FUNCS) && (NCURSES_SP_FUNCS != 0)

extern NCURSES_EXPORT(char *)  NCURSES_SP_NAME(tigetstr) (SCREEN*, const char *);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(putp) (SCREEN*, const char *);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(tigetflag) (SCREEN*, const char *);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(tigetnum) (SCREEN*, const char *);

#if 1 /* NCURSES_TPARM_VARARGS */
extern NCURSES_EXPORT(char *)  NCURSES_SP_NAME(tparm) (SCREEN*, const char *, ...);	/* special */
#else
extern NCURSES_EXPORT(char *)  NCURSES_SP_NAME(tparm) (SCREEN*, const char *, long,long,long,long,long,long,long,long,long);	/* special */
extern NCURSES_EXPORT(char *)  NCURSES_SP_NAME(tparm_varargs) (SCREEN*, const char *, ...);	/* special */
#endif

/* termcap database emulation (XPG4 uses const only for 2nd param of tgetent) */
extern NCURSES_EXPORT(char *)  NCURSES_SP_NAME(tgetstr) (SCREEN*, const char *, char **);
extern NCURSES_EXPORT(char *)  NCURSES_SP_NAME(tgoto) (SCREEN*, const char *, int, int);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(tgetent) (SCREEN*, char *, const char *);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(tgetflag) (SCREEN*, const char *);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(tgetnum) (SCREEN*, const char *);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(tputs) (SCREEN*, const char *, int, NCURSES_SP_OUTC);

extern NCURSES_EXPORT(TERMINAL *) NCURSES_SP_NAME(set_curterm) (SCREEN*, TERMINAL *);
extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(del_curterm) (SCREEN*, TERMINAL *);

extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(restartterm) (SCREEN*, NCURSES_CONST char *, int, int *);
#endif /* NCURSES_SP_FUNCS */

/*
 * Debugging features.
 */
extern NCURSES_EXPORT(void)    exit_terminfo(int) GCC_NORETURN;

#ifdef __cplusplus
}
#endif

#endif /* NCURSES_TERM_H_incl */

EOF
""",
)

genrule(
    name = "include/termcap",
    outs = ["include/termcap.h"],
    cmd = r"""
cat << 'EOF' > $@
/****************************************************************************
 * Copyright 2018,2020 Thomas E. Dickey                                     *
 * Copyright 1998-2000,2001 Free Software Foundation, Inc.                  *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

/****************************************************************************
 *  Author: Zeyd M. Ben-Halim <zmbenhal@netcom.com> 1992,1995               *
 *     and: Eric S. Raymond <esr@snark.thyrsus.com>                         *
 ****************************************************************************/

/* $$Id: termcap.h.in,v 1.19 2020/02/02 23:34:34 tom Exp $$ */

#ifndef NCURSES_TERMCAP_H_incl
#define NCURSES_TERMCAP_H_incl	1

#undef  NCURSES_VERSION
#define NCURSES_VERSION "6.2"

#include <ncurses_dll.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <sys/types.h>

#undef  NCURSES_OSPEED 
#define NCURSES_OSPEED short 

extern NCURSES_EXPORT_VAR(char) PC;
extern NCURSES_EXPORT_VAR(char *) UP;
extern NCURSES_EXPORT_VAR(char *) BC;
extern NCURSES_EXPORT_VAR(NCURSES_OSPEED) ospeed; 

#if !defined(NCURSES_TERM_H_incl)
extern NCURSES_EXPORT(char *) tgetstr (const char *, char **);
extern NCURSES_EXPORT(char *) tgoto (const char *, int, int);
extern NCURSES_EXPORT(int) tgetent (char *, const char *);
extern NCURSES_EXPORT(int) tgetflag (const char *);
extern NCURSES_EXPORT(int) tgetnum (const char *);
extern NCURSES_EXPORT(int) tputs (const char *, int, int (*)(int));
#endif

#ifdef __cplusplus
}
#endif

#endif /* NCURSES_TERMCAP_H_incl */

EOF
""",
)

genrule(
    name = "include/unctrl",
    outs = ["include/unctrl.h"],
    cmd = r"""
cat << 'EOF' > $@
/****************************************************************************
 * Copyright 2020 Thomas E. Dickey                                          *
 * Copyright 1998-2001,2009 Free Software Foundation, Inc.                  *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

/****************************************************************************
 *  Author: Zeyd M. Ben-Halim <zmbenhal@netcom.com> 1992,1995               *
 *     and: Eric S. Raymond <esr@snark.thyrsus.com>                         *
 ****************************************************************************/

/*
 * unctrl.h
 *
 * Display a printable version of a control character.
 * Control characters are displayed in caret notation (^x), DELETE is displayed
 * as ^?. Printable characters are displayed as is.
 */

/* $$Id: unctrl.h.in,v 1.12 2020/02/02 23:34:34 tom Exp $$ */

#ifndef NCURSES_UNCTRL_H_incl
#define NCURSES_UNCTRL_H_incl	1

#undef  NCURSES_VERSION
#define NCURSES_VERSION "6.2"

#ifdef __cplusplus
extern "C" {
#endif

#include <curses.h>

#undef unctrl
NCURSES_EXPORT(NCURSES_CONST char *) unctrl (chtype);

#if 1
NCURSES_EXPORT(NCURSES_CONST char *) NCURSES_SP_NAME(unctrl) (SCREEN*, chtype);
#endif

#ifdef __cplusplus
}
#endif

#endif /* NCURSES_UNCTRL_H_incl */

EOF
""",
)

genrule(
    name = "include/parametrized",
    outs = ["include/parametrized.h"],
    cmd = r"""
cat << 'EOF' > $@
#ifndef PARAMETRIZED_H
#define PARAMETRIZED_H 1
/*
 * parametrized.h --- is a termcap capability parametrized?
 *
 * Note: this file is generated using MKparametrized.sh, do not edit by hand.
 * A value of -1 in the table means suppress both pad and % translations.
 * A value of 0 in the table means do pad but not % translations.
 * A value of 1 in the table means do both pad and % translations.
 */

static short const parametrized[] = {
0,	/*  cbt  */
0,	/*  bel  */
0,	/*  cr  */
1,	/*  csr  */
0,	/*  tbc  */
0,	/*  clear  */
0,	/*  el  */
0,	/*  ed  */
1,	/*  hpa  */
0,	/*  cmdch  */
1,	/*  cup  */
0,	/*  cud1  */
0,	/*  home  */
0,	/*  civis  */
0,	/*  cub1  */
1,	/*  mrcup  */
0,	/*  cnorm  */
0,	/*  cuf1  */
0,	/*  ll  */
0,	/*  cuu1  */
0,	/*  cvvis  */
0,	/*  dch1  */
0,	/*  dl1  */
0,	/*  dsl  */
0,	/*  hd  */
0,	/*  smacs  */
0,	/*  blink  */
0,	/*  bold  */
0,	/*  smcup  */
0,	/*  smdc  */
0,	/*  dim  */
0,	/*  smir  */
0,	/*  invis  */
0,	/*  prot  */
0,	/*  rev  */
0,	/*  smso  */
0,	/*  smul  */
1,	/*  ech  */
0,	/*  rmacs  */
0,	/*  sgr0  */
0,	/*  rmcup  */
0,	/*  rmdc  */
0,	/*  rmir  */
0,	/*  rmso  */
0,	/*  rmul  */
0,	/*  flash  */
0,	/*  ff  */
0,	/*  fsl  */
0,	/*  is1  */
0,	/*  is2  */
0,	/*  is3  */
0,	/*  if  */
0,	/*  ich1  */
0,	/*  il1  */
0,	/*  ip  */
0,	/*  kbs  */
0,	/*  ktbc  */
0,	/*  kclr  */
0,	/*  kctab  */
0,	/*  kdch1  */
0,	/*  kdl1  */
0,	/*  kcud1  */
0,	/*  krmir  */
0,	/*  kel  */
0,	/*  ked  */
0,	/*  kf0  */
0,	/*  kf1  */
0,	/*  kf10  */
0,	/*  kf2  */
0,	/*  kf3  */
0,	/*  kf4  */
0,	/*  kf5  */
0,	/*  kf6  */
0,	/*  kf7  */
0,	/*  kf8  */
0,	/*  kf9  */
0,	/*  khome  */
0,	/*  kich1  */
0,	/*  kil1  */
0,	/*  kcub1  */
0,	/*  kll  */
0,	/*  knp  */
0,	/*  kpp  */
0,	/*  kcuf1  */
0,	/*  kind  */
0,	/*  kri  */
0,	/*  khts  */
0,	/*  kcuu1  */
0,	/*  rmkx  */
0,	/*  smkx  */
0,	/*  lf0  */
0,	/*  lf1  */
0,	/*  lf10  */
0,	/*  lf2  */
0,	/*  lf3  */
0,	/*  lf4  */
0,	/*  lf5  */
0,	/*  lf6  */
0,	/*  lf7  */
0,	/*  lf8  */
0,	/*  lf9  */
0,	/*  rmm  */
0,	/*  smm  */
0,	/*  nel  */
0,	/*  pad  */
1,	/*  dch  */
1,	/*  dl  */
1,	/*  cud  */
1,	/*  ich  */
1,	/*  indn  */
1,	/*  il  */
1,	/*  cub  */
1,	/*  cuf  */
1,	/*  rin  */
1,	/*  cuu  */
1,	/*  pfkey  */
1,	/*  pfloc  */
1,	/*  pfx  */
0,	/*  mc0  */
0,	/*  mc4  */
0,	/*  mc5  */
1,	/*  rep  */
0,	/*  rs1  */
0,	/*  rs2  */
0,	/*  rs3  */
0,	/*  rf  */
0,	/*  rc  */
1,	/*  vpa  */
0,	/*  sc  */
0,	/*  ind  */
0,	/*  ri  */
1,	/*  sgr  */
0,	/*  hts  */
1,	/*  wind  */
0,	/*  ht  */
1,	/*  tsl  */
0,	/*  uc  */
0,	/*  hu  */
0,	/*  iprog  */
0,	/*  ka1  */
0,	/*  ka3  */
0,	/*  kb2  */
0,	/*  kc1  */
0,	/*  kc3  */
1,	/*  mc5p  */
0,	/*  rmp  */
-1,	/*  acsc  */
1,	/*  pln  */
0,	/*  kcbt  */
0,	/*  smxon  */
0,	/*  rmxon  */
0,	/*  smam  */
0,	/*  rmam  */
0,	/*  xonc  */
0,	/*  xoffc  */
0,	/*  enacs  */
0,	/*  smln  */
0,	/*  rmln  */
0,	/*  kbeg  */
0,	/*  kcan  */
0,	/*  kclo  */
0,	/*  kcmd  */
0,	/*  kcpy  */
0,	/*  kcrt  */
0,	/*  kend  */
0,	/*  kent  */
0,	/*  kext  */
0,	/*  kfnd  */
0,	/*  khlp  */
0,	/*  kmrk  */
0,	/*  kmsg  */
0,	/*  kmov  */
0,	/*  knxt  */
0,	/*  kopn  */
0,	/*  kopt  */
0,	/*  kprv  */
0,	/*  kprt  */
0,	/*  krdo  */
0,	/*  kref  */
0,	/*  krfr  */
0,	/*  krpl  */
0,	/*  krst  */
0,	/*  kres  */
0,	/*  ksav  */
0,	/*  kspd  */
0,	/*  kund  */
0,	/*  kBEG  */
0,	/*  kCAN  */
0,	/*  kCMD  */
0,	/*  kCPY  */
0,	/*  kCRT  */
0,	/*  kDC  */
0,	/*  kDL  */
0,	/*  kslt  */
0,	/*  kEND  */
0,	/*  kEOL  */
0,	/*  kEXT  */
0,	/*  kFND  */
1,	/*  kHLP  */
1,	/*  kHOM  */
1,	/*  kIC  */
1,	/*  kLFT  */
0,	/*  kMSG  */
0,	/*  kMOV  */
0,	/*  kNXT  */
0,	/*  kOPT  */
0,	/*  kPRV  */
0,	/*  kPRT  */
0,	/*  kRDO  */
0,	/*  kRPL  */
0,	/*  kRIT  */
0,	/*  kRES  */
0,	/*  kSAV  */
0,	/*  kSPD  */
0,	/*  kUND  */
0,	/*  rfi  */
0,	/*  kf11  */
0,	/*  kf12  */
0,	/*  kf13  */
0,	/*  kf14  */
0,	/*  kf15  */
0,	/*  kf16  */
0,	/*  kf17  */
0,	/*  kf18  */
0,	/*  kf19  */
0,	/*  kf20  */
0,	/*  kf21  */
0,	/*  kf22  */
0,	/*  kf23  */
0,	/*  kf24  */
0,	/*  kf25  */
0,	/*  kf26  */
0,	/*  kf27  */
0,	/*  kf28  */
0,	/*  kf29  */
0,	/*  kf30  */
0,	/*  kf31  */
0,	/*  kf32  */
0,	/*  kf33  */
0,	/*  kf34  */
0,	/*  kf35  */
0,	/*  kf36  */
0,	/*  kf37  */
0,	/*  kf38  */
0,	/*  kf39  */
0,	/*  kf40  */
0,	/*  kf41  */
0,	/*  kf42  */
0,	/*  kf43  */
0,	/*  kf44  */
0,	/*  kf45  */
0,	/*  kf46  */
0,	/*  kf47  */
0,	/*  kf48  */
0,	/*  kf49  */
0,	/*  kf50  */
0,	/*  kf51  */
0,	/*  kf52  */
0,	/*  kf53  */
0,	/*  kf54  */
0,	/*  kf55  */
0,	/*  kf56  */
0,	/*  kf57  */
0,	/*  kf58  */
0,	/*  kf59  */
0,	/*  kf60  */
0,	/*  kf61  */
0,	/*  kf62  */
0,	/*  kf63  */
0,	/*  el1  */
0,	/*  mgc  */
0,	/*  smgl  */
0,	/*  smgr  */
-1,	/*  fln  */
1,	/*  sclk  */
0,	/*  dclk  */
0,	/*  rmclk  */
1,	/*  cwin  */
1,	/*  wingo  */
0,	/*  hup  */
1,	/*  dial  */
1,	/*  qdial  */
0,	/*  tone  */
0,	/*  pulse  */
0,	/*  hook  */
0,	/*  pause  */
0,	/*  wait  */
1,	/*  u0  */
1,	/*  u1  */
1,	/*  u2  */
1,	/*  u3  */
1,	/*  u4  */
1,	/*  u5  */
1,	/*  u6  */
1,	/*  u7  */
1,	/*  u8  */
1,	/*  u9  */
0,	/*  op  */
0,	/*  oc  */
1,	/*  initc  */
1,	/*  initp  */
1,	/*  scp  */
1,	/*  setf  */
1,	/*  setb  */
1,	/*  cpi  */
1,	/*  lpi  */
1,	/*  chr  */
1,	/*  cvr  */
1,	/*  defc  */
0,	/*  swidm  */
0,	/*  sdrfq  */
0,	/*  sitm  */
0,	/*  slm  */
0,	/*  smicm  */
0,	/*  snlq  */
0,	/*  snrmq  */
0,	/*  sshm  */
0,	/*  ssubm  */
0,	/*  ssupm  */
0,	/*  sum  */
0,	/*  rwidm  */
0,	/*  ritm  */
0,	/*  rlm  */
0,	/*  rmicm  */
0,	/*  rshm  */
0,	/*  rsubm  */
0,	/*  rsupm  */
0,	/*  rum  */
0,	/*  mhpa  */
0,	/*  mcud1  */
0,	/*  mcub1  */
0,	/*  mcuf1  */
1,	/*  mvpa  */
0,	/*  mcuu1  */
0,	/*  porder  */
0,	/*  mcud  */
0,	/*  mcub  */
0,	/*  mcuf  */
0,	/*  mcuu  */
1,	/*  scs  */
0,	/*  smgb  */
1,	/*  smgbp  */
1,	/*  smglp  */
1,	/*  smgrp  */
0,	/*  smgt  */
1,	/*  smgtp  */
0,	/*  sbim  */
1,	/*  scsd  */
0,	/*  rbim  */
1,	/*  rcsd  */
0,	/*  subcs  */
0,	/*  supcs  */
0,	/*  docr  */
0,	/*  zerom  */
1,	/*  csnm  */
0,	/*  kmous  */
0,	/*  minfo  */
0,	/*  reqmp  */
1,	/*  getm  */
1,	/*  setaf  */
1,	/*  setab  */
1,	/*  pfxl  */
0,	/*  devt  */
0,	/*  csin  */
0,	/*  s0ds  */
0,	/*  s1ds  */
0,	/*  s2ds  */
0,	/*  s3ds  */
1,	/*  smglr  */
1,	/*  smgtb  */
1,	/*  birep  */
0,	/*  binel  */
0,	/*  bicr  */
1,	/*  colornm  */
0,	/*  defbi  */
0,	/*  endbi  */
1,	/*  setcolor  */
1,	/*  slines  */
1,	/*  dispc  */
0,	/*  smpch  */
0,	/*  rmpch  */
0,	/*  smsc  */
0,	/*  rmsc  */
0,	/*  pctrm  */
0,	/*  scesc  */
0,	/*  scesa  */
0,	/*  ehhlm  */
0,	/*  elhlm  */
0,	/*  elohlm  */
0,	/*  erhlm  */
0,	/*  ethlm  */
0,	/*  evhlm  */
1,	/*  sgr1  */
1,	/*  slength  */
0,	/*  OTi2  */
0,	/*  OTrs  */
0,	/*  OTnl  */
0,	/*  OTbc  */
0,	/*  OTko  */
0,	/*  OTma  */
-1,	/*  OTG2  */
-1,	/*  OTG3  */
-1,	/*  OTG1  */
-1,	/*  OTG4  */
-1,	/*  OTGR  */
-1,	/*  OTGL  */
-1,	/*  OTGU  */
-1,	/*  OTGD  */
-1,	/*  OTGH  */
-1,	/*  OTGV  */
-1,	/*  OTGC  */
0,	/*  meml  */
0,	/*  memu  */
0,	/*  box1  */
} /* 414 entries */;

#endif /* PARAMETRIZED_H */

EOF
""",
)

genrule(
    name = "include/hashsize",
    outs = ["include/hashsize.h"],
    cmd = r"""
cat << 'EOF' > $@
/*
 * hashsize.h -- hash and token table constants
 */

#define CAPTABSIZE	497
#define HASHTABSIZE	(497 * 2)

EOF
""",
)

genrule(
    name = "ncurses/codes",
    outs = ["ncurses/codes.c"],
    cmd = r"""
cat << 'EOF' > $@
/* This file was generated by MKcodes.awk */

#include <curses.priv.h>

#define IT NCURSES_CONST char * const


#if BROKEN_LINKER || USE_REENTRANT

static const char _nc_code_blob[] = 
"bw\0" "am\0" "xb\0" "xs\0" "xn\0" "eo\0" "gn\0" "hc\0" "km\0" "hs\0" "in\0" \
"da\0" "db\0" "mi\0" "ms\0" "os\0" "es\0" "xt\0" "hz\0" "ul\0" "xo\0" "nx\0" \
"5i\0" "HC\0" "NR\0" "NP\0" "ND\0" "cc\0" "ut\0" "hl\0" "YA\0" "YB\0" "YC\0" \
"YD\0" "YE\0" "YF\0" "YG\0" "co\0" "it\0" "li\0" "lm\0" "sg\0" "pb\0" "vt\0" \
"ws\0" "Nl\0" "lh\0" "lw\0" "ma\0" "MW\0" "Co\0" "pa\0" "NC\0" "Ya\0" "Yb\0" \
"Yc\0" "Yd\0" "Ye\0" "Yf\0" "Yg\0" "Yh\0" "Yi\0" "Yj\0" "Yk\0" "Yl\0" "Ym\0" \
"Yn\0" "BT\0" "Yo\0" "Yp\0" "bt\0" "bl\0" "cr\0" "cs\0" "ct\0" "cl\0" "ce\0" \
"cd\0" "ch\0" "CC\0" "cm\0" "do\0" "ho\0" "vi\0" "le\0" "CM\0" "ve\0" "nd\0" \
"ll\0" "up\0" "vs\0" "dc\0" "dl\0" "ds\0" "hd\0" "as\0" "mb\0" "md\0" "ti\0" \
"dm\0" "mh\0" "im\0" "mk\0" "mp\0" "mr\0" "so\0" "us\0" "ec\0" "ae\0" "me\0" \
"te\0" "ed\0" "ei\0" "se\0" "ue\0" "vb\0" "ff\0" "fs\0" "i1\0" "is\0" "i3\0" \
"if\0" "ic\0" "al\0" "ip\0" "kb\0" "ka\0" "kC\0" "kt\0" "kD\0" "kL\0" "kd\0" \
"kM\0" "kE\0" "kS\0" "k0\0" "k1\0" "k;\0" "k2\0" "k3\0" "k4\0" "k5\0" "k6\0" \
"k7\0" "k8\0" "k9\0" "kh\0" "kI\0" "kA\0" "kl\0" "kH\0" "kN\0" "kP\0" "kr\0" \
"kF\0" "kR\0" "kT\0" "ku\0" "ke\0" "ks\0" "l0\0" "l1\0" "la\0" "l2\0" "l3\0" \
"l4\0" "l5\0" "l6\0" "l7\0" "l8\0" "l9\0" "mo\0" "mm\0" "nw\0" "pc\0" "DC\0" \
"DL\0" "DO\0" "IC\0" "SF\0" "AL\0" "LE\0" "RI\0" "SR\0" "UP\0" "pk\0" "pl\0" \
"px\0" "ps\0" "pf\0" "po\0" "rp\0" "r1\0" "r2\0" "r3\0" "rf\0" "rc\0" "cv\0" \
"sc\0" "sf\0" "sr\0" "sa\0" "st\0" "wi\0" "ta\0" "ts\0" "uc\0" "hu\0" "iP\0" \
"K1\0" "K3\0" "K2\0" "K4\0" "K5\0" "pO\0" "rP\0" "ac\0" "pn\0" "kB\0" "SX\0" \
"RX\0" "SA\0" "RA\0" "XN\0" "XF\0" "eA\0" "LO\0" "LF\0" "@1\0" "@2\0" "@3\0" \
"@4\0" "@5\0" "@6\0" "@7\0" "@8\0" "@9\0" "@0\0" "%1\0" "%2\0" "%3\0" "%4\0" \
"%5\0" "%6\0" "%7\0" "%8\0" "%9\0" "%0\0" "&1\0" "&2\0" "&3\0" "&4\0" "&5\0" \
"&6\0" "&7\0" "&8\0" "&9\0" "&0\0" "*1\0" "*2\0" "*3\0" "*4\0" "*5\0" "*6\0" \
"*7\0" "*8\0" "*9\0" "*0\0" "#1\0" "#2\0" "#3\0" "#4\0" "%a\0" "%b\0" "%c\0" \
"%d\0" "%e\0" "%f\0" "%g\0" "%h\0" "%i\0" "%j\0" "!1\0" "!2\0" "!3\0" "RF\0" \
"F1\0" "F2\0" "F3\0" "F4\0" "F5\0" "F6\0" "F7\0" "F8\0" "F9\0" "FA\0" "FB\0" \
"FC\0" "FD\0" "FE\0" "FF\0" "FG\0" "FH\0" "FI\0" "FJ\0" "FK\0" "FL\0" "FM\0" \
"FN\0" "FO\0" "FP\0" "FQ\0" "FR\0" "FS\0" "FT\0" "FU\0" "FV\0" "FW\0" "FX\0" \
"FY\0" "FZ\0" "Fa\0" "Fb\0" "Fc\0" "Fd\0" "Fe\0" "Ff\0" "Fg\0" "Fh\0" "Fi\0" \
"Fj\0" "Fk\0" "Fl\0" "Fm\0" "Fn\0" "Fo\0" "Fp\0" "Fq\0" "Fr\0" "cb\0" "MC\0" \
"ML\0" "MR\0" "Lf\0" "SC\0" "DK\0" "RC\0" "CW\0" "WG\0" "HU\0" "DI\0" "QD\0" \
"TO\0" "PU\0" "fh\0" "PA\0" "WA\0" "u0\0" "u1\0" "u2\0" "u3\0" "u4\0" "u5\0" \
"u6\0" "u7\0" "u8\0" "u9\0" "op\0" "oc\0" "Ic\0" "Ip\0" "sp\0" "Sf\0" "Sb\0" \
"ZA\0" "ZB\0" "ZC\0" "ZD\0" "ZE\0" "ZF\0" "ZG\0" "ZH\0" "ZI\0" "ZJ\0" "ZK\0" \
"ZL\0" "ZM\0" "ZN\0" "ZO\0" "ZP\0" "ZQ\0" "ZR\0" "ZS\0" "ZT\0" "ZU\0" "ZV\0" \
"ZW\0" "ZX\0" "ZY\0" "ZZ\0" "Za\0" "Zb\0" "Zc\0" "Zd\0" "Ze\0" "Zf\0" "Zg\0" \
"Zh\0" "Zi\0" "Zj\0" "Zk\0" "Zl\0" "Zm\0" "Zn\0" "Zo\0" "Zp\0" "Zq\0" "Zr\0" \
"Zs\0" "Zt\0" "Zu\0" "Zv\0" "Zw\0" "Zx\0" "Zy\0" "Km\0" "Mi\0" "RQ\0" "Gm\0" \
"AF\0" "AB\0" "xl\0" "dv\0" "ci\0" "s0\0" "s1\0" "s2\0" "s3\0" "ML\0" "MT\0" \
"Xy\0" "Zz\0" "Yv\0" "Yw\0" "Yx\0" "Yy\0" "Yz\0" "YZ\0" "S1\0" "S2\0" "S3\0" \
"S4\0" "S5\0" "S6\0" "S7\0" "S8\0" "Xh\0" "Xl\0" "Xo\0" "Xr\0" "Xt\0" "Xv\0" \
"sA\0" "YI\0" "i2\0" "rs\0" "ug\0" "bs\0" "ns\0" "nc\0" "dC\0" "dN\0" "nl\0" \
"bc\0" "MT\0" "NL\0" "dB\0" "dT\0" "kn\0" "ko\0" "ma\0" "pt\0" "xr\0" "G2\0" \
"G3\0" "G1\0" "G4\0" "GR\0" "GL\0" "GU\0" "GD\0" "GH\0" "GV\0" "GC\0" "ml\0" \
"mu\0" "bx\0" ;
static const short _nc_offset_boolcodes[] = {
0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42,
45, 48, 51, 54, 57, 60, 63, 66, 69, 72, 75, 78, 81, 84, 87,
90, 93, 96, 99, 102, 105, 108, 1401, 1404, 1407, 1422, 1425, 1443, 1446, };

static NCURSES_CONST char ** ptr_boolcodes = 0;

static const short _nc_offset_numcodes[] = {
111, 114, 117, 120, 123, 126,
129, 132, 135, 138, 141, 144, 147, 150, 153, 156, 159, 162,
165, 168, 171, 174, 177, 180, 183, 186, 189, 192, 195, 198,
201, 204, 207, 1398, 1410, 1413, 1428, 1431, 1434, };

static NCURSES_CONST char ** ptr_numcodes = 0;

static const short _nc_offset_strcodes[] = {
210, 213, 216, 219, 222, 225, 228, 231, 234,
237, 240, 243, 246, 249, 252, 255, 258, 261, 264, 267, 270,
273, 276, 279, 282, 285, 288, 291, 294, 297, 300, 303, 306,
309, 312, 315, 318, 321, 324, 327, 330, 333, 336, 339, 342,
345, 348, 351, 354, 357, 360, 363, 366, 369, 372, 375, 378,
381, 384, 387, 390, 393, 396, 399, 402, 405, 408, 411, 414,
417, 420, 423, 426, 429, 432, 435, 438, 441, 444, 447, 450,
453, 456, 459, 462, 465, 468, 471, 474, 477, 480, 483, 486,
489, 492, 495, 498, 501, 504, 507, 510, 513, 516, 519, 522,
525, 528, 531, 534, 537, 540, 543, 546, 549, 552, 555, 558,
561, 564, 567, 570, 573, 576, 579, 582, 585, 588, 591, 594,
597, 600, 603, 606, 609, 612, 615, 618, 621, 624, 627, 630,
633, 636, 639, 642, 645, 648, 651, 654, 657, 660, 663, 666,
669, 672, 675, 678, 681, 684, 687, 690, 693, 696, 699, 702,
705, 708, 711, 714, 717, 720, 723, 726, 729, 732, 735, 738,
741, 744, 747, 750, 753, 756, 759, 762, 765, 768, 771, 774,
777, 780, 783, 786, 789, 792, 795, 798, 801, 804, 807, 810,
813, 816, 819, 822, 825, 828, 831, 834, 837, 840, 843, 846,
849, 852, 855, 858, 861, 864, 867, 870, 873, 876, 879, 882,
885, 888, 891, 894, 897, 900, 903, 906, 909, 912, 915, 918,
921, 924, 927, 930, 933, 936, 939, 942, 945, 948, 951, 954,
957, 960, 963, 966, 969, 972, 975, 978, 981, 984, 987, 990,
993, 996, 999, 1002, 1005, 1008, 1011, 1014, 1017, 1020, 1023,
1026, 1029, 1032, 1035, 1038, 1041, 1044, 1047, 1050, 1053, 1056,
1059, 1062, 1065, 1068, 1071, 1074, 1077, 1080, 1083, 1086, 1089,
1092, 1095, 1098, 1101, 1104, 1107, 1110, 1113, 1116, 1119, 1122,
1125, 1128, 1131, 1134, 1137, 1140, 1143, 1146, 1149, 1152, 1155,
1158, 1161, 1164, 1167, 1170, 1173, 1176, 1179, 1182, 1185, 1188,
1191, 1194, 1197, 1200, 1203, 1206, 1209, 1212, 1215, 1218, 1221,
1224, 1227, 1230, 1233, 1236, 1239, 1242, 1245, 1248, 1251, 1254,
1257, 1260, 1263, 1266, 1269, 1272, 1275, 1278, 1281, 1284, 1287,
1290, 1293, 1296, 1299, 1302, 1305, 1308, 1311, 1314, 1317, 1320,
1323, 1326, 1329, 1332, 1335, 1338, 1341, 1344, 1347, 1350, 1353,
1356, 1359, 1362, 1365, 1368, 1371, 1374, 1377, 1380, 1383, 1386,
1389, 1392, 1395, 1416, 1419,
1437, 1440, 1449, 1452,
1455, 1458, 1461, 1464, 1467, 1470, 1473, 1476, 1479, 1482, 1485,
1488, };

static NCURSES_CONST char ** ptr_strcodes = 0;


static IT *
alloc_array(NCURSES_CONST char ***value, const short *offsets, unsigned size)
{
	if (*value == 0) {
		if ((*value = typeCalloc(NCURSES_CONST char *, size + 1)) != 0) {
			unsigned n;
			for (n = 0; n < size; ++n) {
				(*value)[n] = (NCURSES_CONST char *) _nc_code_blob + offsets[n];
			}
		}
	}
	return *value;
}

#define FIX(it) NCURSES_IMPEXP IT * NCURSES_API NCURSES_PUBLIC_VAR(it)(void) { return alloc_array(&ptr_##it, _nc_offset_##it, SIZEOF(_nc_offset_##it)); }

/* remove public definition which conflicts with FIX() */
#undef boolcodes
#undef numcodes
#undef strcodes

/* add local definition */
FIX(boolcodes)
FIX(numcodes)
FIX(strcodes)

/* restore the public definition */

#define FREE_FIX(it) if (ptr_##it) { FreeAndNull(ptr_##it); }
#define boolcodes  NCURSES_PUBLIC_VAR(boolcodes())
#define numcodes   NCURSES_PUBLIC_VAR(numcodes())
#define strcodes   NCURSES_PUBLIC_VAR(strcodes())

#if NO_LEAKS
NCURSES_EXPORT(void)
_nc_codes_leaks(void)
{
FREE_FIX(boolcodes)
FREE_FIX(numcodes)
FREE_FIX(strcodes)
}
#endif

#else

#define DCL(it) NCURSES_EXPORT_VAR(IT) it[]

DCL(boolcodes) = {
		"bw",
		"am",
		"xb",
		"xs",
		"xn",
		"eo",
		"gn",
		"hc",
		"km",
		"hs",
		"in",
		"da",
		"db",
		"mi",
		"ms",
		"os",
		"es",
		"xt",
		"hz",
		"ul",
		"xo",
		"nx",
		"5i",
		"HC",
		"NR",
		"NP",
		"ND",
		"cc",
		"ut",
		"hl",
		"YA",
		"YB",
		"YC",
		"YD",
		"YE",
		"YF",
		"YG",
		"bs",
		"ns",
		"nc",
		"MT",
		"NL",
		"pt",
		"xr",

		(NCURSES_CONST char *)0,
};

DCL(numcodes) = {
		"co",
		"it",
		"li",
		"lm",
		"sg",
		"pb",
		"vt",
		"ws",
		"Nl",
		"lh",
		"lw",
		"ma",
		"MW",
		"Co",
		"pa",
		"NC",
		"Ya",
		"Yb",
		"Yc",
		"Yd",
		"Ye",
		"Yf",
		"Yg",
		"Yh",
		"Yi",
		"Yj",
		"Yk",
		"Yl",
		"Ym",
		"Yn",
		"BT",
		"Yo",
		"Yp",
		"ug",
		"dC",
		"dN",
		"dB",
		"dT",
		"kn",

		(NCURSES_CONST char *)0,
};

DCL(strcodes) = {
		"bt",
		"bl",
		"cr",
		"cs",
		"ct",
		"cl",
		"ce",
		"cd",
		"ch",
		"CC",
		"cm",
		"do",
		"ho",
		"vi",
		"le",
		"CM",
		"ve",
		"nd",
		"ll",
		"up",
		"vs",
		"dc",
		"dl",
		"ds",
		"hd",
		"as",
		"mb",
		"md",
		"ti",
		"dm",
		"mh",
		"im",
		"mk",
		"mp",
		"mr",
		"so",
		"us",
		"ec",
		"ae",
		"me",
		"te",
		"ed",
		"ei",
		"se",
		"ue",
		"vb",
		"ff",
		"fs",
		"i1",
		"is",
		"i3",
		"if",
		"ic",
		"al",
		"ip",
		"kb",
		"ka",
		"kC",
		"kt",
		"kD",
		"kL",
		"kd",
		"kM",
		"kE",
		"kS",
		"k0",
		"k1",
		"k;",
		"k2",
		"k3",
		"k4",
		"k5",
		"k6",
		"k7",
		"k8",
		"k9",
		"kh",
		"kI",
		"kA",
		"kl",
		"kH",
		"kN",
		"kP",
		"kr",
		"kF",
		"kR",
		"kT",
		"ku",
		"ke",
		"ks",
		"l0",
		"l1",
		"la",
		"l2",
		"l3",
		"l4",
		"l5",
		"l6",
		"l7",
		"l8",
		"l9",
		"mo",
		"mm",
		"nw",
		"pc",
		"DC",
		"DL",
		"DO",
		"IC",
		"SF",
		"AL",
		"LE",
		"RI",
		"SR",
		"UP",
		"pk",
		"pl",
		"px",
		"ps",
		"pf",
		"po",
		"rp",
		"r1",
		"r2",
		"r3",
		"rf",
		"rc",
		"cv",
		"sc",
		"sf",
		"sr",
		"sa",
		"st",
		"wi",
		"ta",
		"ts",
		"uc",
		"hu",
		"iP",
		"K1",
		"K3",
		"K2",
		"K4",
		"K5",
		"pO",
		"rP",
		"ac",
		"pn",
		"kB",
		"SX",
		"RX",
		"SA",
		"RA",
		"XN",
		"XF",
		"eA",
		"LO",
		"LF",
		"@1",
		"@2",
		"@3",
		"@4",
		"@5",
		"@6",
		"@7",
		"@8",
		"@9",
		"@0",
		"%1",
		"%2",
		"%3",
		"%4",
		"%5",
		"%6",
		"%7",
		"%8",
		"%9",
		"%0",
		"&1",
		"&2",
		"&3",
		"&4",
		"&5",
		"&6",
		"&7",
		"&8",
		"&9",
		"&0",
		"*1",
		"*2",
		"*3",
		"*4",
		"*5",
		"*6",
		"*7",
		"*8",
		"*9",
		"*0",
		"#1",
		"#2",
		"#3",
		"#4",
		"%a",
		"%b",
		"%c",
		"%d",
		"%e",
		"%f",
		"%g",
		"%h",
		"%i",
		"%j",
		"!1",
		"!2",
		"!3",
		"RF",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"FA",
		"FB",
		"FC",
		"FD",
		"FE",
		"FF",
		"FG",
		"FH",
		"FI",
		"FJ",
		"FK",
		"FL",
		"FM",
		"FN",
		"FO",
		"FP",
		"FQ",
		"FR",
		"FS",
		"FT",
		"FU",
		"FV",
		"FW",
		"FX",
		"FY",
		"FZ",
		"Fa",
		"Fb",
		"Fc",
		"Fd",
		"Fe",
		"Ff",
		"Fg",
		"Fh",
		"Fi",
		"Fj",
		"Fk",
		"Fl",
		"Fm",
		"Fn",
		"Fo",
		"Fp",
		"Fq",
		"Fr",
		"cb",
		"MC",
		"ML",
		"MR",
		"Lf",
		"SC",
		"DK",
		"RC",
		"CW",
		"WG",
		"HU",
		"DI",
		"QD",
		"TO",
		"PU",
		"fh",
		"PA",
		"WA",
		"u0",
		"u1",
		"u2",
		"u3",
		"u4",
		"u5",
		"u6",
		"u7",
		"u8",
		"u9",
		"op",
		"oc",
		"Ic",
		"Ip",
		"sp",
		"Sf",
		"Sb",
		"ZA",
		"ZB",
		"ZC",
		"ZD",
		"ZE",
		"ZF",
		"ZG",
		"ZH",
		"ZI",
		"ZJ",
		"ZK",
		"ZL",
		"ZM",
		"ZN",
		"ZO",
		"ZP",
		"ZQ",
		"ZR",
		"ZS",
		"ZT",
		"ZU",
		"ZV",
		"ZW",
		"ZX",
		"ZY",
		"ZZ",
		"Za",
		"Zb",
		"Zc",
		"Zd",
		"Ze",
		"Zf",
		"Zg",
		"Zh",
		"Zi",
		"Zj",
		"Zk",
		"Zl",
		"Zm",
		"Zn",
		"Zo",
		"Zp",
		"Zq",
		"Zr",
		"Zs",
		"Zt",
		"Zu",
		"Zv",
		"Zw",
		"Zx",
		"Zy",
		"Km",
		"Mi",
		"RQ",
		"Gm",
		"AF",
		"AB",
		"xl",
		"dv",
		"ci",
		"s0",
		"s1",
		"s2",
		"s3",
		"ML",
		"MT",
		"Xy",
		"Zz",
		"Yv",
		"Yw",
		"Yx",
		"Yy",
		"Yz",
		"YZ",
		"S1",
		"S2",
		"S3",
		"S4",
		"S5",
		"S6",
		"S7",
		"S8",
		"Xh",
		"Xl",
		"Xo",
		"Xr",
		"Xt",
		"Xv",
		"sA",
		"YI",
		"i2",
		"rs",
		"nl",
		"bc",
		"ko",
		"ma",
		"G2",
		"G3",
		"G1",
		"G4",
		"GR",
		"GL",
		"GU",
		"GD",
		"GH",
		"GV",
		"GC",
		"ml",
		"mu",
		"bx",

		(NCURSES_CONST char *)0,
};


#endif /* BROKEN_LINKER */

EOF
""",
)

genrule(
    name = "ncurses/expanded",
    outs = ["ncurses/expanded.c"],
    cmd = r"""
cat << 'EOF' > $@
/* generated by MKexpanded.sh */
#define NEED_NCURSES_CH_T 1
#include <curses.priv.h>

#ifndef CUR
#define CUR SP_TERMTYPE
#endif

#if NCURSES_EXPANDED
 void
_nc_toggle_attr_on (attr_t *S, attr_t at)
{
 { if (((int)((((unsigned long)(at) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8))) > 0) { (*S) = ((*S) & ALL_BUT_COLOR) | (attr_t) (at); } else { (*S) |= (attr_t) (at); } ;};
}

 void
_nc_toggle_attr_off (attr_t *S, attr_t at)
{
 { if (((int)((((unsigned long)(at) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8))) > 0) { (*S) &= ~(at|((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))); } else { (*S) &= ~(at); } ;};
}

 int
_nc_DelCharCost_sp (SCREEN *sp, int count)
{
 return (((cur_term)->type2. Strings[105] != 0) ? sp->_dch_cost : (((cur_term)->type2. Strings[21] != 0) ? (sp->_dch1_cost * count) : 1000000));
}

 int
_nc_InsCharCost_sp (SCREEN *sp, int count)
{
 return (((cur_term)->type2. Strings[108] != 0) ? sp->_ich_cost : (((cur_term)->type2. Strings[31] && (cur_term)->type2. Strings[42]) ? sp->_smir_cost + sp->_rmir_cost + (sp->_ip_cost * count) : (((cur_term)->type2. Strings[52] != 0) ? ((sp->_ich1_cost + sp->_ip_cost) * count) : 1000000)));
}

 void
_nc_UpdateAttrs_sp (SCREEN *sp, const cchar_t * c)
{
 if (!((((*((sp)->_current_attr))).attr) == (((*c)).attr) && ((((*((sp)->_current_attr))).ext_color) ? (((*((sp)->_current_attr))).ext_color) : ((int)((((unsigned long)((((*((sp)->_current_attr))).attr)) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8)))) == ((((*c)).ext_color) ? (((*c)).ext_color) : ((int)((((unsigned long)((((*c)).attr)) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8)))))) { do { int vid_pair = ((((*c)).ext_color) ? (((*c)).ext_color) : ((int)((((unsigned long)((((*c)).attr)) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8)))); vid_puts_sp( sp, (((*c)).attr), (short) ((((*c)).ext_color) ? (((*c)).ext_color) : ((int)((((unsigned long)((((*c)).attr)) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8)))), &vid_pair, _nc_outch_sp); } while (0); };
}

#if NCURSES_SP_FUNCS
 int
_nc_DelCharCost (int count)
{
 return _nc_DelCharCost_sp (SP, count);
}

 int
_nc_InsCharCost (int count)
{
 return _nc_InsCharCost_sp(SP, count);
}

 void
_nc_UpdateAttrs (const cchar_t * c)
{
 _nc_UpdateAttrs_sp(SP,c);
}
#endif
#else /* ! NCURSES_EXPANDED */
NCURSES_EXPORT(void) _nc_expanded (void) { }
#endif /* NCURSES_EXPANDED */

EOF
""",
)

genrule(
    name = "ncurses/fallback",
    outs = ["ncurses/fallback.c"],
    cmd = r"""
cat << 'EOF' > $@
/* This file was generated by thirdparty/ncurses/ncurses-6.2/ncurses/tinfo/MKfallback.sh */

/*
 * DO NOT EDIT THIS FILE BY HAND!
 */

#include <curses.priv.h>

NCURSES_EXPORT(const TERMTYPE2 *)
_nc_fallback2 (const char *name GCC_UNUSED)
{
	/* the fallback list is empty */
    return((const TERMTYPE2 *)0);
}

#if NCURSES_EXT_NUMBERS
#undef _nc_fallback

/*
 * This entrypoint is used by tack 1.07
 */
NCURSES_EXPORT(const TERMTYPE *)
_nc_fallback (const char *name)
{
    const TERMTYPE2 *tp = _nc_fallback2(name);
    const TERMTYPE *result = 0;
    if (tp != 0) {
	static TERMTYPE temp;
	_nc_export_termtype2(&temp, tp);
	result = &temp;
    }
    return result;
}
#endif

EOF
""",
)

genrule(
    name = "ncurses/lib_gen",
    outs = ["ncurses/lib_gen.c"],
    cmd = r"""
cat << 'EOF' > $@
/* This file was generated by thirdparty/ncurses/ncurses-6.2/ncurses/base/MKlib_gen.sh generated */

/*
 * DO NOT EDIT THIS FILE BY HAND!
 *
 * This is a file of trivial functions generated from macro
 * definitions in curses.h to satisfy the XSI Curses requirement
 * that every macro also exist as a callable function.
 *
 * It will never be linked unless you call one of the entry
 * points with its normal macro definition disabled. In that
 * case, if you have no shared libraries, it will indirectly
 * pull most of the rest of the library into your link image.
 */
#define NCURSES_ATTR_T int
#include <ncurses_cfg.h>

#undef NCURSES_NOMACROS /* _this_ file uses macros */

#include <curses.priv.h>

NCURSES_EXPORT(int) (addch) (const chtype z)
{
	T((T_CALLED("addch(%s)"), _tracechtype2(0,z)));
	returnCode(waddch(stdscr,(z)));
}
NCURSES_EXPORT(int) (addchnstr) (const chtype * a1, int z)
{
	T((T_CALLED("addchnstr(%p,%d)"), (const void *)a1, z));
	returnCode(waddchnstr(stdscr,(a1),(z)));
}
NCURSES_EXPORT(int) (addchstr) (const chtype * z)
{
	T((T_CALLED("addchstr(%p)"), (const void *)z));
	returnCode(waddchnstr(stdscr,(z),-1));
}
NCURSES_EXPORT(int) (addnstr) (const char * a1, int z)
{
	T((T_CALLED("addnstr(%s,%d)"), _nc_visbuf2(0,a1), z));
	returnCode(waddnstr(stdscr,(a1),(z)));
}
NCURSES_EXPORT(int) (addstr) (const char * z)
{
	T((T_CALLED("addstr(%s)"), _nc_visbuf2(0,z)));
	returnCode(waddnstr(stdscr,(z),-1));
}
NCURSES_EXPORT(int) (attroff) (int z)
{
	T((T_CALLED("attroff(%s)"), _traceattr2(0,(chtype)z)));
	returnCode(wattr_off(stdscr, (attr_t)((z)), ((void *)0)));
}
NCURSES_EXPORT(int) (attron) (int z)
{
	T((T_CALLED("attron(%s)"), _traceattr2(0,(chtype)z)));
	returnCode(wattr_on(stdscr, (attr_t)((z)), ((void *)0)));
}
NCURSES_EXPORT(int) (attrset) (int z)
{
	T((T_CALLED("attrset(%s)"), _traceattr2(0,(chtype)z)));
	returnIntAttr((attr_t)((0 != (const void *)((stdscr))) ? ((stdscr)->_color = (int)(((int)((((unsigned long)(((z))) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8)))), (stdscr)->_attrs = (attr_t)((z)), (0)) : (-1)));
}
NCURSES_EXPORT(int) (attr_get) (attr_t * a1, short * a2, void * z GCC_UNUSED)
{
	T((T_CALLED("attr_get(%p,%p,%p)"), (const void *)a1, (const void *)a2, (const void *)z));
	returnCode(((0 != (const void *)((stdscr))) ? ((void)((0 != (const void *)(((a1)))) ? (*((a1)) = (stdscr)->_attrs) : (0)), (void)((0 != (const void *)(((a2)))) ? (*((a2)) = (short) (stdscr)->_color) : (0)), (void)((0 != (const void *)(((z)))) ? (*(int *)((z)) = (stdscr)->_color) : (0)), (0)) : (-1)));
}
NCURSES_EXPORT(int) (attr_off) (attr_t a1, void * z)
{
	T((T_CALLED("attr_off(%s,%p)"), _traceattr2(0,a1), (const void *)z));
	returnCode(wattr_off(stdscr,(a1),(z)));
}
NCURSES_EXPORT(int) (attr_on) (attr_t a1, void * z)
{
	T((T_CALLED("attr_on(%s,%p)"), _traceattr2(0,a1), (const void *)z));
	returnCode(wattr_on(stdscr,(a1),(z)));
}
NCURSES_EXPORT(int) (attr_set) (attr_t a1, short a2, void * z GCC_UNUSED)
{
	T((T_CALLED("attr_set(%s,%#lx,%p)"), _traceattr2(0,a1), (long)a2, (const void *)z));
	returnCode(((0 != (const void *)((stdscr))) ? ((void)((stdscr)->_attrs = (((a1)) & ~((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))), (stdscr)->_color = ((z)) ? *(int *)((z)) : ((a2))), (0)) : (-1)));
}
NCURSES_EXPORT(int) (bkgd) (chtype z)
{
	T((T_CALLED("bkgd(%s)"), _tracechtype2(0,z)));
	returnCode(wbkgd(stdscr,(z)));
}
NCURSES_EXPORT(void) (bkgdset) (chtype z)
{
	T((T_CALLED("bkgdset(%s)"), _tracechtype2(0,z)));
	wbkgdset(stdscr,(z));
	returnVoid;
}
NCURSES_EXPORT(int) (border) (chtype a1, chtype a2, chtype a3, chtype a4, chtype a5, chtype a6, chtype a7, chtype z)
{
	T((T_CALLED("border(%s,%s,%s,%s,%s,%s,%s,%s)"), _tracechtype2(0,a1), _tracechtype2(1,a2), _tracechtype2(2,a3), _tracechtype2(3,a4), _tracechtype2(4,a5), _tracechtype2(5,a6), _tracechtype2(6,a7), _tracechtype2(7,z)));
	returnCode(wborder(stdscr, a1, a2, a3, a4, a5, a6, a7, z));
}
NCURSES_EXPORT(int) (box) (WINDOW * a1, chtype a2, chtype z)
{
	T((T_CALLED("box(%p,%s,%s)"), (const void *)a1, _tracechtype2(1,a2), _tracechtype2(2,z)));
	returnCode(wborder(a1, a2, a2, z, z, 0, 0, 0, 0));
}
NCURSES_EXPORT(int) (chgat) (int a1, attr_t a2, short a3, const void * z)
{
	T((T_CALLED("chgat(%d,%s,%#lx,%p)"), a1, _traceattr2(1,a2), (long)a3, (const void *)z));
	returnCode(wchgat(stdscr,(a1),(a2),(a3),(z)));
}
NCURSES_EXPORT(int) (clear) (void)
{
	T((T_CALLED("clear()")));
	returnCode(wclear(stdscr));
}
NCURSES_EXPORT(int) (clrtobot) (void)
{
	T((T_CALLED("clrtobot()")));
	returnCode(wclrtobot(stdscr));
}
NCURSES_EXPORT(int) (clrtoeol) (void)
{
	T((T_CALLED("clrtoeol()")));
	returnCode(wclrtoeol(stdscr));
}
NCURSES_EXPORT(int) (color_set) (short a1, void * z)
{
	T((T_CALLED("color_set(%#lx,%p)"), (long)a1, (const void *)z));
	returnCode(wcolor_set(stdscr,(a1),(z)));
}
NCURSES_EXPORT(int) (COLOR_PAIR) (int z)
{
	T((T_CALLED("COLOR_PAIR(%d)"), z));
	returnCode((((chtype)(((z))) << ((0) + 8)) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))));
}
NCURSES_EXPORT(int) (delch) (void)
{
	T((T_CALLED("delch()")));
	returnCode(wdelch(stdscr));
}
NCURSES_EXPORT(int) (deleteln) (void)
{
	T((T_CALLED("deleteln()")));
	returnCode(winsdelln(stdscr,-1));
}
NCURSES_EXPORT(int) (echochar) (const chtype z)
{
	T((T_CALLED("echochar(%s)"), _tracechtype2(0,z)));
	returnCode(wechochar(stdscr,(z)));
}
NCURSES_EXPORT(int) (erase) (void)
{
	T((T_CALLED("erase()")));
	returnCode(werase(stdscr));
}
NCURSES_EXPORT(chtype) (getbkgd) (WINDOW * z)
{
	T((T_CALLED("getbkgd(%p)"), (const void *)z));
	returnChtype(((0 != (const void *)((z))) ? ((z)->_bkgd) : 0));
}
NCURSES_EXPORT(int) (getch) (void)
{
	T((T_CALLED("getch()")));
	returnCode(wgetch(stdscr));
}
NCURSES_EXPORT(int) (getnstr) (char * a1, int z)
{
	T((T_CALLED("getnstr(%p,%d)"), _nc_visbuf2(0,a1), z));
	returnCode(wgetnstr(stdscr, a1, (z)));
}
NCURSES_EXPORT(int) (getstr) (char * z)
{
	T((T_CALLED("getstr(%p)"), _nc_visbuf2(0,z)));
	returnCode(wgetnstr(stdscr, (z), -1));
}
NCURSES_EXPORT(int) (hline) (chtype a1, int z)
{
	T((T_CALLED("hline(%s,%d)"), _tracechtype2(0,a1), z));
	returnCode(whline(stdscr, a1, (z)));
}
NCURSES_EXPORT(chtype) (inch) (void)
{
	T((T_CALLED("inch()")));
	returnChtype(winch(stdscr));
}
NCURSES_EXPORT(int) (inchnstr) (chtype * a1, int z)
{
	T((T_CALLED("inchnstr(%p,%d)"), (const void *)a1, z));
	returnCode(winchnstr(stdscr,(a1),(z)));
}
NCURSES_EXPORT(int) (inchstr) (chtype * z)
{
	T((T_CALLED("inchstr(%p)"), (const void *)z));
	returnCode(winchnstr(stdscr, (z), -1));
}
NCURSES_EXPORT(int) (innstr) (char * a1, int z)
{
	return winnstr(stdscr,(a1),(z)) ;
}
NCURSES_EXPORT(int) (insch) (chtype z)
{
	T((T_CALLED("insch(%s)"), _tracechtype2(0,z)));
	returnCode(winsch(stdscr,(z)));
}
NCURSES_EXPORT(int) (insdelln) (int z)
{
	T((T_CALLED("insdelln(%d)"), z));
	returnCode(winsdelln(stdscr,(z)));
}
NCURSES_EXPORT(int) (insertln) (void)
{
	T((T_CALLED("insertln()")));
	returnCode(winsdelln(stdscr,1));
}
NCURSES_EXPORT(int) (insnstr) (const char * a1, int z)
{
	T((T_CALLED("insnstr(%s,%d)"), _nc_visbuf2(0,a1), z));
	returnCode(winsnstr(stdscr,(a1),(z)));
}
NCURSES_EXPORT(int) (insstr) (const char * z)
{
	T((T_CALLED("insstr(%s)"), _nc_visbuf2(0,z)));
	returnCode(winsnstr(stdscr, (z), -1));
}
NCURSES_EXPORT(int) (instr) (char * z)
{
	T((T_CALLED("instr(%s)"), _nc_visbuf2(0,z)));
	returnCode(winnstr(stdscr, (z), -1));
}
NCURSES_EXPORT(int) (move) (int a1, int z)
{
	T((T_CALLED("move(%d,%d)"), a1, z));
	returnCode(wmove(stdscr,(a1),(z)));
}
NCURSES_EXPORT(int) (mvaddch) (int a1, int a2, const chtype z)
{
	T((T_CALLED("mvaddch(%d,%d,%s)"), a1, a2, _tracechtype2(2,z)));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : waddch((stdscr),((z)))));
}
NCURSES_EXPORT(int) (mvaddchnstr) (int a1, int a2, const chtype * a3, int z)
{
	T((T_CALLED("mvaddchnstr(%d,%d,%p,%d)"), a1, a2, (const void *)a3, z));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : waddchnstr((stdscr),((a3)),((z)))));
}
NCURSES_EXPORT(int) (mvaddchstr) (int a1, int a2, const chtype * z)
{
	T((T_CALLED("mvaddchstr(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : waddchnstr((stdscr),((z)),-1)));
}
NCURSES_EXPORT(int) (mvaddnstr) (int a1, int a2, const char * a3, int z)
{
	T((T_CALLED("mvaddnstr(%d,%d,%s,%d)"), a1, a2, _nc_visbuf2(2,a3), z));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : waddnstr((stdscr),((a3)),((z)))));
}
NCURSES_EXPORT(int) (mvaddstr) (int a1, int a2, const char * z)
{
	T((T_CALLED("mvaddstr(%d,%d,%s)"), a1, a2, _nc_visbuf2(2,z)));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : waddnstr((stdscr),((z)),-1)));
}
NCURSES_EXPORT(int) (mvchgat) (int a1, int a2, int a3, attr_t a4, short a5, const void * z)
{
	T((T_CALLED("mvchgat(%d,%d,%d,%s,%#lx,%p)"), a1, a2, a3, _traceattr2(3,a4), (long)a5, (const void *)z));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : wchgat((stdscr),((a3)),((a4)),((a5)),((z)))));
}
NCURSES_EXPORT(int) (mvdelch) (int a1, int z)
{
	T((T_CALLED("mvdelch(%d,%d)"), a1, z));
	returnCode((wmove((stdscr),((a1)),((z))) == (-1) ? (-1) : wdelch(stdscr)));
}
NCURSES_EXPORT(int) (mvgetch) (int a1, int z)
{
	T((T_CALLED("mvgetch(%d,%d)"), a1, z));
	returnCode((wmove((stdscr),((a1)),((z))) == (-1) ? (-1) : wgetch(stdscr)));
}
NCURSES_EXPORT(int) (mvgetnstr) (int a1, int a2, char * a3, int z)
{
	T((T_CALLED("mvgetnstr(%d,%d,%p,%d)"), a1, a2, _nc_visbuf2(2,a3), z));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : wgetnstr((stdscr),((a3)),((z)))));
}
NCURSES_EXPORT(int) (mvgetstr) (int a1, int a2, char * z)
{
	T((T_CALLED("mvgetstr(%d,%d,%p)"), a1, a2, _nc_visbuf2(2,z)));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : wgetnstr((stdscr), ((z)), -1)));
}
NCURSES_EXPORT(int) (mvhline) (int a1, int a2, chtype a3, int z)
{
	T((T_CALLED("mvhline(%d,%d,%s,%d)"), a1, a2, _tracechtype2(2,a3), z));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : whline((stdscr),((a3)),((z)))));
}
NCURSES_EXPORT(chtype) (mvinch) (int a1, int z)
{
	T((T_CALLED("mvinch(%d,%d)"), a1, z));
	returnChtype((wmove((stdscr),((a1)),((z))) == (-1) ? (chtype)((-1)) : winch(stdscr)));
}
NCURSES_EXPORT(int) (mvinchnstr) (int a1, int a2, chtype * a3, int z)
{
	T((T_CALLED("mvinchnstr(%d,%d,%p,%d)"), a1, a2, (const void *)a3, z));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : winchnstr((stdscr),((a3)),((z)))));
}
NCURSES_EXPORT(int) (mvinchstr) (int a1, int a2, chtype * z)
{
	T((T_CALLED("mvinchstr(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : winchnstr((stdscr), ((z)), -1)));
}
NCURSES_EXPORT(int) (mvinnstr) (int a1, int a2, char * a3, int z)
{
	return (wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : winnstr((stdscr),((a3)),((z)))) ;
}
NCURSES_EXPORT(int) (mvinsch) (int a1, int a2, chtype z)
{
	T((T_CALLED("mvinsch(%d,%d,%s)"), a1, a2, _tracechtype2(2,z)));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : winsch((stdscr),((z)))));
}
NCURSES_EXPORT(int) (mvinsnstr) (int a1, int a2, const char * a3, int z)
{
	T((T_CALLED("mvinsnstr(%d,%d,%s,%d)"), a1, a2, _nc_visbuf2(2,a3), z));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : winsnstr((stdscr),((a3)),((z)))));
}
NCURSES_EXPORT(int) (mvinsstr) (int a1, int a2, const char * z)
{
	T((T_CALLED("mvinsstr(%d,%d,%s)"), a1, a2, _nc_visbuf2(2,z)));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : winsnstr((stdscr), ((z)), -1)));
}
NCURSES_EXPORT(int) (mvinstr) (int a1, int a2, char * z)
{
	T((T_CALLED("mvinstr(%d,%d,%s)"), a1, a2, _nc_visbuf2(2,z)));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : winnstr((stdscr), ((z)), -1)));
}
NCURSES_EXPORT(int) (mvvline) (int a1, int a2, chtype a3, int z)
{
	T((T_CALLED("mvvline(%d,%d,%s,%d)"), a1, a2, _tracechtype2(2,a3), z));
	returnCode((wmove((stdscr),((a1)),((a2))) == (-1) ? (-1) : wvline((stdscr),((a3)),((z)))));
}
NCURSES_EXPORT(int) (mvwaddch) (WINDOW * a1, int a2, int a3, const chtype z)
{
	T((T_CALLED("mvwaddch(%p,%d,%d,%s)"), (const void *)a1, a2, a3, _tracechtype2(3,z)));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : waddch((a1),(z))));
}
NCURSES_EXPORT(int) (mvwaddchnstr) (WINDOW * a1, int a2, int a3, const chtype * a4, int z)
{
	T((T_CALLED("mvwaddchnstr(%p,%d,%d,%p,%d)"), (const void *)a1, a2, a3, (const void *)a4, z));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : waddchnstr((a1),(a4),(z))));
}
NCURSES_EXPORT(int) (mvwaddchstr) (WINDOW * a1, int a2, int a3, const chtype * z)
{
	T((T_CALLED("mvwaddchstr(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : waddchnstr((a1),(z),-1)));
}
NCURSES_EXPORT(int) (mvwaddnstr) (WINDOW * a1, int a2, int a3, const char * a4, int z)
{
	T((T_CALLED("mvwaddnstr(%p,%d,%d,%s,%d)"), (const void *)a1, a2, a3, _nc_visbuf2(3,a4), z));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : waddnstr((a1),(a4),(z))));
}
NCURSES_EXPORT(int) (mvwaddstr) (WINDOW * a1, int a2, int a3, const char * z)
{
	T((T_CALLED("mvwaddstr(%p,%d,%d,%s)"), (const void *)a1, a2, a3, _nc_visbuf2(3,z)));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : waddnstr((a1),(z),-1)));
}
NCURSES_EXPORT(int) (mvwchgat) (WINDOW * a1, int a2, int a3, int a4, attr_t a5, short a6, const void * z)
{
	T((T_CALLED("mvwchgat(%p,%d,%d,%d,%s,%#lx,%p)"), (const void *)a1, a2, a3, a4, _traceattr2(4,a5), (long)a6, (const void *)z));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : wchgat((a1),(a4),(a5),(a6),(z))));
}
NCURSES_EXPORT(int) (mvwdelch) (WINDOW * a1, int a2, int z)
{
	T((T_CALLED("mvwdelch(%p,%d,%d)"), (const void *)a1, a2, z));
	returnCode((wmove((a1),(a2),(z)) == (-1) ? (-1) : wdelch(a1)));
}
NCURSES_EXPORT(int) (mvwgetch) (WINDOW * a1, int a2, int z)
{
	T((T_CALLED("mvwgetch(%p,%d,%d)"), (const void *)a1, a2, z));
	returnCode((wmove((a1),(a2),(z)) == (-1) ? (-1) : wgetch(a1)));
}
NCURSES_EXPORT(int) (mvwgetnstr) (WINDOW * a1, int a2, int a3, char * a4, int z)
{
	T((T_CALLED("mvwgetnstr(%p,%d,%d,%p,%d)"), (const void *)a1, a2, a3, _nc_visbuf2(3,a4), z));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : wgetnstr((a1),(a4),(z))));
}
NCURSES_EXPORT(int) (mvwgetstr) (WINDOW * a1, int a2, int a3, char * z)
{
	T((T_CALLED("mvwgetstr(%p,%d,%d,%p)"), (const void *)a1, a2, a3, _nc_visbuf2(3,z)));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : wgetnstr((a1), (z), -1)));
}
NCURSES_EXPORT(int) (mvwhline) (WINDOW * a1, int a2, int a3, chtype a4, int z)
{
	T((T_CALLED("mvwhline(%p,%d,%d,%s,%d)"), (const void *)a1, a2, a3, _tracechtype2(3,a4), z));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : whline((a1),(a4),(z))));
}
NCURSES_EXPORT(chtype) (mvwinch) (WINDOW * a1, int a2, int z)
{
	T((T_CALLED("mvwinch(%p,%d,%d)"), (const void *)a1, a2, z));
	returnChtype((wmove((a1),(a2),(z)) == (-1) ? (chtype)((-1)) : winch(a1)));
}
NCURSES_EXPORT(int) (mvwinchnstr) (WINDOW * a1, int a2, int a3, chtype * a4, int z)
{
	T((T_CALLED("mvwinchnstr(%p,%d,%d,%p,%d)"), (const void *)a1, a2, a3, (const void *)a4, z));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : winchnstr((a1),(a4),(z))));
}
NCURSES_EXPORT(int) (mvwinchstr) (WINDOW * a1, int a2, int a3, chtype * z)
{
	T((T_CALLED("mvwinchstr(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : winchnstr((a1), (z), -1)));
}
NCURSES_EXPORT(int) (mvwinnstr) (WINDOW * a1, int a2, int a3, char * a4, int z)
{
	return (wmove((a1),(a2),(a3)) == (-1) ? (-1) : winnstr((a1),(a4),(z))) ;
}
NCURSES_EXPORT(int) (mvwinsch) (WINDOW * a1, int a2, int a3, chtype z)
{
	T((T_CALLED("mvwinsch(%p,%d,%d,%s)"), (const void *)a1, a2, a3, _tracechtype2(3,z)));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : winsch((a1),(z))));
}
NCURSES_EXPORT(int) (mvwinsnstr) (WINDOW * a1, int a2, int a3, const char * a4, int z)
{
	T((T_CALLED("mvwinsnstr(%p,%d,%d,%s,%d)"), (const void *)a1, a2, a3, _nc_visbuf2(3,a4), z));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : winsnstr((a1),(a4),(z))));
}
NCURSES_EXPORT(int) (mvwinsstr) (WINDOW * a1, int a2, int a3, const char * z)
{
	T((T_CALLED("mvwinsstr(%p,%d,%d,%s)"), (const void *)a1, a2, a3, _nc_visbuf2(3,z)));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : winsnstr((a1), (z), -1)));
}
NCURSES_EXPORT(int) (mvwinstr) (WINDOW * a1, int a2, int a3, char * z)
{
	T((T_CALLED("mvwinstr(%p,%d,%d,%s)"), (const void *)a1, a2, a3, _nc_visbuf2(3,z)));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : winnstr((a1), (z), -1)));
}
NCURSES_EXPORT(int) (mvwvline) (WINDOW * a1, int a2, int a3, chtype a4, int z)
{
	T((T_CALLED("mvwvline(%p,%d,%d,%s,%d)"), (const void *)a1, a2, a3, _tracechtype2(3,a4), z));
	returnCode((wmove((a1),(a2),(a3)) == (-1) ? (-1) : wvline((a1),(a4),(z))));
}
NCURSES_EXPORT(int) (PAIR_NUMBER) (int z)
{
	T((T_CALLED("PAIR_NUMBER(%d)"), z));
	returnCode(((int)((((unsigned long)((z)) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8))));
}
NCURSES_EXPORT(int) (redrawwin) (WINDOW * z)
{
	T((T_CALLED("redrawwin(%p)"), (const void *)z));
	returnCode(wredrawln(z, 0, ((0 != (const void *)((z))) ? (z)->_maxy+1 : -1)));
}
NCURSES_EXPORT(int) (refresh) (void)
{
	T((T_CALLED("refresh()")));
	returnCode(wrefresh(stdscr));
}
NCURSES_EXPORT(int) (scrl) (int z)
{
	T((T_CALLED("scrl(%d)"), z));
	returnCode(wscrl(stdscr,(z)));
}
NCURSES_EXPORT(int) (scroll) (WINDOW * z)
{
	T((T_CALLED("scroll(%p)"), (const void *)z));
	returnCode(wscrl(z,1));
}
NCURSES_EXPORT(int) (setscrreg) (int a1, int z)
{
	T((T_CALLED("setscrreg(%d,%d)"), a1, z));
	returnCode(wsetscrreg(stdscr,(a1),(z)));
}
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (slk_attr_off) (const attr_t a1, void * z)
{
	T((T_CALLED("slk_attr_off(%s,%p)"), _traceattr2(0,a1), (const void *)z));
	returnCode(((z) ? (-1) : slk_attroff(a1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (slk_attr_on) (attr_t a1, void * z)
{
	T((T_CALLED("slk_attr_on(%s,%p)"), _traceattr2(0,a1), (const void *)z));
	returnCode(((z) ? (-1) : slk_attron(a1)));
}
#endif
NCURSES_EXPORT(int) (standout) (void)
{
	T((T_CALLED("standout()")));
	returnIntAttr((attr_t)(((0 != (const void *)((stdscr))) ? ((stdscr)->_color = (int)(((int)((((unsigned long)((((chtype)((1UL)) << ((8) + 8)))) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8)))), (stdscr)->_attrs = (attr_t)(((chtype)((1UL)) << ((8) + 8))), (0)) : (-1))));
}
NCURSES_EXPORT(int) (standend) (void)
{
	T((T_CALLED("standend()")));
	returnIntAttr((attr_t)(((0 != (const void *)((stdscr))) ? ((stdscr)->_color = (int)(((int)((((unsigned long)(((1UL - 1UL))) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8)))), (stdscr)->_attrs = (attr_t)((1UL - 1UL)), (0)) : (-1))));
}
NCURSES_EXPORT(void) (timeout) (int z)
{
	T((T_CALLED("timeout(%d)"), z));
	wtimeout(stdscr,(z));
	returnVoid;
}
NCURSES_EXPORT(int) (touchline) (WINDOW * a1, int a2, int z)
{
	T((T_CALLED("touchline(%p,%d,%d)"), (const void *)a1, a2, z));
	returnCode(wtouchln((a1), a2, z, 1));
}
NCURSES_EXPORT(int) (touchwin) (WINDOW * z)
{
	T((T_CALLED("touchwin(%p)"), (const void *)z));
	returnCode(wtouchln((z), 0, ((0 != (const void *)((z))) ? ((z)->_maxy + 1) : (-1)), 1));
}
NCURSES_EXPORT(int) (untouchwin) (WINDOW * z)
{
	T((T_CALLED("untouchwin(%p)"), (const void *)z));
	returnCode(wtouchln((z), 0, ((0 != (const void *)((z))) ? ((z)->_maxy + 1) : (-1)), 0));
}
NCURSES_EXPORT(int) (vline) (chtype a1, int z)
{
	T((T_CALLED("vline(%s,%d)"), _tracechtype2(0,a1), z));
	returnCode(wvline(stdscr, a1, (z)));
}
NCURSES_EXPORT(int) (waddchstr) (WINDOW * a1, const chtype * z)
{
	T((T_CALLED("waddchstr(%p,%p)"), (const void *)a1, (const void *)z));
	returnCode(waddchnstr(a1,z,-1));
}
NCURSES_EXPORT(int) (waddstr) (WINDOW * a1, const char * z)
{
	T((T_CALLED("waddstr(%p,%s)"), (const void *)a1, _nc_visbuf2(1,z)));
	returnCode(waddnstr(a1,z,-1));
}
NCURSES_EXPORT(int) (wattron) (WINDOW * a1, int z)
{
	T((T_CALLED("wattron(%p,%d)"), (const void *)a1, z));
	returnCode(wattr_on(a1, (attr_t)(z), ((void *)0)));
}
NCURSES_EXPORT(int) (wattroff) (WINDOW * a1, int z)
{
	T((T_CALLED("wattroff(%p,%d)"), (const void *)a1, z));
	returnCode(wattr_off(a1, (attr_t)(z), ((void *)0)));
}
NCURSES_EXPORT(int) (wattrset) (WINDOW * a1, int z)
{
	T((T_CALLED("wattrset(%p,%d)"), (const void *)a1, z));
	returnIntAttr((attr_t)((0 != (const void *)((a1))) ? ((a1)->_color = (int)(((int)((((unsigned long)((z)) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8)))), (a1)->_attrs = (attr_t)(z), (0)) : (-1)));
}
NCURSES_EXPORT(int) (wattr_get) (WINDOW * a1, attr_t * a2, short * a3, void * z GCC_UNUSED)
{
	T((T_CALLED("wattr_get(%p,%p,%p,%p)"), (const void *)a1, (const void *)a2, (const void *)a3, (const void *)z));
	returnCode(((0 != (const void *)((a1))) ? ((void)((0 != (const void *)((a2))) ? (*(a2) = (a1)->_attrs) : (0)), (void)((0 != (const void *)((a3))) ? (*(a3) = (short) (a1)->_color) : (0)), (void)((0 != (const void *)((z))) ? (*(int *)(z) = (a1)->_color) : (0)), (0)) : (-1)));
}
NCURSES_EXPORT(int) (wattr_set) (WINDOW * a1, attr_t a2, short a3, void * z GCC_UNUSED)
{
	T((T_CALLED("wattr_set(%p,%s,%#lx,%p)"), (const void *)a1, _traceattr2(1,a2), (long)a3, (const void *)z));
	returnCode(((0 != (const void *)((a1))) ? ((void)((a1)->_attrs = ((a2) & ~((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))), (a1)->_color = (z) ? *(int *)(z) : (a3)), (0)) : (-1)));
}
NCURSES_EXPORT(int) (wdeleteln) (WINDOW * z)
{
	T((T_CALLED("wdeleteln(%p)"), (const void *)z));
	returnCode(winsdelln(z,-1));
}
NCURSES_EXPORT(int) (wgetstr) (WINDOW * a1, char * z)
{
	T((T_CALLED("wgetstr(%p,%p)"), (const void *)a1, _nc_visbuf2(1,z)));
	returnCode(wgetnstr(a1, z, -1));
}
NCURSES_EXPORT(int) (winchstr) (WINDOW * a1, chtype * z)
{
	T((T_CALLED("winchstr(%p,%p)"), (const void *)a1, (const void *)z));
	returnCode(winchnstr(a1, z, -1));
}
NCURSES_EXPORT(int) (winsertln) (WINDOW * z)
{
	T((T_CALLED("winsertln(%p)"), (const void *)z));
	returnCode(winsdelln(z,1));
}
NCURSES_EXPORT(int) (winsstr) (WINDOW * a1, const char * z)
{
	T((T_CALLED("winsstr(%p,%s)"), (const void *)a1, _nc_visbuf2(1,z)));
	returnCode(winsnstr(a1, z, -1));
}
NCURSES_EXPORT(int) (winstr) (WINDOW * a1, char * z)
{
	T((T_CALLED("winstr(%p,%s)"), (const void *)a1, _nc_visbuf2(1,z)));
	returnCode(winnstr(a1, z, -1));
}
NCURSES_EXPORT(int) (wstandout) (WINDOW * z)
{
	T((T_CALLED("wstandout(%p)"), (const void *)z));
	returnIntAttr((attr_t)(((0 != (const void *)((z))) ? ((z)->_color = (int)(((int)((((unsigned long)((((chtype)((1UL)) << ((8) + 8)))) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8)))), (z)->_attrs = (attr_t)(((chtype)((1UL)) << ((8) + 8))), (0)) : (-1))));
}
NCURSES_EXPORT(int) (wstandend) (WINDOW * z)
{
	T((T_CALLED("wstandend(%p)"), (const void *)z));
	returnIntAttr((attr_t)(((0 != (const void *)((z))) ? ((z)->_color = (int)(((int)((((unsigned long)(((1UL - 1UL))) & ((chtype)((((1UL) << 8) - 1UL)) << ((0) + 8))) >> 8)))), (z)->_attrs = (attr_t)((1UL - 1UL)), (0)) : (-1))));
}
NCURSES_EXPORT(int) (getattrs) (const WINDOW * z)
{
	T((T_CALLED("getattrs(%p)"), (const void *)z));
	returnCode((int)((0 != (const void *)((z))) ? (z)->_attrs : (1UL - 1UL)));
}
NCURSES_EXPORT(int) (getcurx) (const WINDOW * z)
{
	T((T_CALLED("getcurx(%p)"), (const void *)z));
	returnCode(((0 != (const void *)((z))) ? (z)->_curx : (-1)));
}
NCURSES_EXPORT(int) (getcury) (const WINDOW * z)
{
	T((T_CALLED("getcury(%p)"), (const void *)z));
	returnCode(((0 != (const void *)((z))) ? (z)->_cury : (-1)));
}
NCURSES_EXPORT(int) (getbegx) (const WINDOW * z)
{
	T((T_CALLED("getbegx(%p)"), (const void *)z));
	returnCode(((0 != (const void *)((z))) ? (z)->_begx : (-1)));
}
NCURSES_EXPORT(int) (getbegy) (const WINDOW * z)
{
	T((T_CALLED("getbegy(%p)"), (const void *)z));
	returnCode(((0 != (const void *)((z))) ? (z)->_begy : (-1)));
}
NCURSES_EXPORT(int) (getmaxx) (const WINDOW * z)
{
	T((T_CALLED("getmaxx(%p)"), (const void *)z));
	returnCode(((0 != (const void *)((z))) ? ((z)->_maxx + 1) : (-1)));
}
NCURSES_EXPORT(int) (getmaxy) (const WINDOW * z)
{
	T((T_CALLED("getmaxy(%p)"), (const void *)z));
	returnCode(((0 != (const void *)((z))) ? ((z)->_maxy + 1) : (-1)));
}
NCURSES_EXPORT(int) (getparx) (const WINDOW * z)
{
	T((T_CALLED("getparx(%p)"), (const void *)z));
	returnCode(((0 != (const void *)((z))) ? (z)->_parx : (-1)));
}
NCURSES_EXPORT(int) (getpary) (const WINDOW * z)
{
	T((T_CALLED("getpary(%p)"), (const void *)z));
	returnCode(((0 != (const void *)((z))) ? (z)->_pary : (-1)));
}
NCURSES_EXPORT(WINDOW *) (wgetparent) (const WINDOW * z)
{
	T((T_CALLED("wgetparent(%p)"), (const void *)z));
	returnWin(((0 != (const void *)((z))) ? (z)->_parent : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_cleared) (const WINDOW * z)
{
	T((T_CALLED("is_cleared(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? (z)->_clear : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_idcok) (const WINDOW * z)
{
	T((T_CALLED("is_idcok(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? (z)->_idcok : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_idlok) (const WINDOW * z)
{
	T((T_CALLED("is_idlok(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? (z)->_idlok : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_immedok) (const WINDOW * z)
{
	T((T_CALLED("is_immedok(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? (z)->_immed : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_keypad) (const WINDOW * z)
{
	T((T_CALLED("is_keypad(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? (z)->_use_keypad : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_leaveok) (const WINDOW * z)
{
	T((T_CALLED("is_leaveok(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? (z)->_leaveok : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_nodelay) (const WINDOW * z)
{
	T((T_CALLED("is_nodelay(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? ((z)->_delay == 0) : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_notimeout) (const WINDOW * z)
{
	T((T_CALLED("is_notimeout(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? (z)->_notimeout : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_pad) (const WINDOW * z)
{
	T((T_CALLED("is_pad(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? ((z)->_flags & 0x10) != 0 : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_scrollok) (const WINDOW * z)
{
	T((T_CALLED("is_scrollok(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? (z)->_scroll : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_subwin) (const WINDOW * z)
{
	T((T_CALLED("is_subwin(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? ((z)->_flags & 0x01) != 0 : 0));
}
NCURSES_EXPORT(NCURSES_BOOL) (is_syncok) (const WINDOW * z)
{
	T((T_CALLED("is_syncok(%p)"), (const void *)z));
	returnBool(((0 != (const void *)((z))) ? (z)->_sync : 0));
}
NCURSES_EXPORT(int) (wgetdelay) (const WINDOW * z)
{
	T((T_CALLED("wgetdelay(%p)"), (const void *)z));
	returnCode(((0 != (const void *)((z))) ? (z)->_delay : 0));
}
NCURSES_EXPORT(int) (wgetscrreg) (const WINDOW * a1, int * a2, int * z)
{
	T((T_CALLED("wgetscrreg(%p,%p,%p)"), (const void *)a1, (const void *)a2, (const void *)z));
	returnCode(((0 != (const void *)((a1))) ? (*(a2) = (a1)->_regtop, *(z) = (a1)->_regbottom, (0)) : (-1)));
}
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (add_wch) (const cchar_t * z)
{
	T((T_CALLED("add_wch(%p)"), (const void *)z));
	returnCode(wadd_wch(stdscr,(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (add_wchnstr) (const cchar_t * a1, int z)
{
	T((T_CALLED("add_wchnstr(%p,%d)"), (const void *)a1, z));
	returnCode(wadd_wchnstr(stdscr,(a1),(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (add_wchstr) (const cchar_t * z)
{
	T((T_CALLED("add_wchstr(%p)"), (const void *)z));
	returnCode(wadd_wchnstr((stdscr),((z)),-1));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (addnwstr) (const wchar_t * a1, int z)
{
	T((T_CALLED("addnwstr(%p,%d)"), (const void *)a1, z));
	returnCode(waddnwstr(stdscr,(a1),(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (addwstr) (const wchar_t * z)
{
	T((T_CALLED("addwstr(%p)"), (const void *)z));
	returnCode(waddnwstr((stdscr),((z)),-1));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (bkgrnd) (const cchar_t * z)
{
	T((T_CALLED("bkgrnd(%p)"), (const void *)z));
	returnCode(wbkgrnd(stdscr,(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(void) (bkgrndset) (const cchar_t * z)
{
	T((T_CALLED("bkgrndset(%p)"), (const void *)z));
	wbkgrndset(stdscr,(z));
	returnVoid;
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (border_set) (const cchar_t * a1, const cchar_t * a2, const cchar_t * a3, const cchar_t * a4, const cchar_t * a5, const cchar_t * a6, const cchar_t * a7, const cchar_t * z)
{
	T((T_CALLED("border_set(%p,%p,%p,%p,%p,%p,%p,%p)"), (const void *)a1, (const void *)a2, (const void *)a3, (const void *)a4, (const void *)a5, (const void *)a6, (const void *)a7, (const void *)z));
	returnCode(wborder_set(stdscr,(a1),(a2),(a3),(a4),a5,a6,a7,z));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (box_set) (WINDOW * a1, const cchar_t * a2, const cchar_t * z)
{
	T((T_CALLED("box_set(%p,%p,%p)"), (const void *)a1, (const void *)a2, (const void *)z));
	returnCode(wborder_set((a1),(a2),(a2),(z),(z),0,0,0,0));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (echo_wchar) (const cchar_t * z)
{
	T((T_CALLED("echo_wchar(%p)"), (const void *)z));
	returnCode(wecho_wchar(stdscr,(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (get_wch) (wint_t * z)
{
	T((T_CALLED("get_wch(%p)"), (const void *)z));
	returnCode(wget_wch(stdscr,(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (get_wstr) (wint_t * z)
{
	T((T_CALLED("get_wstr(%p)"), (const void *)z));
	returnCode(wgetn_wstr((stdscr),((z)),-1));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (getbkgrnd) (cchar_t * z)
{
	T((T_CALLED("getbkgrnd(%p)"), (const void *)z));
	returnCode(((0 != (const void *)(((z)))) ? ((stdscr) ? (*((z)) = (stdscr)->_bkgrnd) : *((z)), (0)) : (-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (getn_wstr) (wint_t * a1, int z)
{
	T((T_CALLED("getn_wstr(%p,%d)"), (const void *)a1, z));
	returnCode(wgetn_wstr(stdscr,(a1),(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (hline_set) (const cchar_t * a1, int z)
{
	T((T_CALLED("hline_set(%p,%d)"), (const void *)a1, z));
	returnCode(whline_set(stdscr,(a1),(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (in_wch) (cchar_t * z)
{
	T((T_CALLED("in_wch(%p)"), (const void *)z));
	returnCode(win_wch(stdscr,(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (in_wchnstr) (cchar_t * a1, int z)
{
	T((T_CALLED("in_wchnstr(%p,%d)"), (const void *)a1, z));
	returnCode(win_wchnstr(stdscr,(a1),(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (in_wchstr) (cchar_t * z)
{
	T((T_CALLED("in_wchstr(%p)"), (const void *)z));
	returnCode(win_wchnstr((stdscr),((z)),-1));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (innwstr) (wchar_t * a1, int z)
{
	return winnwstr(stdscr,(a1),(z)) ;
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (ins_nwstr) (const wchar_t * a1, int z)
{
	T((T_CALLED("ins_nwstr(%p,%d)"), (const void *)a1, z));
	returnCode(wins_nwstr(stdscr,(a1),(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (ins_wch) (const cchar_t * z)
{
	T((T_CALLED("ins_wch(%p)"), (const void *)z));
	returnCode(wins_wch(stdscr,(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (ins_wstr) (const wchar_t * z)
{
	T((T_CALLED("ins_wstr(%p)"), (const void *)z));
	returnCode(wins_nwstr((stdscr),((z)),-1));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (inwstr) (wchar_t * z)
{
	T((T_CALLED("inwstr(%p)"), (const void *)z));
	returnCode(winwstr(stdscr,(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvadd_wch) (int a1, int a2, const cchar_t * z)
{
	T((T_CALLED("mvadd_wch(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : wadd_wch((stdscr),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvadd_wchnstr) (int a1, int a2, const cchar_t * a3, int z)
{
	T((T_CALLED("mvadd_wchnstr(%d,%d,%p,%d)"), a1, a2, (const void *)a3, z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : wadd_wchnstr((stdscr),((a3)),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvadd_wchstr) (int a1, int a2, const cchar_t * z)
{
	T((T_CALLED("mvadd_wchstr(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : wadd_wchnstr(((stdscr)),(((z))),-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvaddnwstr) (int a1, int a2, const wchar_t * a3, int z)
{
	T((T_CALLED("mvaddnwstr(%d,%d,%p,%d)"), a1, a2, (const void *)a3, z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : waddnwstr((stdscr),((a3)),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvaddwstr) (int a1, int a2, const wchar_t * z)
{
	T((T_CALLED("mvaddwstr(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : waddnwstr(((stdscr)),(((z))),-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvget_wch) (int a1, int a2, wint_t * z)
{
	T((T_CALLED("mvget_wch(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : wget_wch((stdscr),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvget_wstr) (int a1, int a2, wint_t * z)
{
	T((T_CALLED("mvget_wstr(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : wgetn_wstr(((stdscr)),(((z))),-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvgetn_wstr) (int a1, int a2, wint_t * a3, int z)
{
	T((T_CALLED("mvgetn_wstr(%d,%d,%p,%d)"), a1, a2, (const void *)a3, z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : wgetn_wstr((stdscr),((a3)),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvhline_set) (int a1, int a2, const cchar_t * a3, int z)
{
	T((T_CALLED("mvhline_set(%d,%d,%p,%d)"), a1, a2, (const void *)a3, z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : whline_set((stdscr),((a3)),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvin_wch) (int a1, int a2, cchar_t * z)
{
	T((T_CALLED("mvin_wch(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : win_wch((stdscr),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvin_wchnstr) (int a1, int a2, cchar_t * a3, int z)
{
	T((T_CALLED("mvin_wchnstr(%d,%d,%p,%d)"), a1, a2, (const void *)a3, z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : win_wchnstr((stdscr),((a3)),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvin_wchstr) (int a1, int a2, cchar_t * z)
{
	T((T_CALLED("mvin_wchstr(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : win_wchnstr(((stdscr)),(((z))),-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvinnwstr) (int a1, int a2, wchar_t * a3, int z)
{
	return (wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : winnwstr((stdscr),((a3)),((z)))) ;
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvins_nwstr) (int a1, int a2, const wchar_t * a3, int z)
{
	T((T_CALLED("mvins_nwstr(%d,%d,%p,%d)"), a1, a2, (const void *)a3, z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : wins_nwstr((stdscr),((a3)),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvins_wch) (int a1, int a2, const cchar_t * z)
{
	T((T_CALLED("mvins_wch(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : wins_wch((stdscr),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvins_wstr) (int a1, int a2, const wchar_t * z)
{
	T((T_CALLED("mvins_wstr(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : wins_nwstr(((stdscr)),(((z))),-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvinwstr) (int a1, int a2, wchar_t * z)
{
	T((T_CALLED("mvinwstr(%d,%d,%p)"), a1, a2, (const void *)z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : winwstr((stdscr),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvvline_set) (int a1, int a2, const cchar_t * a3, int z)
{
	T((T_CALLED("mvvline_set(%d,%d,%p,%d)"), a1, a2, (const void *)a3, z));
	returnCode((wmove(stdscr,((a1)),((a2))) == (-1) ? (-1) : wvline_set((stdscr),((a3)),((z)))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwadd_wch) (WINDOW * a1, int a2, int a3, const cchar_t * z)
{
	T((T_CALLED("mvwadd_wch(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : wadd_wch((a1),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwadd_wchnstr) (WINDOW * a1, int a2, int a3, const cchar_t * a4, int z)
{
	T((T_CALLED("mvwadd_wchnstr(%p,%d,%d,%p,%d)"), (const void *)a1, a2, a3, (const void *)a4, z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : wadd_wchnstr((a1),(a4),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwadd_wchstr) (WINDOW * a1, int a2, int a3, const cchar_t * z)
{
	T((T_CALLED("mvwadd_wchstr(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : wadd_wchnstr(((a1)),((z)),-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwaddnwstr) (WINDOW * a1, int a2, int a3, const wchar_t * a4, int z)
{
	T((T_CALLED("mvwaddnwstr(%p,%d,%d,%p,%d)"), (const void *)a1, a2, a3, (const void *)a4, z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : waddnwstr((a1),(a4),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwaddwstr) (WINDOW * a1, int a2, int a3, const wchar_t * z)
{
	T((T_CALLED("mvwaddwstr(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : waddnwstr(((a1)),((z)),-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwget_wch) (WINDOW * a1, int a2, int a3, wint_t * z)
{
	T((T_CALLED("mvwget_wch(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : wget_wch((a1),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwget_wstr) (WINDOW * a1, int a2, int a3, wint_t * z)
{
	T((T_CALLED("mvwget_wstr(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : wgetn_wstr(((a1)),((z)),-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwgetn_wstr) (WINDOW * a1, int a2, int a3, wint_t * a4, int z)
{
	T((T_CALLED("mvwgetn_wstr(%p,%d,%d,%p,%d)"), (const void *)a1, a2, a3, (const void *)a4, z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : wgetn_wstr((a1),(a4),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwhline_set) (WINDOW * a1, int a2, int a3, const cchar_t * a4, int z)
{
	T((T_CALLED("mvwhline_set(%p,%d,%d,%p,%d)"), (const void *)a1, a2, a3, (const void *)a4, z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : whline_set((a1),(a4),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwin_wch) (WINDOW * a1, int a2, int a3, cchar_t * z)
{
	T((T_CALLED("mvwin_wch(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : win_wch((a1),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwin_wchnstr) (WINDOW * a1, int a2, int a3, cchar_t * a4, int z)
{
	T((T_CALLED("mvwin_wchnstr(%p,%d,%d,%p,%d)"), (const void *)a1, a2, a3, (const void *)a4, z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : win_wchnstr((a1),(a4),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwin_wchstr) (WINDOW * a1, int a2, int a3, cchar_t * z)
{
	T((T_CALLED("mvwin_wchstr(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : win_wchnstr(((a1)),((z)),-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwinnwstr) (WINDOW * a1, int a2, int a3, wchar_t * a4, int z)
{
	return (wmove(a1,(a2),(a3)) == (-1) ? (-1) : winnwstr((a1),(a4),(z))) ;
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwins_nwstr) (WINDOW * a1, int a2, int a3, const wchar_t * a4, int z)
{
	T((T_CALLED("mvwins_nwstr(%p,%d,%d,%p,%d)"), (const void *)a1, a2, a3, (const void *)a4, z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : wins_nwstr((a1),(a4),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwins_wch) (WINDOW * a1, int a2, int a3, const cchar_t * z)
{
	T((T_CALLED("mvwins_wch(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : wins_wch((a1),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwins_wstr) (WINDOW * a1, int a2, int a3, const wchar_t * z)
{
	T((T_CALLED("mvwins_wstr(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : wins_nwstr(((a1)),((z)),-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwinwstr) (WINDOW * a1, int a2, int a3, wchar_t * z)
{
	T((T_CALLED("mvwinwstr(%p,%d,%d,%p)"), (const void *)a1, a2, a3, (const void *)z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : winwstr((a1),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (mvwvline_set) (WINDOW * a1, int a2, int a3, const cchar_t * a4, int z)
{
	T((T_CALLED("mvwvline_set(%p,%d,%d,%p,%d)"), (const void *)a1, a2, a3, (const void *)a4, z));
	returnCode((wmove(a1,(a2),(a3)) == (-1) ? (-1) : wvline_set((a1),(a4),(z))));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (vline_set) (const cchar_t * a1, int z)
{
	T((T_CALLED("vline_set(%p,%d)"), (const void *)a1, z));
	returnCode(wvline_set(stdscr,(a1),(z)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (wadd_wchstr) (WINDOW * a1, const cchar_t * z)
{
	T((T_CALLED("wadd_wchstr(%p,%p)"), (const void *)a1, (const void *)z));
	returnCode(wadd_wchnstr((a1),(z),-1));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (waddwstr) (WINDOW * a1, const wchar_t * z)
{
	T((T_CALLED("waddwstr(%p,%p)"), (const void *)a1, (const void *)z));
	returnCode(waddnwstr((a1),(z),-1));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (wget_wstr) (WINDOW * a1, wint_t * z)
{
	T((T_CALLED("wget_wstr(%p,%p)"), (const void *)a1, (const void *)z));
	returnCode(wgetn_wstr((a1),(z),-1));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (wgetbkgrnd) (WINDOW * a1, cchar_t * z)
{
	T((T_CALLED("wgetbkgrnd(%p,%p)"), (const void *)a1, (const void *)z));
	returnCode(((0 != (const void *)((z))) ? ((a1) ? (*(z) = (a1)->_bkgrnd) : *(z), (0)) : (-1)));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (win_wchstr) (WINDOW * a1, cchar_t * z)
{
	T((T_CALLED("win_wchstr(%p,%p)"), (const void *)a1, (const void *)z));
	returnCode(win_wchnstr((a1),(z),-1));
}
#endif
#if USE_WIDEC_SUPPORT
NCURSES_EXPORT(int) (wins_wstr) (WINDOW * a1, const wchar_t * z)
{
	T((T_CALLED("wins_wstr(%p,%p)"), (const void *)a1, (const void *)z));
	returnCode(wins_nwstr((a1),(z),-1));
}
#endif
NCURSES_EXPORT(NCURSES_BOOL) (mouse_trafo) (int * a1, int * a2, NCURSES_BOOL z)
{
	T((T_CALLED("mouse_trafo(%p,%p,%#lx)"), (const void *)a1, (const void *)a2, (long)z));
	returnBool(wmouse_trafo(stdscr,a1,a2,z));
}

EOF
""",
)

genrule(
    name = "ncurses/unctrl",
    outs = ["ncurses/unctrl.c"],
    cmd = r"""
cat << 'EOF' > $@
/* generated by MKunctrl.awk */

#include <curses.priv.h>
#include <ctype.h>

#undef unctrl

NCURSES_EXPORT(NCURSES_CONST char *) safe_unctrl(SCREEN *sp, chtype ch)
{
static const short unctrl_table[] = {
       0,   3,   6,   9,  12,  15,  18,  21,
      24,  27,  30,  33,  36,  39,  42,  45,
      48,  51,  54,  57,  60,  63,  66,  69,
      72,  75,  78,  81,  84,  87,  90,  93,
      96,  98, 100, 102, 104, 106, 108, 110,
     112, 114, 116, 118, 120, 122, 124, 126,
     128, 130, 132, 134, 136, 138, 140, 142,
     144, 146, 148, 150, 152, 154, 156, 158,
     160, 162, 164, 166, 168, 170, 172, 174,
     176, 178, 180, 182, 184, 186, 188, 190,
     192, 194, 196, 198, 200, 202, 204, 206,
     208, 210, 212, 214, 216, 218, 220, 222,
     224, 226, 228, 230, 232, 234, 236, 238,
     240, 242, 244, 246, 248, 250, 252, 254,
     256, 258, 260, 262, 264, 266, 268, 270,
     272, 274, 276, 278, 280, 282, 284, 286,
     289, 292, 295, 298, 301, 304, 307, 310,
     313, 316, 319, 322, 325, 328, 331, 334,
     337, 340, 343, 346, 349, 352, 355, 358,
     361, 364, 367, 370, 373, 376, 379, 382,
     385, 389, 393, 397, 401, 405, 409, 413,
     417, 421, 425, 429, 433, 437, 441, 445,
     449, 453, 457, 461, 465, 469, 473, 477,
     481, 485, 489, 493, 497, 501, 505, 509,
     513, 517, 521, 525, 529, 533, 537, 541,
     545, 549, 553, 557, 561, 565, 569, 573,
     577, 581, 585, 589, 593, 597, 601, 605,
     609, 613, 617, 621, 625, 629, 633, 637,
     641, 645, 649, 653, 657, 661, 665, 669,
     673, 677, 681, 685, 689, 693, 697, 701,
     705, 709, 713, 717, 721, 725, 729, 733,
     737, 741, 745, 749, 753, 757, 761, 765,};

#if NCURSES_EXT_FUNCS
static const short unctrl_c1[] = {
     768, 770, 772, 774, 776, 778, 780, 782,
     784, 786, 788, 790, 792, 794, 796, 798,
     800, 802, 804, 806, 808, 810, 812, 814,
     816, 818, 820, 822, 824, 826, 828, 830,
     832, 834, 836, 838, 840, 842, 844, 846,
     848, 850, 852, 854, 856, 858, 860, 862,
     864, 866, 868, 870, 872, 874, 876, 878,
     880, 882, 884, 886, 888, 890, 892, 894,
     896, 898, 900, 902, 904, 906, 908, 910,
     912, 914, 916, 918, 920, 922, 924, 926,
     928, 930, 932, 934, 936, 938, 940, 942,
     944, 946, 948, 950, 952, 954, 956, 958,
     960, 962, 964, 966, 968, 970, 972, 974,
     976, 978, 980, 982, 984, 986, 988, 990,
     992, 994, 996, 998,1000,1002,1004,1006,
    1008,1010,1012,1014,1016,1018,1020,1022,};
#endif /* NCURSES_EXT_FUNCS */

static const char unctrl_blob[] = 
    "^\100\0^\101\0^\102\0^\103\0^\104\0^\105\0^\106\0^\107\0"
    "^\110\0^\111\0^\112\0^\113\0^\114\0^\115\0^\116\0^\117\0"
    "^\120\0^\121\0^\122\0^\123\0^\124\0^\125\0^\126\0^\127\0"
    "^\130\0^\131\0^\132\0^\133\0^\134\0^\135\0^\136\0^\137\0"
    "\040\0\041\0\042\0\043\0\044\0\045\0\046\0\047\0"
    "\050\0\051\0\052\0\053\0\054\0\055\0\056\0\057\0"
    "\060\0\061\0\062\0\063\0\064\0\065\0\066\0\067\0"
    "\070\0\071\0\072\0\073\0\074\0\075\0\076\0\077\0"
    "\100\0\101\0\102\0\103\0\104\0\105\0\106\0\107\0"
    "\110\0\111\0\112\0\113\0\114\0\115\0\116\0\117\0"
    "\120\0\121\0\122\0\123\0\124\0\125\0\126\0\127\0"
    "\130\0\131\0\132\0\133\0\134\0\135\0\136\0\137\0"
    "\140\0\141\0\142\0\143\0\144\0\145\0\146\0\147\0"
    "\150\0\151\0\152\0\153\0\154\0\155\0\156\0\157\0"
    "\160\0\161\0\162\0\163\0\164\0\165\0\166\0\167\0"
    "\170\0\171\0\172\0\173\0\174\0\175\0\176\0^?\0"
    "~\100\0~\101\0~\102\0~\103\0~\104\0~\105\0~\106\0~\107\0"
    "~\110\0~\111\0~\112\0~\113\0~\114\0~\115\0~\116\0~\117\0"
    "~\120\0~\121\0~\122\0~\123\0~\124\0~\125\0~\126\0~\127\0"
    "~\130\0~\131\0~\132\0~\133\0~\134\0~\135\0~\136\0~\137\0"
    "M-\040\0M-\041\0M-\042\0M-\043\0M-\044\0M-\045\0M-\046\0M-\047\0"
    "M-\050\0M-\051\0M-\052\0M-\053\0M-\054\0M-\055\0M-\056\0M-\057\0"
    "M-\060\0M-\061\0M-\062\0M-\063\0M-\064\0M-\065\0M-\066\0M-\067\0"
    "M-\070\0M-\071\0M-\072\0M-\073\0M-\074\0M-\075\0M-\076\0M-\077\0"
    "M-\100\0M-\101\0M-\102\0M-\103\0M-\104\0M-\105\0M-\106\0M-\107\0"
    "M-\110\0M-\111\0M-\112\0M-\113\0M-\114\0M-\115\0M-\116\0M-\117\0"
    "M-\120\0M-\121\0M-\122\0M-\123\0M-\124\0M-\125\0M-\126\0M-\127\0"
    "M-\130\0M-\131\0M-\132\0M-\133\0M-\134\0M-\135\0M-\136\0M-\137\0"
    "M-\140\0M-\141\0M-\142\0M-\143\0M-\144\0M-\145\0M-\146\0M-\147\0"
    "M-\150\0M-\151\0M-\152\0M-\153\0M-\154\0M-\155\0M-\156\0M-\157\0"
    "M-\160\0M-\161\0M-\162\0M-\163\0M-\164\0M-\165\0M-\166\0M-\167\0"
    "M-\170\0M-\171\0M-\172\0M-\173\0M-\174\0M-\175\0M-\176\0~?\0"
/* printable values in 128-255 range */
    "\200\0\201\0\202\0\203\0\204\0\205\0\206\0\207\0"
    "\210\0\211\0\212\0\213\0\214\0\215\0\216\0\217\0"
    "\220\0\221\0\222\0\223\0\224\0\225\0\226\0\227\0"
    "\230\0\231\0\232\0\233\0\234\0\235\0\236\0\237\0"
    "\240\0\241\0\242\0\243\0\244\0\245\0\246\0\247\0"
    "\250\0\251\0\252\0\253\0\254\0\255\0\256\0\257\0"
    "\260\0\261\0\262\0\263\0\264\0\265\0\266\0\267\0"
    "\270\0\271\0\272\0\273\0\274\0\275\0\276\0\277\0"
    "\300\0\301\0\302\0\303\0\304\0\305\0\306\0\307\0"
    "\310\0\311\0\312\0\313\0\314\0\315\0\316\0\317\0"
    "\320\0\321\0\322\0\323\0\324\0\325\0\326\0\327\0"
    "\330\0\331\0\332\0\333\0\334\0\335\0\336\0\337\0"
    "\340\0\341\0\342\0\343\0\344\0\345\0\346\0\347\0"
    "\350\0\351\0\352\0\353\0\354\0\355\0\356\0\357\0"
    "\360\0\361\0\362\0\363\0\364\0\365\0\366\0\367\0"
    "\370\0\371\0\372\0\373\0\374\0\375\0\376\0\377\0"
;

	int check = (int) ChCharOf(ch);
	const char *result;

(void) sp;
	if (check >= 0 && check < (int)SIZEOF(unctrl_table)) {
#if NCURSES_EXT_FUNCS
		if ((sp != 0)
		 && (sp->_legacy_coding > 1)
		 && (check >= 128)
		 && (check < 160))
			result = unctrl_blob + unctrl_c1[check - 128];
		else
		if ((check >= 160)
		 && (check < 256)
		 && ((sp != 0)
		  && ((sp->_legacy_coding > 0)
		   || (sp->_legacy_coding == 0
		       && isprint(check)))))
			result = unctrl_blob + unctrl_c1[check - 128];
		else
#endif /* NCURSES_EXT_FUNCS */
			result = unctrl_blob + unctrl_table[check];
	} else {
		result = 0;
	}
	return (NCURSES_CONST char *)result;
}

NCURSES_EXPORT(NCURSES_CONST char *) unctrl (chtype ch)
{
	return safe_unctrl(CURRENT_SCREEN, ch);
}

EOF
""",
)

genrule(
    name = "ncurses/init_keytry",
    outs = ["ncurses/init_keytry.h"],
    cmd = r"""
cat << 'EOF' > $@
#ifndef NCU_KEYS_H
#define NCU_KEYS_H 1

/* This file was generated by MAKE_KEYS */

#if BROKEN_LINKER
static
#endif
const struct tinfo_fkeys _nc_tinfo_fkeys[] = {
	{  139, KEY_A1           },	/* key_a1 */
	{  140, KEY_A3           },	/* key_a3 */
	{  141, KEY_B2           },	/* key_b2 */
	{   55, KEY_BACKSPACE    },	/* key_backspace */
	{  158, KEY_BEG          },	/* key_beg */
	{  148, KEY_BTAB         },	/* key_btab */
	{  142, KEY_C1           },	/* key_c1 */
	{  143, KEY_C3           },	/* key_c3 */
	{  159, KEY_CANCEL       },	/* key_cancel */
	{   56, KEY_CATAB        },	/* key_catab */
	{   57, KEY_CLEAR        },	/* key_clear */
	{  160, KEY_CLOSE        },	/* key_close */
	{  161, KEY_COMMAND      },	/* key_command */
	{  162, KEY_COPY         },	/* key_copy */
	{  163, KEY_CREATE       },	/* key_create */
	{   58, KEY_CTAB         },	/* key_ctab */
	{   59, KEY_DC           },	/* key_dc */
	{   60, KEY_DL           },	/* key_dl */
	{   61, KEY_DOWN         },	/* key_down */
	{   62, KEY_EIC          },	/* key_eic */
	{  164, KEY_END          },	/* key_end */
	{  165, KEY_ENTER        },	/* key_enter */
	{   63, KEY_EOL          },	/* key_eol */
	{   64, KEY_EOS          },	/* key_eos */
	{  166, KEY_EXIT         },	/* key_exit */
	{   65, KEY_F(0)         },	/* key_f0 */
	{   66, KEY_F(1)         },	/* key_f1 */
	{   67, KEY_F(10)        },	/* key_f10 */
	{  216, KEY_F(11)        },	/* key_f11 */
	{  217, KEY_F(12)        },	/* key_f12 */
	{  218, KEY_F(13)        },	/* key_f13 */
	{  219, KEY_F(14)        },	/* key_f14 */
	{  220, KEY_F(15)        },	/* key_f15 */
	{  221, KEY_F(16)        },	/* key_f16 */
	{  222, KEY_F(17)        },	/* key_f17 */
	{  223, KEY_F(18)        },	/* key_f18 */
	{  224, KEY_F(19)        },	/* key_f19 */
	{   68, KEY_F(2)         },	/* key_f2 */
	{  225, KEY_F(20)        },	/* key_f20 */
	{  226, KEY_F(21)        },	/* key_f21 */
	{  227, KEY_F(22)        },	/* key_f22 */
	{  228, KEY_F(23)        },	/* key_f23 */
	{  229, KEY_F(24)        },	/* key_f24 */
	{  230, KEY_F(25)        },	/* key_f25 */
	{  231, KEY_F(26)        },	/* key_f26 */
	{  232, KEY_F(27)        },	/* key_f27 */
	{  233, KEY_F(28)        },	/* key_f28 */
	{  234, KEY_F(29)        },	/* key_f29 */
	{   69, KEY_F(3)         },	/* key_f3 */
	{  235, KEY_F(30)        },	/* key_f30 */
	{  236, KEY_F(31)        },	/* key_f31 */
	{  237, KEY_F(32)        },	/* key_f32 */
	{  238, KEY_F(33)        },	/* key_f33 */
	{  239, KEY_F(34)        },	/* key_f34 */
	{  240, KEY_F(35)        },	/* key_f35 */
	{  241, KEY_F(36)        },	/* key_f36 */
	{  242, KEY_F(37)        },	/* key_f37 */
	{  243, KEY_F(38)        },	/* key_f38 */
	{  244, KEY_F(39)        },	/* key_f39 */
	{   70, KEY_F(4)         },	/* key_f4 */
	{  245, KEY_F(40)        },	/* key_f40 */
	{  246, KEY_F(41)        },	/* key_f41 */
	{  247, KEY_F(42)        },	/* key_f42 */
	{  248, KEY_F(43)        },	/* key_f43 */
	{  249, KEY_F(44)        },	/* key_f44 */
	{  250, KEY_F(45)        },	/* key_f45 */
	{  251, KEY_F(46)        },	/* key_f46 */
	{  252, KEY_F(47)        },	/* key_f47 */
	{  253, KEY_F(48)        },	/* key_f48 */
	{  254, KEY_F(49)        },	/* key_f49 */
	{   71, KEY_F(5)         },	/* key_f5 */
	{  255, KEY_F(50)        },	/* key_f50 */
	{  256, KEY_F(51)        },	/* key_f51 */
	{  257, KEY_F(52)        },	/* key_f52 */
	{  258, KEY_F(53)        },	/* key_f53 */
	{  259, KEY_F(54)        },	/* key_f54 */
	{  260, KEY_F(55)        },	/* key_f55 */
	{  261, KEY_F(56)        },	/* key_f56 */
	{  262, KEY_F(57)        },	/* key_f57 */
	{  263, KEY_F(58)        },	/* key_f58 */
	{  264, KEY_F(59)        },	/* key_f59 */
	{   72, KEY_F(6)         },	/* key_f6 */
	{  265, KEY_F(60)        },	/* key_f60 */
	{  266, KEY_F(61)        },	/* key_f61 */
	{  267, KEY_F(62)        },	/* key_f62 */
	{  268, KEY_F(63)        },	/* key_f63 */
	{   73, KEY_F(7)         },	/* key_f7 */
	{   74, KEY_F(8)         },	/* key_f8 */
	{   75, KEY_F(9)         },	/* key_f9 */
	{  167, KEY_FIND         },	/* key_find */
	{  168, KEY_HELP         },	/* key_help */
	{   76, KEY_HOME         },	/* key_home */
	{   77, KEY_IC           },	/* key_ic */
	{   78, KEY_IL           },	/* key_il */
	{   79, KEY_LEFT         },	/* key_left */
	{   80, KEY_LL           },	/* key_ll */
	{  169, KEY_MARK         },	/* key_mark */
	{  170, KEY_MESSAGE      },	/* key_message */
	{  355, KEY_MOUSE        },	/* key_mouse */
	{  171, KEY_MOVE         },	/* key_move */
	{  172, KEY_NEXT         },	/* key_next */
	{   81, KEY_NPAGE        },	/* key_npage */
	{  173, KEY_OPEN         },	/* key_open */
	{  174, KEY_OPTIONS      },	/* key_options */
	{   82, KEY_PPAGE        },	/* key_ppage */
	{  175, KEY_PREVIOUS     },	/* key_previous */
	{  176, KEY_PRINT        },	/* key_print */
	{  177, KEY_REDO         },	/* key_redo */
	{  178, KEY_REFERENCE    },	/* key_reference */
	{  179, KEY_REFRESH      },	/* key_refresh */
	{  180, KEY_REPLACE      },	/* key_replace */
	{  181, KEY_RESTART      },	/* key_restart */
	{  182, KEY_RESUME       },	/* key_resume */
	{   83, KEY_RIGHT        },	/* key_right */
	{  183, KEY_SAVE         },	/* key_save */
	{  186, KEY_SBEG         },	/* key_sbeg */
	{  187, KEY_SCANCEL      },	/* key_scancel */
	{  188, KEY_SCOMMAND     },	/* key_scommand */
	{  189, KEY_SCOPY        },	/* key_scopy */
	{  190, KEY_SCREATE      },	/* key_screate */
	{  191, KEY_SDC          },	/* key_sdc */
	{  192, KEY_SDL          },	/* key_sdl */
	{  193, KEY_SELECT       },	/* key_select */
	{  194, KEY_SEND         },	/* key_send */
	{  195, KEY_SEOL         },	/* key_seol */
	{  196, KEY_SEXIT        },	/* key_sexit */
	{   84, KEY_SF           },	/* key_sf */
	{  197, KEY_SFIND        },	/* key_sfind */
	{  198, KEY_SHELP        },	/* key_shelp */
	{  199, KEY_SHOME        },	/* key_shome */
	{  200, KEY_SIC          },	/* key_sic */
	{  201, KEY_SLEFT        },	/* key_sleft */
	{  202, KEY_SMESSAGE     },	/* key_smessage */
	{  203, KEY_SMOVE        },	/* key_smove */
	{  204, KEY_SNEXT        },	/* key_snext */
	{  205, KEY_SOPTIONS     },	/* key_soptions */
	{  206, KEY_SPREVIOUS    },	/* key_sprevious */
	{  207, KEY_SPRINT       },	/* key_sprint */
	{   85, KEY_SR           },	/* key_sr */
	{  208, KEY_SREDO        },	/* key_sredo */
	{  209, KEY_SREPLACE     },	/* key_sreplace */
	{  210, KEY_SRIGHT       },	/* key_sright */
	{  211, KEY_SRSUME       },	/* key_srsume */
	{  212, KEY_SSAVE        },	/* key_ssave */
	{  213, KEY_SSUSPEND     },	/* key_ssuspend */
	{   86, KEY_STAB         },	/* key_stab */
	{  214, KEY_SUNDO        },	/* key_sundo */
	{  184, KEY_SUSPEND      },	/* key_suspend */
	{  185, KEY_UNDO         },	/* key_undo */
	{   87, KEY_UP           },	/* key_up */
	{ 0, 0} };

#endif /* NCU_KEYS_H */

EOF
""",
)

genrule(
    name = "ncurses/lib_keyname",
    outs = ["ncurses/lib_keyname.c"],
    cmd = r"""
cat << 'EOF' > $@
/* generated by MKkeyname.awk */

#include <curses.priv.h>
#include <tic.h>

struct kn { short offset; int code; };
static const struct kn _nc_key_names[] = {
	{ 0, KEY_A1 },
	{ 7, KEY_A3 },
	{ 14, KEY_B2 },
	{ 21, KEY_BACKSPACE },
	{ 35, KEY_BEG },
	{ 43, KEY_BREAK },
	{ 53, KEY_BTAB },
	{ 62, KEY_C1 },
	{ 69, KEY_C3 },
	{ 76, KEY_CANCEL },
	{ 87, KEY_CATAB },
	{ 97, KEY_CLEAR },
	{ 107, KEY_CLOSE },
	{ 117, KEY_COMMAND },
	{ 129, KEY_COPY },
	{ 138, KEY_CREATE },
	{ 149, KEY_CTAB },
	{ 158, KEY_DC },
	{ 165, KEY_DL },
	{ 172, KEY_DOWN },
	{ 181, KEY_EIC },
	{ 189, KEY_END },
	{ 197, KEY_ENTER },
	{ 207, KEY_EOL },
	{ 215, KEY_EOS },
	{ 223, KEY_EXIT },
	{ 232, KEY_F(0) },
	{ 241, KEY_F(1) },
	{ 250, KEY_F(10) },
	{ 260, KEY_F(11) },
	{ 270, KEY_F(12) },
	{ 280, KEY_F(13) },
	{ 290, KEY_F(14) },
	{ 300, KEY_F(15) },
	{ 310, KEY_F(16) },
	{ 320, KEY_F(17) },
	{ 330, KEY_F(18) },
	{ 340, KEY_F(19) },
	{ 350, KEY_F(2) },
	{ 359, KEY_F(20) },
	{ 369, KEY_F(21) },
	{ 379, KEY_F(22) },
	{ 389, KEY_F(23) },
	{ 399, KEY_F(24) },
	{ 409, KEY_F(25) },
	{ 419, KEY_F(26) },
	{ 429, KEY_F(27) },
	{ 439, KEY_F(28) },
	{ 449, KEY_F(29) },
	{ 459, KEY_F(3) },
	{ 468, KEY_F(30) },
	{ 478, KEY_F(31) },
	{ 488, KEY_F(32) },
	{ 498, KEY_F(33) },
	{ 508, KEY_F(34) },
	{ 518, KEY_F(35) },
	{ 528, KEY_F(36) },
	{ 538, KEY_F(37) },
	{ 548, KEY_F(38) },
	{ 558, KEY_F(39) },
	{ 568, KEY_F(4) },
	{ 577, KEY_F(40) },
	{ 587, KEY_F(41) },
	{ 597, KEY_F(42) },
	{ 607, KEY_F(43) },
	{ 617, KEY_F(44) },
	{ 627, KEY_F(45) },
	{ 637, KEY_F(46) },
	{ 647, KEY_F(47) },
	{ 657, KEY_F(48) },
	{ 667, KEY_F(49) },
	{ 677, KEY_F(5) },
	{ 686, KEY_F(50) },
	{ 696, KEY_F(51) },
	{ 706, KEY_F(52) },
	{ 716, KEY_F(53) },
	{ 726, KEY_F(54) },
	{ 736, KEY_F(55) },
	{ 746, KEY_F(56) },
	{ 756, KEY_F(57) },
	{ 766, KEY_F(58) },
	{ 776, KEY_F(59) },
	{ 786, KEY_F(6) },
	{ 795, KEY_F(60) },
	{ 805, KEY_F(61) },
	{ 815, KEY_F(62) },
	{ 825, KEY_F(63) },
	{ 835, KEY_F(7) },
	{ 844, KEY_F(8) },
	{ 853, KEY_F(9) },
	{ 862, KEY_FIND },
	{ 871, KEY_HELP },
	{ 880, KEY_HOME },
	{ 889, KEY_IC },
	{ 896, KEY_IL },
	{ 903, KEY_LEFT },
	{ 912, KEY_LL },
	{ 919, KEY_MARK },
	{ 928, KEY_MESSAGE },
	{ 940, KEY_MOUSE },
	{ 950, KEY_MOVE },
	{ 959, KEY_NEXT },
	{ 968, KEY_NPAGE },
	{ 978, KEY_OPEN },
	{ 987, KEY_OPTIONS },
	{ 999, KEY_PPAGE },
	{ 1009, KEY_PREVIOUS },
	{ 1022, KEY_PRINT },
	{ 1032, KEY_REDO },
	{ 1041, KEY_REFERENCE },
	{ 1055, KEY_REFRESH },
	{ 1067, KEY_REPLACE },
	{ 1079, KEY_RESET },
	{ 1089, KEY_RESIZE },
	{ 1100, KEY_RESTART },
	{ 1112, KEY_RESUME },
	{ 1123, KEY_RIGHT },
	{ 1133, KEY_SAVE },
	{ 1142, KEY_SBEG },
	{ 1151, KEY_SCANCEL },
	{ 1163, KEY_SCOMMAND },
	{ 1176, KEY_SCOPY },
	{ 1186, KEY_SCREATE },
	{ 1198, KEY_SDC },
	{ 1206, KEY_SDL },
	{ 1214, KEY_SELECT },
	{ 1225, KEY_SEND },
	{ 1234, KEY_SEOL },
	{ 1243, KEY_SEXIT },
	{ 1253, KEY_SF },
	{ 1260, KEY_SFIND },
	{ 1270, KEY_SHELP },
	{ 1280, KEY_SHOME },
	{ 1290, KEY_SIC },
	{ 1298, KEY_SLEFT },
	{ 1308, KEY_SMESSAGE },
	{ 1321, KEY_SMOVE },
	{ 1331, KEY_SNEXT },
	{ 1341, KEY_SOPTIONS },
	{ 1354, KEY_SPREVIOUS },
	{ 1368, KEY_SPRINT },
	{ 1379, KEY_SR },
	{ 1386, KEY_SREDO },
	{ 1396, KEY_SREPLACE },
	{ 1409, KEY_SRESET },
	{ 1420, KEY_SRIGHT },
	{ 1431, KEY_SRSUME },
	{ 1442, KEY_SSAVE },
	{ 1452, KEY_SSUSPEND },
	{ 1465, KEY_STAB },
	{ 1474, KEY_SUNDO },
	{ 1484, KEY_SUSPEND },
	{ 1496, KEY_UNDO },
	{ 1505, KEY_UP },
	{ -1, 0 }};

static const char key_names[] = 
	"KEY_A1\0"
	"KEY_A3\0"
	"KEY_B2\0"
	"KEY_BACKSPACE\0"
	"KEY_BEG\0"
	"KEY_BREAK\0"
	"KEY_BTAB\0"
	"KEY_C1\0"
	"KEY_C3\0"
	"KEY_CANCEL\0"
	"KEY_CATAB\0"
	"KEY_CLEAR\0"
	"KEY_CLOSE\0"
	"KEY_COMMAND\0"
	"KEY_COPY\0"
	"KEY_CREATE\0"
	"KEY_CTAB\0"
	"KEY_DC\0"
	"KEY_DL\0"
	"KEY_DOWN\0"
	"KEY_EIC\0"
	"KEY_END\0"
	"KEY_ENTER\0"
	"KEY_EOL\0"
	"KEY_EOS\0"
	"KEY_EXIT\0"
	"KEY_F(0)\0"
	"KEY_F(1)\0"
	"KEY_F(10)\0"
	"KEY_F(11)\0"
	"KEY_F(12)\0"
	"KEY_F(13)\0"
	"KEY_F(14)\0"
	"KEY_F(15)\0"
	"KEY_F(16)\0"
	"KEY_F(17)\0"
	"KEY_F(18)\0"
	"KEY_F(19)\0"
	"KEY_F(2)\0"
	"KEY_F(20)\0"
	"KEY_F(21)\0"
	"KEY_F(22)\0"
	"KEY_F(23)\0"
	"KEY_F(24)\0"
	"KEY_F(25)\0"
	"KEY_F(26)\0"
	"KEY_F(27)\0"
	"KEY_F(28)\0"
	"KEY_F(29)\0"
	"KEY_F(3)\0"
	"KEY_F(30)\0"
	"KEY_F(31)\0"
	"KEY_F(32)\0"
	"KEY_F(33)\0"
	"KEY_F(34)\0"
	"KEY_F(35)\0"
	"KEY_F(36)\0"
	"KEY_F(37)\0"
	"KEY_F(38)\0"
	"KEY_F(39)\0"
	"KEY_F(4)\0"
	"KEY_F(40)\0"
	"KEY_F(41)\0"
	"KEY_F(42)\0"
	"KEY_F(43)\0"
	"KEY_F(44)\0"
	"KEY_F(45)\0"
	"KEY_F(46)\0"
	"KEY_F(47)\0"
	"KEY_F(48)\0"
	"KEY_F(49)\0"
	"KEY_F(5)\0"
	"KEY_F(50)\0"
	"KEY_F(51)\0"
	"KEY_F(52)\0"
	"KEY_F(53)\0"
	"KEY_F(54)\0"
	"KEY_F(55)\0"
	"KEY_F(56)\0"
	"KEY_F(57)\0"
	"KEY_F(58)\0"
	"KEY_F(59)\0"
	"KEY_F(6)\0"
	"KEY_F(60)\0"
	"KEY_F(61)\0"
	"KEY_F(62)\0"
	"KEY_F(63)\0"
	"KEY_F(7)\0"
	"KEY_F(8)\0"
	"KEY_F(9)\0"
	"KEY_FIND\0"
	"KEY_HELP\0"
	"KEY_HOME\0"
	"KEY_IC\0"
	"KEY_IL\0"
	"KEY_LEFT\0"
	"KEY_LL\0"
	"KEY_MARK\0"
	"KEY_MESSAGE\0"
	"KEY_MOUSE\0"
	"KEY_MOVE\0"
	"KEY_NEXT\0"
	"KEY_NPAGE\0"
	"KEY_OPEN\0"
	"KEY_OPTIONS\0"
	"KEY_PPAGE\0"
	"KEY_PREVIOUS\0"
	"KEY_PRINT\0"
	"KEY_REDO\0"
	"KEY_REFERENCE\0"
	"KEY_REFRESH\0"
	"KEY_REPLACE\0"
	"KEY_RESET\0"
	"KEY_RESIZE\0"
	"KEY_RESTART\0"
	"KEY_RESUME\0"
	"KEY_RIGHT\0"
	"KEY_SAVE\0"
	"KEY_SBEG\0"
	"KEY_SCANCEL\0"
	"KEY_SCOMMAND\0"
	"KEY_SCOPY\0"
	"KEY_SCREATE\0"
	"KEY_SDC\0"
	"KEY_SDL\0"
	"KEY_SELECT\0"
	"KEY_SEND\0"
	"KEY_SEOL\0"
	"KEY_SEXIT\0"
	"KEY_SF\0"
	"KEY_SFIND\0"
	"KEY_SHELP\0"
	"KEY_SHOME\0"
	"KEY_SIC\0"
	"KEY_SLEFT\0"
	"KEY_SMESSAGE\0"
	"KEY_SMOVE\0"
	"KEY_SNEXT\0"
	"KEY_SOPTIONS\0"
	"KEY_SPREVIOUS\0"
	"KEY_SPRINT\0"
	"KEY_SR\0"
	"KEY_SREDO\0"
	"KEY_SREPLACE\0"
	"KEY_SRESET\0"
	"KEY_SRIGHT\0"
	"KEY_SRSUME\0"
	"KEY_SSAVE\0"
	"KEY_SSUSPEND\0"
	"KEY_STAB\0"
	"KEY_SUNDO\0"
	"KEY_SUSPEND\0"
	"KEY_UNDO\0"
	"KEY_UP\0";

#define SIZEOF_TABLE 256
#define MyTable _nc_globals.keyname_table
#define MyInit  _nc_globals.init_keyname

NCURSES_EXPORT(NCURSES_CONST char *)
safe_keyname (SCREEN *sp, int c)
{
	char name[20];
	NCURSES_CONST char *result = 0;

	if (c == -1) {
		result = "-1";
	} else {
		int i;
		for (i = 0; _nc_key_names[i].offset != -1; i++) {
			if (_nc_key_names[i].code == c) {
				result = (NCURSES_CONST char *)key_names + _nc_key_names[i].offset;
				break;
			}
		}

		if (result == 0 && (c >= 0 && c < SIZEOF_TABLE)) {
			if (MyTable == 0)
				MyTable = typeCalloc(char *, SIZEOF_TABLE);

			if (MyTable != 0) {
				int m_prefix = (sp == 0 || sp->_use_meta);

				/* if sense of meta() changed, discard cached data */
				if (MyInit != (m_prefix + 1)) {
					MyInit = m_prefix + 1;
					for (i = 0; i < SIZEOF_TABLE; ++i) {
						if (MyTable[i]) {
							FreeAndNull(MyTable[i]);
						}
					}
				}

				/* create and cache result as needed */
				if (MyTable[c] == 0) {
					int cc = c;
					char *p = name;
#define P_LIMIT (sizeof(name) - (size_t) (p - name))
					if (cc >= 128 && m_prefix) {
						_nc_STRCPY(p, "M-", P_LIMIT);
						p += 2;
						cc -= 128;
					}
					if (cc < 32)
						_nc_SPRINTF(p, _nc_SLIMIT(P_LIMIT) "^%c", cc + '@');
					else if (cc == 127)
						_nc_STRCPY(p, "^?", P_LIMIT);
					else
						_nc_SPRINTF(p, _nc_SLIMIT(P_LIMIT) "%c", cc);
					MyTable[c] = strdup(name);
				}
				result = MyTable[c];
			}
#if NCURSES_EXT_FUNCS && NCURSES_XNAMES
		} else if (result == 0 && HasTerminal(sp)) {
			int j, k;
			char * bound;
			TERMTYPE2 *tp = &TerminalType(TerminalOf(sp));
			unsigned save_trace = _nc_tracing;

			_nc_tracing = 0;	/* prevent recursion via keybound() */
			for (j = 0; (bound = NCURSES_SP_NAME(keybound)(NCURSES_SP_ARGx c, j)) != 0; ++j) {
				for(k = STRCOUNT; k < (int) NUM_STRINGS(tp);  k++) {
					if (tp->Strings[k] != 0 && !strcmp(bound, tp->Strings[k])) {
						result = ExtStrname(tp, k, strnames);
						break;
					}
				}
				free(bound);
				if (result != 0)
					break;
			}
			_nc_tracing = save_trace;
#endif
		}
	}
	return result;
}

NCURSES_EXPORT(NCURSES_CONST char *)
keyname (int c)
{
	return safe_keyname (CURRENT_SCREEN, c);
}

#if NO_LEAKS
void _nc_keyname_leaks(void)
{
	if (MyTable != 0) {
		int j;
		for (j = 0; j < SIZEOF_TABLE; ++j) {
			FreeIfNeeded(MyTable[j]);
		}
		FreeAndNull(MyTable);
	}
}
#endif /* NO_LEAKS */

EOF
""",
)

genrule(
    name = "ncurses/comp_captab",
    outs = ["ncurses/comp_captab.c"],
    cmd = r"""
cat << 'EOF' > $@
/*
 * generated by thirdparty/ncurses/ncurses-6.2/ncurses/tinfo/MKcaptab.sh
 */

/*
 *	comp_captab.c -- The names of the capabilities indexed via a hash
 *		         table for the compiler.
 *
 */

#include <curses.priv.h>
#include <tic.h>
#include <hashsize.h>

/* *INDENT-OFF* */
/* 147 collisions out of 497 entries */
static const char info_names_text[] = \
"bw\0" "am\0" "xsb\0" "xhp\0" "xenl\0" "eo\0" "gn\0" "hc\0" "km\0" \
"hs\0" "in\0" "da\0" "db\0" "mir\0" "msgr\0" "os\0" "eslok\0" "xt\0" \
"hz\0" "ul\0" "xon\0" "nxon\0" "mc5i\0" "chts\0" "nrrmc\0" "npc\0" \
"ndscr\0" "ccc\0" "bce\0" "hls\0" "xhpa\0" "crxm\0" "daisy\0" "xvpa\0" \
"sam\0" "cpix\0" "lpix\0" "cols\0" "it\0" "lines\0" "lm\0" "xmc\0" \
"pb\0" "vt\0" "wsl\0" "nlab\0" "lh\0" "lw\0" "ma\0" "wnum\0" "colors\0" \
"pairs\0" "ncv\0" "bufsz\0" "spinv\0" "spinh\0" "maddr\0" "mjump\0" \
"mcs\0" "mls\0" "npins\0" "orc\0" "orl\0" "orhi\0" "orvi\0" "cps\0" \
"widcs\0" "btns\0" "bitwin\0" "bitype\0" "cbt\0" "bel\0" "cr\0" "csr\0" \
"tbc\0" "clear\0" "el\0" "ed\0" "hpa\0" "cmdch\0" "cup\0" "cud1\0" \
"home\0" "civis\0" "cub1\0" "mrcup\0" "cnorm\0" "cuf1\0" "ll\0" \
"cuu1\0" "cvvis\0" "dch1\0" "dl1\0" "dsl\0" "hd\0" "smacs\0" "blink\0" \
"bold\0" "smcup\0" "smdc\0" "dim\0" "smir\0" "invis\0" "prot\0" "rev\0" \
"smso\0" "smul\0" "ech\0" "rmacs\0" "sgr0\0" "rmcup\0" "rmdc\0" \
"rmir\0" "rmso\0" "rmul\0" "flash\0" "ff\0" "fsl\0" "is1\0" "is2\0" \
"is3\0" "if\0" "ich1\0" "il1\0" "ip\0" "kbs\0" "ktbc\0" "kclr\0" \
"kctab\0" "kdch1\0" "kdl1\0" "kcud1\0" "krmir\0" "kel\0" "ked\0" \
"kf0\0" "kf1\0" "kf10\0" "kf2\0" "kf3\0" "kf4\0" "kf5\0" "kf6\0" \
"kf7\0" "kf8\0" "kf9\0" "khome\0" "kich1\0" "kil1\0" "kcub1\0" "kll\0" \
"knp\0" "kpp\0" "kcuf1\0" "kind\0" "kri\0" "khts\0" "kcuu1\0" "rmkx\0" \
"smkx\0" "lf0\0" "lf1\0" "lf10\0" "lf2\0" "lf3\0" "lf4\0" "lf5\0" \
"lf6\0" "lf7\0" "lf8\0" "lf9\0" "rmm\0" "smm\0" "nel\0" "pad\0" "dch\0" \
"dl\0" "cud\0" "ich\0" "indn\0" "il\0" "cub\0" "cuf\0" "rin\0" "cuu\0" \
"pfkey\0" "pfloc\0" "pfx\0" "mc0\0" "mc4\0" "mc5\0" "rep\0" "rs1\0" \
"rs2\0" "rs3\0" "rf\0" "rc\0" "vpa\0" "sc\0" "ind\0" "ri\0" "sgr\0" \
"hts\0" "wind\0" "ht\0" "tsl\0" "uc\0" "hu\0" "iprog\0" "ka1\0" "ka3\0" \
"kb2\0" "kc1\0" "kc3\0" "mc5p\0" "rmp\0" "acsc\0" "pln\0" "kcbt\0" \
"smxon\0" "rmxon\0" "smam\0" "rmam\0" "xonc\0" "xoffc\0" "enacs\0" \
"smln\0" "rmln\0" "kbeg\0" "kcan\0" "kclo\0" "kcmd\0" "kcpy\0" "kcrt\0" \
"kend\0" "kent\0" "kext\0" "kfnd\0" "khlp\0" "kmrk\0" "kmsg\0" "kmov\0" \
"knxt\0" "kopn\0" "kopt\0" "kprv\0" "kprt\0" "krdo\0" "kref\0" "krfr\0" \
"krpl\0" "krst\0" "kres\0" "ksav\0" "kspd\0" "kund\0" "kBEG\0" "kCAN\0" \
"kCMD\0" "kCPY\0" "kCRT\0" "kDC\0" "kDL\0" "kslt\0" "kEND\0" "kEOL\0" \
"kEXT\0" "kFND\0" "kHLP\0" "kHOM\0" "kIC\0" "kLFT\0" "kMSG\0" "kMOV\0" \
"kNXT\0" "kOPT\0" "kPRV\0" "kPRT\0" "kRDO\0" "kRPL\0" "kRIT\0" "kRES\0" \
"kSAV\0" "kSPD\0" "kUND\0" "rfi\0" "kf11\0" "kf12\0" "kf13\0" "kf14\0" \
"kf15\0" "kf16\0" "kf17\0" "kf18\0" "kf19\0" "kf20\0" "kf21\0" "kf22\0" \
"kf23\0" "kf24\0" "kf25\0" "kf26\0" "kf27\0" "kf28\0" "kf29\0" "kf30\0" \
"kf31\0" "kf32\0" "kf33\0" "kf34\0" "kf35\0" "kf36\0" "kf37\0" "kf38\0" \
"kf39\0" "kf40\0" "kf41\0" "kf42\0" "kf43\0" "kf44\0" "kf45\0" "kf46\0" \
"kf47\0" "kf48\0" "kf49\0" "kf50\0" "kf51\0" "kf52\0" "kf53\0" "kf54\0" \
"kf55\0" "kf56\0" "kf57\0" "kf58\0" "kf59\0" "kf60\0" "kf61\0" "kf62\0" \
"kf63\0" "el1\0" "mgc\0" "smgl\0" "smgr\0" "fln\0" "sclk\0" "dclk\0" \
"rmclk\0" "cwin\0" "wingo\0" "hup\0" "dial\0" "qdial\0" "tone\0" \
"pulse\0" "hook\0" "pause\0" "wait\0" "u0\0" "u1\0" "u2\0" "u3\0" \
"u4\0" "u5\0" "u6\0" "u7\0" "u8\0" "u9\0" "op\0" "oc\0" "initc\0" \
"initp\0" "scp\0" "setf\0" "setb\0" "cpi\0" "lpi\0" "chr\0" "cvr\0" \
"defc\0" "swidm\0" "sdrfq\0" "sitm\0" "slm\0" "smicm\0" "snlq\0" \
"snrmq\0" "sshm\0" "ssubm\0" "ssupm\0" "sum\0" "rwidm\0" "ritm\0" \
"rlm\0" "rmicm\0" "rshm\0" "rsubm\0" "rsupm\0" "rum\0" "mhpa\0" \
"mcud1\0" "mcub1\0" "mcuf1\0" "mvpa\0" "mcuu1\0" "porder\0" "mcud\0" \
"mcub\0" "mcuf\0" "mcuu\0" "scs\0" "smgb\0" "smgbp\0" "smglp\0" \
"smgrp\0" "smgt\0" "smgtp\0" "sbim\0" "scsd\0" "rbim\0" "rcsd\0" \
"subcs\0" "supcs\0" "docr\0" "zerom\0" "csnm\0" "kmous\0" "minfo\0" \
"reqmp\0" "getm\0" "setaf\0" "setab\0" "pfxl\0" "devt\0" "csin\0" \
"s0ds\0" "s1ds\0" "s2ds\0" "s3ds\0" "smglr\0" "smgtb\0" "birep\0" \
"binel\0" "bicr\0" "colornm\0" "defbi\0" "endbi\0" "setcolor\0" \
"slines\0" "dispc\0" "smpch\0" "rmpch\0" "smsc\0" "rmsc\0" "pctrm\0" \
"scesc\0" "scesa\0" "ehhlm\0" "elhlm\0" "elohlm\0" "erhlm\0" "ethlm\0" \
"evhlm\0" "sgr1\0" "slength\0" "OTi2\0" "OTrs\0" "OTug\0" "OTbs\0" \
"OTns\0" "OTnc\0" "OTdC\0" "OTdN\0" "OTnl\0" "OTbc\0" "OTMT\0" "OTNL\0" \
"OTdB\0" "OTdT\0" "OTkn\0" "OTko\0" "OTma\0" "OTpt\0" "OTxr\0" "OTG2\0" \
"OTG3\0" "OTG1\0" "OTG4\0" "OTGR\0" "OTGL\0" "OTGU\0" "OTGD\0" "OTGH\0" \
"OTGV\0" "OTGC\0" "meml\0" "memu\0" "box1\0" ;

static name_table_data const info_names_data[] =
{
	{               0,	   BOOLEAN,	  0,  -1 },
	{               3,	   BOOLEAN,	  1,  -1 },
	{               6,	   BOOLEAN,	  2,  -1 },
	{              10,	   BOOLEAN,	  3,  -1 },
	{              14,	   BOOLEAN,	  4,  -1 },
	{              19,	   BOOLEAN,	  5,  -1 },
	{              22,	   BOOLEAN,	  6,  -1 },
	{              25,	   BOOLEAN,	  7,  -1 },
	{              28,	   BOOLEAN,	  8,  -1 },
	{              31,	   BOOLEAN,	  9,  -1 },
	{              34,	   BOOLEAN,	 10,  -1 },
	{              37,	   BOOLEAN,	 11,  -1 },
	{              40,	   BOOLEAN,	 12,  -1 },
	{              43,	   BOOLEAN,	 13,  -1 },
	{              47,	   BOOLEAN,	 14,  -1 },
	{              52,	   BOOLEAN,	 15,  -1 },
	{              55,	   BOOLEAN,	 16,  -1 },
	{              61,	   BOOLEAN,	 17,  -1 },
	{              64,	   BOOLEAN,	 18,  -1 },
	{              67,	   BOOLEAN,	 19,  -1 },
	{              70,	   BOOLEAN,	 20,  -1 },
	{              74,	   BOOLEAN,	 21,  -1 },
	{              79,	   BOOLEAN,	 22,  -1 },
	{              84,	   BOOLEAN,	 23,  -1 },
	{              89,	   BOOLEAN,	 24,  -1 },
	{              95,	   BOOLEAN,	 25,  -1 },
	{              99,	   BOOLEAN,	 26,  -1 },
	{             105,	   BOOLEAN,	 27,  -1 },
	{             109,	   BOOLEAN,	 28,  -1 },
	{             113,	   BOOLEAN,	 29,  -1 },
	{             117,	   BOOLEAN,	 30,  -1 },
	{             122,	   BOOLEAN,	 31,  -1 },
	{             127,	   BOOLEAN,	 32,  -1 },
	{             133,	   BOOLEAN,	 33,  -1 },
	{             138,	   BOOLEAN,	 34,  -1 },
	{             142,	   BOOLEAN,	 35,  -1 },
	{             147,	   BOOLEAN,	 36,  -1 },
	{             152,	    NUMBER,	  0,  -1 },
	{             157,	    NUMBER,	  1,  -1 },
	{             160,	    NUMBER,	  2,   6 },
	{             166,	    NUMBER,	  3,  -1 },
	{             169,	    NUMBER,	  4,  -1 },
	{             173,	    NUMBER,	  5,  -1 },
	{             176,	    NUMBER,	  6,  -1 },
	{             179,	    NUMBER,	  7,  -1 },
	{             183,	    NUMBER,	  8,  -1 },
	{             188,	    NUMBER,	  9,  -1 },
	{             191,	    NUMBER,	 10,  -1 },
	{             194,	    NUMBER,	 11,  -1 },
	{             197,	    NUMBER,	 12,  -1 },
	{             202,	    NUMBER,	 13,  -1 },
	{             209,	    NUMBER,	 14,  -1 },
	{             215,	    NUMBER,	 15,  -1 },
	{             219,	    NUMBER,	 16,  46 },
	{             225,	    NUMBER,	 17,  -1 },
	{             231,	    NUMBER,	 18,  -1 },
	{             237,	    NUMBER,	 19,  -1 },
	{             243,	    NUMBER,	 20,  -1 },
	{             249,	    NUMBER,	 21,  -1 },
	{             253,	    NUMBER,	 22,  -1 },
	{             257,	    NUMBER,	 23,  -1 },
	{             263,	    NUMBER,	 24,  -1 },
	{             267,	    NUMBER,	 25,  -1 },
	{             271,	    NUMBER,	 26,  -1 },
	{             276,	    NUMBER,	 27,  -1 },
	{             281,	    NUMBER,	 28,  -1 },
	{             285,	    NUMBER,	 29,  -1 },
	{             291,	    NUMBER,	 30,  -1 },
	{             296,	    NUMBER,	 31,  -1 },
	{             303,	    NUMBER,	 32,  68 },
	{             310,	    STRING,	  0,  -1 },
	{             314,	    STRING,	  1,  -1 },
	{             318,	    STRING,	  2,  -1 },
	{             321,	    STRING,	  3,  -1 },
	{             325,	    STRING,	  4,  -1 },
	{             329,	    STRING,	  5,  -1 },
	{             335,	    STRING,	  6,  -1 },
	{             338,	    STRING,	  7,  -1 },
	{             341,	    STRING,	  8,  -1 },
	{             345,	    STRING,	  9,  -1 },
	{             351,	    STRING,	 10,  73 },
	{             355,	    STRING,	 11,  -1 },
	{             360,	    STRING,	 12,  -1 },
	{             365,	    STRING,	 13,  -1 },
	{             371,	    STRING,	 14,  -1 },
	{             376,	    STRING,	 15,  -1 },
	{             382,	    STRING,	 16,  -1 },
	{             388,	    STRING,	 17,  -1 },
	{             393,	    STRING,	 18,  -1 },
	{             396,	    STRING,	 19,  -1 },
	{             401,	    STRING,	 20,  -1 },
	{             407,	    STRING,	 21,  -1 },
	{             412,	    STRING,	 22,  -1 },
	{             416,	    STRING,	 23,  -1 },
	{             420,	    STRING,	 24,  -1 },
	{             423,	    STRING,	 25,  -1 },
	{             429,	    STRING,	 26,  -1 },
	{             435,	    STRING,	 27,  -1 },
	{             440,	    STRING,	 28,  -1 },
	{             446,	    STRING,	 29,  -1 },
	{             451,	    STRING,	 30,  -1 },
	{             455,	    STRING,	 31,  -1 },
	{             460,	    STRING,	 32,  -1 },
	{             466,	    STRING,	 33,  -1 },
	{             471,	    STRING,	 34,  -1 },
	{             475,	    STRING,	 35,  -1 },
	{             480,	    STRING,	 36,  -1 },
	{             485,	    STRING,	 37,  -1 },
	{             489,	    STRING,	 38,  -1 },
	{             495,	    STRING,	 39,  -1 },
	{             500,	    STRING,	 40,  -1 },
	{             506,	    STRING,	 41,  -1 },
	{             511,	    STRING,	 42,  -1 },
	{             516,	    STRING,	 43,  -1 },
	{             521,	    STRING,	 44,  -1 },
	{             526,	    STRING,	 45,  -1 },
	{             532,	    STRING,	 46,  -1 },
	{             535,	    STRING,	 47,  -1 },
	{             539,	    STRING,	 48,  -1 },
	{             543,	    STRING,	 49,  59 },
	{             547,	    STRING,	 50,  76 },
	{             551,	    STRING,	 51,  -1 },
	{             554,	    STRING,	 52,  20 },
	{             559,	    STRING,	 53,  -1 },
	{             563,	    STRING,	 54,  -1 },
	{             566,	    STRING,	 55,  -1 },
	{             570,	    STRING,	 56,  -1 },
	{             575,	    STRING,	 57,  98 },
	{             580,	    STRING,	 58,  -1 },
	{             586,	    STRING,	 59,  -1 },
	{             592,	    STRING,	 60,  -1 },
	{             597,	    STRING,	 61,  -1 },
	{             603,	    STRING,	 62,  -1 },
	{             609,	    STRING,	 63,  -1 },
	{             613,	    STRING,	 64,  -1 },
	{             617,	    STRING,	 65,  -1 },
	{             621,	    STRING,	 66,  -1 },
	{             625,	    STRING,	 67,  -1 },
	{             630,	    STRING,	 68,  -1 },
	{             634,	    STRING,	 69,  -1 },
	{             638,	    STRING,	 70,  -1 },
	{             642,	    STRING,	 71,  61 },
	{             646,	    STRING,	 72,  -1 },
	{             650,	    STRING,	 73,  -1 },
	{             654,	    STRING,	 74,  -1 },
	{             658,	    STRING,	 75,  -1 },
	{             662,	    STRING,	 76,  -1 },
	{             668,	    STRING,	 77,  -1 },
	{             674,	    STRING,	 78,  -1 },
	{             679,	    STRING,	 79,  -1 },
	{             685,	    STRING,	 80,  -1 },
	{             689,	    STRING,	 81,  -1 },
	{             693,	    STRING,	 82,  -1 },
	{             697,	    STRING,	 83,  -1 },
	{             703,	    STRING,	 84,  55 },
	{             708,	    STRING,	 85, 105 },
	{             712,	    STRING,	 86,  -1 },
	{             717,	    STRING,	 87,  81 },
	{             723,	    STRING,	 88,  -1 },
	{             728,	    STRING,	 89,  -1 },
	{             733,	    STRING,	 90,  -1 },
	{             737,	    STRING,	 91,  -1 },
	{             741,	    STRING,	 92,  -1 },
	{             746,	    STRING,	 93,  -1 },
	{             750,	    STRING,	 94,  33 },
	{             754,	    STRING,	 95,  -1 },
	{             758,	    STRING,	 96,  -1 },
	{             762,	    STRING,	 97,  -1 },
	{             766,	    STRING,	 98,   7 },
	{             770,	    STRING,	 99,  94 },
	{             774,	    STRING,	100,  -1 },
	{             778,	    STRING,	101, 131 },
	{             782,	    STRING,	102,  -1 },
	{             786,	    STRING,	103,  -1 },
	{             790,	    STRING,	104,  30 },
	{             794,	    STRING,	105,  -1 },
	{             798,	    STRING,	106,  -1 },
	{             801,	    STRING,	107,  -1 },
	{             805,	    STRING,	108,  -1 },
	{             809,	    STRING,	109,  -1 },
	{             814,	    STRING,	110,  -1 },
	{             817,	    STRING,	111,  -1 },
	{             821,	    STRING,	112, 156 },
	{             825,	    STRING,	113,  -1 },
	{             829,	    STRING,	114,  -1 },
	{             833,	    STRING,	115,  51 },
	{             839,	    STRING,	116,  -1 },
	{             845,	    STRING,	117,  -1 },
	{             849,	    STRING,	118,  -1 },
	{             853,	    STRING,	119,  -1 },
	{             857,	    STRING,	120,  -1 },
	{             861,	    STRING,	121,  -1 },
	{             865,	    STRING,	122,  -1 },
	{             869,	    STRING,	123,  -1 },
	{             873,	    STRING,	124, 126 },
	{             877,	    STRING,	125,  -1 },
	{             880,	    STRING,	126,  -1 },
	{             883,	    STRING,	127,  -1 },
	{             887,	    STRING,	128,  -1 },
	{             890,	    STRING,	129,  -1 },
	{             894,	    STRING,	130,  -1 },
	{             897,	    STRING,	131,  -1 },
	{             901,	    STRING,	132,  -1 },
	{             905,	    STRING,	133,  -1 },
	{             910,	    STRING,	134,  -1 },
	{             913,	    STRING,	135,  -1 },
	{             917,	    STRING,	136,  23 },
	{             920,	    STRING,	137,  -1 },
	{             923,	    STRING,	138,  -1 },
	{             929,	    STRING,	139,  -1 },
	{             933,	    STRING,	140,  -1 },
	{             937,	    STRING,	141, 210 },
	{             941,	    STRING,	142, 211 },
	{             945,	    STRING,	143, 135 },
	{             949,	    STRING,	144,  -1 },
	{             954,	    STRING,	145,  -1 },
	{             958,	    STRING,	146, 176 },
	{             963,	    STRING,	147,  -1 },
	{             967,	    STRING,	148, 194 },
	{             972,	    STRING,	149,  -1 },
	{             978,	    STRING,	150,  -1 },
	{             984,	    STRING,	151, 137 },
	{             989,	    STRING,	152,  -1 },
	{             994,	    STRING,	153,  -1 },
	{             999,	    STRING,	154,  -1 },
	{            1005,	    STRING,	155,  -1 },
	{            1011,	    STRING,	156,  -1 },
	{            1016,	    STRING,	157,  -1 },
	{            1021,	    STRING,	158,  -1 },
	{            1026,	    STRING,	159,  -1 },
	{            1031,	    STRING,	160,  -1 },
	{            1036,	    STRING,	161,  -1 },
	{            1041,	    STRING,	162,  -1 },
	{            1046,	    STRING,	163,  54 },
	{            1051,	    STRING,	164, 192 },
	{            1056,	    STRING,	165,  -1 },
	{            1061,	    STRING,	166,  -1 },
	{            1066,	    STRING,	167, 193 },
	{            1071,	    STRING,	168,  -1 },
	{            1076,	    STRING,	169,  70 },
	{            1081,	    STRING,	170, 235 },
	{            1086,	    STRING,	171,  -1 },
	{            1091,	    STRING,	172,  -1 },
	{            1096,	    STRING,	173, 177 },
	{            1101,	    STRING,	174,  -1 },
	{            1106,	    STRING,	175,  -1 },
	{            1111,	    STRING,	176,  -1 },
	{            1116,	    STRING,	177,  -1 },
	{            1121,	    STRING,	178,  -1 },
	{            1126,	    STRING,	179, 239 },
	{            1131,	    STRING,	180, 219 },
	{            1136,	    STRING,	181,  80 },
	{            1141,	    STRING,	182, 249 },
	{            1146,	    STRING,	183, 252 },
	{            1151,	    STRING,	184, 240 },
	{            1156,	    STRING,	185, 254 },
	{            1161,	    STRING,	186,  -1 },
	{            1166,	    STRING,	187,  -1 },
	{            1171,	    STRING,	188, 101 },
	{            1176,	    STRING,	189,  -1 },
	{            1181,	    STRING,	190,  -1 },
	{            1186,	    STRING,	191,  -1 },
	{            1190,	    STRING,	192,  -1 },
	{            1194,	    STRING,	193, 244 },
	{            1199,	    STRING,	194,  -1 },
	{            1204,	    STRING,	195, 152 },
	{            1209,	    STRING,	196,  -1 },
	{            1214,	    STRING,	197, 150 },
	{            1219,	    STRING,	198,  -1 },
	{            1224,	    STRING,	199, 268 },
	{            1229,	    STRING,	200,  -1 },
	{            1233,	    STRING,	201,  72 },
	{            1238,	    STRING,	202,  -1 },
	{            1243,	    STRING,	203,  -1 },
	{            1248,	    STRING,	204,  -1 },
	{            1253,	    STRING,	205,  -1 },
	{            1258,	    STRING,	206,  -1 },
	{            1263,	    STRING,	207, 196 },
	{            1268,	    STRING,	208,  -1 },
	{            1273,	    STRING,	209,  -1 },
	{            1278,	    STRING,	210,  -1 },
	{            1283,	    STRING,	211,  -1 },
	{            1288,	    STRING,	212, 281 },
	{            1293,	    STRING,	213, 272 },
	{            1298,	    STRING,	214, 283 },
	{            1303,	    STRING,	215,  -1 },
	{            1307,	    STRING,	216,  -1 },
	{            1312,	    STRING,	217, 134 },
	{            1317,	    STRING,	218,  -1 },
	{            1322,	    STRING,	219,  -1 },
	{            1327,	    STRING,	220,  -1 },
	{            1332,	    STRING,	221,  43 },
	{            1337,	    STRING,	222, 256 },
	{            1342,	    STRING,	223,  -1 },
	{            1347,	    STRING,	224,  -1 },
	{            1352,	    STRING,	225, 286 },
	{            1357,	    STRING,	226, 287 },
	{            1362,	    STRING,	227, 288 },
	{            1367,	    STRING,	228, 289 },
	{            1372,	    STRING,	229, 290 },
	{            1377,	    STRING,	230, 291 },
	{            1382,	    STRING,	231, 292 },
	{            1387,	    STRING,	232, 293 },
	{            1392,	    STRING,	233, 294 },
	{            1397,	    STRING,	234, 133 },
	{            1402,	    STRING,	235, 296 },
	{            1407,	    STRING,	236, 297 },
	{            1412,	    STRING,	237, 298 },
	{            1417,	    STRING,	238, 299 },
	{            1422,	    STRING,	239, 300 },
	{            1427,	    STRING,	240, 301 },
	{            1432,	    STRING,	241, 302 },
	{            1437,	    STRING,	242, 303 },
	{            1442,	    STRING,	243, 304 },
	{            1447,	    STRING,	244, 257 },
	{            1452,	    STRING,	245, 306 },
	{            1457,	    STRING,	246, 307 },
	{            1462,	    STRING,	247, 308 },
	{            1467,	    STRING,	248, 309 },
	{            1472,	    STRING,	249, 310 },
	{            1477,	    STRING,	250, 311 },
	{            1482,	    STRING,	251, 312 },
	{            1487,	    STRING,	252, 313 },
	{            1492,	    STRING,	253, 314 },
	{            1497,	    STRING,	254, 226 },
	{            1502,	    STRING,	255, 316 },
	{            1507,	    STRING,	256, 317 },
	{            1512,	    STRING,	257, 318 },
	{            1517,	    STRING,	258, 319 },
	{            1522,	    STRING,	259, 320 },
	{            1527,	    STRING,	260, 321 },
	{            1532,	    STRING,	261, 322 },
	{            1537,	    STRING,	262, 323 },
	{            1542,	    STRING,	263, 324 },
	{            1547,	    STRING,	264, 258 },
	{            1552,	    STRING,	265, 326 },
	{            1557,	    STRING,	266, 327 },
	{            1562,	    STRING,	267, 328 },
	{            1567,	    STRING,	268, 329 },
	{            1572,	    STRING,	269,  -1 },
	{            1576,	    STRING,	270,  -1 },
	{            1580,	    STRING,	271, 335 },
	{            1585,	    STRING,	272, 332 },
	{            1590,	    STRING,	273,  -1 },
	{            1594,	    STRING,	274,  -1 },
	{            1599,	    STRING,	275,  -1 },
	{            1604,	    STRING,	276,  -1 },
	{            1610,	    STRING,	277,  37 },
	{            1615,	    STRING,	278,  -1 },
	{            1621,	    STRING,	279,  -1 },
	{            1625,	    STRING,	280,  -1 },
	{            1630,	    STRING,	281,  -1 },
	{            1636,	    STRING,	282,  -1 },
	{            1641,	    STRING,	283,  -1 },
	{            1647,	    STRING,	284,  -1 },
	{            1652,	    STRING,	285,   8 },
	{            1658,	    STRING,	286, 262 },
	{            1663,	    STRING,	287,  -1 },
	{            1666,	    STRING,	288,  -1 },
	{            1669,	    STRING,	289,  -1 },
	{            1672,	    STRING,	290,  -1 },
	{            1675,	    STRING,	291,  -1 },
	{            1678,	    STRING,	292,  -1 },
	{            1681,	    STRING,	293,  -1 },
	{            1684,	    STRING,	294,  -1 },
	{            1687,	    STRING,	295,  -1 },
	{            1690,	    STRING,	296,  -1 },
	{            1693,	    STRING,	297,  -1 },
	{            1696,	    STRING,	298,  -1 },
	{            1699,	    STRING,	299,  -1 },
	{            1705,	    STRING,	300,  -1 },
	{            1711,	    STRING,	301,  -1 },
	{            1715,	    STRING,	302, 325 },
	{            1720,	    STRING,	303, 221 },
	{            1725,	    STRING,	304, 243 },
	{            1729,	    STRING,	305,  -1 },
	{            1733,	    STRING,	306, 250 },
	{            1737,	    STRING,	307,  -1 },
	{            1741,	    STRING,	308, 141 },
	{            1746,	    STRING,	309, 248 },
	{            1752,	    STRING,	310, 218 },
	{            1758,	    STRING,	311,  -1 },
	{            1763,	    STRING,	312, 201 },
	{            1767,	    STRING,	313, 229 },
	{            1773,	    STRING,	314, 264 },
	{            1778,	    STRING,	315, 253 },
	{            1784,	    STRING,	316, 334 },
	{            1789,	    STRING,	317,  -1 },
	{            1795,	    STRING,	318, 236 },
	{            1801,	    STRING,	319, 185 },
	{            1805,	    STRING,	320,  -1 },
	{            1811,	    STRING,	321,  -1 },
	{            1816,	    STRING,	322,  -1 },
	{            1820,	    STRING,	323,  -1 },
	{            1826,	    STRING,	324, 112 },
	{            1831,	    STRING,	325,  -1 },
	{            1837,	    STRING,	326,  -1 },
	{            1843,	    STRING,	327,  -1 },
	{            1847,	    STRING,	328,  -1 },
	{            1852,	    STRING,	329,  -1 },
	{            1858,	    STRING,	330,  -1 },
	{            1864,	    STRING,	331,  53 },
	{            1870,	    STRING,	332,  -1 },
	{            1875,	    STRING,	333,  47 },
	{            1881,	    STRING,	334, 155 },
	{            1888,	    STRING,	335,  -1 },
	{            1893,	    STRING,	336,  -1 },
	{            1898,	    STRING,	337,  -1 },
	{            1903,	    STRING,	338,  -1 },
	{            1908,	    STRING,	339,  -1 },
	{            1912,	    STRING,	340,  -1 },
	{            1917,	    STRING,	341, 383 },
	{            1923,	    STRING,	342,  -1 },
	{            1929,	    STRING,	343,  -1 },
	{            1935,	    STRING,	344, 386 },
	{            1940,	    STRING,	345, 238 },
	{            1946,	    STRING,	346,  -1 },
	{            1951,	    STRING,	347, 344 },
	{            1956,	    STRING,	348,  31 },
	{            1961,	    STRING,	349,  -1 },
	{            1966,	    STRING,	350, 380 },
	{            1972,	    STRING,	351, 255 },
	{            1978,	    STRING,	352,  -1 },
	{            1983,	    STRING,	353,  -1 },
	{            1989,	    STRING,	354, 347 },
	{            1994,	    STRING,	355,  -1 },
	{            2000,	    STRING,	356,  -1 },
	{            2006,	    STRING,	357,  -1 },
	{            2012,	    STRING,	358,  87 },
	{            2017,	    STRING,	359,  -1 },
	{            2023,	    STRING,	360,  -1 },
	{            2029,	    STRING,	361,  -1 },
	{            2034,	    STRING,	362,  -1 },
	{            2039,	    STRING,	363,  -1 },
	{            2044,	    STRING,	364,  -1 },
	{            2049,	    STRING,	365, 212 },
	{            2054,	    STRING,	366, 109 },
	{            2059,	    STRING,	367, 213 },
	{            2064,	    STRING,	368, 230 },
	{            2070,	    STRING,	369,  -1 },
	{            2076,	    STRING,	370,  -1 },
	{            2082,	    STRING,	371,  -1 },
	{            2088,	    STRING,	372,  -1 },
	{            2093,	    STRING,	373,  -1 },
	{            2101,	    STRING,	374,  -1 },
	{            2107,	    STRING,	375,  -1 },
	{            2113,	    STRING,	376,  -1 },
	{            2122,	    STRING,	377, 116 },
	{            2129,	    STRING,	378,  -1 },
	{            2135,	    STRING,	379, 231 },
	{            2141,	    STRING,	380,  -1 },
	{            2147,	    STRING,	381, 338 },
	{            2152,	    STRING,	382,  -1 },
	{            2157,	    STRING,	383,  -1 },
	{            2163,	    STRING,	384, 197 },
	{            2169,	    STRING,	385, 430 },
	{            2175,	    STRING,	386,  -1 },
	{            2181,	    STRING,	387,  -1 },
	{            2187,	    STRING,	388,  -1 },
	{            2194,	    STRING,	389,  -1 },
	{            2200,	    STRING,	390,  -1 },
	{            2206,	    STRING,	391,  -1 },
	{            2212,	    STRING,	392, 437 },
	{            2217,	    STRING,	393,  -1 },
	{            2225,	    STRING,	394,  -1 },
	{            2230,	    STRING,	395,  -1 },
	{            2235,	    NUMBER,	 33,  -1 },
	{            2240,	   BOOLEAN,	 37,  -1 },
	{            2245,	   BOOLEAN,	 38,  -1 },
	{            2250,	   BOOLEAN,	 39,  -1 },
	{            2255,	    NUMBER,	 34,  -1 },
	{            2260,	    NUMBER,	 35,  -1 },
	{            2265,	    STRING,	396,  -1 },
	{            2270,	    STRING,	397,  13 },
	{            2275,	   BOOLEAN,	 40,  -1 },
	{            2280,	   BOOLEAN,	 41, 446 },
	{            2285,	    NUMBER,	 36,  -1 },
	{            2290,	    NUMBER,	 37,  -1 },
	{            2295,	    NUMBER,	 38,  -1 },
	{            2300,	    STRING,	398, 472 },
	{            2305,	    STRING,	399,  -1 },
	{            2310,	   BOOLEAN,	 42,  -1 },
	{            2315,	   BOOLEAN,	 43,  -1 },
	{            2320,	    STRING,	400,  -1 },
	{            2325,	    STRING,	401,  -1 },
	{            2330,	    STRING,	402,  -1 },
	{            2335,	    STRING,	403,  -1 },
	{            2340,	    STRING,	404,  -1 },
	{            2345,	    STRING,	405,  -1 },
	{            2350,	    STRING,	406,  -1 },
	{            2355,	    STRING,	407,  -1 },
	{            2360,	    STRING,	408,  26 },
	{            2365,	    STRING,	409,  60 },
	{            2370,	    STRING,	410, 121 },
	{            2375,	    STRING,	411, 407 },
	{            2380,	    STRING,	412, 402 },
	{            2385,	    STRING,	413,  -1 } 
};

static struct name_table_entry *_nc_info_table = 0;

static const HashValue _nc_info_hash_table[995] =
{
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	465,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	261,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	457,
	 -1,
	 -1,
	265,
	216,
	120,
	 -1,
	 -1,
	 -1,
	180,
	 -1,
	 -1,
	 88,
	 -1,
	420,
	 -1,
	398,
	 -1,
	348,
	 -1,
	 -1,
	 19,
	 -1,
	 -1,
	 -1,
	359,
	 -1,
	174,
	 -1,
	245,
	 -1,
	 74,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	269,
	 -1,
	480,
	 -1,
	 -1,
	 -1,
	124,
	 -1,
	 -1,
	 -1,
	390,
	379,
	367,
	 -1,
	 -1,
	444,
	 -1,
	 -1,
	 -1,
	305,
	 -1,
	 -1,
	363,
	 -1,
	 -1,
	483,
	377,
	 -1,
	 -1,
	 -1,
	 -1,
	460,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	204,
	 38,
	 -1,
	 82,
	 -1,
	110,
	127,
	 -1,
	 -1,
	463,
	 -1,
	 -1,
	 -1,
	 -1,
	336,
	 -1,
	 17,
	128,
	434,
	 -1,
	188,
	129,
	 -1,
	351,
	 -1,
	 -1,
	 16,
	 -1,
	 -1,
	259,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	489,
	 -1,
	353,
	 -1,
	 71,
	247,
	 -1,
	 -1,
	 -1,
	 -1,
	 78,
	 -1,
	 -1,
	331,
	 -1,
	 -1,
	173,
	136,
	161,
	189,
	 -1,
	 -1,
	 -1,
	 -1,
	454,
	 -1,
	 -1,
	 -1,
	 -1,
	224,
	479,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	354,
	 -1,
	 -1,
	233,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	125,
	 11,
	 -1,
	 -1,
	378,
	166,
	 -1,
	191,
	 -1,
	 -1,
	 48,
	228,
	 -1,
	  2,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	374,
	 -1,
	408,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	375,
	 -1,
	 52,
	145,
	170,
	 -1,
	392,
	382,
	 -1,
	393,
	411,
	 -1,
	 -1,
	 -1,
	276,
	 -1,
	 -1,
	 35,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	396,
	388,
	 36,
	 -1,
	 -1,
	 64,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	350,
	 -1,
	 -1,
	215,
	 91,
	 -1,
	 -1,
	439,
	 -1,
	122,
	 -1,
	200,
	 -1,
	 67,
	 -1,
	410,
	 -1,
	 -1,
	 89,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 96,
	 21,
	 -1,
	103,
	  1,
	 -1,
	 -1,
	369,
	 -1,
	 -1,
	345,
	 -1,
	 -1,
	 -1,
	355,
	 40,
	 -1,
	 27,
	 -1,
	406,
	 -1,
	 -1,
	 -1,
	482,
	419,
	417,
	 -1,
	 -1,
	360,
	270,
	 -1,
	 -1,
	251,
	 -1,
	 -1,
	 -1,
	 -1,
	349,
	 -1,
	 -1,
	278,
	 -1,
	442,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	438,
	 -1,
	494,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	315,
	 -1,
	340,
	364,
	356,
	 -1,
	484,
	 -1,
	 -1,
	 -1,
	 -1,
	 32,
	 -1,
	 -1,
	 -1,
	260,
	 -1,
	 -1,
	 -1,
	 -1,
	207,
	487,
	 84,
	453,
	 -1,
	 -1,
	413,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	214,
	 -1,
	337,
	352,
	477,
	 -1,
	435,
	 56,
	 -1,
	 -1,
	 34,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	132,
	 -1,
	 85,
	492,
	428,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	199,
	 -1,
	342,
	 -1,
	 -1,
	 -1,
	138,
	163,
	190,
	147,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	266,
	 -1,
	 -1,
	433,
	 -1,
	 -1,
	474,
	 -1,
	 -1,
	 -1,
	 -1,
	385,
	100,
	 -1,
	 -1,
	 -1,
	431,
	 -1,
	391,
	381,
	 12,
	 58,
	 -1,
	142,
	167,
	 -1,
	 -1,
	409,
	 -1,
	 -1,
	 -1,
	 -1,
	 42,
	 45,
	 66,
	 -1,
	 -1,
	424,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	220,
	376,
	 -1,
	 -1,
	343,
	 -1,
	 -1,
	 -1,
	114,
	106,
	 -1,
	 -1,
	447,
	 -1,
	217,
	493,
	171,
	172,
	399,
	346,
	 -1,
	 -1,
	 -1,
	 -1,
	195,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	496,
	 -1,
	 -1,
	 -1,
	 -1,
	241,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	151,
	 -1,
	118,
	 -1,
	 62,
	187,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	234,
	 -1,
	443,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	357,
	 -1,
	 -1,
	 -1,
	246,
	 -1,
	 -1,
	 -1,
	448,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 39,
	 -1,
	 10,
	397,
	389,
	 -1,
	 -1,
	154,
	 -1,
	 -1,
	 -1,
	130,
	 -1,
	 22,
	222,
	373,
	162,
	 -1,
	361,
	203,
	 -1,
	 -1,
	242,
	 -1,
	 -1,
	 -1,
	 -1,
	459,
	 -1,
	 -1,
	271,
	 -1,
	 97,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	427,
	 -1,
	175,
	107,
	 -1,
	 -1,
	 -1,
	178,
	423,
	372,
	 69,
	 -1,
	365,
	 -1,
	  4,
	486,
	184,
	 -1,
	 -1,
	 -1,
	 -1,
	461,
	 -1,
	 -1,
	282,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	475,
	 -1,
	 -1,
	 -1,
	395,
	387,
	 -1,
	 -1,
	 79,
	 63,
	 -1,
	 -1,
	452,
	451,
	 -1,
	 50,
	 -1,
	436,
	 -1,
	 -1,
	285,
	 -1,
	 -1,
	 83,
	455,
	 -1,
	 -1,
	 -1,
	279,
	370,
	 -1,
	 -1,
	 -1,
	 18,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	421,
	 -1,
	495,
	 -1,
	 -1,
	 -1,
	 -1,
	227,
	333,
	 -1,
	 -1,
	 25,
	139,
	164,
	 -1,
	 -1,
	371,
	 -1,
	 -1,
	429,
	 -1,
	 -1,
	 -1,
	273,
	 -1,
	466,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	181,
	 -1,
	 -1,
	 75,
	 -1,
	 92,
	339,
	 -1,
	384,
	 -1,
	123,
	 -1,
	143,
	168,
	 -1,
	183,
	186,
	 -1,
	108,
	 95,
	368,
	 -1,
	 -1,
	277,
	198,
	 -1,
	206,
	432,
	 -1,
	476,
	 -1,
	458,
	 -1,
	 -1,
	182,
	 -1,
	441,
	 -1,
	 -1,
	 -1,
	115,
	113,
	404,
	 -1,
	473,
	 -1,
	 -1,
	 -1,
	490,
	104,
	 -1,
	 -1,
	450,
	449,
	 -1,
	 -1,
	 -1,
	274,
	 -1,
	481,
	111,
	 99,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	263,
	 93,
	 -1,
	117,
	 -1,
	 29,
	 -1,
	 -1,
	 -1,
	 -1,
	119,
	 -1,
	 -1,
	426,
	491,
	 -1,
	 -1,
	205,
	 -1,
	237,
	 44,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	418,
	416,
	 -1,
	 -1,
	358,
	 -1,
	 -1,
	 -1,
	 65,
	 -1,
	440,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	  5,
	 -1,
	 -1,
	 -1,
	488,
	 -1,
	 -1,
	 -1,
	 28,
	412,
	 -1,
	405,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	295,
	 -1,
	471,
	362,
	 -1,
	 -1,
	485,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	202,
	 -1,
	 -1,
	284,
	 -1,
	469,
	 -1,
	 -1,
	  9,
	 24,
	 -1,
	 -1,
	179,
	 -1,
	 -1,
	 15,
	 -1,
	 -1,
	148,
	 -1,
	 -1,
	 -1,
	341,
	 -1,
	 -1,
	366,
	209,
	223,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	  0,
	 -1,
	208,
	467,
	 -1,
	422,
	 -1,
	464,
	157,
	 -1,
	403,
	 -1,
	415,
	 -1,
	 -1,
	 -1,
	 -1,
	445,
	 -1,
	 -1,
	330,
	 -1,
	 -1,
	 -1,
	462,
	160,
	 -1,
	 -1,
	 -1,
	 -1,
	 86,
	 -1,
	 -1,
	 41,
	 -1,
	280,
	 -1,
	478,
	 -1,
	 -1,
	 57,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	394,
	414,
	 -1,
	 -1,
	 -1,
	140,
	165,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	275,
	102,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	232,
	 -1,
	 14,
	 -1,
	 -1,
	225,
	 -1,
	 -1,
	267,
	 -1,
	 77,
	 -1,
	144,
	169,
	 -1,
	149,
	 -1,
	400,
	 -1,
	 -1,
	 -1,
	  3,
	 -1,
	 -1,
	 -1,
	468,
	425,
	 -1,
	 -1,
	470,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	456,
	 -1,
	158,
	159,
	 -1,
	 -1,
	146,
	 49,
	 -1,
	 -1,
	153,
	 -1,
	401,
	 90,
	0	/* base-of-table */
};

#if (BOOLCOUNT!=44)||(NUMCOUNT!=39)||(STRCOUNT!=414)
#error	--> term.h and comp_captab.c disagree about the <--
#error	--> numbers of booleans, numbers and/or strings <--
#endif

/* 103 collisions out of 497 entries */
static const char cap_names_text[] = \
"bw\0" "am\0" "xb\0" "xs\0" "xn\0" "eo\0" "gn\0" "hc\0" "km\0" "hs\0" \
"in\0" "da\0" "db\0" "mi\0" "ms\0" "os\0" "es\0" "xt\0" "hz\0" "ul\0" \
"xo\0" "nx\0" "5i\0" "HC\0" "NR\0" "NP\0" "ND\0" "cc\0" "ut\0" "hl\0" \
"YA\0" "YB\0" "YC\0" "YD\0" "YE\0" "YF\0" "YG\0" "co\0" "it\0" "li\0" \
"lm\0" "sg\0" "pb\0" "vt\0" "ws\0" "Nl\0" "lh\0" "lw\0" "ma\0" "MW\0" \
"Co\0" "pa\0" "NC\0" "Ya\0" "Yb\0" "Yc\0" "Yd\0" "Ye\0" "Yf\0" "Yg\0" \
"Yh\0" "Yi\0" "Yj\0" "Yk\0" "Yl\0" "Ym\0" "Yn\0" "BT\0" "Yo\0" "Yp\0" \
"bt\0" "bl\0" "cr\0" "cs\0" "ct\0" "cl\0" "ce\0" "cd\0" "ch\0" "CC\0" \
"cm\0" "do\0" "ho\0" "vi\0" "le\0" "CM\0" "ve\0" "nd\0" "ll\0" "up\0" \
"vs\0" "dc\0" "dl\0" "ds\0" "hd\0" "as\0" "mb\0" "md\0" "ti\0" "dm\0" \
"mh\0" "im\0" "mk\0" "mp\0" "mr\0" "so\0" "us\0" "ec\0" "ae\0" "me\0" \
"te\0" "ed\0" "ei\0" "se\0" "ue\0" "vb\0" "ff\0" "fs\0" "i1\0" "is\0" \
"i3\0" "if\0" "ic\0" "al\0" "ip\0" "kb\0" "ka\0" "kC\0" "kt\0" "kD\0" \
"kL\0" "kd\0" "kM\0" "kE\0" "kS\0" "k0\0" "k1\0" "k;\0" "k2\0" "k3\0" \
"k4\0" "k5\0" "k6\0" "k7\0" "k8\0" "k9\0" "kh\0" "kI\0" "kA\0" "kl\0" \
"kH\0" "kN\0" "kP\0" "kr\0" "kF\0" "kR\0" "kT\0" "ku\0" "ke\0" "ks\0" \
"l0\0" "l1\0" "la\0" "l2\0" "l3\0" "l4\0" "l5\0" "l6\0" "l7\0" "l8\0" \
"l9\0" "mo\0" "mm\0" "nw\0" "pc\0" "DC\0" "DL\0" "DO\0" "IC\0" "SF\0" \
"AL\0" "LE\0" "RI\0" "SR\0" "UP\0" "pk\0" "pl\0" "px\0" "ps\0" "pf\0" \
"po\0" "rp\0" "r1\0" "r2\0" "r3\0" "rf\0" "rc\0" "cv\0" "sc\0" "sf\0" \
"sr\0" "sa\0" "st\0" "wi\0" "ta\0" "ts\0" "uc\0" "hu\0" "iP\0" "K1\0" \
"K3\0" "K2\0" "K4\0" "K5\0" "pO\0" "rP\0" "ac\0" "pn\0" "kB\0" "SX\0" \
"RX\0" "SA\0" "RA\0" "XN\0" "XF\0" "eA\0" "LO\0" "LF\0" "@1\0" "@2\0" \
"@3\0" "@4\0" "@5\0" "@6\0" "@7\0" "@8\0" "@9\0" "@0\0" "%1\0" "%2\0" \
"%3\0" "%4\0" "%5\0" "%6\0" "%7\0" "%8\0" "%9\0" "%0\0" "&1\0" "&2\0" \
"&3\0" "&4\0" "&5\0" "&6\0" "&7\0" "&8\0" "&9\0" "&0\0" "*1\0" "*2\0" \
"*3\0" "*4\0" "*5\0" "*6\0" "*7\0" "*8\0" "*9\0" "*0\0" "#1\0" "#2\0" \
"#3\0" "#4\0" "%a\0" "%b\0" "%c\0" "%d\0" "%e\0" "%f\0" "%g\0" "%h\0" \
"%i\0" "%j\0" "!1\0" "!2\0" "!3\0" "RF\0" "F1\0" "F2\0" "F3\0" "F4\0" \
"F5\0" "F6\0" "F7\0" "F8\0" "F9\0" "FA\0" "FB\0" "FC\0" "FD\0" "FE\0" \
"FF\0" "FG\0" "FH\0" "FI\0" "FJ\0" "FK\0" "FL\0" "FM\0" "FN\0" "FO\0" \
"FP\0" "FQ\0" "FR\0" "FS\0" "FT\0" "FU\0" "FV\0" "FW\0" "FX\0" "FY\0" \
"FZ\0" "Fa\0" "Fb\0" "Fc\0" "Fd\0" "Fe\0" "Ff\0" "Fg\0" "Fh\0" "Fi\0" \
"Fj\0" "Fk\0" "Fl\0" "Fm\0" "Fn\0" "Fo\0" "Fp\0" "Fq\0" "Fr\0" "cb\0" \
"MC\0" "ML\0" "MR\0" "Lf\0" "SC\0" "DK\0" "RC\0" "CW\0" "WG\0" "HU\0" \
"DI\0" "QD\0" "TO\0" "PU\0" "fh\0" "PA\0" "WA\0" "u0\0" "u1\0" "u2\0" \
"u3\0" "u4\0" "u5\0" "u6\0" "u7\0" "u8\0" "u9\0" "op\0" "oc\0" "Ic\0" \
"Ip\0" "sp\0" "Sf\0" "Sb\0" "ZA\0" "ZB\0" "ZC\0" "ZD\0" "ZE\0" "ZF\0" \
"ZG\0" "ZH\0" "ZI\0" "ZJ\0" "ZK\0" "ZL\0" "ZM\0" "ZN\0" "ZO\0" "ZP\0" \
"ZQ\0" "ZR\0" "ZS\0" "ZT\0" "ZU\0" "ZV\0" "ZW\0" "ZX\0" "ZY\0" "ZZ\0" \
"Za\0" "Zb\0" "Zc\0" "Zd\0" "Ze\0" "Zf\0" "Zg\0" "Zh\0" "Zi\0" "Zj\0" \
"Zk\0" "Zl\0" "Zm\0" "Zn\0" "Zo\0" "Zp\0" "Zq\0" "Zr\0" "Zs\0" "Zt\0" \
"Zu\0" "Zv\0" "Zw\0" "Zx\0" "Zy\0" "Km\0" "Mi\0" "RQ\0" "Gm\0" "AF\0" \
"AB\0" "xl\0" "dv\0" "ci\0" "s0\0" "s1\0" "s2\0" "s3\0" "ML\0" "MT\0" \
"Xy\0" "Zz\0" "Yv\0" "Yw\0" "Yx\0" "Yy\0" "Yz\0" "YZ\0" "S1\0" "S2\0" \
"S3\0" "S4\0" "S5\0" "S6\0" "S7\0" "S8\0" "Xh\0" "Xl\0" "Xo\0" "Xr\0" \
"Xt\0" "Xv\0" "sA\0" "YI\0" "i2\0" "rs\0" "ug\0" "bs\0" "ns\0" "nc\0" \
"dC\0" "dN\0" "nl\0" "bc\0" "MT\0" "NL\0" "dB\0" "dT\0" "kn\0" "ko\0" \
"ma\0" "pt\0" "xr\0" "G2\0" "G3\0" "G1\0" "G4\0" "GR\0" "GL\0" "GU\0" \
"GD\0" "GH\0" "GV\0" "GC\0" "ml\0" "mu\0" "bx\0" ;

static name_table_data const cap_names_data[] =
{
	{               0,	   BOOLEAN,	  0,  -1 },
	{               3,	   BOOLEAN,	  1,  -1 },
	{               6,	   BOOLEAN,	  2,  -1 },
	{               9,	   BOOLEAN,	  3,  -1 },
	{              12,	   BOOLEAN,	  4,  -1 },
	{              15,	   BOOLEAN,	  5,  -1 },
	{              18,	   BOOLEAN,	  6,  -1 },
	{              21,	   BOOLEAN,	  7,  -1 },
	{              24,	   BOOLEAN,	  8,  -1 },
	{              27,	   BOOLEAN,	  9,  -1 },
	{              30,	   BOOLEAN,	 10,  -1 },
	{              33,	   BOOLEAN,	 11,  -1 },
	{              36,	   BOOLEAN,	 12,  -1 },
	{              39,	   BOOLEAN,	 13,  -1 },
	{              42,	   BOOLEAN,	 14,  -1 },
	{              45,	   BOOLEAN,	 15,  -1 },
	{              48,	   BOOLEAN,	 16,  -1 },
	{              51,	   BOOLEAN,	 17,  -1 },
	{              54,	   BOOLEAN,	 18,  -1 },
	{              57,	   BOOLEAN,	 19,  -1 },
	{              60,	   BOOLEAN,	 20,  -1 },
	{              63,	   BOOLEAN,	 21,  -1 },
	{              66,	   BOOLEAN,	 22,  -1 },
	{              69,	   BOOLEAN,	 23,  -1 },
	{              72,	   BOOLEAN,	 24,   1 },
	{              75,	   BOOLEAN,	 25,  -1 },
	{              78,	   BOOLEAN,	 26,  -1 },
	{              81,	   BOOLEAN,	 27,  -1 },
	{              84,	   BOOLEAN,	 28,  -1 },
	{              87,	   BOOLEAN,	 29,  -1 },
	{              90,	   BOOLEAN,	 30,  -1 },
	{              93,	   BOOLEAN,	 31,  -1 },
	{              96,	   BOOLEAN,	 32,  -1 },
	{              99,	   BOOLEAN,	 33,  -1 },
	{             102,	   BOOLEAN,	 34,  -1 },
	{             105,	   BOOLEAN,	 35,  -1 },
	{             108,	   BOOLEAN,	 36,  -1 },
	{             111,	    NUMBER,	  0,  -1 },
	{             114,	    NUMBER,	  1,  -1 },
	{             117,	    NUMBER,	  2,  -1 },
	{             120,	    NUMBER,	  3,  -1 },
	{             123,	    NUMBER,	  4,  -1 },
	{             126,	    NUMBER,	  5,  -1 },
	{             129,	    NUMBER,	  6,  -1 },
	{             132,	    NUMBER,	  7,  -1 },
	{             135,	    NUMBER,	  8,  -1 },
	{             138,	    NUMBER,	  9,  -1 },
	{             141,	    NUMBER,	 10,  -1 },
	{             144,	    NUMBER,	 11,  -1 },
	{             147,	    NUMBER,	 12,  -1 },
	{             150,	    NUMBER,	 13,  -1 },
	{             153,	    NUMBER,	 14,  -1 },
	{             156,	    NUMBER,	 15,  -1 },
	{             159,	    NUMBER,	 16,  -1 },
	{             162,	    NUMBER,	 17,  -1 },
	{             165,	    NUMBER,	 18,  -1 },
	{             168,	    NUMBER,	 19,  -1 },
	{             171,	    NUMBER,	 20,  -1 },
	{             174,	    NUMBER,	 21,  -1 },
	{             177,	    NUMBER,	 22,  -1 },
	{             180,	    NUMBER,	 23,  -1 },
	{             183,	    NUMBER,	 24,  -1 },
	{             186,	    NUMBER,	 25,  -1 },
	{             189,	    NUMBER,	 26,  -1 },
	{             192,	    NUMBER,	 27,  -1 },
	{             195,	    NUMBER,	 28,  -1 },
	{             198,	    NUMBER,	 29,  -1 },
	{             201,	    NUMBER,	 30,  -1 },
	{             204,	    NUMBER,	 31,  -1 },
	{             207,	    NUMBER,	 32,  -1 },
	{             210,	    STRING,	  0,  -1 },
	{             213,	    STRING,	  1,  -1 },
	{             216,	    STRING,	  2,  -1 },
	{             219,	    STRING,	  3,  -1 },
	{             222,	    STRING,	  4,  -1 },
	{             225,	    STRING,	  5,  -1 },
	{             228,	    STRING,	  6,  -1 },
	{             231,	    STRING,	  7,  -1 },
	{             234,	    STRING,	  8,  -1 },
	{             237,	    STRING,	  9,  -1 },
	{             240,	    STRING,	 10,  -1 },
	{             243,	    STRING,	 11,  -1 },
	{             246,	    STRING,	 12,  -1 },
	{             249,	    STRING,	 13,  -1 },
	{             252,	    STRING,	 14,  -1 },
	{             255,	    STRING,	 15,  -1 },
	{             258,	    STRING,	 16,  -1 },
	{             261,	    STRING,	 17,  -1 },
	{             264,	    STRING,	 18,  -1 },
	{             267,	    STRING,	 19,  -1 },
	{             270,	    STRING,	 20,  -1 },
	{             273,	    STRING,	 21,  -1 },
	{             276,	    STRING,	 22,  -1 },
	{             279,	    STRING,	 23,  -1 },
	{             282,	    STRING,	 24,  -1 },
	{             285,	    STRING,	 25,  -1 },
	{             288,	    STRING,	 26,  -1 },
	{             291,	    STRING,	 27,  -1 },
	{             294,	    STRING,	 28,  -1 },
	{             297,	    STRING,	 29,  -1 },
	{             300,	    STRING,	 30,  -1 },
	{             303,	    STRING,	 31,  -1 },
	{             306,	    STRING,	 32,  -1 },
	{             309,	    STRING,	 33,  -1 },
	{             312,	    STRING,	 34,  -1 },
	{             315,	    STRING,	 35,  -1 },
	{             318,	    STRING,	 36,  -1 },
	{             321,	    STRING,	 37,  -1 },
	{             324,	    STRING,	 38,  -1 },
	{             327,	    STRING,	 39,  -1 },
	{             330,	    STRING,	 40,  -1 },
	{             333,	    STRING,	 41,  -1 },
	{             336,	    STRING,	 42,  -1 },
	{             339,	    STRING,	 43,  -1 },
	{             342,	    STRING,	 44,  -1 },
	{             345,	    STRING,	 45,  -1 },
	{             348,	    STRING,	 46,  -1 },
	{             351,	    STRING,	 47,  -1 },
	{             354,	    STRING,	 48, 102 },
	{             357,	    STRING,	 49,  -1 },
	{             360,	    STRING,	 50,  -1 },
	{             363,	    STRING,	 51,  -1 },
	{             366,	    STRING,	 52,  -1 },
	{             369,	    STRING,	 53,  -1 },
	{             372,	    STRING,	 54,  -1 },
	{             375,	    STRING,	 55,  -1 },
	{             378,	    STRING,	 56,  -1 },
	{             381,	    STRING,	 57,  -1 },
	{             384,	    STRING,	 58,  -1 },
	{             387,	    STRING,	 59,  -1 },
	{             390,	    STRING,	 60,  -1 },
	{             393,	    STRING,	 61,  -1 },
	{             396,	    STRING,	 62,  -1 },
	{             399,	    STRING,	 63,  -1 },
	{             402,	    STRING,	 64,  -1 },
	{             405,	    STRING,	 65,  -1 },
	{             408,	    STRING,	 66,  -1 },
	{             411,	    STRING,	 67,  -1 },
	{             414,	    STRING,	 68,  -1 },
	{             417,	    STRING,	 69,  -1 },
	{             420,	    STRING,	 70,  -1 },
	{             423,	    STRING,	 71,  -1 },
	{             426,	    STRING,	 72,  -1 },
	{             429,	    STRING,	 73,  -1 },
	{             432,	    STRING,	 74,  -1 },
	{             435,	    STRING,	 75,  15 },
	{             438,	    STRING,	 76,  -1 },
	{             441,	    STRING,	 77,  -1 },
	{             444,	    STRING,	 78,  -1 },
	{             447,	    STRING,	 79,  -1 },
	{             450,	    STRING,	 80,  -1 },
	{             453,	    STRING,	 81,  -1 },
	{             456,	    STRING,	 82,  -1 },
	{             459,	    STRING,	 83,  -1 },
	{             462,	    STRING,	 84,  -1 },
	{             465,	    STRING,	 85,  -1 },
	{             468,	    STRING,	 86,  -1 },
	{             471,	    STRING,	 87,  -1 },
	{             474,	    STRING,	 88,  -1 },
	{             477,	    STRING,	 89,  -1 },
	{             480,	    STRING,	 90,  -1 },
	{             483,	    STRING,	 91,  -1 },
	{             486,	    STRING,	 92,  35 },
	{             489,	    STRING,	 93,  -1 },
	{             492,	    STRING,	 94,  -1 },
	{             495,	    STRING,	 95,  -1 },
	{             498,	    STRING,	 96,  -1 },
	{             501,	    STRING,	 97,  -1 },
	{             504,	    STRING,	 98,  -1 },
	{             507,	    STRING,	 99,  -1 },
	{             510,	    STRING,	100,  -1 },
	{             513,	    STRING,	101,  -1 },
	{             516,	    STRING,	102, 120 },
	{             519,	    STRING,	103,  -1 },
	{             522,	    STRING,	104,  -1 },
	{             525,	    STRING,	105,  -1 },
	{             528,	    STRING,	106,  -1 },
	{             531,	    STRING,	107,  -1 },
	{             534,	    STRING,	108,  -1 },
	{             537,	    STRING,	109,  -1 },
	{             540,	    STRING,	110,  -1 },
	{             543,	    STRING,	111,  -1 },
	{             546,	    STRING,	112, 111 },
	{             549,	    STRING,	113,  -1 },
	{             552,	    STRING,	114,  -1 },
	{             555,	    STRING,	115, 161 },
	{             558,	    STRING,	116, 163 },
	{             561,	    STRING,	117,  -1 },
	{             564,	    STRING,	118, 170 },
	{             567,	    STRING,	119,  -1 },
	{             570,	    STRING,	120, 166 },
	{             573,	    STRING,	121,  -1 },
	{             576,	    STRING,	122,  -1 },
	{             579,	    STRING,	123,  -1 },
	{             582,	    STRING,	124,  -1 },
	{             585,	    STRING,	125,  -1 },
	{             588,	    STRING,	126,  -1 },
	{             591,	    STRING,	127,  -1 },
	{             594,	    STRING,	128,  -1 },
	{             597,	    STRING,	129,  -1 },
	{             600,	    STRING,	130,  -1 },
	{             603,	    STRING,	131,  -1 },
	{             606,	    STRING,	132,  -1 },
	{             609,	    STRING,	133,  -1 },
	{             612,	    STRING,	134,  -1 },
	{             615,	    STRING,	135,  -1 },
	{             618,	    STRING,	136,  -1 },
	{             621,	    STRING,	137,  -1 },
	{             624,	    STRING,	138,  -1 },
	{             627,	    STRING,	139,  -1 },
	{             630,	    STRING,	140,  -1 },
	{             633,	    STRING,	141,  -1 },
	{             636,	    STRING,	142,  -1 },
	{             639,	    STRING,	143,  -1 },
	{             642,	    STRING,	144,  -1 },
	{             645,	    STRING,	145,  37 },
	{             648,	    STRING,	146,  -1 },
	{             651,	    STRING,	147, 165 },
	{             654,	    STRING,	148,  -1 },
	{             657,	    STRING,	149, 117 },
	{             660,	    STRING,	150,  16 },
	{             663,	    STRING,	151,  -1 },
	{             666,	    STRING,	152,  -1 },
	{             669,	    STRING,	153,  -1 },
	{             672,	    STRING,	154, 126 },
	{             675,	    STRING,	155,  -1 },
	{             678,	    STRING,	156,  -1 },
	{             681,	    STRING,	157,  -1 },
	{             684,	    STRING,	158,  -1 },
	{             687,	    STRING,	159,  -1 },
	{             690,	    STRING,	160,  -1 },
	{             693,	    STRING,	161,  -1 },
	{             696,	    STRING,	162,  -1 },
	{             699,	    STRING,	163,  -1 },
	{             702,	    STRING,	164, 183 },
	{             705,	    STRING,	165,  -1 },
	{             708,	    STRING,	166,  -1 },
	{             711,	    STRING,	167, 116 },
	{             714,	    STRING,	168,  -1 },
	{             717,	    STRING,	169,  97 },
	{             720,	    STRING,	170, 109 },
	{             723,	    STRING,	171,  -1 },
	{             726,	    STRING,	172,  -1 },
	{             729,	    STRING,	173, 100 },
	{             732,	    STRING,	174,  13 },
	{             735,	    STRING,	175,  -1 },
	{             738,	    STRING,	176, 118 },
	{             741,	    STRING,	177,  96 },
	{             744,	    STRING,	178,  -1 },
	{             747,	    STRING,	179,  87 },
	{             750,	    STRING,	180,  -1 },
	{             753,	    STRING,	181,  -1 },
	{             756,	    STRING,	182,  -1 },
	{             759,	    STRING,	183,  -1 },
	{             762,	    STRING,	184,  -1 },
	{             765,	    STRING,	185,  -1 },
	{             768,	    STRING,	186,  -1 },
	{             771,	    STRING,	187,  -1 },
	{             774,	    STRING,	188, 196 },
	{             777,	    STRING,	189,  -1 },
	{             780,	    STRING,	190,  -1 },
	{             783,	    STRING,	191, 195 },
	{             786,	    STRING,	192,  -1 },
	{             789,	    STRING,	193,  -1 },
	{             792,	    STRING,	194,  -1 },
	{             795,	    STRING,	195,  -1 },
	{             798,	    STRING,	196,  -1 },
	{             801,	    STRING,	197,  -1 },
	{             804,	    STRING,	198,  -1 },
	{             807,	    STRING,	199, 131 },
	{             810,	    STRING,	200, 158 },
	{             813,	    STRING,	201,  -1 },
	{             816,	    STRING,	202,  -1 },
	{             819,	    STRING,	203,  -1 },
	{             822,	    STRING,	204,  -1 },
	{             825,	    STRING,	205,  -1 },
	{             828,	    STRING,	206,  -1 },
	{             831,	    STRING,	207,  -1 },
	{             834,	    STRING,	208,  -1 },
	{             837,	    STRING,	209,  -1 },
	{             840,	    STRING,	210,  -1 },
	{             843,	    STRING,	211,  -1 },
	{             846,	    STRING,	212, 122 },
	{             849,	    STRING,	213,  -1 },
	{             852,	    STRING,	214,  -1 },
	{             855,	    STRING,	215,  -1 },
	{             858,	    STRING,	216,  -1 },
	{             861,	    STRING,	217,  46 },
	{             864,	    STRING,	218,  39 },
	{             867,	    STRING,	219,  -1 },
	{             870,	    STRING,	220,  -1 },
	{             873,	    STRING,	221,  88 },
	{             876,	    STRING,	222,  40 },
	{             879,	    STRING,	223,  -1 },
	{             882,	    STRING,	224,  -1 },
	{             885,	    STRING,	225,  47 },
	{             888,	    STRING,	226,  -1 },
	{             891,	    STRING,	227,  -1 },
	{             894,	    STRING,	228,  -1 },
	{             897,	    STRING,	229,  -1 },
	{             900,	    STRING,	230,  53 },
	{             903,	    STRING,	231,  54 },
	{             906,	    STRING,	232,  55 },
	{             909,	    STRING,	233,  56 },
	{             912,	    STRING,	234,  57 },
	{             915,	    STRING,	235,  58 },
	{             918,	    STRING,	236,  59 },
	{             921,	    STRING,	237,  60 },
	{             924,	    STRING,	238,  61 },
	{             927,	    STRING,	239,  62 },
	{             930,	    STRING,	240,  63 },
	{             933,	    STRING,	241,  64 },
	{             936,	    STRING,	242,  65 },
	{             939,	    STRING,	243,  66 },
	{             942,	    STRING,	244,  68 },
	{             945,	    STRING,	245,  69 },
	{             948,	    STRING,	246,  -1 },
	{             951,	    STRING,	247,  -1 },
	{             954,	    STRING,	248,  -1 },
	{             957,	    STRING,	249,  -1 },
	{             960,	    STRING,	250,  -1 },
	{             963,	    STRING,	251,  -1 },
	{             966,	    STRING,	252,  -1 },
	{             969,	    STRING,	253,  -1 },
	{             972,	    STRING,	254,  -1 },
	{             975,	    STRING,	255,  -1 },
	{             978,	    STRING,	256,  -1 },
	{             981,	    STRING,	257,   7 },
	{             984,	    STRING,	258,  94 },
	{             987,	    STRING,	259,  -1 },
	{             990,	    STRING,	260,  -1 },
	{             993,	    STRING,	261,  -1 },
	{             996,	    STRING,	262,  -1 },
	{             999,	    STRING,	263,  -1 },
	{            1002,	    STRING,	264,  -1 },
	{            1005,	    STRING,	265, 184 },
	{            1008,	    STRING,	266,  29 },
	{            1011,	    STRING,	267,  -1 },
	{            1014,	    STRING,	268,  -1 },
	{            1017,	    STRING,	269,  -1 },
	{            1020,	    STRING,	270,  -1 },
	{            1023,	    STRING,	271,  -1 },
	{            1026,	    STRING,	272,  -1 },
	{            1029,	    STRING,	273, 257 },
	{            1032,	    STRING,	274,  -1 },
	{            1035,	    STRING,	275,  -1 },
	{            1038,	    STRING,	276,  -1 },
	{            1041,	    STRING,	277,   4 },
	{            1044,	    STRING,	278,  -1 },
	{            1047,	    STRING,	279,  -1 },
	{            1050,	    STRING,	280,  -1 },
	{            1053,	    STRING,	281,  -1 },
	{            1056,	    STRING,	282,  -1 },
	{            1059,	    STRING,	283,  -1 },
	{            1062,	    STRING,	284, 229 },
	{            1065,	    STRING,	285,  -1 },
	{            1068,	    STRING,	286,  -1 },
	{            1071,	    STRING,	287,  -1 },
	{            1074,	    STRING,	288,  -1 },
	{            1077,	    STRING,	289,  -1 },
	{            1080,	    STRING,	290,  -1 },
	{            1083,	    STRING,	291,  -1 },
	{            1086,	    STRING,	292,  -1 },
	{            1089,	    STRING,	293,  -1 },
	{            1092,	    STRING,	294,  -1 },
	{            1095,	    STRING,	295,  -1 },
	{            1098,	    STRING,	296,  -1 },
	{            1101,	    STRING,	297, 142 },
	{            1104,	    STRING,	298,  -1 },
	{            1107,	    STRING,	299,  -1 },
	{            1110,	    STRING,	300, 149 },
	{            1113,	    STRING,	301,  -1 },
	{            1116,	    STRING,	302,  -1 },
	{            1119,	    STRING,	303,  -1 },
	{            1122,	    STRING,	304,  -1 },
	{            1125,	    STRING,	305,  -1 },
	{            1128,	    STRING,	306,  -1 },
	{            1131,	    STRING,	307,  -1 },
	{            1134,	    STRING,	308,  -1 },
	{            1137,	    STRING,	309,  48 },
	{            1140,	    STRING,	310, 247 },
	{            1143,	    STRING,	311, 238 },
	{            1146,	    STRING,	312, 239 },
	{            1149,	    STRING,	313, 240 },
	{            1152,	    STRING,	314, 241 },
	{            1155,	    STRING,	315, 242 },
	{            1158,	    STRING,	316, 243 },
	{            1161,	    STRING,	317, 244 },
	{            1164,	    STRING,	318, 245 },
	{            1167,	    STRING,	319, 246 },
	{            1170,	    STRING,	320,  -1 },
	{            1173,	    STRING,	321, 172 },
	{            1176,	    STRING,	322,  -1 },
	{            1179,	    STRING,	323, 171 },
	{            1182,	    STRING,	324, 103 },
	{            1185,	    STRING,	325,  -1 },
	{            1188,	    STRING,	326, 104 },
	{            1191,	    STRING,	327,  14 },
	{            1194,	    STRING,	328,  -1 },
	{            1197,	    STRING,	329,  -1 },
	{            1200,	    STRING,	330,  -1 },
	{            1203,	    STRING,	331,  -1 },
	{            1206,	    STRING,	332,  -1 },
	{            1209,	    STRING,	333,  -1 },
	{            1212,	    STRING,	334,  -1 },
	{            1215,	    STRING,	335,  -1 },
	{            1218,	    STRING,	336,  -1 },
	{            1221,	    STRING,	337,  -1 },
	{            1224,	    STRING,	338,  -1 },
	{            1227,	    STRING,	339,  -1 },
	{            1230,	    STRING,	340,  -1 },
	{            1233,	    STRING,	341,  -1 },
	{            1236,	    STRING,	342,  -1 },
	{            1239,	    STRING,	343,  -1 },
	{            1242,	    STRING,	344, 208 },
	{            1245,	    STRING,	345,  -1 },
	{            1248,	    STRING,	346,  -1 },
	{            1251,	    STRING,	347,  -1 },
	{            1254,	    STRING,	348,  -1 },
	{            1257,	    STRING,	349,  -1 },
	{            1260,	    STRING,	350,  -1 },
	{            1263,	    STRING,	351,  -1 },
	{            1266,	    STRING,	352,  -1 },
	{            1269,	    STRING,	353, 272 },
	{            1272,	    STRING,	354, 273 },
	{            1275,	    STRING,	355, 387 },
	{            1278,	    STRING,	356,  -1 },
	{            1281,	    STRING,	357,  -1 },
	{            1284,	    STRING,	358,  -1 },
	{            1287,	    STRING,	359,  -1 },
	{            1290,	    STRING,	360,  -1 },
	{            1293,	    STRING,	361,  -1 },
	{            1296,	    STRING,	362,  -1 },
	{            1299,	    STRING,	363,  -1 },
	{            1302,	    STRING,	364,  -1 },
	{            1305,	    STRING,	365,  67 },
	{            1308,	    STRING,	366,  -1 },
	{            1311,	    STRING,	367,  -1 },
	{            1314,	    STRING,	368, 341 },
	{            1317,	    STRING,	369,  -1 },
	{            1320,	    STRING,	370,  -1 },
	{            1323,	    STRING,	371, 274 },
	{            1326,	    STRING,	372,  -1 },
	{            1329,	    STRING,	373,  -1 },
	{            1332,	    STRING,	374,  -1 },
	{            1335,	    STRING,	375,  -1 },
	{            1338,	    STRING,	376,  -1 },
	{            1341,	    STRING,	377,  -1 },
	{            1344,	    STRING,	378,  -1 },
	{            1347,	    STRING,	379,  -1 },
	{            1350,	    STRING,	380,  -1 },
	{            1353,	    STRING,	381, 357 },
	{            1356,	    STRING,	382, 358 },
	{            1359,	    STRING,	383, 359 },
	{            1362,	    STRING,	384, 360 },
	{            1365,	    STRING,	385, 361 },
	{            1368,	    STRING,	386,  -1 },
	{            1371,	    STRING,	387,  -1 },
	{            1374,	    STRING,	388,  -1 },
	{            1377,	    STRING,	389,  -1 },
	{            1380,	    STRING,	390,  -1 },
	{            1383,	    STRING,	391,  -1 },
	{            1386,	    STRING,	392,  -1 },
	{            1389,	    STRING,	393,  -1 },
	{            1392,	    STRING,	394, 390 },
	{            1395,	    STRING,	395,  -1 },
	{            1398,	    NUMBER,	 33,  -1 },
	{            1401,	   BOOLEAN,	 37,  -1 },
	{            1404,	   BOOLEAN,	 38,  -1 },
	{            1407,	   BOOLEAN,	 39, 248 },
	{            1410,	    NUMBER,	 34,  -1 },
	{            1413,	    NUMBER,	 35, 203 },
	{            1416,	    STRING,	396,  -1 },
	{            1419,	    STRING,	397,  -1 },
	{            1422,	   BOOLEAN,	 40, 439 },
	{            1425,	   BOOLEAN,	 41,  -1 },
	{            1428,	    NUMBER,	 36,  -1 },
	{            1431,	    NUMBER,	 37,  -1 },
	{            1434,	    NUMBER,	 38,  -1 },
	{            1437,	    STRING,	398,  -1 },
	{            1440,	    STRING,	399, 379 },
	{            1443,	   BOOLEAN,	 42,  -1 },
	{            1446,	   BOOLEAN,	 43,  -1 },
	{            1449,	    STRING,	400, 386 },
	{            1452,	    STRING,	401, 425 },
	{            1455,	    STRING,	402, 385 },
	{            1458,	    STRING,	403, 388 },
	{            1461,	    STRING,	404, 412 },
	{            1464,	    STRING,	405, 406 },
	{            1467,	    STRING,	406, 415 },
	{            1470,	    STRING,	407,  -1 },
	{            1473,	    STRING,	408, 402 },
	{            1476,	    STRING,	409, 416 },
	{            1479,	    STRING,	410,  -1 },
	{            1482,	    STRING,	411, 464 },
	{            1485,	    STRING,	412, 399 },
	{            1488,	    STRING,	413,  -1 } 
};

static struct name_table_entry *_nc_cap_table = 0;

static const HashValue _nc_cap_hash_table[995] =
{
	253,
	 -1,
	 45,
	211,
	263,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	449,
	457,
	311,
	411,
	 -1,
	132,
	 -1,
	 -1,
	 -1,
	 -1,
	123,
	 71,
	 75,
	 92,
	427,
	233,
	 -1,
	336,
	 -1,
	 -1,
	370,
	291,
	494,
	472,
	138,
	186,
	 -1,
	 -1,
	 -1,
	 -1,
	 19,
	193,
	436,
	431,
	453,
	 -1,
	315,
	489,
	349,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	353,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	124,
	 -1,
	 -1,
	 -1,
	394,
	 -1,
	367,
	167,
	 -1,
	191,
	371,
	 -1,
	 89,
	 -1,
	 -1,
	 -1,
	363,
	460,
	319,
	419,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 70,
	 74,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 38,
	 -1,
	128,
	 -1,
	398,
	 -1,
	 -1,
	481,
	 -1,
	 -1,
	202,
	 -1,
	 28,
	 43,
	 -1,
	 17,
	 -1,
	 -1,
	444,
	423,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	496,
	 -1,
	 -1,
	 -1,
	 -1,
	430,
	 -1,
	 -1,
	 -1,
	 -1,
	296,
	 -1,
	 21,
	 -1,
	187,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	321,
	276,
	 -1,
	 -1,
	 31,
	375,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	429,
	476,
	 -1,
	 -1,
	 -1,
	300,
	400,
	 -1,
	218,
	 -1,
	 -1,
	227,
	 -1,
	 -1,
	 -1,
	 -1,
	 11,
	285,
	179,
	 -1,
	325,
	280,
	 -1,
	224,
	162,
	480,
	 -1,
	 -1,
	 51,
	 -1,
	 -1,
	201,
	204,
	 -1,
	 -1,
	 -1,
	 -1,
	 22,
	 -1,
	304,
	404,
	 -1,
	154,
	 -1,
	 -1,
	 -1,
	 -1,
	108,
	 -1,
	 76,
	 -1,
	 -1,
	 -1,
	 -1,
	329,
	284,
	 -1,
	270,
	 84,
	383,
	250,
	426,
	 -1,
	 -1,
	260,
	113,
	110,
	114,
	 86,
	 -1,
	 -1,
	 -1,
	 -1,
	308,
	408,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	433,
	 -1,
	112,
	230,
	 -1,
	333,
	428,
	 -1,
	223,
	288,
	484,
	254,
	 -1,
	 -1,
	210,
	264,
	 -1,
	 98,
	 -1,
	 83,
	471,
	 -1,
	450,
	 -1,
	312,
	487,
	 -1,
	151,
	 -1,
	 -1,
	 -1,
	342,
	 24,
	 -1,
	 80,
	 99,
	 -1,
	234,
	 -1,
	337,
	101,
	 -1,
	  8,
	292,
	391,
	 -1,
	139,
	164,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	194,
	437,
	 -1,
	454,
	 -1,
	316,
	492,
	 -1,
	155,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	395,
	 -1,
	143,
	168,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	364,
	 -1,
	320,
	420,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	207,
	 -1,
	 -1,
	157,
	447,
	495,
	 -1,
	137,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	440,
	445,
	424,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 79,
	175,
	 -1,
	297,
	493,
	 23,
	178,
	 -1,
	 -1,
	 -1,
	340,
	 52,
	 -1,
	 -1,
	 -1,
	346,
	344,
	 -1,
	322,
	277,
	 -1,
	 -1,
	 32,
	376,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	373,
	 -1,
	470,
	 -1,
	 -1,
	 -1,
	301,
	401,
	 -1,
	127,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	339,
	 12,
	 -1,
	 -1,
	 -1,
	326,
	281,
	348,
	125,
	 36,
	380,
	343,
	 -1,
	 42,
	 -1,
	267,
	 -1,
	 -1,
	372,
	115,
	 -1,
	  2,
	345,
	 -1,
	305,
	405,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	237,
	 -1,
	330,
	121,
	 -1,
	271,
	 -1,
	384,
	251,
	 -1,
	189,
	 -1,
	261,
	199,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	177,
	 -1,
	309,
	409,
	 -1,
	 -1,
	 -1,
	 -1,
	226,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	231,
	352,
	334,
	 -1,
	 -1,
	 -1,
	289,
	486,
	255,
	135,
	160,
	212,
	265,
	 -1,
	 -1,
	 -1,
	 -1,
	434,
	 -1,
	451,
	 -1,
	313,
	413,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	214,
	 -1,
	 -1,
	 -1,
	 -1,
	235,
	  6,
	338,
	 10,
	 -1,
	478,
	293,
	392,
	 -1,
	140,
	217,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	347,
	455,
	459,
	317,
	417,
	 -1,
	134,
	 -1,
	 -1,
	 -1,
	 49,
	 -1,
	 -1,
	 72,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	153,
	 -1,
	396,
	 -1,
	144,
	169,
	 -1,
	 -1,
	200,
	 -1,
	 -1,
	 -1,
	 -1,
	482,
	365,
	461,
	442,
	421,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	197,
	432,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	446,
	441,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 18,
	 -1,
	 -1,
	 -1,
	298,
	490,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 26,
	 -1,
	 -1,
	351,
	 -1,
	 -1,
	 -1,
	323,
	278,
	 -1,
	369,
	 33,
	377,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	302,
	491,
	 -1,
	129,
	 -1,
	 -1,
	 -1,
	 -1,
	216,
	473,
	 27,
	 91,
	107,
	 -1,
	 -1,
	327,
	282,
	 -1,
	268,
	 -1,
	381,
	469,
	368,
	174,
	 -1,
	258,
	198,
	 -1,
	206,
	180,
	 -1,
	 -1,
	176,
	 -1,
	306,
	488,
	 -1,
	150,
	 -1,
	 -1,
	 -1,
	438,
	475,
	 -1,
	 -1,
	 -1,
	 -1,
	228,
	 -1,
	331,
	 -1,
	 -1,
	 -1,
	286,
	485,
	252,
	 -1,
	 -1,
	209,
	262,
	 41,
	 -1,
	466,
	 -1,
	 -1,
	 -1,
	448,
	 -1,
	310,
	410,
	 -1,
	130,
	 -1,
	 -1,
	 -1,
	 -1,
	 25,
	 -1,
	 -1,
	 -1,
	 50,
	232,
	 -1,
	335,
	 -1,
	 -1,
	 -1,
	290,
	389,
	256,
	136,
	185,
	213,
	266,
	 -1,
	 -1,
	 -1,
	192,
	435,
	 -1,
	452,
	458,
	314,
	414,
	 -1,
	152,
	 -1,
	 -1,
	 -1,
	474,
	 -1,
	 -1,
	215,
	 81,
	  5,
	236,
	 -1,
	 82,
	 -1,
	 -1,
	479,
	294,
	393,
	 -1,
	141,
	190,
	 -1,
	 -1,
	105,
	 -1,
	 -1,
	 -1,
	477,
	 20,
	362,
	 -1,
	318,
	418,
	 -1,
	156,
	 -1,
	 -1,
	 -1,
	 -1,
	 95,
	467,
	 73,
	 93,
	220,
	219,
	 -1,
	  9,
	119,
	 -1,
	159,
	 -1,
	397,
	468,
	145,
	188,
	 -1,
	465,
	 -1,
	205,
	106,
	 90,
	 44,
	  3,
	366,
	 -1,
	443,
	422,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	  0,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	295,
	 -1,
	173,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	355,
	 -1,
	222,
	221,
	 -1,
	 -1,
	275,
	356,
	 -1,
	 30,
	374,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	225,
	 -1,
	 -1,
	299,
	 -1,
	 -1,
	148,
	 -1,
	 -1,
	181,
	 -1,
	 -1,
	 -1,
	 -1,
	462,
	 -1,
	 -1,
	 -1,
	324,
	279,
	 -1,
	 -1,
	 34,
	378,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	350,
	 -1,
	303,
	403,
	 -1,
	133,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 77,
	 -1,
	182,
	 -1,
	 -1,
	328,
	283,
	 -1,
	269,
	463,
	382,
	249,
	 -1,
	 -1,
	 -1,
	259,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 85,
	 -1,
	456,
	307,
	407,
	 -1,
	147,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 78,
	 -1,
	 -1,
	354,
	 -1,
	332,
	 -1,
	 -1,
	146,
	287,
	483,
	0	/* base-of-table */
};

#if (BOOLCOUNT!=44)||(NUMCOUNT!=39)||(STRCOUNT!=414)
#error	--> term.h and comp_captab.c disagree about the <--
#error	--> numbers of booleans, numbers and/or strings <--
#endif

/* generated by MKcaptab.awk capalias(1) */

static struct alias *_nc_capalias_table = 0;

static const char capalias_text[] = "\
sb\0sr\0BSD\0\
BO\0mr\0AT&T\0\
CI\0vi\0AT&T\0\
CV\0ve\0AT&T\0\
DS\0mh\0AT&T\0\
FE\0LF\0AT&T\0\
FL\0LO\0AT&T\0\
XS\0mk\0AT&T\0\
EE\0mh\0XENIX\0\
GE\0ae\0XENIX\0\
GS\0as\0XENIX\0\
CF\0vi\0XENIX\0\
CO\0ve\0XENIX\0\
EN\0@7\0XENIX\0\
HM\0kh\0XENIX\0\
LD\0kL\0XENIX\0\
PD\0kN\0XENIX\0\
PN\0po\0XENIX\0\
PS\0pf\0XENIX\0\
PU\0kP\0XENIX\0\
RT\0@8\0XENIX\0\
UP\0ku\0XENIX\0\
G6\0XENIX\0\
G7\0XENIX\0\
G5\0XENIX\0\
G8\0XENIX\0\
Gr\0XENIX\0\
Gr\0XENIX\0\
Gu\0XENIX\0\
Gd\0XENIX\0\
Gh\0XENIX\0\
Gv\0XENIX\0\
Gc\0XENIX\0\
GG\0XENIX\0\
kq\0%1\0IBM\0\
HS\0mh\0IRIS\0\
KA\0k;\0Tek\0\
KB\0F1\0Tek\0\
KC\0F2\0Tek\0\
KD\0F3\0Tek\0\
KE\0F4\0Tek\0\
KF\0F5\0Tek\0\
BC\0Sb\0Tek\0\
FC\0Sf\0Tek\0\
";

static const alias_table_data capalias_data[] = {
	{    0,     3,     6},	 /* scroll */
	{   10,    13,    16},	 /* enter_reverse_mode */
	{   21,    24,    27},	 /* cursor_invisible */
	{   32,    35,    38},	 /* cursor_normal */
	{   43,    46,    49},	 /* enter_dim_mode */
	{   54,    57,    60},	 /* label_on */
	{   65,    68,    71},	 /* label_off */
	{   76,    79,    82},	 /* enter_secure_mode */
	{   87,    90,    93},	 /* exit_attribute_mode */
	{   99,   102,   105},	 /* exit_alt_charset_mode */
	{  111,   114,   117},	 /* enter_alt_charset_mode */
	{  123,   126,   129},	 /* cursor_invis */
	{  135,   138,   141},	 /* cursor_normal */
	{  147,   150,   153},	 /* key_end */
	{  159,   162,   165},	 /* key_home */
	{  171,   174,   177},	 /* key_dl */
	{  183,   186,   189},	 /* key_npage */
	{  195,   198,   201},	 /* prtr_off */
	{  207,   210,   213},	 /* prtr_on */
	{  219,   222,   225},	 /* key_ppage */
	{  231,   234,   237},	 /* kent */
	{  243,   246,   249},	 /* kcuu1 */
	{  255,    -1,   258},	 /* double-ACS_ULCORNER */
	{  264,    -1,   267},	 /* double-ACS_LLCORNER */
	{  273,    -1,   276},	 /* double-ACS_URCORNER */
	{  282,    -1,   285},	 /* double-ACS_LRCORNER */
	{  291,    -1,   294},	 /* double-ACS_LTEE */
	{  300,    -1,   303},	 /* double-ACS_RTEE */
	{  309,    -1,   312},	 /* double-ACS_BTEE */
	{  318,    -1,   321},	 /* double */
	{  327,    -1,   330},	 /* double-ACS_HLINE */
	{  336,    -1,   339},	 /* double-ACS_VLINE */
	{  345,    -1,   348},	 /* double-ACS_PLUS */
	{  354,    -1,   357},	 /* acs-glitch */
	{  363,   366,   369},	 /* key_help */
	{  373,   376,   379},	 /* enter_dim_mode */
	{  384,   387,   390},	 /* key_f10 */
	{  394,   397,   400},	 /* key_f11 */
	{  404,   407,   410},	 /* key_f12 */
	{  414,   417,   420},	 /* key_f13 */
	{  424,   427,   430},	 /* key_f14 */
	{  434,   437,   440},	 /* key_f15 */
	{  444,   447,   450},	 /* set_background */
	{  454,   457,   460},	 /* set_foreground */
};

/* generated by MKcaptab.awk infoalias(1) */

static struct alias *_nc_infoalias_table = 0;

static const char infoalias_text[] = "\
font0\0s0ds\0IBM\0\
font1\0s1ds\0IBM\0\
font2\0s2ds\0IBM\0\
font3\0s3ds\0IBM\0\
kbtab\0kcbt\0IBM\0\
ksel\0kslt\0IBM\0\
";

static const alias_table_data infoalias_data[] = {
	{    0,     6,    11},	 /* set0_des_seq */
	{   15,    21,    26},	 /* set1_des_seq */
	{   30,    36,    41},	 /* set2_des_seq */
	{   45,    51,    56},	 /* set3_des_seq */
	{   60,    66,    71},	 /* key_backtab */
	{   75,    80,    85},	 /* key_select */
};

/* *INDENT-ON* */

#if 1
static void
next_string(const char *strings, unsigned *offset)
{
    *offset += (unsigned) strlen(strings + *offset) + 1;
}

static const struct name_table_entry *
_nc_build_names(struct name_table_entry **actual,
		const name_table_data * source,
		const char *strings)
{
    if (*actual == 0) {
	*actual = typeCalloc(struct name_table_entry, CAPTABSIZE);
	if (*actual != 0) {
	    unsigned n;
	    unsigned len = 0;
	    for (n = 0; n < CAPTABSIZE; ++n) {
		(*actual)[n].nte_name = strings + len;
		(*actual)[n].nte_type = source[n].nte_type;
		(*actual)[n].nte_index = source[n].nte_index;
		(*actual)[n].nte_link = source[n].nte_link;
		next_string(strings, &len);
	    }
	}
    }
    return *actual;
}

#define add_alias(field) \
	if (source[n].field >= 0) { \
		(*actual)[n].field = strings + source[n].field; \
	}

static const struct alias *
_nc_build_alias(struct alias **actual,
		const alias_table_data * source,
		const char *strings,
		size_t tablesize)
{
    if (*actual == 0) {
	*actual = typeCalloc(struct alias, tablesize + 1);
	if (*actual != 0) {
	    size_t n;
	    for (n = 0; n < tablesize; ++n) {
		add_alias(from);
		add_alias(to);
		add_alias(source);
	    }
	}
    }
    return *actual;
}

#define build_names(root) _nc_build_names(&_nc_##root##_table, \
					  root##_names_data, \
					  root##_names_text)
#define build_alias(root) _nc_build_alias(&_nc_##root##alias_table, \
					  root##alias_data, \
					  root##alias_text, \
					  SIZEOF(root##alias_data))
#else
#define build_names(root) _nc_ ## root ## _table
#define build_alias(root) _nc_ ## root ## alias_table
#endif

NCURSES_EXPORT(const struct name_table_entry *)
_nc_get_table(bool termcap)
{
    return termcap ? build_names(cap) : build_names(info);
}

/* entrypoint used by tack 1.07 */
NCURSES_EXPORT(const HashValue *)
_nc_get_hash_table(bool termcap)
{
    return termcap ? _nc_cap_hash_table : _nc_info_hash_table;
}

NCURSES_EXPORT(const struct alias *)
_nc_get_alias_table(bool termcap)
{
    return termcap ? build_alias(cap) : build_alias(info);
}

static HashValue
info_hash(const char *string)
{
    long sum = 0;

    DEBUG(9, ("hashing %s", string));
    while (*string) {
	sum += (long) (UChar(*string) + (UChar(*(string + 1)) << 8));
	string++;
    }

    DEBUG(9, ("sum is %ld", sum));
    return (HashValue) (sum % HASHTABSIZE);
}

#define TCAP_LEN 2		/* only 1- or 2-character names are used */

static HashValue
tcap_hash(const char *string)
{
    char temp[TCAP_LEN + 1];
    int limit = 0;

    while (*string) {
	temp[limit++] = *string++;
	if (limit >= TCAP_LEN)
	    break;
    }
    temp[limit] = '\0';
    return info_hash(temp);
}

static int
compare_tcap_names(const char *a, const char *b)
{
    return !strncmp(a, b, (size_t) TCAP_LEN);
}

static int
compare_info_names(const char *a, const char *b)
{
    return !strcmp(a, b);
}

static const HashData hash_data[2] =
{
    {HASHTABSIZE, _nc_info_hash_table, info_hash, compare_info_names},
    {HASHTABSIZE, _nc_cap_hash_table, tcap_hash, compare_tcap_names}
};

NCURSES_EXPORT(const HashData *)
_nc_get_hash_info(bool termcap)
{
    return &hash_data[(termcap != FALSE)];
}

#if NO_LEAKS
NCURSES_EXPORT(void)
_nc_comp_captab_leaks(void)
{
#if 1
    FreeIfNeeded(_nc_cap_table);
    FreeIfNeeded(_nc_info_table);
    FreeIfNeeded(_nc_capalias_table);
    FreeIfNeeded(_nc_infoalias_table);
#endif
}
#endif /* NO_LEAKS */

EOF
""",
)

genrule(
    name = "ncurses/names",
    outs = ["ncurses/names.c"],
    cmd = r"""
cat << 'EOF' > $@
/* This file was generated by MKnames.awk */

#include <curses.priv.h>

#define IT NCURSES_CONST char * const


#if BROKEN_LINKER || USE_REENTRANT

static const char _nc_name_blob[] = 
"bw\0" "auto_left_margin\0" "am\0" "auto_right_margin\0" "xsb\0" "no_esc_ctlc\0" \
"xhp\0" "ceol_standout_glitch\0" "xenl\0" "eat_newline_glitch\0" "eo\0" \
"erase_overstrike\0" "gn\0" "generic_type\0" "hc\0" "hard_copy\0" "km\0" \
"has_meta_key\0" "hs\0" "has_status_line\0" "in\0" "insert_null_glitch\0" \
"da\0" "memory_above\0" "db\0" "memory_below\0" "mir\0" "move_insert_mode\0" \
"msgr\0" "move_standout_mode\0" "os\0" "over_strike\0" "eslok\0" "status_line_esc_ok\0" \
"xt\0" "dest_tabs_magic_smso\0" "hz\0" "tilde_glitch\0" "ul\0" "transparent_underline\0" \
"xon\0" "xon_xoff\0" "nxon\0" "needs_xon_xoff\0" "mc5i\0" "prtr_silent\0" \
"chts\0" "hard_cursor\0" "nrrmc\0" "non_rev_rmcup\0" "npc\0" "no_pad_char\0" \
"ndscr\0" "non_dest_scroll_region\0" "ccc\0" "can_change\0" "bce\0" "back_color_erase\0" \
"hls\0" "hue_lightness_saturation\0" "xhpa\0" "col_addr_glitch\0" "crxm\0" \
"cr_cancels_micro_mode\0" "daisy\0" "has_print_wheel\0" "xvpa\0" "row_addr_glitch\0" \
"sam\0" "semi_auto_right_margin\0" "cpix\0" "cpi_changes_res\0" "lpix\0" \
"lpi_changes_res\0" "cols\0" "columns\0" "it\0" "init_tabs\0" "lines\0" \
"lines\0" "lm\0" "lines_of_memory\0" "xmc\0" "magic_cookie_glitch\0" "pb\0" \
"padding_baud_rate\0" "vt\0" "virtual_terminal\0" "wsl\0" "width_status_line\0" \
"nlab\0" "num_labels\0" "lh\0" "label_height\0" "lw\0" "label_width\0" \
"ma\0" "max_attributes\0" "wnum\0" "maximum_windows\0" "colors\0" "max_colors\0" \
"pairs\0" "max_pairs\0" "ncv\0" "no_color_video\0" "bufsz\0" "buffer_capacity\0" \
"spinv\0" "dot_vert_spacing\0" "spinh\0" "dot_horz_spacing\0" "maddr\0" \
"max_micro_address\0" "mjump\0" "max_micro_jump\0" "mcs\0" "micro_col_size\0" \
"mls\0" "micro_line_size\0" "npins\0" "number_of_pins\0" "orc\0" "output_res_char\0" \
"orl\0" "output_res_line\0" "orhi\0" "output_res_horz_inch\0" "orvi\0" \
"output_res_vert_inch\0" "cps\0" "print_rate\0" "widcs\0" "wide_char_size\0" \
"btns\0" "buttons\0" "bitwin\0" "bit_image_entwining\0" "bitype\0" "bit_image_type\0" \
"cbt\0" "back_tab\0" "bel\0" "bell\0" "cr\0" "carriage_return\0" "csr\0" \
"change_scroll_region\0" "tbc\0" "clear_all_tabs\0" "clear\0" "clear_screen\0" \
"el\0" "clr_eol\0" "ed\0" "clr_eos\0" "hpa\0" "column_address\0" "cmdch\0" \
"command_character\0" "cup\0" "cursor_address\0" "cud1\0" "cursor_down\0" \
"home\0" "cursor_home\0" "civis\0" "cursor_invisible\0" "cub1\0" "cursor_left\0" \
"mrcup\0" "cursor_mem_address\0" "cnorm\0" "cursor_normal\0" "cuf1\0" "cursor_right\0" \
"ll\0" "cursor_to_ll\0" "cuu1\0" "cursor_up\0" "cvvis\0" "cursor_visible\0" \
"dch1\0" "delete_character\0" "dl1\0" "delete_line\0" "dsl\0" "dis_status_line\0" \
"hd\0" "down_half_line\0" "smacs\0" "enter_alt_charset_mode\0" "blink\0" \
"enter_blink_mode\0" "bold\0" "enter_bold_mode\0" "smcup\0" "enter_ca_mode\0" \
"smdc\0" "enter_delete_mode\0" "dim\0" "enter_dim_mode\0" "smir\0" "enter_insert_mode\0" \
"invis\0" "enter_secure_mode\0" "prot\0" "enter_protected_mode\0" "rev\0" \
"enter_reverse_mode\0" "smso\0" "enter_standout_mode\0" "smul\0" "enter_underline_mode\0" \
"ech\0" "erase_chars\0" "rmacs\0" "exit_alt_charset_mode\0" "sgr0\0" "exit_attribute_mode\0" \
"rmcup\0" "exit_ca_mode\0" "rmdc\0" "exit_delete_mode\0" "rmir\0" "exit_insert_mode\0" \
"rmso\0" "exit_standout_mode\0" "rmul\0" "exit_underline_mode\0" "flash\0" \
"flash_screen\0" "ff\0" "form_feed\0" "fsl\0" "from_status_line\0" "is1\0" \
"init_1string\0" "is2\0" "init_2string\0" "is3\0" "init_3string\0" "if\0" \
"init_file\0" "ich1\0" "insert_character\0" "il1\0" "insert_line\0" "ip\0" \
"insert_padding\0" "kbs\0" "key_backspace\0" "ktbc\0" "key_catab\0" "kclr\0" \
"key_clear\0" "kctab\0" "key_ctab\0" "kdch1\0" "key_dc\0" "kdl1\0" "key_dl\0" \
"kcud1\0" "key_down\0" "krmir\0" "key_eic\0" "kel\0" "key_eol\0" "ked\0" \
"key_eos\0" "kf0\0" "key_f0\0" "kf1\0" "key_f1\0" "kf10\0" "key_f10\0" \
"kf2\0" "key_f2\0" "kf3\0" "key_f3\0" "kf4\0" "key_f4\0" "kf5\0" "key_f5\0" \
"kf6\0" "key_f6\0" "kf7\0" "key_f7\0" "kf8\0" "key_f8\0" "kf9\0" "key_f9\0" \
"khome\0" "key_home\0" "kich1\0" "key_ic\0" "kil1\0" "key_il\0" "kcub1\0" \
"key_left\0" "kll\0" "key_ll\0" "knp\0" "key_npage\0" "kpp\0" "key_ppage\0" \
"kcuf1\0" "key_right\0" "kind\0" "key_sf\0" "kri\0" "key_sr\0" "khts\0" \
"key_stab\0" "kcuu1\0" "key_up\0" "rmkx\0" "keypad_local\0" "smkx\0" "keypad_xmit\0" \
"lf0\0" "lab_f0\0" "lf1\0" "lab_f1\0" "lf10\0" "lab_f10\0" "lf2\0" "lab_f2\0" \
"lf3\0" "lab_f3\0" "lf4\0" "lab_f4\0" "lf5\0" "lab_f5\0" "lf6\0" "lab_f6\0" \
"lf7\0" "lab_f7\0" "lf8\0" "lab_f8\0" "lf9\0" "lab_f9\0" "rmm\0" "meta_off\0" \
"smm\0" "meta_on\0" "nel\0" "newline\0" "pad\0" "pad_char\0" "dch\0" "parm_dch\0" \
"dl\0" "parm_delete_line\0" "cud\0" "parm_down_cursor\0" "ich\0" "parm_ich\0" \
"indn\0" "parm_index\0" "il\0" "parm_insert_line\0" "cub\0" "parm_left_cursor\0" \
"cuf\0" "parm_right_cursor\0" "rin\0" "parm_rindex\0" "cuu\0" "parm_up_cursor\0" \
"pfkey\0" "pkey_key\0" "pfloc\0" "pkey_local\0" "pfx\0" "pkey_xmit\0" "mc0\0" \
"print_screen\0" "mc4\0" "prtr_off\0" "mc5\0" "prtr_on\0" "rep\0" "repeat_char\0" \
"rs1\0" "reset_1string\0" "rs2\0" "reset_2string\0" "rs3\0" "reset_3string\0" \
"rf\0" "reset_file\0" "rc\0" "restore_cursor\0" "vpa\0" "row_address\0" \
"sc\0" "save_cursor\0" "ind\0" "scroll_forward\0" "ri\0" "scroll_reverse\0" \
"sgr\0" "set_attributes\0" "hts\0" "set_tab\0" "wind\0" "set_window\0" \
"ht\0" "tab\0" "tsl\0" "to_status_line\0" "uc\0" "underline_char\0" "hu\0" \
"up_half_line\0" "iprog\0" "init_prog\0" "ka1\0" "key_a1\0" "ka3\0" "key_a3\0" \
"kb2\0" "key_b2\0" "kc1\0" "key_c1\0" "kc3\0" "key_c3\0" "mc5p\0" "prtr_non\0" \
"rmp\0" "char_padding\0" "acsc\0" "acs_chars\0" "pln\0" "plab_norm\0" "kcbt\0" \
"key_btab\0" "smxon\0" "enter_xon_mode\0" "rmxon\0" "exit_xon_mode\0" "smam\0" \
"enter_am_mode\0" "rmam\0" "exit_am_mode\0" "xonc\0" "xon_character\0" \
"xoffc\0" "xoff_character\0" "enacs\0" "ena_acs\0" "smln\0" "label_on\0" \
"rmln\0" "label_off\0" "kbeg\0" "key_beg\0" "kcan\0" "key_cancel\0" "kclo\0" \
"key_close\0" "kcmd\0" "key_command\0" "kcpy\0" "key_copy\0" "kcrt\0" "key_create\0" \
"kend\0" "key_end\0" "kent\0" "key_enter\0" "kext\0" "key_exit\0" "kfnd\0" \
"key_find\0" "khlp\0" "key_help\0" "kmrk\0" "key_mark\0" "kmsg\0" "key_message\0" \
"kmov\0" "key_move\0" "knxt\0" "key_next\0" "kopn\0" "key_open\0" "kopt\0" \
"key_options\0" "kprv\0" "key_previous\0" "kprt\0" "key_print\0" "krdo\0" \
"key_redo\0" "kref\0" "key_reference\0" "krfr\0" "key_refresh\0" "krpl\0" \
"key_replace\0" "krst\0" "key_restart\0" "kres\0" "key_resume\0" "ksav\0" \
"key_save\0" "kspd\0" "key_suspend\0" "kund\0" "key_undo\0" "kBEG\0" "key_sbeg\0" \
"kCAN\0" "key_scancel\0" "kCMD\0" "key_scommand\0" "kCPY\0" "key_scopy\0" \
"kCRT\0" "key_screate\0" "kDC\0" "key_sdc\0" "kDL\0" "key_sdl\0" "kslt\0" \
"key_select\0" "kEND\0" "key_send\0" "kEOL\0" "key_seol\0" "kEXT\0" "key_sexit\0" \
"kFND\0" "key_sfind\0" "kHLP\0" "key_shelp\0" "kHOM\0" "key_shome\0" "kIC\0" \
"key_sic\0" "kLFT\0" "key_sleft\0" "kMSG\0" "key_smessage\0" "kMOV\0" "key_smove\0" \
"kNXT\0" "key_snext\0" "kOPT\0" "key_soptions\0" "kPRV\0" "key_sprevious\0" \
"kPRT\0" "key_sprint\0" "kRDO\0" "key_sredo\0" "kRPL\0" "key_sreplace\0" \
"kRIT\0" "key_sright\0" "kRES\0" "key_srsume\0" "kSAV\0" "key_ssave\0" \
"kSPD\0" "key_ssuspend\0" "kUND\0" "key_sundo\0" "rfi\0" "req_for_input\0" \
"kf11\0" "key_f11\0" "kf12\0" "key_f12\0" "kf13\0" "key_f13\0" "kf14\0" \
"key_f14\0" "kf15\0" "key_f15\0" "kf16\0" "key_f16\0" "kf17\0" "key_f17\0" \
"kf18\0" "key_f18\0" "kf19\0" "key_f19\0" "kf20\0" "key_f20\0" "kf21\0" \
"key_f21\0" "kf22\0" "key_f22\0" "kf23\0" "key_f23\0" "kf24\0" "key_f24\0" \
"kf25\0" "key_f25\0" "kf26\0" "key_f26\0" "kf27\0" "key_f27\0" "kf28\0" \
"key_f28\0" "kf29\0" "key_f29\0" "kf30\0" "key_f30\0" "kf31\0" "key_f31\0" \
"kf32\0" "key_f32\0" "kf33\0" "key_f33\0" "kf34\0" "key_f34\0" "kf35\0" \
"key_f35\0" "kf36\0" "key_f36\0" "kf37\0" "key_f37\0" "kf38\0" "key_f38\0" \
"kf39\0" "key_f39\0" "kf40\0" "key_f40\0" "kf41\0" "key_f41\0" "kf42\0" \
"key_f42\0" "kf43\0" "key_f43\0" "kf44\0" "key_f44\0" "kf45\0" "key_f45\0" \
"kf46\0" "key_f46\0" "kf47\0" "key_f47\0" "kf48\0" "key_f48\0" "kf49\0" \
"key_f49\0" "kf50\0" "key_f50\0" "kf51\0" "key_f51\0" "kf52\0" "key_f52\0" \
"kf53\0" "key_f53\0" "kf54\0" "key_f54\0" "kf55\0" "key_f55\0" "kf56\0" \
"key_f56\0" "kf57\0" "key_f57\0" "kf58\0" "key_f58\0" "kf59\0" "key_f59\0" \
"kf60\0" "key_f60\0" "kf61\0" "key_f61\0" "kf62\0" "key_f62\0" "kf63\0" \
"key_f63\0" "el1\0" "clr_bol\0" "mgc\0" "clear_margins\0" "smgl\0" "set_left_margin\0" \
"smgr\0" "set_right_margin\0" "fln\0" "label_format\0" "sclk\0" "set_clock\0" \
"dclk\0" "display_clock\0" "rmclk\0" "remove_clock\0" "cwin\0" "create_window\0" \
"wingo\0" "goto_window\0" "hup\0" "hangup\0" "dial\0" "dial_phone\0" "qdial\0" \
"quick_dial\0" "tone\0" "tone\0" "pulse\0" "pulse\0" "hook\0" "flash_hook\0" \
"pause\0" "fixed_pause\0" "wait\0" "wait_tone\0" "u0\0" "user0\0" "u1\0" \
"user1\0" "u2\0" "user2\0" "u3\0" "user3\0" "u4\0" "user4\0" "u5\0" "user5\0" \
"u6\0" "user6\0" "u7\0" "user7\0" "u8\0" "user8\0" "u9\0" "user9\0" "op\0" \
"orig_pair\0" "oc\0" "orig_colors\0" "initc\0" "initialize_color\0" "initp\0" \
"initialize_pair\0" "scp\0" "set_color_pair\0" "setf\0" "set_foreground\0" \
"setb\0" "set_background\0" "cpi\0" "change_char_pitch\0" "lpi\0" "change_line_pitch\0" \
"chr\0" "change_res_horz\0" "cvr\0" "change_res_vert\0" "defc\0" "define_char\0" \
"swidm\0" "enter_doublewide_mode\0" "sdrfq\0" "enter_draft_quality\0" "sitm\0" \
"enter_italics_mode\0" "slm\0" "enter_leftward_mode\0" "smicm\0" "enter_micro_mode\0" \
"snlq\0" "enter_near_letter_quality\0" "snrmq\0" "enter_normal_quality\0" \
"sshm\0" "enter_shadow_mode\0" "ssubm\0" "enter_subscript_mode\0" "ssupm\0" \
"enter_superscript_mode\0" "sum\0" "enter_upward_mode\0" "rwidm\0" "exit_doublewide_mode\0" \
"ritm\0" "exit_italics_mode\0" "rlm\0" "exit_leftward_mode\0" "rmicm\0" \
"exit_micro_mode\0" "rshm\0" "exit_shadow_mode\0" "rsubm\0" "exit_subscript_mode\0" \
"rsupm\0" "exit_superscript_mode\0" "rum\0" "exit_upward_mode\0" "mhpa\0" \
"micro_column_address\0" "mcud1\0" "micro_down\0" "mcub1\0" "micro_left\0" \
"mcuf1\0" "micro_right\0" "mvpa\0" "micro_row_address\0" "mcuu1\0" "micro_up\0" \
"porder\0" "order_of_pins\0" "mcud\0" "parm_down_micro\0" "mcub\0" "parm_left_micro\0" \
"mcuf\0" "parm_right_micro\0" "mcuu\0" "parm_up_micro\0" "scs\0" "select_char_set\0" \
"smgb\0" "set_bottom_margin\0" "smgbp\0" "set_bottom_margin_parm\0" "smglp\0" \
"set_left_margin_parm\0" "smgrp\0" "set_right_margin_parm\0" "smgt\0" "set_top_margin\0" \
"smgtp\0" "set_top_margin_parm\0" "sbim\0" "start_bit_image\0" "scsd\0" \
"start_char_set_def\0" "rbim\0" "stop_bit_image\0" "rcsd\0" "stop_char_set_def\0" \
"subcs\0" "subscript_characters\0" "supcs\0" "superscript_characters\0" \
"docr\0" "these_cause_cr\0" "zerom\0" "zero_motion\0" "csnm\0" "char_set_names\0" \
"kmous\0" "key_mouse\0" "minfo\0" "mouse_info\0" "reqmp\0" "req_mouse_pos\0" \
"getm\0" "get_mouse\0" "setaf\0" "set_a_foreground\0" "setab\0" "set_a_background\0" \
"pfxl\0" "pkey_plab\0" "devt\0" "device_type\0" "csin\0" "code_set_init\0" \
"s0ds\0" "set0_des_seq\0" "s1ds\0" "set1_des_seq\0" "s2ds\0" "set2_des_seq\0" \
"s3ds\0" "set3_des_seq\0" "smglr\0" "set_lr_margin\0" "smgtb\0" "set_tb_margin\0" \
"birep\0" "bit_image_repeat\0" "binel\0" "bit_image_newline\0" "bicr\0" \
"bit_image_carriage_return\0" "colornm\0" "color_names\0" "defbi\0" "define_bit_image_region\0" \
"endbi\0" "end_bit_image_region\0" "setcolor\0" "set_color_band\0" "slines\0" \
"set_page_length\0" "dispc\0" "display_pc_char\0" "smpch\0" "enter_pc_charset_mode\0" \
"rmpch\0" "exit_pc_charset_mode\0" "smsc\0" "enter_scancode_mode\0" "rmsc\0" \
"exit_scancode_mode\0" "pctrm\0" "pc_term_options\0" "scesc\0" "scancode_escape\0" \
"scesa\0" "alt_scancode_esc\0" "ehhlm\0" "enter_horizontal_hl_mode\0" "elhlm\0" \
"enter_left_hl_mode\0" "elohlm\0" "enter_low_hl_mode\0" "erhlm\0" "enter_right_hl_mode\0" \
"ethlm\0" "enter_top_hl_mode\0" "evhlm\0" "enter_vertical_hl_mode\0" "sgr1\0" \
"set_a_attributes\0" "slength\0" "set_pglen_inch\0" "OTi2\0" "termcap_init2\0" \
"OTrs\0" "termcap_reset\0" "OTug\0" "magic_cookie_glitch_ul\0" "OTbs\0" \
"backspaces_with_bs\0" "OTns\0" "crt_no_scrolling\0" "OTnc\0" "no_correctly_working_cr\0" \
"OTdC\0" "carriage_return_delay\0" "OTdN\0" "new_line_delay\0" "OTnl\0" \
"linefeed_if_not_lf\0" "OTbc\0" "backspace_if_not_bs\0" "OTMT\0" "gnu_has_meta_key\0" \
"OTNL\0" "linefeed_is_newline\0" "OTdB\0" "backspace_delay\0" "OTdT\0" \
"horizontal_tab_delay\0" "OTkn\0" "number_of_function_keys\0" "OTko\0" \
"other_non_function_keys\0" "OTma\0" "arrow_key_map\0" "OTpt\0" "has_hardware_tabs\0" \
"OTxr\0" "return_does_clr_eol\0" "OTG2\0" "acs_ulcorner\0" "OTG3\0" "acs_llcorner\0" \
"OTG1\0" "acs_urcorner\0" "OTG4\0" "acs_lrcorner\0" "OTGR\0" "acs_ltee\0" \
"OTGL\0" "acs_rtee\0" "OTGU\0" "acs_btee\0" "OTGD\0" "acs_ttee\0" "OTGH\0" \
"acs_hline\0" "OTGV\0" "acs_vline\0" "OTGC\0" "acs_plus\0" "meml\0" "memory_lock\0" \
"memu\0" "memory_unlock\0" "box1\0" "box_chars_1\0" ;
static const short _nc_offset_boolfnames[] = {
3, 23, 45, 61, 87, 109, 129,
145, 158, 174, 193, 215, 231,
248, 270, 292, 310, 332, 356,
372, 398, 412, 432, 449, 467,
485, 503, 530, 545, 566, 596,
617, 645, 666, 686, 714, 735,
8193, 8217, 8239, 8364, 8386, 8535, 8558, };

static NCURSES_CONST char ** ptr_boolfnames = 0;

static const short _nc_offset_boolnames[] = {
0, 20, 41, 57, 82, 106, 126, 142, 155, 171, 190, 212, 228, 244, 265, 289, 304, 329, 353, 369, 394, 407, 427, 444, 461, 481, 497, 526, 541, 562, 591, 612, 639, 661, 682, 709, 730, 8188, 8212, 8234, 8359, 8381, 8530, 8553, };

static NCURSES_CONST char ** ptr_boolnames = 0;

static const short _nc_offset_numfnames[] = {
756, 767, 783, 792, 812, 835,
856, 877, 900, 914, 930, 945,
965, 988, 1005, 1019, 1040, 1062, 1085, 1108, 1132, 1151, 1170,
1192, 1211, 1231, 1252, 1278, 1303, 1320, 1340, 1355, 1382, 8165,
8268, 8295, 8411, 8432,
8458, };

static NCURSES_CONST char ** ptr_numfnames = 0;

static const short _nc_offset_numnames[] = {
751, 764, 777, 789, 808, 832, 853, 873, 895, 911, 927, 942, 960, 981, 999, 1015, 1034, 1056,
1079, 1102, 1126, 1147, 1166, 1186, 1207, 1227, 1247, 1273, 1299,
1314, 1335, 1348, 1375, 8160, 8263, 8290, 8406, 8427, 8453, };

static NCURSES_CONST char ** ptr_numnames = 0;

static const short _nc_offset_strfnames[] = {
1401,
1414, 1422, 1442, 1467, 1488, 1504, 1515, 1527, 1548, 1570, 1590,
1607, 1625, 1647, 1665, 1690, 1709, 1725, 1743, 1759, 1779, 1800,
1816, 1835, 1856, 1885, 1907, 1929, 1948, 1970, 1990, 2014, 2037,
2062, 2086, 2111, 2136, 2154, 2181, 2207, 2225, 2247, 2269, 2293,
2319, 2335, 2349, 2370, 2387, 2404, 2420, 2435, 2456, 2471, 2490,
2509, 2524, 2540, 2555, 2567, 2580, 2595, 2607, 2619, 2631, 2642,
2654, 2666, 2677, 2688, 2699, 2710, 2721, 2732, 2743, 2756, 2771,
2783, 2796, 2809, 2820, 2834, 2850, 2865, 2876, 2888, 2903, 2915,
2933, 2949, 2960, 2972, 2984, 2995, 3006, 3017, 3028, 3039, 3050,
3061, 3072, 3085, 3097, 3109, 3122, 3134, 3155, 3176, 3190, 3204,
3225, 3246, 3268, 3284, 3305, 3320, 3335, 3349, 3366, 3379, 3391,
3407, 3425, 3443, 3460, 3474, 3493, 3508, 3524, 3542, 3561, 3580,
3593, 3607, 3615, 3633, 3651, 3670, 3684, 3695, 3706, 3717, 3728,
3740, 3753, 3771, 3785, 3800, 3815, 3836, 3855, 3874, 3892, 3912,
3933, 3946, 3960, 3975, 3988, 4004, 4019, 4036, 4050, 4066, 4079,
4094, 4108, 4122, 4136, 4150, 4167, 4181, 4195, 4209, 4226, 4244,
4259, 4273, 4292, 4309, 4326, 4343, 4359, 4373, 4390, 4404, 4418,
4435, 4453, 4468, 4484, 4496, 4509, 4525, 4539, 4553, 4568, 4583,
4598, 4612, 4625, 4640, 4658, 4673, 4688, 4706, 4725, 4741, 4756,
4774, 4790, 4806, 4821, 4839, 4853, 4872, 4885, 4898, 4911, 4924,
4937, 4950, 4963, 4976, 4989, 5002, 5015, 5028, 5041, 5054, 5067,
5080, 5093, 5106, 5119, 5132, 5145, 5158, 5171, 5184, 5197, 5210,
5223, 5236, 5249, 5262, 5275, 5288, 5301, 5314, 5327, 5340, 5353,
5366, 5379, 5392, 5405, 5418, 5431, 5444, 5457, 5470, 5483, 5496,
5509, 5522, 5535, 5548, 5560, 5572, 5591, 5612, 5633, 5651, 5666,
5686, 5704, 5724, 5740, 5752, 5769, 5785, 5796, 5807, 5824, 5841,
5854, 5863, 5872, 5881, 5890, 5899, 5908, 5917, 5926, 5935, 5944,
5957, 5975, 5998, 6018, 6038, 6058, 6077, 6099, 6121, 6141, 6162,
6180, 6208, 6233, 6256, 6282, 6304, 6336, 6362, 6386, 6413, 6440,
6464, 6490, 6512, 6537, 6558, 6581, 6607, 6633, 6655, 6682, 6699,
6716, 6733, 6757, 6773, 6792, 6813, 6834, 6856, 6874, 6895, 6919,
6948, 6975, 7002, 7023, 7048, 7069, 7093, 7113, 7137, 7164, 7192,
7213, 7230, 7251, 7267, 7284, 7303, 7319, 7342, 7364, 7379, 7396,
7415, 7433, 7451, 7469, 7488, 7508, 7528, 7551, 7574, 7608, 7626,
7656, 7686, 7708, 7730, 7752, 7780, 7806, 7831, 7856, 7878, 7900,
7923, 7954, 7980, 8004, 8030, 8054, 8082, 8107, 8127, 8146, 8315, 8339, 8487, 8516, 8583, 8601, 8619, 8637, 8655, 8669,
8683, 8697, 8711, 8726, 8741, 8755, 8772, 8791, };

static NCURSES_CONST char ** ptr_strfnames = 0;

static const short _nc_offset_strnames[] = {
1397, 1410, 1419, 1438, 1463, 1482, 1501,
1512, 1523, 1542, 1566, 1585, 1602, 1619, 1642, 1659, 1684, 1704,
1722, 1738, 1753, 1774, 1796, 1812, 1832, 1850, 1879, 1902, 1923,
1943, 1966, 1985, 2008, 2032, 2058, 2081, 2106, 2132, 2148, 2176,
2201, 2220, 2242, 2264, 2288, 2313, 2332, 2345, 2366, 2383, 2400,
2417, 2430, 2452, 2468, 2486, 2504, 2519, 2534, 2549, 2562, 2574,
2589, 2603, 2615, 2627, 2638, 2649, 2662, 2673, 2684, 2695, 2706,
2717, 2728, 2739, 2750, 2765, 2778, 2790, 2805, 2816, 2830, 2844,
2860, 2872, 2883, 2897, 2910, 2928, 2945, 2956, 2967, 2980, 2991,
3002, 3013, 3024, 3035, 3046, 3057, 3068, 3081, 3093, 3105, 3118,
3131, 3151, 3172, 3185, 3201, 3221, 3242, 3264, 3280, 3299, 3314,
3331, 3345, 3362, 3375, 3387, 3403, 3421, 3439, 3457, 3471, 3489,
3505, 3520, 3539, 3557, 3576, 3588, 3604, 3611, 3630, 3648, 3664,
3680, 3691, 3702, 3713, 3724, 3735, 3749, 3766, 3781, 3795, 3809,
3830, 3850, 3869, 3887, 3906, 3927, 3941, 3955, 3970, 3983, 3999,
4014, 4031, 4045, 4061, 4074, 4089, 4103, 4117, 4131, 4145, 4162,
4176, 4190, 4204, 4221, 4239, 4254, 4268, 4287, 4304, 4321, 4338,
4354, 4368, 4385, 4399, 4413, 4430, 4448, 4463, 4480, 4492, 4504,
4520, 4534, 4548, 4563, 4578, 4593, 4608, 4620, 4635, 4653, 4668,
4683, 4701, 4720, 4736, 4751, 4769, 4785, 4801, 4816, 4834, 4849,
4867, 4880, 4893, 4906, 4919, 4932, 4945, 4958, 4971, 4984, 4997,
5010, 5023, 5036, 5049, 5062, 5075, 5088, 5101, 5114, 5127, 5140,
5153, 5166, 5179, 5192, 5205, 5218, 5231, 5244, 5257, 5270, 5283,
5296, 5309, 5322, 5335, 5348, 5361, 5374, 5387, 5400, 5413, 5426,
5439, 5452, 5465, 5478, 5491, 5504, 5517, 5530, 5543, 5556, 5568,
5586, 5607, 5629, 5646, 5661, 5680, 5699, 5718, 5736, 5747, 5763,
5780, 5790, 5802, 5818, 5836, 5851, 5860, 5869, 5878, 5887, 5896,
5905, 5914, 5923, 5932, 5941, 5954, 5969, 5992, 6014, 6033, 6053,
6073, 6095, 6117, 6137, 6157, 6174, 6202, 6228, 6252, 6276, 6299,
6330, 6357, 6380, 6407, 6436, 6458, 6485, 6508, 6531, 6553, 6575,
6601, 6629, 6650, 6676, 6693, 6710, 6728, 6751, 6766, 6787, 6808,
6829, 6851, 6870, 6890, 6913, 6942, 6969, 6997, 7017, 7043, 7064,
7088, 7108, 7131, 7158, 7187, 7207, 7225, 7245, 7261, 7278, 7298,
7313, 7336, 7359, 7374, 7391, 7410, 7428, 7446, 7464, 7482, 7502,
7522, 7545, 7569, 7600, 7620, 7650, 7677, 7701, 7724, 7746, 7774,
7801, 7826, 7850, 7872, 7894, 7917, 7948, 7973, 7998, 8024, 8048,
8077, 8099, 8122, 8141, 8310,
8334, 8482, 8511, 8578,
8596, 8614, 8632, 8650, 8664, 8678, 8692, 8706, 8721, 8736, 8750,
8767, 8786, };

static NCURSES_CONST char ** ptr_strnames = 0;


static IT *
alloc_array(NCURSES_CONST char ***value, const short *offsets, unsigned size)
{
	if (*value == 0) {
		if ((*value = typeCalloc(NCURSES_CONST char *, size + 1)) != 0) {
			unsigned n;
			for (n = 0; n < size; ++n) {
				(*value)[n] = (NCURSES_CONST char *) _nc_name_blob + offsets[n];
			}
		}
	}
	return *value;
}

#define FIX(it) NCURSES_IMPEXP IT * NCURSES_API NCURSES_PUBLIC_VAR(it)(void) { return alloc_array(&ptr_##it, _nc_offset_##it, SIZEOF(_nc_offset_##it)); }

/* remove public definition which conflicts with FIX() */
#undef boolnames
#undef boolfnames
#undef numnames
#undef numfnames
#undef strnames
#undef strfnames

/* add local definition */
FIX(boolnames)
FIX(boolfnames)
FIX(numnames)
FIX(numfnames)
FIX(strnames)
FIX(strfnames)

/* restore the public definition */
#define boolnames  NCURSES_PUBLIC_VAR(boolnames())
#define boolfnames NCURSES_PUBLIC_VAR(boolfnames())
#define numnames   NCURSES_PUBLIC_VAR(numnames())
#define numfnames  NCURSES_PUBLIC_VAR(numfnames())
#define strnames   NCURSES_PUBLIC_VAR(strnames())
#define strfnames  NCURSES_PUBLIC_VAR(strfnames())

#define FREE_FIX(it) if (ptr_##it) { FreeAndNull(ptr_##it); }

#if NO_LEAKS
NCURSES_EXPORT(void)
_nc_names_leaks(void)
{
FREE_FIX(boolnames)
FREE_FIX(boolfnames)
FREE_FIX(numnames)
FREE_FIX(numfnames)
FREE_FIX(strnames)
FREE_FIX(strfnames)
}
#endif

#else

#define DCL(it) NCURSES_EXPORT_VAR(IT) it[]

DCL(boolnames) = {
		"bw",
		"am",
		"xsb",
		"xhp",
		"xenl",
		"eo",
		"gn",
		"hc",
		"km",
		"hs",
		"in",
		"da",
		"db",
		"mir",
		"msgr",
		"os",
		"eslok",
		"xt",
		"hz",
		"ul",
		"xon",
		"nxon",
		"mc5i",
		"chts",
		"nrrmc",
		"npc",
		"ndscr",
		"ccc",
		"bce",
		"hls",
		"xhpa",
		"crxm",
		"daisy",
		"xvpa",
		"sam",
		"cpix",
		"lpix",
		"OTbs",
		"OTns",
		"OTnc",
		"OTMT",
		"OTNL",
		"OTpt",
		"OTxr",

		(NCURSES_CONST char *)0,
};

DCL(boolfnames) = {
		"auto_left_margin",
		"auto_right_margin",
		"no_esc_ctlc",
		"ceol_standout_glitch",
		"eat_newline_glitch",
		"erase_overstrike",
		"generic_type",
		"hard_copy",
		"has_meta_key",
		"has_status_line",
		"insert_null_glitch",
		"memory_above",
		"memory_below",
		"move_insert_mode",
		"move_standout_mode",
		"over_strike",
		"status_line_esc_ok",
		"dest_tabs_magic_smso",
		"tilde_glitch",
		"transparent_underline",
		"xon_xoff",
		"needs_xon_xoff",
		"prtr_silent",
		"hard_cursor",
		"non_rev_rmcup",
		"no_pad_char",
		"non_dest_scroll_region",
		"can_change",
		"back_color_erase",
		"hue_lightness_saturation",
		"col_addr_glitch",
		"cr_cancels_micro_mode",
		"has_print_wheel",
		"row_addr_glitch",
		"semi_auto_right_margin",
		"cpi_changes_res",
		"lpi_changes_res",
		"backspaces_with_bs",
		"crt_no_scrolling",
		"no_correctly_working_cr",
		"gnu_has_meta_key",
		"linefeed_is_newline",
		"has_hardware_tabs",
		"return_does_clr_eol",

		(NCURSES_CONST char *)0,
};

DCL(numnames) = {
		"cols",
		"it",
		"lines",
		"lm",
		"xmc",
		"pb",
		"vt",
		"wsl",
		"nlab",
		"lh",
		"lw",
		"ma",
		"wnum",
		"colors",
		"pairs",
		"ncv",
		"bufsz",
		"spinv",
		"spinh",
		"maddr",
		"mjump",
		"mcs",
		"mls",
		"npins",
		"orc",
		"orl",
		"orhi",
		"orvi",
		"cps",
		"widcs",
		"btns",
		"bitwin",
		"bitype",
		"OTug",
		"OTdC",
		"OTdN",
		"OTdB",
		"OTdT",
		"OTkn",

		(NCURSES_CONST char *)0,
};

DCL(numfnames) = {
		"columns",
		"init_tabs",
		"lines",
		"lines_of_memory",
		"magic_cookie_glitch",
		"padding_baud_rate",
		"virtual_terminal",
		"width_status_line",
		"num_labels",
		"label_height",
		"label_width",
		"max_attributes",
		"maximum_windows",
		"max_colors",
		"max_pairs",
		"no_color_video",
		"buffer_capacity",
		"dot_vert_spacing",
		"dot_horz_spacing",
		"max_micro_address",
		"max_micro_jump",
		"micro_col_size",
		"micro_line_size",
		"number_of_pins",
		"output_res_char",
		"output_res_line",
		"output_res_horz_inch",
		"output_res_vert_inch",
		"print_rate",
		"wide_char_size",
		"buttons",
		"bit_image_entwining",
		"bit_image_type",
		"magic_cookie_glitch_ul",
		"carriage_return_delay",
		"new_line_delay",
		"backspace_delay",
		"horizontal_tab_delay",
		"number_of_function_keys",

		(NCURSES_CONST char *)0,
};

DCL(strnames) = {
		"cbt",
		"bel",
		"cr",
		"csr",
		"tbc",
		"clear",
		"el",
		"ed",
		"hpa",
		"cmdch",
		"cup",
		"cud1",
		"home",
		"civis",
		"cub1",
		"mrcup",
		"cnorm",
		"cuf1",
		"ll",
		"cuu1",
		"cvvis",
		"dch1",
		"dl1",
		"dsl",
		"hd",
		"smacs",
		"blink",
		"bold",
		"smcup",
		"smdc",
		"dim",
		"smir",
		"invis",
		"prot",
		"rev",
		"smso",
		"smul",
		"ech",
		"rmacs",
		"sgr0",
		"rmcup",
		"rmdc",
		"rmir",
		"rmso",
		"rmul",
		"flash",
		"ff",
		"fsl",
		"is1",
		"is2",
		"is3",
		"if",
		"ich1",
		"il1",
		"ip",
		"kbs",
		"ktbc",
		"kclr",
		"kctab",
		"kdch1",
		"kdl1",
		"kcud1",
		"krmir",
		"kel",
		"ked",
		"kf0",
		"kf1",
		"kf10",
		"kf2",
		"kf3",
		"kf4",
		"kf5",
		"kf6",
		"kf7",
		"kf8",
		"kf9",
		"khome",
		"kich1",
		"kil1",
		"kcub1",
		"kll",
		"knp",
		"kpp",
		"kcuf1",
		"kind",
		"kri",
		"khts",
		"kcuu1",
		"rmkx",
		"smkx",
		"lf0",
		"lf1",
		"lf10",
		"lf2",
		"lf3",
		"lf4",
		"lf5",
		"lf6",
		"lf7",
		"lf8",
		"lf9",
		"rmm",
		"smm",
		"nel",
		"pad",
		"dch",
		"dl",
		"cud",
		"ich",
		"indn",
		"il",
		"cub",
		"cuf",
		"rin",
		"cuu",
		"pfkey",
		"pfloc",
		"pfx",
		"mc0",
		"mc4",
		"mc5",
		"rep",
		"rs1",
		"rs2",
		"rs3",
		"rf",
		"rc",
		"vpa",
		"sc",
		"ind",
		"ri",
		"sgr",
		"hts",
		"wind",
		"ht",
		"tsl",
		"uc",
		"hu",
		"iprog",
		"ka1",
		"ka3",
		"kb2",
		"kc1",
		"kc3",
		"mc5p",
		"rmp",
		"acsc",
		"pln",
		"kcbt",
		"smxon",
		"rmxon",
		"smam",
		"rmam",
		"xonc",
		"xoffc",
		"enacs",
		"smln",
		"rmln",
		"kbeg",
		"kcan",
		"kclo",
		"kcmd",
		"kcpy",
		"kcrt",
		"kend",
		"kent",
		"kext",
		"kfnd",
		"khlp",
		"kmrk",
		"kmsg",
		"kmov",
		"knxt",
		"kopn",
		"kopt",
		"kprv",
		"kprt",
		"krdo",
		"kref",
		"krfr",
		"krpl",
		"krst",
		"kres",
		"ksav",
		"kspd",
		"kund",
		"kBEG",
		"kCAN",
		"kCMD",
		"kCPY",
		"kCRT",
		"kDC",
		"kDL",
		"kslt",
		"kEND",
		"kEOL",
		"kEXT",
		"kFND",
		"kHLP",
		"kHOM",
		"kIC",
		"kLFT",
		"kMSG",
		"kMOV",
		"kNXT",
		"kOPT",
		"kPRV",
		"kPRT",
		"kRDO",
		"kRPL",
		"kRIT",
		"kRES",
		"kSAV",
		"kSPD",
		"kUND",
		"rfi",
		"kf11",
		"kf12",
		"kf13",
		"kf14",
		"kf15",
		"kf16",
		"kf17",
		"kf18",
		"kf19",
		"kf20",
		"kf21",
		"kf22",
		"kf23",
		"kf24",
		"kf25",
		"kf26",
		"kf27",
		"kf28",
		"kf29",
		"kf30",
		"kf31",
		"kf32",
		"kf33",
		"kf34",
		"kf35",
		"kf36",
		"kf37",
		"kf38",
		"kf39",
		"kf40",
		"kf41",
		"kf42",
		"kf43",
		"kf44",
		"kf45",
		"kf46",
		"kf47",
		"kf48",
		"kf49",
		"kf50",
		"kf51",
		"kf52",
		"kf53",
		"kf54",
		"kf55",
		"kf56",
		"kf57",
		"kf58",
		"kf59",
		"kf60",
		"kf61",
		"kf62",
		"kf63",
		"el1",
		"mgc",
		"smgl",
		"smgr",
		"fln",
		"sclk",
		"dclk",
		"rmclk",
		"cwin",
		"wingo",
		"hup",
		"dial",
		"qdial",
		"tone",
		"pulse",
		"hook",
		"pause",
		"wait",
		"u0",
		"u1",
		"u2",
		"u3",
		"u4",
		"u5",
		"u6",
		"u7",
		"u8",
		"u9",
		"op",
		"oc",
		"initc",
		"initp",
		"scp",
		"setf",
		"setb",
		"cpi",
		"lpi",
		"chr",
		"cvr",
		"defc",
		"swidm",
		"sdrfq",
		"sitm",
		"slm",
		"smicm",
		"snlq",
		"snrmq",
		"sshm",
		"ssubm",
		"ssupm",
		"sum",
		"rwidm",
		"ritm",
		"rlm",
		"rmicm",
		"rshm",
		"rsubm",
		"rsupm",
		"rum",
		"mhpa",
		"mcud1",
		"mcub1",
		"mcuf1",
		"mvpa",
		"mcuu1",
		"porder",
		"mcud",
		"mcub",
		"mcuf",
		"mcuu",
		"scs",
		"smgb",
		"smgbp",
		"smglp",
		"smgrp",
		"smgt",
		"smgtp",
		"sbim",
		"scsd",
		"rbim",
		"rcsd",
		"subcs",
		"supcs",
		"docr",
		"zerom",
		"csnm",
		"kmous",
		"minfo",
		"reqmp",
		"getm",
		"setaf",
		"setab",
		"pfxl",
		"devt",
		"csin",
		"s0ds",
		"s1ds",
		"s2ds",
		"s3ds",
		"smglr",
		"smgtb",
		"birep",
		"binel",
		"bicr",
		"colornm",
		"defbi",
		"endbi",
		"setcolor",
		"slines",
		"dispc",
		"smpch",
		"rmpch",
		"smsc",
		"rmsc",
		"pctrm",
		"scesc",
		"scesa",
		"ehhlm",
		"elhlm",
		"elohlm",
		"erhlm",
		"ethlm",
		"evhlm",
		"sgr1",
		"slength",
		"OTi2",
		"OTrs",
		"OTnl",
		"OTbc",
		"OTko",
		"OTma",
		"OTG2",
		"OTG3",
		"OTG1",
		"OTG4",
		"OTGR",
		"OTGL",
		"OTGU",
		"OTGD",
		"OTGH",
		"OTGV",
		"OTGC",
		"meml",
		"memu",
		"box1",

		(NCURSES_CONST char *)0,
};

DCL(strfnames) = {
		"back_tab",
		"bell",
		"carriage_return",
		"change_scroll_region",
		"clear_all_tabs",
		"clear_screen",
		"clr_eol",
		"clr_eos",
		"column_address",
		"command_character",
		"cursor_address",
		"cursor_down",
		"cursor_home",
		"cursor_invisible",
		"cursor_left",
		"cursor_mem_address",
		"cursor_normal",
		"cursor_right",
		"cursor_to_ll",
		"cursor_up",
		"cursor_visible",
		"delete_character",
		"delete_line",
		"dis_status_line",
		"down_half_line",
		"enter_alt_charset_mode",
		"enter_blink_mode",
		"enter_bold_mode",
		"enter_ca_mode",
		"enter_delete_mode",
		"enter_dim_mode",
		"enter_insert_mode",
		"enter_secure_mode",
		"enter_protected_mode",
		"enter_reverse_mode",
		"enter_standout_mode",
		"enter_underline_mode",
		"erase_chars",
		"exit_alt_charset_mode",
		"exit_attribute_mode",
		"exit_ca_mode",
		"exit_delete_mode",
		"exit_insert_mode",
		"exit_standout_mode",
		"exit_underline_mode",
		"flash_screen",
		"form_feed",
		"from_status_line",
		"init_1string",
		"init_2string",
		"init_3string",
		"init_file",
		"insert_character",
		"insert_line",
		"insert_padding",
		"key_backspace",
		"key_catab",
		"key_clear",
		"key_ctab",
		"key_dc",
		"key_dl",
		"key_down",
		"key_eic",
		"key_eol",
		"key_eos",
		"key_f0",
		"key_f1",
		"key_f10",
		"key_f2",
		"key_f3",
		"key_f4",
		"key_f5",
		"key_f6",
		"key_f7",
		"key_f8",
		"key_f9",
		"key_home",
		"key_ic",
		"key_il",
		"key_left",
		"key_ll",
		"key_npage",
		"key_ppage",
		"key_right",
		"key_sf",
		"key_sr",
		"key_stab",
		"key_up",
		"keypad_local",
		"keypad_xmit",
		"lab_f0",
		"lab_f1",
		"lab_f10",
		"lab_f2",
		"lab_f3",
		"lab_f4",
		"lab_f5",
		"lab_f6",
		"lab_f7",
		"lab_f8",
		"lab_f9",
		"meta_off",
		"meta_on",
		"newline",
		"pad_char",
		"parm_dch",
		"parm_delete_line",
		"parm_down_cursor",
		"parm_ich",
		"parm_index",
		"parm_insert_line",
		"parm_left_cursor",
		"parm_right_cursor",
		"parm_rindex",
		"parm_up_cursor",
		"pkey_key",
		"pkey_local",
		"pkey_xmit",
		"print_screen",
		"prtr_off",
		"prtr_on",
		"repeat_char",
		"reset_1string",
		"reset_2string",
		"reset_3string",
		"reset_file",
		"restore_cursor",
		"row_address",
		"save_cursor",
		"scroll_forward",
		"scroll_reverse",
		"set_attributes",
		"set_tab",
		"set_window",
		"tab",
		"to_status_line",
		"underline_char",
		"up_half_line",
		"init_prog",
		"key_a1",
		"key_a3",
		"key_b2",
		"key_c1",
		"key_c3",
		"prtr_non",
		"char_padding",
		"acs_chars",
		"plab_norm",
		"key_btab",
		"enter_xon_mode",
		"exit_xon_mode",
		"enter_am_mode",
		"exit_am_mode",
		"xon_character",
		"xoff_character",
		"ena_acs",
		"label_on",
		"label_off",
		"key_beg",
		"key_cancel",
		"key_close",
		"key_command",
		"key_copy",
		"key_create",
		"key_end",
		"key_enter",
		"key_exit",
		"key_find",
		"key_help",
		"key_mark",
		"key_message",
		"key_move",
		"key_next",
		"key_open",
		"key_options",
		"key_previous",
		"key_print",
		"key_redo",
		"key_reference",
		"key_refresh",
		"key_replace",
		"key_restart",
		"key_resume",
		"key_save",
		"key_suspend",
		"key_undo",
		"key_sbeg",
		"key_scancel",
		"key_scommand",
		"key_scopy",
		"key_screate",
		"key_sdc",
		"key_sdl",
		"key_select",
		"key_send",
		"key_seol",
		"key_sexit",
		"key_sfind",
		"key_shelp",
		"key_shome",
		"key_sic",
		"key_sleft",
		"key_smessage",
		"key_smove",
		"key_snext",
		"key_soptions",
		"key_sprevious",
		"key_sprint",
		"key_sredo",
		"key_sreplace",
		"key_sright",
		"key_srsume",
		"key_ssave",
		"key_ssuspend",
		"key_sundo",
		"req_for_input",
		"key_f11",
		"key_f12",
		"key_f13",
		"key_f14",
		"key_f15",
		"key_f16",
		"key_f17",
		"key_f18",
		"key_f19",
		"key_f20",
		"key_f21",
		"key_f22",
		"key_f23",
		"key_f24",
		"key_f25",
		"key_f26",
		"key_f27",
		"key_f28",
		"key_f29",
		"key_f30",
		"key_f31",
		"key_f32",
		"key_f33",
		"key_f34",
		"key_f35",
		"key_f36",
		"key_f37",
		"key_f38",
		"key_f39",
		"key_f40",
		"key_f41",
		"key_f42",
		"key_f43",
		"key_f44",
		"key_f45",
		"key_f46",
		"key_f47",
		"key_f48",
		"key_f49",
		"key_f50",
		"key_f51",
		"key_f52",
		"key_f53",
		"key_f54",
		"key_f55",
		"key_f56",
		"key_f57",
		"key_f58",
		"key_f59",
		"key_f60",
		"key_f61",
		"key_f62",
		"key_f63",
		"clr_bol",
		"clear_margins",
		"set_left_margin",
		"set_right_margin",
		"label_format",
		"set_clock",
		"display_clock",
		"remove_clock",
		"create_window",
		"goto_window",
		"hangup",
		"dial_phone",
		"quick_dial",
		"tone",
		"pulse",
		"flash_hook",
		"fixed_pause",
		"wait_tone",
		"user0",
		"user1",
		"user2",
		"user3",
		"user4",
		"user5",
		"user6",
		"user7",
		"user8",
		"user9",
		"orig_pair",
		"orig_colors",
		"initialize_color",
		"initialize_pair",
		"set_color_pair",
		"set_foreground",
		"set_background",
		"change_char_pitch",
		"change_line_pitch",
		"change_res_horz",
		"change_res_vert",
		"define_char",
		"enter_doublewide_mode",
		"enter_draft_quality",
		"enter_italics_mode",
		"enter_leftward_mode",
		"enter_micro_mode",
		"enter_near_letter_quality",
		"enter_normal_quality",
		"enter_shadow_mode",
		"enter_subscript_mode",
		"enter_superscript_mode",
		"enter_upward_mode",
		"exit_doublewide_mode",
		"exit_italics_mode",
		"exit_leftward_mode",
		"exit_micro_mode",
		"exit_shadow_mode",
		"exit_subscript_mode",
		"exit_superscript_mode",
		"exit_upward_mode",
		"micro_column_address",
		"micro_down",
		"micro_left",
		"micro_right",
		"micro_row_address",
		"micro_up",
		"order_of_pins",
		"parm_down_micro",
		"parm_left_micro",
		"parm_right_micro",
		"parm_up_micro",
		"select_char_set",
		"set_bottom_margin",
		"set_bottom_margin_parm",
		"set_left_margin_parm",
		"set_right_margin_parm",
		"set_top_margin",
		"set_top_margin_parm",
		"start_bit_image",
		"start_char_set_def",
		"stop_bit_image",
		"stop_char_set_def",
		"subscript_characters",
		"superscript_characters",
		"these_cause_cr",
		"zero_motion",
		"char_set_names",
		"key_mouse",
		"mouse_info",
		"req_mouse_pos",
		"get_mouse",
		"set_a_foreground",
		"set_a_background",
		"pkey_plab",
		"device_type",
		"code_set_init",
		"set0_des_seq",
		"set1_des_seq",
		"set2_des_seq",
		"set3_des_seq",
		"set_lr_margin",
		"set_tb_margin",
		"bit_image_repeat",
		"bit_image_newline",
		"bit_image_carriage_return",
		"color_names",
		"define_bit_image_region",
		"end_bit_image_region",
		"set_color_band",
		"set_page_length",
		"display_pc_char",
		"enter_pc_charset_mode",
		"exit_pc_charset_mode",
		"enter_scancode_mode",
		"exit_scancode_mode",
		"pc_term_options",
		"scancode_escape",
		"alt_scancode_esc",
		"enter_horizontal_hl_mode",
		"enter_left_hl_mode",
		"enter_low_hl_mode",
		"enter_right_hl_mode",
		"enter_top_hl_mode",
		"enter_vertical_hl_mode",
		"set_a_attributes",
		"set_pglen_inch",
		"termcap_init2",
		"termcap_reset",
		"linefeed_if_not_lf",
		"backspace_if_not_bs",
		"other_non_function_keys",
		"arrow_key_map",
		"acs_ulcorner",
		"acs_llcorner",
		"acs_urcorner",
		"acs_lrcorner",
		"acs_ltee",
		"acs_rtee",
		"acs_btee",
		"acs_ttee",
		"acs_hline",
		"acs_vline",
		"acs_plus",
		"memory_lock",
		"memory_unlock",
		"box_chars_1",

		(NCURSES_CONST char *)0,
};


#endif /* BROKEN_LINKER */

EOF
""",
)

genrule(
    name = "ncurses/comp_userdefs",
    outs = ["ncurses/comp_userdefs.c"],
    cmd = r"""
cat << 'EOF' > $@
/*
 * generated by thirdparty/ncurses/ncurses-6.2/ncurses/tinfo/MKuserdefs.sh
 */

/*
 *    comp_userdefs.c -- The names of widely used user-defined capabilities
 *                       indexed via a hash table for the compiler.
 *
 */

#include <curses.priv.h>
#include <tic.h>
#include <hashsize.h>

#if NCURSES_XNAMES
/* 10 collisions out of 90 entries */
static const char user_names_text[] = \
"E3\0" "RGB\0" "TS\0" "U8\0" "XM\0" "grbom\0" "gsbom\0" "xm\0" "AN\0" \
"AX\0" "C0\0" "C8\0" "CE\0" "CS\0" "E0\0" "G0\0" "KJ\0" "OL\0" "S0\0" \
"TF\0" "WS\0" "XC\0" "XT\0" "Z0\0" "Z1\0" "Cr\0" "Cs\0" "Csr\0" "Ms\0" \
"Se\0" "Smulx\0" "Ss\0" "rmxx\0" "smxx\0" "kDC3\0" "kDC4\0" "kDC5\0" \
"kDC6\0" "kDC7\0" "kDN\0" "kDN3\0" "kDN4\0" "kDN5\0" "kDN6\0" "kDN7\0" \
"kEND3\0" "kEND4\0" "kEND5\0" "kEND6\0" "kEND7\0" "kHOM3\0" "kHOM4\0" \
"kHOM5\0" "kHOM6\0" "kHOM7\0" "kIC3\0" "kIC4\0" "kIC5\0" "kIC6\0" \
"kIC7\0" "kLFT3\0" "kLFT4\0" "kLFT5\0" "kLFT6\0" "kLFT7\0" "kNXT3\0" \
"kNXT4\0" "kNXT5\0" "kNXT6\0" "kNXT7\0" "kPRV3\0" "kPRV4\0" "kPRV5\0" \
"kPRV6\0" "kPRV7\0" "kRIT3\0" "kRIT4\0" "kRIT5\0" "kRIT6\0" "kRIT7\0" \
"kUP\0" "kUP3\0" "kUP4\0" "kUP5\0" "kUP6\0" "kUP7\0" "ka2\0" "kb1\0" \
"kb3\0" "kc2\0" ;

static user_table_data const user_names_data[] =
{
	{               0,	(1<<STRING),	0,0,	  0,  -1 },
	{               3,	(1<<BOOLEAN|1<<NUMBER|1<<STRING),	0,0,	  1,  -1 },
	{               7,	(1<<STRING),	0,0,	  2,  -1 },
	{              10,	(1<<NUMBER),	0,0,	  1,  -1 },
	{              13,	(1<<STRING),	1,0,	  3,  -1 },
	{              16,	(1<<STRING),	0,0,	  4,  -1 },
	{              22,	(1<<STRING),	0,0,	  5,  -1 },
	{              28,	(1<<STRING),	8,8,	 14,  -1 },
	{              31,	(1<<BOOLEAN),	0,0,	  1,  -1 },
	{              34,	(1<<BOOLEAN),	0,0,	  2,  -1 },
	{              37,	(1<<STRING),	0,0,	 15,  -1 },
	{              40,	(1<<BOOLEAN),	0,0,	  3,  -1 },
	{              43,	(1<<STRING),	0,0,	 16,  -1 },
	{              46,	(1<<STRING),	0,0,	 17,  -1 },
	{              49,	(1<<STRING),	0,0,	 18,  -1 },
	{              52,	(1<<BOOLEAN),	0,0,	  4,  -1 },
	{              55,	(1<<STRING),	1,1,	 19,  -1 },
	{              58,	(1<<NUMBER),	0,0,	  2,  -1 },
	{              61,	(1<<STRING),	1,1,	 20,  -1 },
	{              64,	(1<<BOOLEAN),	0,0,	  5,  -1 },
	{              67,	(1<<STRING),	2,0,	 21,  -1 },
	{              70,	(1<<STRING),	1,1,	 22,  -1 },
	{              73,	(1<<BOOLEAN),	0,0,	  6,  -1 },
	{              76,	(1<<STRING),	0,0,	 23,  -1 },
	{              79,	(1<<STRING),	0,0,	 24,  -1 },
	{              82,	(1<<STRING),	0,0,	 25,  -1 },
	{              85,	(1<<STRING),	1,1,	 26,  -1 },
	{              88,	(1<<STRING),	1,0,	 27,  -1 },
	{              92,	(1<<STRING),	2,3,	 28,  -1 },
	{              95,	(1<<STRING),	0,0,	 29,  -1 },
	{              98,	(1<<STRING),	1,0,	 30,  -1 },
	{             104,	(1<<STRING),	1,0,	 31,  -1 },
	{             107,	(1<<STRING),	0,0,	 32,  -1 },
	{             112,	(1<<STRING),	0,0,	 33,  -1 },
	{             117,	(1<<STRING),	0,0,	 34,  -1 },
	{             122,	(1<<STRING),	0,0,	 35,  -1 },
	{             127,	(1<<STRING),	0,0,	 36,  -1 },
	{             132,	(1<<STRING),	0,0,	 37,  -1 },
	{             137,	(1<<STRING),	0,0,	 38,   8 },
	{             142,	(1<<STRING),	0,0,	 39,  -1 },
	{             146,	(1<<STRING),	0,0,	 40,  -1 },
	{             151,	(1<<STRING),	0,0,	 41,  -1 },
	{             156,	(1<<STRING),	0,0,	 42,  -1 },
	{             161,	(1<<STRING),	0,0,	 43,   9 },
	{             166,	(1<<STRING),	0,0,	 44,  -1 },
	{             171,	(1<<STRING),	0,0,	 45,  -1 },
	{             177,	(1<<STRING),	0,0,	 46,  -1 },
	{             183,	(1<<STRING),	0,0,	 47,  -1 },
	{             189,	(1<<STRING),	0,0,	 48,  -1 },
	{             195,	(1<<STRING),	0,0,	 49,  -1 },
	{             201,	(1<<STRING),	0,0,	 50,  -1 },
	{             207,	(1<<STRING),	0,0,	 51,  -1 },
	{             213,	(1<<STRING),	0,0,	 52,  -1 },
	{             219,	(1<<STRING),	0,0,	 53,  -1 },
	{             225,	(1<<STRING),	0,0,	 54,  -1 },
	{             231,	(1<<STRING),	0,0,	 55,  -1 },
	{             236,	(1<<STRING),	0,0,	 56,  -1 },
	{             241,	(1<<STRING),	0,0,	 57,  -1 },
	{             246,	(1<<STRING),	0,0,	 58,  -1 },
	{             251,	(1<<STRING),	0,0,	 59,  -1 },
	{             256,	(1<<STRING),	0,0,	 60,  52 },
	{             262,	(1<<STRING),	0,0,	 61,  53 },
	{             268,	(1<<STRING),	0,0,	 62,  54 },
	{             274,	(1<<STRING),	0,0,	 63,  -1 },
	{             280,	(1<<STRING),	0,0,	 64,  -1 },
	{             286,	(1<<STRING),	0,0,	 65,  -1 },
	{             292,	(1<<STRING),	0,0,	 66,  -1 },
	{             298,	(1<<STRING),	0,0,	 67,  -1 },
	{             304,	(1<<STRING),	0,0,	 68,  -1 },
	{             310,	(1<<STRING),	0,0,	 69,  -1 },
	{             316,	(1<<STRING),	0,0,	 70,  -1 },
	{             322,	(1<<STRING),	0,0,	 71,  -1 },
	{             328,	(1<<STRING),	0,0,	 72,  65 },
	{             334,	(1<<STRING),	0,0,	 73,  66 },
	{             340,	(1<<STRING),	0,0,	 74,  67 },
	{             346,	(1<<STRING),	0,0,	 75,  -1 },
	{             352,	(1<<STRING),	0,0,	 76,  -1 },
	{             358,	(1<<STRING),	0,0,	 77,  -1 },
	{             364,	(1<<STRING),	0,0,	 78,  -1 },
	{             370,	(1<<STRING),	0,0,	 79,  -1 },
	{             376,	(1<<STRING),	0,0,	 80,  -1 },
	{             380,	(1<<STRING),	0,0,	 81,  -1 },
	{             385,	(1<<STRING),	0,0,	 82,  -1 },
	{             390,	(1<<STRING),	0,0,	 83,  -1 },
	{             395,	(1<<STRING),	0,0,	 84,  -1 },
	{             400,	(1<<STRING),	0,0,	 85,  -1 },
	{             405,	(1<<STRING),	0,0,	 86,  -1 },
	{             409,	(1<<STRING),	0,0,	 87,  86 },
	{             413,	(1<<STRING),	0,0,	 88,  -1 },
	{             417,	(1<<STRING),	0,0,	 89,  88 }
};

static struct user_table_entry *_nc_user_table = 0;

static const HashValue _nc_user_hash_table[995] =
{
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 57,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 61,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 40,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	  6,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 44,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 75,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 87,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 79,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 46,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 19,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 73,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 29,
	 34,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 16,
	 -1,
	 -1,
	 -1,
	 -1,
	 82,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 38,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 50,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	  0,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 58,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 27,
	 -1,
	 62,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 41,
	 -1,
	  7,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 76,
	 -1,
	 -1,
	 32,
	 33,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 47,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 21,
	 -1,
	 -1,
	 70,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 74,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 35,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 30,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 83,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 10,
	 -1,
	 14,
	 -1,
	 15,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 55,
	 -1,
	 -1,
	 18,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 23,
	 51,
	 -1,
	  1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 59,
	 -1,
	 13,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 63,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 25,
	 -1,
	  2,
	 -1,
	 11,
	 20,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 42,
	 -1,
	 -1,
	 -1,
	 -1,
	  3,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 77,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 89,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 48,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 71,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 68,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 36,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 17,
	 84,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 56,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 24,
	 60,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 80,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 64,
	 -1,
	 -1,
	  5,
	 -1,
	 -1,
	 26,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 22,
	 -1,
	 -1,
	 -1,
	 28,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 31,
	 43,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 39,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 78,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 45,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 12,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 49,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 72,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 81,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 69,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 37,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 85,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	 -1,
	  4,
	 -1,
	 -1,
	0	/* base-of-table */
};


#define USERTABSIZE SIZEOF(user_names_data)

#if 1
static void
next_string(const char *strings, unsigned *offset)
{
    *offset += (unsigned) strlen(strings + *offset) + 1;
}

static const struct user_table_entry *
_nc_build_names(struct user_table_entry **actual,
		const user_table_data *source,
		const char *strings)
{
    if (*actual == 0) {
	*actual = typeCalloc(struct user_table_entry, USERTABSIZE);
	if (*actual != 0) {
	    unsigned n;
	    unsigned len = 0;
	    for (n = 0; n < USERTABSIZE; ++n) {
		(*actual)[n].ute_name = strings + len;
		(*actual)[n].ute_type = (int) source[n].ute_type;
		(*actual)[n].ute_argc = source[n].ute_argc;
		(*actual)[n].ute_args = source[n].ute_args;
		(*actual)[n].ute_index = source[n].ute_index;
		(*actual)[n].ute_link = source[n].ute_link;
		next_string(strings, &len);
	    }
	}
    }
    return *actual;
}

#define build_names(root) _nc_build_names(&_nc_##root##_table, \
					  root##_names_data, \
					  root##_names_text)
#else
#define build_names(root) _nc_ ## root ## _table
#endif

NCURSES_EXPORT(const struct user_table_entry *) _nc_get_userdefs_table (void)
{
    return build_names(user) ;
}

static HashValue
info_hash(const char *string)
{
    long sum = 0;

    DEBUG(9, ("hashing %s", string));
    while (*string) {
	sum += (long) (*string + (*(string + 1) << 8));
	string++;
    }

    DEBUG(9, ("sum is %ld", sum));
    return (HashValue) (sum % HASHTABSIZE);
}

static int
compare_info_names(const char *a, const char *b)
{
    return !strcmp(a, b);
}

static const HashData hash_data[] = {
    { HASHTABSIZE, _nc_user_hash_table, info_hash, compare_info_names }
};

NCURSES_EXPORT(const HashData *) _nc_get_hash_user (void)
{
    return hash_data;
}

#if NO_LEAKS
NCURSES_EXPORT(void) _nc_comp_userdefs_leaks(void)
{
#if 1
    FreeIfNeeded(_nc_user_table);
#endif
}
#endif /* NO_LEAKS */

#else /*! NCURSES_XNAMES */
NCURSES_EXPORT(void) _nc_comp_userdefs(void);
NCURSES_EXPORT(void) _nc_comp_userdefs(void) { }
#endif /* NCURSES_XNAMES */

EOF
""",
)
