
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-bindings.h>
#include <phoneui/phoneui.h>
#include "phoneuid-call-management.h"
#include "phoneuid-dialer.h"
#include "phoneuid-notification.h"
#include "phoneuid-contacts.h"
#include "phoneuid-messages.h"
#include "phoneuid-dbus-common.h"

static FILE *logfile = NULL;

static void
_log_handler(const gchar *domain, GLogLevelFlags level, const gchar *message,
		gpointer userdata)
{
	char date_str[30];
	struct timeval tv;
	struct tm ptime;
	gettimeofday(&tv, NULL);
	localtime_r(&tv.tv_sec, &ptime);

	strftime(date_str, 30, "%Y.%m.%d %T", &ptime);

	fprintf(logfile, "%s.%06d [%s]\t %s\n", date_str, tv.tv_usec, domain, message);
	fflush(logfile);
}

static gpointer
dbus_register_object(DBusGConnection * connection,
		     DBusGProxy * proxy,
		     GType object_type,
		     const DBusGObjectInfo * info, const gchar * path)
{
	GObject *object = g_object_new(object_type, NULL);
	dbus_g_object_type_install_info(object_type, info);
	dbus_g_connection_register_g_object(connection, path, object);
	return object;
}

static void
phoneuid_dbus_setup()
{
	guint result;
	GError *error = NULL;

	phoneuid_call_management_service_new();
	phoneuid_dialer_service_new();
	phoneuid_notification_service_new();
	phoneuid_contacts_service_new();
	phoneuid_messages_service_new();

	/* -- register with phonefsod as UI handler -- */
	g_debug("registering with phonefsod as UI handler");
	DBusGConnection *bus = dbus_g_bus_get(DBUS_BUS_SYSTEM, &error);
	DBusGProxy *proxy = dbus_g_proxy_new_for_name(bus, PHONEFSOD_USAGE_NAME,
			PHONEFSOD_USAGE_PATH, PHONEFSOD_USAGE_INTERFACE);
	if (error == NULL) {
		dbus_g_proxy_call(proxy, "RegisterUiHandler", &error,
				G_TYPE_STRING, getenv("DBUS_SESSION_BUS_ADDRESS"),
				G_TYPE_INVALID, G_TYPE_INVALID);
	}
	else {
		g_message("(%d) %s", error->code, error->message);
		g_error_free(error);
	}
}


int
main(int argc, char **argv)
{

	logfile = fopen("/var/log/phoneuid.log", "a");
	if (!logfile) {
		printf("Error creating the logfile!!!");
		return (-3);
	}
	g_log_set_default_handler(_log_handler, NULL);
	g_type_init();

	if (!g_thread_supported())
		g_thread_init(NULL);
	dbus_g_thread_init();

	phoneui_load("phoneuid");
	phoneui_init(argc, argv, NULL);
	phoneuid_dbus_setup();
	phoneui_loop();
	g_debug("exited from phoneui_loop!");
}


