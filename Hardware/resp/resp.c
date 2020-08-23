#include <resp.h>
#include <stddef.h>
#include <stdint.h>
#include <stm32l4xx.h>
#include <stm32l4xx_it.h>
#include <usart.h>

static USART_TypeDef *s_pUSART = USART2;
static uint32_t s_uwIRQn = USART2_IRQn;

/*******************************************************************************
function     :use this function to deal the uart interrupt
parameters   :
instruction  :we cached the data in the temp buffer,when the idle interrupt reached,
              then we write the data and the length to the ring if the ring has enough
              space
*******************************************************************************/
static  uart2_interrupt_entry(void)
{
    
    // USART2_IRQHandler();
    // printf("receive:%c\r\n", resp_rcv_byte);
    // HAL_UART_Receive_IT(&huart2, &resp_rcv_byte, 1);
    // // printf("receive string:%s\r\n", resp_rcv_data);
    // // (void)memset(resp_rcv_data, 0, 64);
    // // HAL_UART_Receive_IT(&huart2, &resp_rcv_data, 5);

    // // if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) != RESET)
    // // {
    // //     value = (uint8_t)(s_pUSART->RDR & 0x00FF);
    // //     resp_rcv_data[strlen(resp_rcv_data)] = value;
    // //     if (value == '3')
    // //         osal_semp_post(resp_rcv_sync);
    // // }
}

bool_t uart_resp_init(void)
{
    if (false == osal_semp_create(&resp_rcv_sync, 1, 0))
    {
        printf("%s:semp create error\n\r", __FUNCTION__);
        goto EXIT_SEMP;
    }

    MX_USART2_UART_Init();
    // LOS_HwiCreate(s_uwIRQn, 0, 0, uart2_interrupt_entry, 0);
    LOS_HwiCreate(s_uwIRQn, 3, 0, USART2_IRQHandler, 0);
    // HAL_UART_Receive_IT(&huart2, &resp_rcv_byte, 1);
    // HAL_UART_Receive_IT(&huart2, &resp_rcv_data, 5);
    // __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_TC);
    
    // __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
    // __HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
    return true;

EXIT_SEMP:
    return false;
}
//receive 100 主动去读

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
//     if(huart == &huart2)
//     {
//         //resp_rcv_data[]
//         printf("receive:%c\r\n", resp_rcv_byte);
//         HAL_UART_Receive_IT(&huart2, resp_rcv_byte, 1);
//     }
// }
