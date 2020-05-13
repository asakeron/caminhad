#include <stdlib.h>
#include <string.h>
#include <systemd/sd-bus-vtable.h>
#include <systemd/sd-bus.h>

#include "src/freedesktop_notification.h"
#include "src/freedesktop_notification_messages.h"

static const sd_bus_vtable VTABLE[]
    = { SD_BUS_VTABLE_START (0),
        SD_BUS_METHOD ("GetCapabilities", "", "as", handle_get_capabilities,
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

  if ((status
       = sd_bus_add_object_vtable (bus, &bus_slot, notification_object,
                                   notification_interface, VTABLE, NULL))
      < 0)
    {
      fprintf (stderr, "Could not register object vtable: %s",
               strerror (-status));
      return status;
    }

  if ((status = sd_bus_request_name (bus, notification_service, 0)) < 0)
    {
      fprintf (stderr, "Could not request service %s: %s\n",
               notification_service, strerror (-status));
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
