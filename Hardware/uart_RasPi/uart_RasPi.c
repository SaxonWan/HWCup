#include <uart_RasPi.h>

static USART_TypeDef *s_pUSART = USART2;
static uint32_t s_uwIRQn = USART2_IRQn;

static bool_t s_uart_init = false;

UART_HandleTypeDef uart_RasPi;

extern char RasPi_rcv_data[64];
extern osal_semp_t RasPi_rcv_sync;

static void uart_RasPi_irq(void)
{
    unsigned char value;
    if (__HAL_UART_GET_FLAG(&uart_RasPi, UART_FLAG_RXNE) != RESET)
    {
        value = (uint8_t)(uart_RasPi.Instance->RDR & 0x00FF);
        RasPi_rcv_data[strlen(RasPi_rcv_data)] = value;
        if (value == '2')
            (void)memset(RasPi_rcv_data, 0, 64);
        if (value == '3')
            LOS_SemPost(RasPi_rcv_sync);
    }
    else if (__HAL_UART_GET_FLAG(&uart_RasPi, UART_FLAG_IDLE) != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&uart_RasPi);
    }
}

void RasPi_uart_init(int baud)
{
    uart_RasPi.Instance = s_pUSART;
    uart_RasPi.Init.BaudRate = baud;
    uart_RasPi.Init.WordLength = UART_WORDLENGTH_8B;
    uart_RasPi.Init.StopBits = UART_STOPBITS_1;
    uart_RasPi.Init.Parity = UART_PARITY_NONE;
    uart_RasPi.Init.Mode = UART_MODE_TX_RX;
    uart_RasPi.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart_RasPi.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&uart_RasPi) != HAL_OK)
    {
        return;
    }
    LOS_HwiCreate(s_uwIRQn, 1, 0, uart_RasPi_irq, 0);
    //__HAL_UART_ENABLE_IT(&uart_RasPi, UART_IT_IDLE);
    __HAL_UART_ENABLE_IT(&uart_RasPi, UART_IT_RXNE);

    // extern UINT32 osSemCreate(UINT16 usCount, UINT16 usMaxCount, UINT32 * puwSemHandle);
    // osSemCreate(0, 64, (UINT32 *)&RasPi_rcv_sync);
    s_uart_init = true;
}

void RasPi_request(void)
{
    HAL_UART_Transmit(&uart_RasPi, "1", 1, 0xffff);
}
