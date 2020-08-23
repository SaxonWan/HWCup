#ifndef __CONVEYOR_H
#define __CONVEYOR_H

#include <stm32l4xx_hal.h>
#include <stm32l4xx.h>

#include <osal.h>

#define IR_INT_Pin GPIO_PIN_11
#define IR_INT_GPIO_Port GPIOA
#define IR_INT_EXTI_IRQn EXTI15_10_IRQn

#define DIR_Pin GPIO_PIN_6
#define DIR_GPIO_Port GPIOB
#define EN_Pin GPIO_PIN_8
#define EN_GPIO_Port GPIOB

void conveyor_init(void);
void start_conveyor(void);
bool_t stop_conveyor(void);

#endif
