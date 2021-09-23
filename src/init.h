
#ifndef INIT_H_
#define INIT_H_
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "math.h"
#define NUMBER_ADC_DATA 16

volatile uint16_t finalData[NUMBER_ADC_DATA];

void timer_1ms(void);

void timer_100us(void);

void init_GPIO_speed_difference(void);

void int_GPIO_R(void);

void int_GPIO_L(void);

void init_gpio_debug(void);

void init_DAC(void);

void velOut_gpio(void);

void velOut_gpio2(void);

void button_gpio(void);

void init_TIM6_ON(void);

void init_TIM6_OFF(void);

void init_adc(void);

void init_GPIO_ADC(void);

void ini_dma(void);

#endif /* INIT_H_ */
