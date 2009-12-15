MAINTAINERCLEANFILES = Makefile.in

phoneuid-contacts-service-glue.h: $(SPECS_PATH)/org.shr.phoneui.Contacts.xml
	$(DBUSBINDINGTOOL) --mode=glib-server --output=$@ --prefix=phoneuid_contacts_service $^

phoneuid-messages-service-glue.h: $(SPECS_PATH)/org.shr.phoneui.Messages.xml
	$(DBUSBINDINGTOOL) --mode=glib-server --output=$@ --prefix=phoneuid_messages_service $^

phoneuid-call-management-service-glue.h: $(SPECS_PATH)/org.shr.phoneui.CallManagement.xml
	$(DBUSBINDINGTOOL) --mode=glib-server --output=$@ --prefix=phoneuid_call_management_service $^

phoneuid-dialer-service-glue.h: $(SPECS_PATH)/org.shr.phoneui.Dialer.xml
	$(DBUSBINDINGTOOL) --mode=glib-server --output=$@ --prefix=phoneuid_dialer_service $^

phoneuid-notification-service-glue.h: $(SPECS_PATH)/org.shr.phoneui.Notification.xml
	$(DBUSBINDINGTOOL) --mode=glib-server --output=$@ --prefix=phoneuid_notification_service $^

phoneuid-settings-service-glue.h: $(SPECS_PATH)/org.shr.phoneui.Settings.xml
	$(DBUSBINDINGTOOL) --mode=glib-server --output=$@ --prefix=phoneuid_settings_service $^

phoneuid-idle-screen-service-glue.h: $(SPECS_PATH)/org.shr.phoneui.IdleScreen.xml
	$(DBUSBINDINGTOOL) --mode=glib-server --output=$@ --prefix=phoneuid_idle_screen_service $^


bin_PROGRAMS = phoneuid
dbus_sources = phoneuid-contacts-service-glue.h \
	       phoneuid-messages-service-glue.h \
	       phoneuid-call-management-service-glue.h \
	       phoneuid-dialer-service-glue.h \
	       phoneuid-notification-service-glue.h \
	       phoneuid-settings-service-glue.h \
	       phoneuid-idle-screen-service-glue.h


BUILT_SOURCES = $(dbus_sources)

phoneuid_SOURCES = $(dbus_sources) \
	phoneuid.c \
	phoneuid-contacts.c \
	phoneuid-contacts.h \
	phoneuid-messages.c \
	phoneuid-messages.h \
	phoneuid-call-management.c \
	phoneuid-call-management.h \
	phoneuid-notification.c \
	phoneuid-notification.h \
	phoneuid-dialer.c \
	phoneuid-dialer.h \
	phoneuid-settings.c \
	phoneuid-settings.h \
	phoneuid-idle-screen.c \
	phoneuid-idle-screen.h

phoneuid_CFLAGS = -Wall -Wextra -Werror \
		  -DDATADIR=\"$(datadir)\" \
		  -DPKGDATADIR=\"$(pkgdatadir)\" \
		  -DG_LOG_DOMAIN=\"phoneuid\" \
		  @DBUS_GLIB_CFLAGS@ \
		  @DBUS_CFLAGS@ \
		  @LIBPHONEUI_CFLAGS@ \
		  -ggdb

phoneuid_LDFLAGS = \
		   -ldl \
		   @DBUS_GLIB_LIBS@ \
		   @DBUS_LIBS@ \
		   @LIBPHONEUI_LIBS@


