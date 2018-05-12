#include <stm32f10x.h>
#include <contiki.h>
#include <sys/clock.h>
#include <sys/cc.h>
#include <sys/etimer.h>

static volatile clock_time_t current_clock = 0;
static volatile unsigned long current_seconds = 0;
static unsigned int second_countdown = CLOCK_SECOND;

static uint32_t count =0;

void clockHandle(void)
{
  current_clock++;
  if(etimer_pending() && etimer_next_expiration_time() <= current_clock) {
    etimer_request_poll();

  }
  if (--second_countdown == 0) {
    current_seconds++;
    second_countdown = CLOCK_SECOND;
  }

}

void SysTick_Handler(void)
{
    clockHandle();
}

void
clock_init()
{
    SysTick_Config(720000); //10ms
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
}

clock_time_t
clock_time(void)
{
  return current_clock;
}

#if 0
/* The inner loop takes 4 cycles. The outer 5+SPIN_COUNT*4. */

#define SPIN_TIME 2 /* us */
#define SPIN_COUNT (((MCK*SPIN_TIME/1000000)-5)/4)

#ifndef __MAKING_DEPS__

void
clock_delay(unsigned int t)
{
#ifdef __THUMBEL__ 
  asm volatile("1: mov r1,%2\n2:\tsub r1,#1\n\tbne 2b\n\tsub %0,#1\n\tbne 1b\n":"=l"(t):"0"(t),"l"(SPIN_COUNT));
#else
#error Must be compiled in thumb mode
#endif
}
#endif
#endif /* __MAKING_DEPS__ */

unsigned long
clock_seconds(void)
{
  return current_seconds;
}
