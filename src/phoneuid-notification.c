
#include <glib.h>
#include <glib-object.h>
#include <dbus/dbus-glib-bindings.h>
#include "phoneuid-dbus-common.h"
#include "phoneuid-notification.h"
#include "phoneuid-notification-service-glue.h"

G_DEFINE_TYPE(PhoneuidNotificationService, phoneuid_notification_service, G_TYPE_OBJECT)

static void
phoneuid_notification_service_class_init(PhoneuidNotificationServiceClass *klass)
{
	GError *error = NULL;

	/* Init the DBus connection, per-klass */
	klass->connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (klass->connection == NULL) {
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}

	dbus_g_object_type_install_info (PHONEUID_TYPE_NOTIFICATION_SERVICE,
			&dbus_glib_phoneuid_notification_service_object_info);
}

static void
phoneuid_notification_service_init(PhoneuidNotificationService *object)
{
	GError *error = NULL;
	DBusGProxy *driver_proxy;
	PhoneuidNotificationServiceClass *klass =
		PHONEUID_NOTIFICATION_SERVICE_GET_CLASS(object);
	int request_ret;

	/* Register DBUS path */
	dbus_g_connection_register_g_object(klass->connection,
			PHONEUID_NOTIFICATION_PATH,
			G_OBJECT (object));

	/* Register the service name, the constant here are defined in dbus-glib-bindings.h */
	driver_proxy = dbus_g_proxy_new_for_name (klass->connection,
			DBUS_SERVICE_DBUS,
			DBUS_PATH_DBUS,
			DBUS_INTERFACE_DBUS);

	if (!org_freedesktop_DBus_request_name (driver_proxy,
			PHONEUID_NOTIFICATION_NAME, 0, &request_ret, &error)) {
		g_warning("Unable to register service: %s", error->message);
		g_error_free (error);
	}
	g_object_unref(driver_proxy);
}


PhoneuidNotificationService *
phoneuid_notification_service_new(void)
{
	return (g_object_new(PHONEUID_TYPE_NOTIFICATION_SERVICE, NULL));
}


gboolean
phoneuid_notification_service_display_sim_auth(PhoneuidNotificationService *object,
		const int status, DBusGMethodInvocation *context)
{
	dbus_g_method_return(context);
	phoneui_sim_auth_show(status);
	return (TRUE);
}

gboolean
phoneuid_notification_service_hide_sim_auth(PhoneuidNotificationService *object,
		const int status, DBusGMethodInvocation *context)
{
	dbus_g_method_return(context);
	phoneui_sim_auth_hide(status);
	return (TRUE);
}

gboolean
phoneuid_notification_service_display_ussd(PhoneuidNotificationService *object,
		const int mode, const char *message, DBusGMethodInvocation *context)
{
	dbus_g_method_return(context);
	phoneui_ussd_show(mode, message);
	return (TRUE);

}

gboolean
phoneuid_notification_service_display_dialog(PhoneuidNotificationService *object,
		const int dialog, DBusGMethodInvocation *context)
{
	dbus_g_method_return(context);
	phoneui_dialog_show(dialog);
	return (TRUE);
}

gboolean
phoneuid_notification_service_feedback_action(PhoneuidNotificationService *object,
		const char *action, const char *level, DBusGMethodInvocation *context)
{
	dbus_g_method_return(context);
	return (TRUE);
}

