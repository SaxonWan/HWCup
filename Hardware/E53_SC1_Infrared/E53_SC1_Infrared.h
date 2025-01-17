/********************************************************************************
    * 文件名称 ：E53_SC1_Infrared.h
    * 作     者：LGS
    * 版     本：V1.0
    * 编写日期 ：2019-11-27
    * 功     能：E53_CS1扩展板增加人体红外传感器驱动
*********************************************************************************
    * 说    明 ：本例程配套小熊派开源社区开发板使用
    *
    * 淘     宝：https://shop336827451.taobao.com/
    * 论     坛：https://bbs.huaweicloud.com/forum/forum-734-1.html
    * 微信公众号：小熊派开源社区
*********************************************************************************/
#ifndef __E53_SC1_Infrared_H__
#define __E53_SC1_Infrared_H__
/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* 控制设备IO口定义 ------------------------------------------------------------*/

#define SC1_Light_Pin GPIO_PIN_9
#define SC1_Light_GPIO_Port GPIOB
#define SC1_Light_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

#define SC1_Infrared_Pin GPIO_PIN_9
#define SC1_Infrared_GPIO_Port GPIOC
#define SC1_Infrared_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

/* E53_IA1传感器数据类型定义 ------------------------------------------------------------*/
typedef struct
{
		float    Lux;							//光照强度
} E53_SC1_Data_TypeDef;

extern E53_SC1_Data_TypeDef E53_SC1_Data;


/* 寄存器宏定义 --------------------------------------------------------------------*/
#define I2C_OWN_ADDRESS                            0x0A

#define BH1750_Addr 0x46
#define BH1750_ON   0x01
#define BH1750_CON  0x10
#define BH1750_ONE  0x20
#define BH1750_RSET 0x07

void Init_E53_SC1(void);
void E53_SC1_Read_Data(void);
void Init_E53_SC1_Infrared(void);

#endif











