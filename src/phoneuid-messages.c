
#include <glib.h>
#include <glib-object.h>
#include <dbus/dbus-glib-bindings.h>
#include <phoneui/phoneui.h>

#include "phoneuid-dbus-common.h"
#include "phoneuid-messages.h"
#include "phoneuid-messages-service-glue.h"

G_DEFINE_TYPE(PhoneuidMessagesService, phoneuid_messages_service, G_TYPE_OBJECT)

static void
phoneuid_messages_service_class_init(PhoneuidMessagesServiceClass *klass)
{
	GError *error = NULL;

	/* Init the DBus connection, per-klass */
	klass->connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (klass->connection == NULL) {
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}

	dbus_g_object_type_install_info (PHONEUID_TYPE_MESSAGES_SERVICE,
			&dbus_glib_phoneuid_messages_service_object_info);
}

static void
phoneuid_messages_service_init(PhoneuidMessagesService *object)
{
	PhoneuidMessagesServiceClass *klass =
		PHONEUID_MESSAGES_SERVICE_GET_CLASS(object);

	/* Register DBUS path */
	dbus_g_connection_register_g_object(klass->connection,
			PHONEUID_MESSAGES_PATH,
			G_OBJECT (object));
}


PhoneuidMessagesService *
phoneuid_messages_service_new(void)
{
	return (g_object_new(PHONEUID_TYPE_MESSAGES_SERVICE, NULL));
}


gboolean
phoneuid_messages_service_display_list(PhoneuidMessagesService *object,
		GHashTable *options, DBusGMethodInvocation *context)
{
	(void) object;
	(void) options;
	g_debug("org.shr.phoneui.Messages.DisplayList");
	dbus_g_method_return(context);
	phoneui_messages_show();
	return (TRUE);
}

gboolean
phoneuid_messages_service_display_message(PhoneuidMessagesService *object,
		const char *message_path, DBusGMethodInvocation *context)
{
	(void) object;
	(void) message_path;
	g_debug("org.shr.phoneui.Messages.DisplayMessage");
	dbus_g_method_return(context);
	return (TRUE);
}

gboolean
phoneuid_messages_service_create_message(PhoneuidMessagesService *object,
		GHashTable *values, DBusGMethodInvocation *context)
{
	(void) object;
	(void) values;
	g_debug("org.shr.phoneui.Messages.CreateContact");
	dbus_g_method_return(context);
	return (TRUE);
}

