#ifndef freedesktop_notification_messages_h
#define freedesktop_notification_messages_h

#include <systemd/sd-bus.h>

/* Declaratios of dbus messages supported by a server which conforms to the
   Freedesktop Notification Specification */

/* This message returns the optional capabilities implemented by the server */
const int handle_get_capabilities (sd_bus_message *request, void *data,
                                   sd_bus_error *error);

/* Sends a notification to the notification server. */
int handle_notify (sd_bus_message *request, void *data, sd_bus_error *error);

/* Causes a notification to be forcefully closed and removed
   from the user's view. */
int handle_close_notification (sd_bus_message *request, void *data,
                               sd_bus_error *error);

/* This message returns the information on the server. Specifically,
   the server name, vendor, and version number. */
int handle_get_server_information (sd_bus_message *request, void *data,
                                   sd_bus_error *error);

#endif /* freedesktop_notification_messages_h */
