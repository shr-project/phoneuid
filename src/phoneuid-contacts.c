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
#include "phoneuid-contacts.h"
#include "phoneuid-contacts-service-glue.h"

G_DEFINE_TYPE(PhoneuidContactsService, phoneuid_contacts_service, G_TYPE_OBJECT)

static void
phoneuid_contacts_service_class_init(PhoneuidContactsServiceClass *klass)
{
	GError *error = NULL;

	/* Init the DBus connection, per-klass */
	klass->connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (klass->connection == NULL) {
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}

	dbus_g_object_type_install_info (PHONEUID_TYPE_CONTACTS_SERVICE,
			&dbus_glib_phoneuid_contacts_service_object_info);
}

static void
phoneuid_contacts_service_init(PhoneuidContactsService *object)
{
	PhoneuidContactsServiceClass *klass =
		PHONEUID_CONTACTS_SERVICE_GET_CLASS(object);

	/* Register DBUS path */
	dbus_g_connection_register_g_object(klass->connection,
			PHONEUID_CONTACTS_PATH,
			G_OBJECT (object));
}


PhoneuidContactsService *
phoneuid_contacts_service_new(void)
{
	return (g_object_new(PHONEUID_TYPE_CONTACTS_SERVICE, NULL));
}


/* === org.shr.phoneuid.Contacts methods === */

/* --- DisplayList --- */

gboolean
phoneuid_contacts_service_display_list(PhoneuidContactsService *object,
		GHashTable *filter, DBusGMethodInvocation *context)
{
	(void) object;
	(void) filter;
	g_debug("org.shr.phoneuid.Contacts.DisplayList");
	dbus_g_method_return(context);
	phoneui_contacts_show();
	return (TRUE);
}

gboolean
phoneuid_contacts_service_display_contact(PhoneuidContactsService *object,
		const char *contact_path, DBusGMethodInvocation *context)
{
	(void) object;
	g_debug("org.shr.phoneuid.Contacts.DisplayContact");
	dbus_g_method_return(context);
	phoneui_contacts_contact_show(contact_path);
	return (TRUE);
}

gboolean
phoneuid_contacts_service_create_contact(PhoneuidContactsService *object,
		GHashTable *values, DBusGMethodInvocation *context)
{
	(void) object;
	g_debug("org.shr.phoneuid.Contacts.CreateContact");
	dbus_g_method_return(context);
	phoneui_contacts_contact_new(values);
	return (TRUE);
}

gboolean
phoneuid_contacts_service_edit_contact(PhoneuidContactsService *object,
		const char *contact_path, DBusGMethodInvocation *context)
{
	(void) object;
	g_debug("org.shr.phoneuid.Contacts.EditContact");
	dbus_g_method_return(context);
	phoneui_contacts_contact_edit(contact_path);
	return (TRUE);
}


