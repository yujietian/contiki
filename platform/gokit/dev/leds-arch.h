

#ifndef LEDS_ARCH_H_
#define LEDS_ARCH_H_

#include "contiki.h"

#define led1 sensorLed1
#define led2 sensorLed2
#define led3 sensorLed3
#define led4 sensorLed4

extern const struct sensors_sensor sensorLed1;
extern const struct sensors_sensor sensorLed2;
extern const struct sensors_sensor sensorLed3;
extern const struct sensors_sensor sensorLed4;

int32_t led1Config(int32_t type, int32_t value);
int32_t led1Value(int32_t type);
int32_t led1Status(int32_t type);

int32_t led2Config(int32_t type, int32_t value);
int32_t led2Value(int32_t type);
int32_t led2Status(int32_t type);

int32_t led3Config(int32_t type, int32_t value);
int32_t led3Value(int32_t type);
int32_t led3Status(int32_t type);

int32_t led4Config(int32_t type, int32_t value);
int32_t led4Value(int32_t type);
int32_t led4Status(int32_t type);

#endif /* LEDS_ARCH_H_ */
