#ifndef __RESP_H_
#define __RESP_H_

#include <osal.h>

extern char resp_rcv_byte;
extern char resp_rcv_data[64];
extern osal_semp_t resp_rcv_sync;

bool_t uart_resp_init(void);

#endif