
#include <gio/gio.h>
#include <shr-bindings.h>
#include <phoneui.h>
#include <phoneui-utils-device.h>

#include "phoneuid-dbus.h"
#include "phoneuid-dbus-common.h"


static guint phoneuid_owner_id;

/* g_bus_own_name callbacks */
static void _on_bus_acquired (GDBusConnection *connection, const gchar *name, gpointer user_data);
static void _on_name_acquired (GDBusConnection *connection, const gchar *name, gpointer user_data);
static void _on_name_lost (GDBusConnection *connection, const gchar *name, gpointer user_data);

/* phoneui method handlers */
static gboolean _call_management_display_incoming(PhoneuiCallManagement *object, GDBusMethodInvocation *invocation, const int call_id, const int status, const char *number, gpointer data);
static gboolean _call_management_hide_incoming(PhoneuiCallManagement *object, GDBusMethodInvocation *invocation, const int call_id, gpointer data);
static gboolean _call_management_display_outgoing(PhoneuiCallManagement *object, GDBusMethodInvocation *invocation, const int call_id, const int status, const char *number, gpointer data);
static gboolean _call_management_hide_outgoing(PhoneuiCallManagement *object, GDBusMethodInvocation *invocation, const int call_id, gpointer data);

static gboolean _contacts_display_list(PhoneuiContacts *object, GDBusMethodInvocation *invocation, GHashTable *filter, gpointer data);
static gboolean _contacts_display_contact(PhoneuiContacts *object, GDBusMethodInvocation *invocation, const char *contact_path, gpointer data);
static gboolean _contacts_create_contact(PhoneuiContacts *object, GDBusMethodInvocation *invocation, GHashTable *values, gpointer data);
static gboolean _contacts_edit_contact(PhoneuiContacts *object, GDBusMethodInvocation *invocation, const char *contact_path, gpointer data);

static gboolean _dialer_display(PhoneuiDialer *object, GDBusMethodInvocation *invocation, GHashTable *options, gpointer data);

static gboolean _idle_screen_display(PhoneuiIdleScreen *object, GDBusMethodInvocation *invocation, gpointer data);
static gboolean _idle_screen_hide(PhoneuiIdleScreen *object, GDBusMethodInvocation *invocation, gpointer data);
static gboolean _idle_screen_activate_screensaver(PhoneuiIdleScreen *object, GDBusMethodInvocation *invocation, gpointer data);
static gboolean _idle_screen_deactivate_screensaver(PhoneuiIdleScreen *object, GDBusMethodInvocation *invocation, gpointer data);
static gboolean _idle_screen_toggle(PhoneuiIdleScreen *object, GDBusMethodInvocation *invocation, gpointer data);

static gboolean _messages_display_list(PhoneuiMessages *object, GDBusMethodInvocation *invocation, GHashTable *options, gpointer data);
static gboolean _messages_display_message(PhoneuiMessages *object, GDBusMethodInvocation *invocation, const char *message_path, gpointer data);
static gboolean _messages_create_message(PhoneuiMessages *object, GDBusMethodInvocation *invocation, GHashTable *values, gpointer data);

static gboolean _notification_display_sim_auth(PhoneuiNotification *object, GDBusMethodInvocation *invocation, const int status, gpointer data);
static gboolean _notification_hide_sim_auth(PhoneuiNotification *object, GDBusMethodInvocation *invocation, const int status, gpointer data);
static gboolean _notification_display_ussd(PhoneuiNotification *object, GDBusMethodInvocation *invocation, const int mode, const char *message, gpointer data);
static gboolean _notification_display_dialog(PhoneuiNotification *object, GDBusMethodInvocation *invocation, const int dialog, gpointer data);
static gboolean _notification_feedback_action(PhoneuiNotification *object, GDBusMethodInvocation *invocation, const char *action, const char *level, gpointer data);

static gboolean _phonelog_display_list(PhoneuiPhoneLog *object, GDBusMethodInvocation *invocation, GHashTable *options, gpointer data);

static gboolean _settings_display_quick_settings(PhoneuiSettings *object, GDBusMethodInvocation *invocation, gpointer data);
static gboolean _settings_display_sim_manager(PhoneuiSettings *object, GDBusMethodInvocation *invocation, gpointer data);


void
phoneuid_dbus_setup()
{

	phoneuid_owner_id = g_bus_own_name
	(G_BUS_TYPE_SYSTEM, PHONEUID_SERVICE,
	 G_BUS_NAME_OWNER_FLAGS_REPLACE | G_BUS_NAME_OWNER_FLAGS_ALLOW_REPLACEMENT,
	 _on_bus_acquired, _on_name_acquired, _on_name_lost, NULL, NULL );

/*	phoneuid_watcher_id = g_bus_watch_name
	(G_BUS_TYPE_SYSTEM, PHONEUID_SERVICE,
	 G_BUS_NAME_WATCHER_FLAGS_NONE,
	 _on_phoneuid_appeared, _on_phoneuid_vanished, NULL, NULL);*/

}



/* handlers for g_bus_own_name */

static void
_register_interface(GDBusInterface *iface,
		      GDBusConnection *connection,
		      const char *path)
{
	GError *error = NULL;

	g_dbus_interface_register_object(iface, connection, path, &error);
	if (error) {
		g_critical("Failed to register %s: %s",
			    PHONEUID_CALL_MANAGEMENT_PATH, error->message);
		g_error_free(error);
	}
}

static void
_on_bus_acquired (GDBusConnection *connection,
		    const gchar     *name,
		    gpointer         user_data)
{
	(void) user_data;
	(void) name;

	PhoneuiCallManagement *call_management = phoneui_call_management_stub_new();
	g_signal_connect(call_management, "handle-display-incoming", G_CALLBACK(_call_management_display_incoming), NULL);
	g_signal_connect(call_management, "handle-hide-incoming", G_CALLBACK(_call_management_hide_incoming), NULL);
	g_signal_connect(call_management, "handle-display-outgoing", G_CALLBACK(_call_management_display_outgoing), NULL);
	g_signal_connect(call_management, "handle-hide-outgoing", G_CALLBACK(_call_management_hide_outgoing), NULL);
	_register_interface(G_DBUS_INTERFACE(call_management), connection, PHONEUID_CALL_MANAGEMENT_PATH);

	PhoneuiContacts *contacts = phoneui_contacts_stub_new();
	g_signal_connect(contacts, "handle-display-list", G_CALLBACK(_contacts_display_list), NULL);
	g_signal_connect(contacts, "handle-display-contact", G_CALLBACK(_contacts_display_contact), NULL);
	g_signal_connect(contacts, "handle-create-contact", G_CALLBACK(_contacts_create_contact), NULL);
	g_signal_connect(contacts, "handle-edit-contact", G_CALLBACK(_contacts_edit_contact), NULL);
	_register_interface(G_DBUS_INTERFACE(contacts), connection, PHONEUID_CONTACTS_PATH);

	PhoneuiDialer *dialer = phoneui_dialer_stub_new();
	g_signal_connect(dialer, "handle-display", G_CALLBACK(_dialer_display), NULL);
	_register_interface(G_DBUS_INTERFACE(dialer), connection, PHONEUID_DIALER_PATH);

	PhoneuiIdleScreen *idle = phoneui_idle_screen_stub_new();
	g_signal_connect(idle, "handle-display", G_CALLBACK(_idle_screen_display), NULL);
	g_signal_connect(idle, "handle-hide", G_CALLBACK(_idle_screen_hide), NULL);
	g_signal_connect(idle, "handle-toggle", G_CALLBACK(_idle_screen_toggle), NULL);
	g_signal_connect(idle, "handle-activate-screensaver", G_CALLBACK(_idle_screen_activate_screensaver), NULL);
	g_signal_connect(idle, "handle-deactivate-screensaver", G_CALLBACK(_idle_screen_deactivate_screensaver), NULL);
	_register_interface(G_DBUS_INTERFACE(idle), connection, PHONEUID_IDLE_SCREEN_PATH);

	PhoneuiMessages *messages = phoneui_messages_stub_new();
	g_signal_connect(messages, "handle-display-list", G_CALLBACK(_messages_display_list), NULL);
	g_signal_connect(messages, "handle-display-message", G_CALLBACK(_messages_display_message), NULL);
	g_signal_connect(messages, "handle-create-message", G_CALLBACK(_messages_create_message), NULL);
	_register_interface(G_DBUS_INTERFACE(messages), connection, PHONEUID_MESSAGES_PATH);

	PhoneuiNotification *notification = phoneui_notification_stub_new();
	g_signal_connect(notification, "handle-display-sim-auth", G_CALLBACK(_notification_display_sim_auth), NULL);
	g_signal_connect(notification, "handle-hide-sim-auth", G_CALLBACK(_notification_hide_sim_auth), NULL);
	g_signal_connect(notification, "handle-display-dialog", G_CALLBACK(_notification_display_dialog), NULL);
	g_signal_connect(notification, "handle-display-ussd", G_CALLBACK(_notification_display_ussd), NULL);
	g_signal_connect(notification, "handle-feedback-action", G_CALLBACK(_notification_feedback_action), NULL);
	_register_interface(G_DBUS_INTERFACE(notification), connection, PHONEUID_NOTIFICATION_PATH);

	PhoneuiPhoneLog *phonelog = phoneui_phone_log_stub_new();
	g_signal_connect(phonelog, "handle-display-list", G_CALLBACK(_phonelog_display_list), NULL);
	_register_interface(G_DBUS_INTERFACE(phonelog), connection, PHONEUID_PHONE_LOG_PATH);

	PhoneuiSettings *settings = phoneui_settings_stub_new();
	g_signal_connect(settings, "handle-display-quick-settings", G_CALLBACK(_settings_display_quick_settings), NULL);
	g_signal_connect(settings, "handle-display-sim-manager", G_CALLBACK(_settings_display_sim_manager), NULL);
	_register_interface(G_DBUS_INTERFACE(settings), connection, PHONEUID_SETTINGS_PATH);
}

static void
_on_name_acquired (GDBusConnection *connection,
		     const gchar     *name,
		     gpointer         user_data)
{
	(void) connection;
	(void) user_data;
	g_debug ("Acquired the name %s on the session bus\n", name);
}

static void
_on_name_lost (GDBusConnection *connection,
		 const gchar     *name,
		 gpointer         user_data)
{
	(void) connection;
	(void) user_data;
	g_debug ("Lost the name %s on the session bus\n", name);
}

/* phoneui method handlers */

gboolean
_call_management_display_incoming(PhoneuiCallManagement* object,
				      GDBusMethodInvocation* invocation,
				      const int call_id,
				      const int status,
				      const char* number,
				      gpointer data)
{
	(void) data;
	phoneui_incoming_call_show(call_id, status, number);
	phoneui_call_management_complete_display_incoming(object, invocation);
	return (TRUE);
}

gboolean
_call_management_display_outgoing(PhoneuiCallManagement* object,
				      GDBusMethodInvocation* invocation,
				      const int call_id,
				      const int status,
				      const char* number,
				      gpointer data)
{
	(void) data;
	phoneui_outgoing_call_show(call_id, status, number);
	phoneui_call_management_complete_display_outgoing(object, invocation);
	return TRUE;
}

gboolean
_call_management_hide_incoming(PhoneuiCallManagement* object,
				   GDBusMethodInvocation* invocation,
				   const int call_id,
				   gpointer data)
{
	(void) data;
	phoneui_incoming_call_hide(call_id);
	phoneui_call_management_complete_hide_incoming(object, invocation);
	return TRUE;
}

gboolean
_call_management_hide_outgoing(PhoneuiCallManagement* object,
				   GDBusMethodInvocation* invocation,
				   const int call_id,
				   gpointer data)
{
	(void) data;
	phoneui_outgoing_call_hide(call_id);
	phoneui_call_management_complete_hide_outgoing(object, invocation);
	return TRUE;
}


gboolean
_contacts_display_list(PhoneuiContacts* object,
			  GDBusMethodInvocation* invocation,
			  GHashTable* filter,
			  gpointer data)
{
	(void) data;
	(void) filter;
	phoneui_contacts_show();
	phoneui_contacts_complete_display_list(object, invocation);
	return TRUE;
}

gboolean
_contacts_display_contact(PhoneuiContacts* object,
			     GDBusMethodInvocation* invocation,
			     const char* contact_path,
			     gpointer data)
{
	(void) data;
	phoneui_contacts_contact_show(contact_path);
	phoneui_contacts_complete_display_contact(object, invocation);
	return TRUE;
}

gboolean
_contacts_edit_contact(PhoneuiContacts* object,
			  GDBusMethodInvocation* invocation,
			  const char* contact_path,
			  gpointer data)
{
	(void) data;
	phoneui_contacts_contact_edit(contact_path);
	phoneui_contacts_complete_edit_contact(object, invocation);
	return TRUE;
}

gboolean
_contacts_create_contact(PhoneuiContacts* object,
			    GDBusMethodInvocation* invocation,
			    GHashTable* values,
			    gpointer data)
{
	(void) data;
	phoneui_contacts_contact_new(values);
	phoneui_contacts_complete_create_contact(object, invocation, NULL);
	return TRUE;
}


gboolean
_dialer_display(PhoneuiDialer* object,
		  GDBusMethodInvocation* invocation,
		  GHashTable* options,
		  gpointer data)
{
	(void) data;
	(void) options;
	phoneui_dialer_show();
	phoneui_dialer_complete_display(object, invocation);
	return TRUE;
}


gboolean
_idle_screen_display(PhoneuiIdleScreen* object,
			GDBusMethodInvocation* invocation,
			gpointer data)
{
	(void) data;
	phoneui_idle_screen_show();
	phoneui_idle_screen_complete_display(object, invocation);
	return TRUE;
}

gboolean
_idle_screen_hide(PhoneuiIdleScreen* object,
		    GDBusMethodInvocation* invocation,
		    gpointer data)
{
	(void) data;
	phoneui_idle_screen_hide();
	phoneui_idle_screen_complete_hide(object, invocation);
	return TRUE;
}

gboolean
_idle_screen_toggle(PhoneuiIdleScreen* object,
		      GDBusMethodInvocation* invocation,
		      gpointer data)
{
	(void) data;
	phoneui_idle_screen_toggle();
	phoneui_idle_screen_complete_toggle(object, invocation);
	return TRUE;
}

gboolean
_idle_screen_activate_screensaver(PhoneuiIdleScreen* object,
				      GDBusMethodInvocation* invocation,
				      gpointer data)
{
	(void) data;
	phoneui_utils_device_activate_screensaver();
	phoneui_idle_screen_complete_activate_screensaver(object, invocation);
	return TRUE;
}

gboolean
_idle_screen_deactivate_screensaver(PhoneuiIdleScreen* object,
					 GDBusMethodInvocation* invocation,
					 gpointer data)
{
	(void) data;
	phoneui_utils_device_deactivate_screensaver();
	phoneui_idle_screen_complete_deactivate_screensaver(object, invocation);
	return TRUE;
}

gboolean
_notification_display_sim_auth(PhoneuiNotification* object,
				   GDBusMethodInvocation* invocation,
				   const int status,
				   gpointer data)
{
	(void) data;
	phoneui_sim_auth_show(status);
	phoneui_notification_complete_display_sim_auth(object, invocation);
	return TRUE;
}

gboolean
_notification_hide_sim_auth(PhoneuiNotification* object,
				GDBusMethodInvocation* invocation,
				const int status,
				gpointer data)
{
	(void) data;
	phoneui_sim_auth_hide(status);
	phoneui_notification_complete_hide_sim_auth(object, invocation);
	return TRUE;
}

gboolean
_notification_display_dialog(PhoneuiNotification* object,
				 GDBusMethodInvocation* invocation,
				 const int dialog,
				 gpointer data)
{
	(void) data;
	phoneui_dialog_show(dialog);
	phoneui_notification_complete_display_dialog(object, invocation);
	return TRUE;
}

gboolean _notification_display_ussd(PhoneuiNotification* object, GDBusMethodInvocation* invocation, const int mode, const char* message, gpointer data)
{
	(void) data;
	phoneui_ussd_show(mode, message);
	phoneui_notification_complete_display_ussd(object, invocation);
	return TRUE;
}

gboolean
_notification_feedback_action(PhoneuiNotification* object,
				  GDBusMethodInvocation* invocation,
				  const char* action,
				  const char* level,
				  gpointer data)
{
	(void) data;
	(void) action;
	(void) level;
	// TODO
	phoneui_notification_complete_feedback_action(object, invocation);
	return TRUE;
}

gboolean
_messages_display_list(PhoneuiMessages* object,
			  GDBusMethodInvocation* invocation,
			  GHashTable* options,
			  gpointer data)
{
	(void) data;
	(void) options;
	phoneui_messages_show();
	phoneui_messages_complete_display_list(object, invocation);
	return TRUE;
}

gboolean
_messages_display_message(PhoneuiMessages* object,
			     GDBusMethodInvocation* invocation,
			     const char* message_path,
			     gpointer data)
{
	(void) data;
	phoneui_messages_message_show(message_path);
	phoneui_messages_complete_display_message(object, invocation);
	return TRUE;
}

gboolean
_messages_create_message(PhoneuiMessages* object,
			    GDBusMethodInvocation* invocation,
			    GHashTable* values,
			    gpointer data)
{
	(void) data;
	phoneui_messages_message_new(values);
	phoneui_messages_complete_create_message(object, invocation);
	return TRUE;
}

gboolean
_phonelog_display_list(PhoneuiPhoneLog* object,
			  GDBusMethodInvocation* invocation,
			  GHashTable* options,
			  gpointer data)
{
	(void) data;
	(void) options;
	phoneui_phone_log_show();
	phoneui_phone_log_complete_display_list(object, invocation);
	return TRUE;
}

gboolean
_settings_display_quick_settings(PhoneuiSettings* object,
				     GDBusMethodInvocation* invocation,
				     gpointer data)
{
	(void) data;
	phoneui_quick_settings_show();
	phoneui_settings_complete_display_quick_settings(object, invocation);
	return TRUE;
}

gboolean
_settings_display_sim_manager(PhoneuiSettings* object,
				  GDBusMethodInvocation* invocation,
				  gpointer data)
{
	(void) data;
	phoneui_sim_manager_show();
	phoneui_settings_complete_display_sim_manager(object, invocation);
	return TRUE;
}
