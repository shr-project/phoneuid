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
#include "phoneuid-settings.h"
#include "phoneuid-settings-service-glue.h"

G_DEFINE_TYPE(PhoneuidSettingsService, phoneuid_settings_service, G_TYPE_OBJECT)

static void
phoneuid_settings_service_class_init(PhoneuidSettingsServiceClass *klass)
{
	GError *error = NULL;

	/* Init the DBus connection, per-klass */
	klass->connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (klass->connection == NULL) {
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}

	dbus_g_object_type_install_info (PHONEUID_TYPE_SETTINGS_SERVICE,
			&dbus_glib_phoneuid_settings_service_object_info);
}

static void
phoneuid_settings_service_init(PhoneuidSettingsService *object)
{
	PhoneuidSettingsServiceClass *klass =
		PHONEUID_SETTINGS_SERVICE_GET_CLASS(object);

	/* Register DBUS path */
	dbus_g_connection_register_g_object(klass->connection,
			PHONEUID_SETTINGS_PATH,
			G_OBJECT (object));
}


PhoneuidSettingsService *
phoneuid_settings_service_new(void)
{
	return (g_object_new(PHONEUID_TYPE_SETTINGS_SERVICE, NULL));
}


gboolean
phoneuid_settings_service_display_quick_settings(PhoneuidSettingsService *object,
		DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_quick_settings_show();
	return (TRUE);
} 

gboolean
phoneuid_settings_service_display_sim_manager(PhoneuidSettingsService *object,
		DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_sim_manager_show();
	return (TRUE);
}

