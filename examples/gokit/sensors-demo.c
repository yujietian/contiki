
#include "contiki.h"
#include "contiki-conf.h"
#include "sensors.h"
#include "dev/leds-arch.h"

#define DEBUG 1

#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else /* DEBUG */
/* We overwrite (read as annihilate) all output functions here */
#define PRINTF(...)
#endif /* DEBUG */

/*---------------------------------------------------------------------------*/
PROCESS(sensors_test_process, "Sensor Test Process");
AUTOSTART_PROCESSES(&sensors_test_process);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sensors_test_process, ev, data)
{
  static struct etimer et;
  static int32_t count = 0;

  PROCESS_BEGIN();

  PRINTF("========================\n");
  PRINTF("Starting Sensor Example.\n");
  PRINTF("========================\n");

  /* Set an etimer. We take sensor readings when it expires and reset it. */
  etimer_set(&et, CLOCK_SECOND);

  led1.configure(SENSORS_HW_INIT, 0);

  while(1)
  {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    PRINTF("------------------\n");
    led1.configure(SENSORS_ACTIVE, count%2);

    count++;
    etimer_reset(&et);
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
