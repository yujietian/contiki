//#include <stm32f10x_map.h>
//#include <stm32f10x_dma.h>
//#include <gpio.h>
//#include <nvic.h>
#include <stdint.h>
#include <stdio.h>
#include <contiki.h>
//#include <debug-uart.h>
#include <sys/process.h>
#include <sys/procinit.h>
#include <etimer.h>
#include <sys/autostart.h>
//#include <clock.h>
#include "stm32f10x.h"

unsigned int idle_count = 0;

int
main()
{
  SystemInit();

  uartxInit();
  printf("Initialising\n");

  clock_init();
  rtimer_init();

  process_init();
  process_start(&etimer_process, NULL);
  autostart_start(autostart_processes);
  printf("Processes running\n");
  while(1) {
    do {
    } while(process_run() > 0);
    idle_count++;
    /* Idle! */
    /* Stop processor clock */
    /* asm("wfi"::); */ 
  }
  return 0;
}




