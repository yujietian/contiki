
#include "contiki-conf.h"
#include "sensors.h"
#include "dev/leds-arch.h"
#include "stm32f10x_gpio.h"

const struct sensors_sensor sensorLed1;

/*---------------------------------------------------------------------------*/
int32_t led1Config(int32_t type, int32_t value)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    switch(type)
    {
        case SENSORS_HW_INIT:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

            //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_11 |GPIO_Pin_14 | GPIO_Pin_15;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);

            if(0 == value)
            {
                GPIO_ResetBits(GPIOB, GPIO_Pin_15);
            }
            else
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_15);
            }
            break;
        case SENSORS_ACTIVE:
            if(0 == value)
            {
                GPIO_ResetBits(GPIOB, GPIO_Pin_15);
            }
            else
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_15);
            }
        default:
            break;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/
int32_t led1Value(int32_t type)
{
    return 0;
}

/*---------------------------------------------------------------------------*/
int32_t led1Status(int32_t type)
{
    return 0;
}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
int32_t led2Config(int32_t type, int32_t value)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    switch(type)
    {
        case SENSORS_HW_INIT:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);

            if(0 == value)
            {
                GPIO_ResetBits(GPIOB, GPIO_Pin_14);
            }
            else
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_14);
            }
            break;
        case SENSORS_ACTIVE:
            if(0 == value)
            {
                GPIO_ResetBits(GPIOB, GPIO_Pin_14);
            }
            else
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_14);
            }
        default:
            break;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/
int32_t led2Value(int32_t type)
{
    return 0;
}

/*---------------------------------------------------------------------------*/
int32_t led2Status(int32_t type)
{
    return 0;
}


/*---------------------------------------------------------------------------*/
int32_t led3Config(int32_t type, int32_t value)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    switch(type)
    {
        case SENSORS_HW_INIT:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);

            if(0 == value)
            {
                GPIO_ResetBits(GPIOB, GPIO_Pin_11);
            }
            else
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_11);
            }
            break;
        case SENSORS_ACTIVE:
            if(0 == value)
            {
                GPIO_ResetBits(GPIOB, GPIO_Pin_11);
            }
            else
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_11);
            }
        default:
            break;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/
int32_t led3Value(int32_t type)
{
    return 0;
}

/*---------------------------------------------------------------------------*/
int32_t led3Status(int32_t type)
{
    return 0;
}



/*---------------------------------------------------------------------------*/
int32_t led4Config(int32_t type, int32_t value)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    switch(type)
    {
        case SENSORS_HW_INIT:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);

            if(0 == value)
            {
                GPIO_ResetBits(GPIOB, GPIO_Pin_1);
            }
            else
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_1);
            }
            break;
        case SENSORS_ACTIVE:
            if(0 == value)
            {
                GPIO_ResetBits(GPIOB, GPIO_Pin_1);
            }
            else
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_1);
            }
        default:
            break;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/
int32_t led4Value(int32_t type)
{
    return 0;
}

/*---------------------------------------------------------------------------*/
int32_t led4Status(int32_t type)
{
    return 0;
}

SENSORS_SENSOR(sensorLed1, "led1", led1Value, led1Config, led1Status);
SENSORS_SENSOR(sensorLed2, "led2", led2Value, led2Config, led2Status);
SENSORS_SENSOR(sensorLed3, "led3", led3Value, led3Config, led3Status);
SENSORS_SENSOR(sensorLed4, "led4", led4Value, led4Config, led4Status);
