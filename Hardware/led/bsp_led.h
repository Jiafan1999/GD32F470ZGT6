#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "gd32f4xx.h"
#include "systick.h"

#define RCU_LED2 RCU_GPIOD  // GPIOD��ʱ��
#define PORT_LED2 GPIOD     // GPIOD�Ķ˿�
#define PIN_LED2 GPIO_PIN_7 // GPIOD������

#define RCU_LED4 RCU_GPIOA  // GPIOD��ʱ��
#define PORT_LED4 GPIOA     // GPIOD�Ķ˿�
#define PIN_LED4 GPIO_PIN_5 // GPIOD������

void led_gpio_config(void); // led gpio��������

#endif /* BSP_LED_H */
