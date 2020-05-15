#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <systemd/sd-bus.h>

#include "freedesktop_notification.h"
#include "freedesktop_notification_messages.h"

const static char *supported_capabilities[]
    = { "action-icons", "actions",     "body",       "body-hyperlinks",
        "body-images",  "body-markup", "icon-multi", "icon-static",
        "persistence",  "sound" };

const static size_t capabilities_size
    = sizeof (supported_capabilities) / sizeof (char *);

int
handle_get_capabilities (sd_bus_message *request, void *data,
                         sd_bus_error *error)
{
  int status = 0;
  __attribute__ ((cleanup (sd_bus_message_unrefp))) sd_bus_message *response
      = NULL;

  status = sd_bus_message_new_method_return (request, &response);
  if (status < 0)
    {
      fprintf (stderr, "Failed creating response: %s", strerror (-status));
      return status;
    }

  status = sd_bus_message_open_container (response, 'a', "s");
  if (status < 0)
    {
      fprintf (stderr, "Failed creating response: %s", strerror (-status));
      return status;
    }

  for (size_t i = 0; i < capabilities_size; ++i)
    {
      status
          = sd_bus_message_append (response, "s", supported_capabilities[i]);
      if (status < 0)
        {
          fprintf (stderr, "Failed appending capability to response: %s",
                   strerror (-status));
          return status;
        }
    }
  status = sd_bus_message_close_container (response);

  status = sd_bus_send (NULL, response, NULL);
  if (status < 0)
    {
      fprintf (stderr, "Failed sending response: %s", strerror (-status));
      return status;
    }

  return status;
}

int
handle_get_server_information (sd_bus_message *request, void *data,
                               sd_bus_error *error)
{
  int status = 0;
  __attribute__ ((cleanup (sd_bus_message_unrefp))) sd_bus_message *response
      = NULL;

  status = sd_bus_message_new_method_return (request, &response);
  if (status < 0)
    {
      fprintf (stderr, "Failed creating response: %s", strerror (-status));
      return status;
    }

  status = sd_bus_message_append (response, "ssss", "caminhad", "none",
                                  "0.1.0", "");
  if (status < 0)
    {
      fprintf (stderr, "Failed creating response: %s", strerror (-status));
      return status;
    }

  status = sd_bus_send (NULL, response, NULL);
  if (status < 0)
    {
      fprintf (stderr, "Failed sending response: %s", strerror (-status));
      return status;
    }

  return status;
}
