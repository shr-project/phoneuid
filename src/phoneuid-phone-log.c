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
#include "phoneuid-phone-log.h"
#include "phoneuid-phone-log-service-glue.h"

G_DEFINE_TYPE(PhoneuidPhoneLogService, phoneuid_phone_log_service, G_TYPE_OBJECT)

static void
phoneuid_phone_log_service_class_init(PhoneuidPhoneLogServiceClass *klass)
{
	GError *error = NULL;

	/* Init the DBus connection, per-klass */
	klass->connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (klass->connection == NULL) {
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}

	dbus_g_object_type_install_info (PHONEUID_TYPE_PHONE_LOG_SERVICE,
			&dbus_glib_phoneuid_phone_log_service_object_info);
}

static void
phoneuid_phone_log_service_init(PhoneuidPhoneLogService *object)
{
	PhoneuidPhoneLogServiceClass *klass =
		PHONEUID_PHONE_LOG_SERVICE_GET_CLASS(object);

	/* Register DBUS path */
	dbus_g_connection_register_g_object(klass->connection,
			PHONEUID_PHONE_LOG_PATH,
			G_OBJECT (object));
}


PhoneuidPhoneLogService *
phoneuid_phone_log_service_new(void)
{
	return (g_object_new(PHONEUID_TYPE_PHONE_LOG_SERVICE, NULL));
}



gboolean
phoneuid_phone_log_service_display_list(PhoneuidPhoneLogService *object,
		GHashTable *options, DBusGMethodInvocation *context)
{
	(void) object;
	(void) options;
	dbus_g_method_return(context);
	// TODO: activate when done in libphone-ui
	phoneui_phone_log_show();
	return (TRUE);
}


