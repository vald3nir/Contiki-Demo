
#include "contiki.h"
#include "net/rime/rimeaddr.h"

#include <stdio.h>

PROCESS(hello_world_process, "Init hello world process");
AUTOSTART_PROCESSES(&hello_world_process);

int get_id_current_device()
{
  return rimeaddr_node_addr.u8[0];
}

PROCESS_THREAD(hello_world_process, ev, data)
{
  PROCESS_BEGIN();
  printf("Hello, world, ID:%d\n", get_id_current_device());
  PROCESS_END();
}
