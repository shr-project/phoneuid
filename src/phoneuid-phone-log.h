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

#ifndef _PHONEUID_PHONE_LOG_H
#define _PHONEUID_PHONE_LOG_H

#define PHONEUID_TYPE_PHONE_LOG_SERVICE            (phoneuid_phone_log_service_get_type ())
#define PHONEUID_PHONE_LOG_SERVICE(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), PHONEUID_TYPE_PHONE_LOG_SERVICE, PhoneuidPhoneLogService))
#define PHONEUID_PHONE_LOG_SERVICE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PHONEUID_TYPE_PHONE_LOG_SERVICE, PhoneuidPhoneLogServiceClass))
#define PHONEUID_IS_PHONE_LOG_SERVICE(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), PHONEUID_TYPE_PHONE_LOG_SERVICE))
#define PHONEUID_IS_PHONE_LOG_SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PHONEUID_TYPE_PHONE_LOG_SERVICE))
#define PHONEUID_PHONE_LOG_SERVICE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), PHONEUID_TYPE_PHONE_LOG_SERVICE, PhoneuidPhoneLogServiceClass))


typedef struct _PhoneuidPhoneLogService PhoneuidPhoneLogService;
typedef struct _PhoneuidPhoneLogServiceClass PhoneuidPhoneLogServiceClass;

GType phoneuid_phone_log_service_get_type(void);

struct _PhoneuidPhoneLogService {
	GObject parent;
};

struct _PhoneuidPhoneLogServiceClass {
	GObjectClass parent;
	DBusGConnection *connection;
};

gboolean
phoneuid_phone_log_service_display_list(PhoneuidPhoneLogService *object,
		GHashTable *options, DBusGMethodInvocation *context);

PhoneuidPhoneLogService *phoneuid_phone_log_service_new(void);

#endif

