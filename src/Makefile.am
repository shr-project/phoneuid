MAINTAINERCLEANFILES = Makefile.in

bin_PROGRAMS = phoneuid


phoneuid_SOURCES = \
	phoneuid.c \
	phoneuid-dbus.h \
	phoneuid-dbus.c
	phoneuid-settings.c \
	phoneuid-settings.h \
	phoneuid-phone-log.c \
	phoneuid-phone-log.h

phoneuid_CFLAGS = -Wall -Wextra -Werror -Wno-strict-aliasing \
		  -DDATADIR=\"$(datadir)\" \
		  -DPKGDATADIR=\"$(pkgdatadir)\" \
		  -DG_LOG_DOMAIN=\"phoneuid\" \
		  @GLIB_CFLAGS@ \
		  @LIBPHONEUI_CFLAGS@ \
		  -ggdb

phoneuid_LDFLAGS = \
		   -ldl \
		   @GLIB_LIBS@ \
		   @LIBPHONEUI_LIBS@


