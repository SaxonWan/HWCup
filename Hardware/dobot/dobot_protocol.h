#ifndef __DOBOT_PROTOCOL_H
#define __DOBOT_PROTOCOL_H

#define SYNC_BYTE   0xAA

#define MAX_PAYLOAD_SIZE (SYNC_BYTE - 1)                                // Minus 1 for not larger than SYNC_BYTE

#pragma pack(push)
#pragma pack(1)

typedef struct tagMessage {
    uint8_t id;
    uint8_t paramsLen;
    uint8_t params[MAX_PAYLOAD_SIZE - 2];
}Message;

#pragma pack(pop)

#endif
