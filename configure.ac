# get rid of that stupid cache mechanism
rm -f config.cache

AC_INIT(phoneuid, 0.1, http://shr-project.org/)
AC_PREREQ(2.52)
AC_CONFIG_SRCDIR(configure.ac)
AC_ISC_POSIX

AM_INIT_AUTOMAKE(1.6 dist-bzip2)
AM_CONFIG_HEADER(config.h)
AC_PROG_CC
AC_HEADER_STDC

PKG_CHECK_MODULES(GLIB,
	glib-2.0 >= 2.26.1
	gthread-2.0
	shr-glib-1.0
	gdbus-codegen
)
PKG_CHECK_MODULES(LIBPHONEUI, libphone-ui)

AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)
AC_SUBST(LIBPHONEUI_CFLAGS)
AC_SUBST(LIBPHONEUI_LIBS)

AC_OUTPUT([
Makefile
src/Makefile
data/Makefile
])

