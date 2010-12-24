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

#ifndef _PHONEUID_CALENDAR_H
#define _PHONEUID_CALENDAR_H

#define PHONEUID_TYPE_CALENDAR_SERVICE            (phoneuid_calendar_service_get_type ())
#define PHONEUID_CALENDAR_SERVICE(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), PHONEUID_TYPE_CALENDAR_SERVICE, PhoneuidCalendarService))
#define PHONEUID_CALENDAR_SERVICE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PHONEUID_TYPE_CALENDAR_SERVICE, PhoneuidCalendarServiceClass))
#define PHONEUID_IS_CALENDAR_SERVICE(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), PHONEUID_TYPE_CALENDAR_SERVICE))
#define PHONEUID_IS_CALENDAR_SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PHONEUID_TYPE_CALENDAR_SERVICE))
#define PHONEUID_CALENDAR_SERVICE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), PHONEUID_TYPE_CALENDAR_SERVICE, PhoneuidCalendarServiceClass))


typedef struct _PhoneuidCalendarService PhoneuidCalendarService;
typedef struct _PhoneuidCalendarServiceClass PhoneuidCalendarServiceClass;

GType phoneuid_calendar_service_get_type(void);

struct _PhoneuidCalendarService {
	GObject parent;
};

struct _PhoneuidCalendarServiceClass {
	GObjectClass parent;
	DBusGConnection *connection;
};

gboolean phoneuid_calendar_service_display_month(PhoneuidCalendarService *object,
		int month, DBusGMethodInvocation *context);
gboolean phoneuid_calendar_service_display_day(PhoneuidCalendarService *object,
		const char *day, DBusGMethodInvocation *context);
gboolean phoneuid_calendar_service_display_date(PhoneuidCalendarService *object,
		const char *path, DBusGMethodInvocation *context);
gboolean phoneuid_calendar_service_create_date(PhoneuidCalendarService *object,
		GHashTable *options, DBusGMethodInvocation *context);

PhoneuidCalendarService *phoneuid_calendar_service_new(void);



#endif

