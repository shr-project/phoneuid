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

#ifndef _PHONEUID_CALL_MANAGEMENT_H
#define _PHONEUID_CALL_MANAGEMENT_H

#define PHONEUID_TYPE_CALL_MANAGEMENT_SERVICE            (phoneuid_call_management_service_get_type ())
#define PHONEUID_CALL_MANAGEMENT_SERVICE(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), PHONEUID_TYPE_CALL_MANAGEMENT_SERVICE, PhoneuidCallManagementService))
#define PHONEUID_CALL_MANAGEMENT_SERVICE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PHONEUID_TYPE_CALL_MANAGEMENT_SERVICE, PhoneuidCallManagementServiceClass))
#define PHONEUID_IS_CALL_MANAGEMENT_SERVICE(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), PHONEUID_TYPE_CALL_MANAGEMENT_SERVICE))
#define PHONEUID_IS_CALL_MANAGEMENT_SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PHONEUID_TYPE_CALL_MANAGEMENT_SERVICE))
#define PHONEUID_CALL_MANAGEMENT_SERVICE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), PHONEUID_TYPE_CALL_MANAGEMENT_SERVICE, PhoneuidCallManagementServiceClass))

typedef struct _PhoneuidCallManagementService PhoneuidCallManagementService;
typedef struct _PhoneuidCallManagementServiceClass PhoneuidCallManagementServiceClass;

GType phoneuid_contacts_service_get_type(void);

struct _PhoneuidCallManagementService {
	GObject parent;
};

struct _PhoneuidCallManagementServiceClass {
	GObjectClass parent;
	DBusGConnection *connection;
};

gboolean
phoneuid_call_management_service_display_incoming(
		PhoneuidCallManagementService *object, const int call_id,
		const int status, const char *number,
		DBusGMethodInvocation *context);
gboolean
phoneuid_call_management_service_hide_incoming(
		PhoneuidCallManagementService *object, const int call_id,
		DBusGMethodInvocation *context);

gboolean
phoneuid_call_management_service_display_outgoing(
		PhoneuidCallManagementService *object, const int call_id,
		const int status, const char *number,
		DBusGMethodInvocation *context);

gboolean
phoneuid_call_management_service_hide_outgoing(
		PhoneuidCallManagementService *object, const int call_id,
		DBusGMethodInvocation *context);


PhoneuidCallManagementService *phoneuid_call_management_service_new(void);

#endif
