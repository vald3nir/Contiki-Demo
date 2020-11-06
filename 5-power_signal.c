
#include "contiki.h"
#include "net/rime.h"
#include "random.h"
#include "dev/cc2420.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

PROCESS(example_broadcast_process, "Broadcast example");
AUTOSTART_PROCESSES(&example_broadcast_process);

int get_power_signal_level()
{
  return abs((int)cc2420_last_rssi + (-45)); // -45 = offset
}

static void broadcast_recv(struct broadcast_conn *c, const rimeaddr_t *from)
{
  printf("broadcast from %d: power: %d\n", from->u8[0], get_power_signal_level());
}

static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;

PROCESS_THREAD(example_broadcast_process, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)
  PROCESS_BEGIN();

  broadcast_open(&broadcast, 129, &broadcast_call);

  while (1)
  {
    etimer_set(&et, CLOCK_SECOND * 4 + random_rand() % (CLOCK_SECOND * 4));
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    broadcast_send(&broadcast);
  }

  PROCESS_END();
}