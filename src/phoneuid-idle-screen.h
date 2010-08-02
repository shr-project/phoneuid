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

#ifndef _PHONEUID_IDLE_SCREEN_H
#define _PHONEUID_IDLE_SCREEN_H

#define PHONEUID_TYPE_IDLE_SCREEN_SERVICE            (phoneuid_idle_screen_service_get_type ())
#define PHONEUID_IDLE_SCREEN_SERVICE(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), PHONEUID_TYPE_IDLE_SCREEN_SERVICE, PhoneuidIdleScreenService))
#define PHONEUID_IDLE_SCREEN_SERVICE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PHONEUID_TYPE_IDLE_SCREEN_SERVICE, PhoneuidIdleScreenServiceClass))
#define PHONEUID_IS_IDLE_SCREEN_SERVICE(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), PHONEUID_TYPE_IDLE_SCREEN_SERVICE))
#define PHONEUID_IS_IDLE_SCREEN_SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PHONEUID_TYPE_IDLE_SCREEN_SERVICE))
#define PHONEUID_IDLE_SCREEN_SERVICE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), PHONEUID_TYPE_IDLE_SCREEN_SERVICE, PhoneuidIdleScreenServiceClass))


typedef struct _PhoneuidIdleScreenService PhoneuidIdleScreenService;
typedef struct _PhoneuidIdleScreenServiceClass PhoneuidIdleScreenServiceClass;

GType phoneuid_idle_screen_service_get_type(void);

struct _PhoneuidIdleScreenService {
	GObject parent;
};

struct _PhoneuidIdleScreenServiceClass {
	GObjectClass parent;
	DBusGConnection *connection;
};

gboolean
phoneuid_idle_screen_service_display(PhoneuidIdleScreenService *object,
		DBusGMethodInvocation *context);
gboolean
phoneuid_idle_screen_service_hide(PhoneuidIdleScreenService *object,
		DBusGMethodInvocation *context);

gboolean
phoneuid_idle_screen_service_activate_screensaver(PhoneuidIdleScreenService *object,
		DBusGMethodInvocation *context);

gboolean
phoneuid_idle_screen_service_deactivate_screensaver(PhoneuidIdleScreenService *object,
		DBusGMethodInvocation *context);

gboolean
phoneuid_idle_screen_service_toggle(PhoneuidIdleScreenService *object,
		DBusGMethodInvocation *context);

PhoneuidIdleScreenService *phoneuid_idle_screen_service_new(void);


#endif


