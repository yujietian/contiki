/**
 * \addtogroup mbxxx-platform
 *
 * @{
 */

/*
 * Copyright (c) 2010, STMicroelectronics.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
* \file
*			Real-timer specific implementation for STM32W.
* \author
*			Salvatore Pitrulli <salvopitru@users.sourceforge.net>
*/

#include "sys/energest.h"
#include "sys/rtimer.h"
#include "stm32f10x.h"

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

/*---------------------------------------------------------------------------*/
void
TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_CC1) == SET)
    {
        TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);

        rtimer_arch_disable_irq();

        rtimer_run_next();
    }
}
/*---------------------------------------------------------------------------*/
void
rtimer_arch_init(void)
{
    uint16_t arr = 65535;
    uint16_t psc = (uint16_t)(SystemCoreClock/RTIMER_ARCH_SECOND) - 1;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位0

    TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

    //中断优先级NVIC设置
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //优占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

    TIM_Cmd(TIM3, ENABLE);  //使能TIMx
}
/*---------------------------------------------------------------------------*/
void
rtimer_arch_disable_irq(void)
{
    TIM_ITConfig(TIM3,TIM_IT_CC1, DISABLE);
}
/*---------------------------------------------------------------------------*/
void
rtimer_arch_enable_irq(void)
{
    TIM_ClearFlag(TIM3, TIM_IT_CC1);

    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
}
/*---------------------------------------------------------------------------*/
rtimer_clock_t
rtimer_arch_now(void)
{
  rtimer_clock_t t1, t2;

  do
  {
      t1 = TIM_GetCounter(TIM3);
      t2 = TIM_GetCounter(TIM3);
  }while(t1 != t2);

  return t1;
}

/*---------------------------------------------------------------------------*/
void
rtimer_arch_schedule(rtimer_clock_t t)
{
    TIM_SetCompare1(TIM3, t);

    PRINTF("rtimer_arch_schedule, %d !\n", rtimer_arch_now());

    TIM_ClearFlag(TIM3, TIM_IT_CC1);

    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
}
/*---------------------------------------------------------------------------*/
/** @} */
