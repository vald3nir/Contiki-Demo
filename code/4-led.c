#include "contiki.h"
#include "dev/leds.h"

PROCESS(led_process, "Init process example");
AUTOSTART_PROCESSES(&led_process);

PROCESS_THREAD(led_process, ev, data)
{
  static struct etimer et;
  PROCESS_BEGIN();

  while (1)
  {

    leds_off(LEDS_ALL);
    leds_on(LEDS_GREEN);

    etimer_set(&et, CLOCK_SECOND * 5);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    leds_off(LEDS_ALL);
    leds_on(LEDS_RED);

    etimer_set(&et, CLOCK_SECOND * 5);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    leds_off(LEDS_ALL);
    leds_on(LEDS_BLUE);

    etimer_set(&et, CLOCK_SECOND * 5);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }

  PROCESS_END();
}