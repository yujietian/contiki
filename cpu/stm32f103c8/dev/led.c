#include "stm32f10x_gpio.h"
#include "led.h"

void ledInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_11 |GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//最高速率2MHz
    GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void ledSetValue(uint16_t led, int8_t value)
{
    uint16_t pin = 0;

    if(1 == led)
    {
        pin = GPIO_Pin_15;
    }
    else if(2 == led)
    {
        pin = GPIO_Pin_14;
    }
    else if(3 == led)
    {
        pin = GPIO_Pin_11;
    }
    else if(4 == led)
    {
        pin = GPIO_Pin_1;
    }

    if(0 == value)
    {
        GPIO_ResetBits(GPIOB, pin);
    }
    else
    {
        GPIO_SetBits(GPIOB, pin);
    }

}

