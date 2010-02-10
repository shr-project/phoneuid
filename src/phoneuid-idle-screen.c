
#include <glib.h>
#include <glib-object.h>
#include <dbus/dbus-glib-bindings.h>
#include <phoneui/phoneui.h>
#include <phoneui/phoneui-utils-device.h>
#include "phoneuid-dbus-common.h"
#include "phoneuid-idle-screen.h"
#include "phoneuid-idle-screen-service-glue.h"

G_DEFINE_TYPE(PhoneuidIdleScreenService, phoneuid_idle_screen_service, G_TYPE_OBJECT)

static void
phoneuid_idle_screen_service_class_init(PhoneuidIdleScreenServiceClass *klass)
{
	GError *error = NULL;

	/* Init the DBus connection, per-klass */
	klass->connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (klass->connection == NULL) {
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}

	dbus_g_object_type_install_info (PHONEUID_TYPE_IDLE_SCREEN_SERVICE,
			&dbus_glib_phoneuid_idle_screen_service_object_info);
}

static void
phoneuid_idle_screen_service_init(PhoneuidIdleScreenService *object)
{
	PhoneuidIdleScreenServiceClass *klass =
		PHONEUID_IDLE_SCREEN_SERVICE_GET_CLASS(object);

	/* Register DBUS path */
	dbus_g_connection_register_g_object(klass->connection,
			PHONEUID_IDLE_SCREEN_PATH,
			G_OBJECT (object));
}


PhoneuidIdleScreenService *
phoneuid_idle_screen_service_new(void)
{
	return (g_object_new(PHONEUID_TYPE_IDLE_SCREEN_SERVICE, NULL));
}


gboolean
phoneuid_idle_screen_service_display(PhoneuidIdleScreenService *object,
		DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_idle_screen_show();
	return (TRUE);
}


gboolean
phoneuid_idle_screen_service_hide(PhoneuidIdleScreenService *object,
		DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_idle_screen_hide();
	return (TRUE);
}


gboolean
phoneuid_idle_screen_service_toggle(PhoneuidIdleScreenService *object,
		DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_idle_screen_toggle();
	return (TRUE);
}


gboolean
phoneuid_idle_screen_service_activate_screensaver(PhoneuidIdleScreenService *object,
		DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_utils_device_activate_screensaver();
	return (TRUE);
}

gboolean
phoneuid_idle_screen_service_deactivate_screensaver(PhoneuidIdleScreenService *object,
		DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_utils_device_deactivate_screensaver();
	return (TRUE);
}

