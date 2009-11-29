#ifndef _PHONEUID_NOTIFICATION_H
#define _PHONEUID_NOTIFICATION_H

#define PHONEUID_TYPE_NOTIFICATION_SERVICE            (phoneuid_notification_service_get_type ())
#define PHONEUID_NOTIFICATION_SERVICE(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), PHONEUID_TYPE_NOTIFICATION_SERVICE, PhoneuidNotificationService))
#define PHONEUID_NOTIFICATION_SERVICE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PHONEUID_TYPE_NOTIFICATION_SERVICE, PhoneuidNotificationServiceClass))
#define PHONEUID_IS_NOTIFICATION_SERVICE(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), PHONEUID_TYPE_NOTIFICATION_SERVICE))
#define PHONEUID_IS_NOTIFICATION_SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PHONEUID_TYPE_NOTIFICATION_SERVICE))
#define PHONEUID_NOTIFICATION_SERVICE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), PHONEUID_TYPE_NOTIFICATION_SERVICE, PhoneuidNotificationServiceClass))


typedef struct _PhoneuidNotificationService PhoneuidNotificationService;
typedef struct _PhoneuidNotificationServiceClass PhoneuidNotificationServiceClass;

GType phoneuid_notification_service_get_type(void);

struct _PhoneuidNotificationService {
	GObject parent;
};

struct _PhoneuidNotificationServiceClass {
	GObjectClass parent;
	DBusGConnection *connection;
};

gboolean
phoneuid_notification_service_display_sim_auth(PhoneuidNotificationService *object,
		const int status, DBusGMethodInvocation *context);
gboolean
phoneuid_notification_service_hide_sim_auth(PhoneuidNotificationService *object,
		const int status, DBusGMethodInvocation *context);
gboolean
phoneuid_notification_service_display_ussd(PhoneuidNotificationService *object,
		const int mode, const char *message,
		DBusGMethodInvocation *context);
gboolean
phoneuid_notification_service_display_dialog(PhoneuidNotificationService *object,
		const int dialog, DBusGMethodInvocation *context);
gboolean
phoneuid_notification_service_feedback_action(PhoneuidNotificationService *object,
		const char *action, const char *level, DBusGMethodInvocation *context);


PhoneuidNotificationService *phoneuid_notification_service_new(void);



#endif
