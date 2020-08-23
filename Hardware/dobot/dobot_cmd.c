#include <stdio.h>
#include <string.h>
#include <dobot_cmd.h>
#include <dobot_protocol.h>
#include <usart.h>

#define TX_BUFFER_SIZE 1024
static uint8_t txbuffer[TX_BUFFER_SIZE];
static uint8_t txlen;

static void SendCommand(const Message *message);

void SetPTPCoordinateParams(const PTPCoordinateParams *ptpCoordinateParams)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = 81;
    tempMessage.paramsLen = sizeof(PTPCoordinateParams);
    memcpy(tempMessage.params, (uint8_t *)ptpCoordinateParams, tempMessage.paramsLen);
    SendCommand(&tempMessage);
}

void SetPTPCommonParams(const PTPCommonParams *ptpCommonParams)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = 83;
    tempMessage.paramsLen = sizeof(PTPCommonParams);
    memcpy(tempMessage.params, (uint8_t *)ptpCommonParams, tempMessage.paramsLen);
    SendCommand(&tempMessage);
}

void SetPTPCmd(const PTPCmd *ptpCmd)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = 84;
    tempMessage.paramsLen = sizeof(PTPCmd);
    memcpy(tempMessage.params, (uint8_t *)ptpCmd, tempMessage.paramsLen);
    SendCommand(&tempMessage);
}

void CtrEndEffectorGripper(uint8_t control, uint8_t grip)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = 63;
    tempMessage.paramsLen = 2;
    tempMessage.params[0] = control;
    tempMessage.params[1] = grip;
    SendCommand(&tempMessage);
}

static void SendCommand(const Message *message)
{
    memset(txbuffer, 0, TX_BUFFER_SIZE);
    txlen = 0;

    uint8_t checksum = 0x03;
    checksum += message->id;
    txbuffer[txlen++] = SYNC_BYTE;
    txbuffer[txlen++] = SYNC_BYTE;
    txbuffer[txlen++] = message->paramsLen + 2;
    txbuffer[txlen++] = message->id;
    txbuffer[txlen++] = 0x03;
    for (uint8_t i = 0; i < message->paramsLen; i++)
    {
        txbuffer[txlen++] = message->params[i];
        checksum += message->params[i];
    }
	checksum = (uint8_t)(0 - checksum);
    txbuffer[txlen++] = checksum;
    HAL_UART_Transmit(&huart3, txbuffer, txlen, 0xffff);
}
