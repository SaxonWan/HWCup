#ifndef __DOBOT_H
#define __DOBOT_H

#include <main.h>
#include <dobot_cmd.h>

#define SHORT_INT_TIME 1000 * 1.5
#define MID_INT_TIME 1000 * 2
#define LONG_INT_TIME 1000 * 3

typedef struct{
    PTPCmd SetPoint;
    PTPCmd GetPoint;
    PTPCmd OutPoint;
}PTS;

static const PTS ChopSticks1 = {
    .SetPoint = {
        .ptpMode = MOVJ_XYZ,
        .x = 187.2871,
        .y = 20.0920,
        .z = 20.7805,
        .r = -31.4446,
    },
    .GetPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 187.2873,
        .y = 20.0920,
        .z = -27.6757,
        .r = -31.4446,
    },
    .OutPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 187.2870,
        .y = 20.0920,
        .z = 80.6364,
        .r = -31.4446,
    },
};

static const PTS ChopSticks2 = {
    .SetPoint = {
        .ptpMode = MOVJ_XYZ,
        .x = 191.7784,
        .y = -35.3899,
        .z = 4.6727,
        .r = -29.6531,
    },
    .GetPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 191.7785,
        .y = -35.3899,
        .z = -29.2397,
        .r = -29.6531,
    },
    .OutPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 191.7792,
        .y = -35.3900,
        .z = 108.7605,
        .r = -29.6531,
    },
};

static const PTPCmd ChopSticksDes = {
    .ptpMode = MOVJ_XYZ,
    .x = 179.9614,
    .y = -218.9740,
    .z = 122.1701,
    .r = -29.2861,
};

static const PTS RedSauce1 = {
    .SetPoint = {
        .ptpMode = MOVJ_XYZ,
        .x = 269.7323,
        .y = 116.4751,
        .z = 64.8922,
        .r = 64.2978,
    },
    .GetPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 269.7351,
        .y = 116.4763,
        .z = 22.1959,
        .r = 64.2978,
    },
    .OutPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 269.7382,
        .y = 116.4776,
        .z = 131.5238,
        .r = 64.2978,
    },
};

static const PTS RedSauce2 = {
    .SetPoint = {
        .ptpMode = MOVJ_XYZ,
        .x = 225.4056,
        .y = 117.7000,
        .z = 64.8924,
        .r = 64.2978,
    },
    .GetPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 225.4055,
        .y = 117.7000,
        .z = 22.6763,
        .r = 64.2978,
    },
    .OutPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 225.4062,
        .y = 117.7003,
        .z = 136.5081,
        .r = 64.2978,
    },
};

static const PTPCmd SauceDes = {
    .ptpMode = MOVJ_XYZ,
    .x = 173.8375,
    .y = -193.3654,
    .z = 159.0950,
    .r = 11.1381,
};

static const PTS GreenSauce1 = {
    .SetPoint = {
        .ptpMode = MOVJ_XYZ,
        .x = 169.2775,
        .y = 102.5537,
        .z = 38.4343,
        .r = 59.0402,
    },
    .GetPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 169.2768,
        .y = 105.2174,
        .z = 22.0191,
        .r = 59.0402,
    },
    .OutPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 169.2744,
        .y = 105.2159,
        .z = 112.1156,
        .r = 59.0402,
    },
};

static const PTS GreenSauce2 = {
    .SetPoint = {
        .ptpMode = MOVJ_XYZ,
        .x = 136.7574,
        .y = 103.7061,
        .z = 41.8665,
        .r = 59.0402,
    },
    .GetPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 136.7571,
        .y = 103.7059,
        .z = 22.6903,
        .r = 59.0402,
    },
    .OutPoint = {
        .ptpMode = MOVL_XYZ,
        .x = 169.2744,
        .y = 105.2159,
        .z = 112.1156,
        .r = 59.0402,
    },
};

static const PTPCoordinateParams gPTPCoordinateParams = {
    .xyzVelocity = 100,
    .rVelocity = 100,
    .xyzAcceleration = 80,
    .rAcceleration = 80,
};

static const PTPCommonParams gPTPCommonParams = {
    .velocityRatio = 50,
    .accelerationRatio = 50,
};

static const PTPCmd Idle = {
	.ptpMode = MOVJ_XYZ,
	.x = 206.9603,
	.y = 53.9545,
	.z = 51.0530,
	.r = 56.1713,
};

void dobot_init(void);
void grip_ChopSticks(uint8_t num);
void grip_RedSauce(uint8_t num);
void grip_GreenSauce(uint8_t num);

#endif
