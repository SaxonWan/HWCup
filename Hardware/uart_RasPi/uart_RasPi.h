#ifndef __UART_RASPI_H
#define __UART_RASPI_H

#include <usart.h>
#include <stm32l4xx.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <osal.h>
#include <link_misc.h>
#include <los_hwi.h>
#include <los_sem.h>
#include <los_base.h>

void RasPi_uart_init(int baud);
void RasPi_request(void);

#endif
