#ifndef FREEDESKTOP_NOTIFICATION_H
#define FREEDESKTOP_NOTIFICATION_H

/* Declaration of the Freedesktop Notification Specification
  The document used as reference is availiable in
  https://developer.gnome.org/notification-spec/ */

/* A conforming implementation should take the org.freedesktop.Notifications
   service on the session bus. */
extern const char *notification_service;

/* The server should implement the org.freedesktop.Notifications interface. */
extern const char *notification_interface;

/* [...] on an object with the path "/org/freedesktop/Notifications". */
extern const char *notification_object;

/* Type representing a freedesktop notification. */
struct freedesktop_notification
{
  /* The unique ID allocated by the server. */
  unsigned int id;
  /* An optional ID of an existing notification that this notification is
     intended to replace. */
  unsigned int replaces_id;
  /* This is the optional name of the application sending the notification. */
  char *application_name;
  /* The notification icon. */
  char *icon;
  /* This is a single line overview of the notification. */
  char *summary;
  /* This is a multi-line body of text. Each line is a paragraph, server
     implementations are free to word wrap them as they see fit.  */
  char *body;
  /* The actions send a request message back to the notification client when
     invoked. */
  char *actions;
  /* Hints are a way to provide extra data to a notification server that the
     server may be able to make use of. */
  char *hints;
  /* The timeout time in milliseconds since the display of the notification a
     which the notification should automatically close. */
  int expiration_timeout;
};

#endif /* not FREEDESKTOP_NOTIFICATION_H */

