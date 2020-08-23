#ifndef __USER_MAIN_H
#define __USER_MAIN_H

//C标准库
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
//STM32标准库
#include <usart.h>
#include <gpio.h>
//LiteOS标准库
#include <osal.h>
#include <cJSON.h>
#include <lcd.h>
//自定义
#include <EMW3080.h>
#include <uart_RasPi.h>
#include <dobot.h>
#include <conveyor.h>

typedef struct 
{
    uint8_t id;
    int8_t result_red_sauces;
    int8_t result_green_sauces;
    int8_t result_chop_sticks;
    uint8_t rest_red_sauces;
    uint8_t rest_green_sauces;
    uint8_t rest_chop_sticks;
    osal_semp_t sync_red_sauces;
    osal_semp_t sync_green_sauces;
    osal_semp_t sync_chop_sticks;
    osal_semp_t dobot_task_sync;
    osal_semp_t conveyor_task_sync;
}t_status;

#endif
