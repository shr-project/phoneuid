/*
 *  Copyright (C) 2009
 *      Authors (alphabetical) :
 *              Klaus 'mrmoku' Kurzmann <mok@fluxnetz.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Public License as published by
 *  the Free Software Foundation; version 2 of the license or any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser Public License for more details.
 */


#include <glib.h>
#include <glib-object.h>
#include <dbus/dbus-glib-bindings.h>
#include <phoneui/phoneui.h>

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
	PhoneuidNotificationServiceClass *klass =
		PHONEUID_NOTIFICATION_SERVICE_GET_CLASS(object);

	/* Register DBUS path */
	dbus_g_connection_register_g_object(klass->connection,
			PHONEUID_NOTIFICATION_PATH,
			G_OBJECT (object));
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
	(void) object;
	dbus_g_method_return(context);
	phoneui_sim_auth_show(status);
	return (TRUE);
}

gboolean
phoneuid_notification_service_hide_sim_auth(PhoneuidNotificationService *object,
		const int status, DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_sim_auth_hide(status);
	return (TRUE);
}

gboolean
phoneuid_notification_service_display_ussd(PhoneuidNotificationService *object,
		const int mode, const char *message, DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_ussd_show(mode, message);
	return (TRUE);

}

gboolean
phoneuid_notification_service_display_dialog(PhoneuidNotificationService *object,
		const int dialog, DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_dialog_show(dialog);
	return (TRUE);
}

gboolean
phoneuid_notification_service_feedback_action(PhoneuidNotificationService *object,
		const char *action, const char *level, DBusGMethodInvocation *context)
{
	(void) object;
	(void) action;
	(void) level;
	dbus_g_method_return(context);
	return (TRUE);
}

