/*
 *  Copyright (C) 2009
 *      Authors (alphabetical) :
 *              Klaus 'mrmoku' Kurzmann <mok@fluxnetz.de>
 *              Thomas Zimmermann <bugs@vdm-design.de>
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
#include "phoneuid-calendar.h"
#include "phoneuid-calendar-service-glue.h"

G_DEFINE_TYPE(PhoneuidCalendarService, phoneuid_calendar_service, G_TYPE_OBJECT)

static void
phoneuid_calendar_service_class_init(PhoneuidCalendarServiceClass *klass)
{
	GError *error = NULL;

	/* Init the DBus connection, per-klass */
	klass->connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (klass->connection == NULL) {
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}

	dbus_g_object_type_install_info (PHONEUID_TYPE_CALENDAR_SERVICE,
			&dbus_glib_phoneuid_calendar_service_object_info);
}

static void
phoneuid_calendar_service_init(PhoneuidCalendarService *object)
{
	PhoneuidCalendarServiceClass *klass =
		PHONEUID_CALENDAR_SERVICE_GET_CLASS(object);

	/* Register DBUS path */
	dbus_g_connection_register_g_object(klass->connection,
			PHONEUID_CALENDAR_PATH,
			G_OBJECT (object));
}


PhoneuidCalendarService *
phoneuid_calendar_service_new(void)
{
	return (g_object_new(PHONEUID_TYPE_CALENDAR_SERVICE, NULL));
}



gboolean
phoneuid_calendar_service_display_month(PhoneuidCalendarService *object,
		const int month, DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	phoneui_calendar_month_show(month);
	return (TRUE);
}

gboolean
phoneuid_calendar_service_display_day(PhoneuidCalendarService *object,
		const char *day, DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	(void)day;
	//phoneui_calendar_day_show(day);
	return (TRUE);
}

gboolean
phoneuid_calendar_service_display_date(PhoneuidCalendarService *object,
		const char *path, DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	(void) path;
	//phoneui_calendar_date_show(path);
	return (TRUE);
}

gboolean
phoneuid_calendar_service_create_date(PhoneuidCalendarService *object,
		GHashTable *options, DBusGMethodInvocation *context)
{
	(void) object;
	dbus_g_method_return(context);
	(void) options;
	//phoneui_calendar_date_new(options);
	return (TRUE);
}

