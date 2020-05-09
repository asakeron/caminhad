#include <stdlib.h>
#include <string.h>
#include <systemd/sd-bus-vtable.h>
#include <systemd/sd-bus.h>

static const char SERVICE_NAME[] = "org.freedesktop.Notifications";
static const char OBJECT_PATH[] = "/org/freedesktop/Notifications";
static const char *INTERFACE = SERVICE_NAME;

static const size_t caps_size = 10;
static const char *capabilities[]
    = { "action-icons", "actions",     "body",       "body-hyperlinks",
        "body-images",  "body-markup", "icon-multi", "icon-static",
        "persistence",  "sound" };

static int
get_capabilities (sd_bus_message *request, void *data, sd_bus_error *error)
{
  int status = 0;
  __attribute__ ((cleanup (sd_bus_message_unrefp))) sd_bus_message *response
      = NULL;

  if ((status = sd_bus_message_new_method_return (request, &response)) < 0
      || (status = sd_bus_message_open_container (response, 'a', "s")) < 0)
    {
      fprintf (stderr, "Could not create response: %s", strerror (-status));
      return status;
    }

  for (size_t i = 0; i < caps_size; ++i)
    {
      sd_bus_message_append (response, "s", capabilities[i]);
    }

  if ((status = sd_bus_message_close_container (response)) < 0)
    {
      fprintf (stderr, "Error closing container: %s", strerror (-status));
      return status;
    }

  sd_bus_send (NULL, response, NULL);

  return status;
}

static const sd_bus_vtable VTABLE[]
    = { SD_BUS_VTABLE_START (0),
        SD_BUS_METHOD ("GetCapabilities", "", "as", get_capabilities,
                       SD_BUS_VTABLE_UNPRIVILEGED),
        SD_BUS_VTABLE_END };

int
main (int argc, char **argv)
{
  int status = 0;
  __attribute__ ((cleanup (sd_bus_unrefp))) sd_bus *bus = NULL;
  __attribute__ ((cleanup (sd_bus_slot_unrefp))) sd_bus_slot *bus_slot = NULL;

  if ((status = sd_bus_default_user (&bus)) < 0)
    {
      fprintf (stderr, "Could not connect to D-Bus: %s\n", strerror (status));
      return status;
    }

  if ((status = sd_bus_add_object_vtable (bus, &bus_slot, OBJECT_PATH,
                                          INTERFACE, VTABLE, NULL))
      < 0)
    {
      fprintf (stderr, "Could not register object vtable: %s",
               strerror (-status));
      return status;
    }

  if ((status = sd_bus_request_name (bus, SERVICE_NAME, 0)) < 0)
    {
      fprintf (stderr, "Could not request service %s: %s\n", SERVICE_NAME,
               strerror (-status));
      return status;
    }

  do
    {
      if ((status = sd_bus_process (bus, NULL)) < 0)
        {
          fprintf (stderr, "Could not process bus: %s\n", strerror (-status));
          break;
        }

      if (status > 0)
        {
          continue;
        }

      if ((status = sd_bus_wait (bus, -1)) < 0)
        {
          fprintf (stderr, "Could not wait on bus: %s", strerror (-status));
          break;
        }
    }
  while (1);

  return status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
