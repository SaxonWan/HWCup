#ifndef __DOBOT_CMD_H
#define __DOBOT_CMD_H

#include <stdint.h>

#define hold 	    1
#define release	    0
#define engage	    1
#define idle	    0

#pragma pack(push)
#pragma pack(1)

enum
{
    JUMP_XYZ,	//0
    MOVJ_XYZ,	//1
    MOVL_XYZ,	//2
    JUMP_ANGLE,
    MOVJ_ANGLE,
    MOVL_ANGLE,
    MOVJ_INC,
    MOVL_INC,
};

typedef struct tagPTPCoordinateParams {
    float xyzVelocity;
    float rVelocity;
    float xyzAcceleration;
    float rAcceleration;
}PTPCoordinateParams;

typedef struct tagPTPCommonParams {
    float velocityRatio;
    float accelerationRatio;
}PTPCommonParams;

typedef struct tagPTPCmd {
uint8_t ptpMode;
    float x;
    float y;
    float z;
    float r;
}PTPCmd;

#pragma pack(pop)

void SetPTPCoordinateParams(const PTPCoordinateParams *ptpCoordinateParams);
void SetPTPCommonParams(const PTPCommonParams *ptpCommonParams);
void SetPTPCmd(const PTPCmd *ptpCmd);
void CtrEndEffectorGripper(uint8_t control, uint8_t grip);

#endif
