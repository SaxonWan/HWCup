#include <dobot.h>

void dobot_init(void)
{
    MX_USART3_UART_Init();
    SetPTPCoordinateParams(&gPTPCoordinateParams);
    SetPTPCommonParams(&gPTPCommonParams);
}

void grip_ChopSticks(uint8_t num)
{
	PTS *target = (PTS*)&ChopSticks2;
	if(num == 2)
		target = (PTS*)&ChopSticks1;

    //移动到筷子上方
    SetPTPCmd(&target->SetPoint);
    osal_task_sleep(MID_INT_TIME);

    //进入抓取位置
    SetPTPCmd(&target->GetPoint);
    osal_task_sleep(SHORT_INT_TIME);

    //抓取
    CtrEndEffectorGripper(engage, hold);
    osal_task_sleep(MID_INT_TIME);

    //取出筷子
    SetPTPCmd(&target->OutPoint);
    osal_task_sleep(MID_INT_TIME);

    //移动到泡面上方
    SetPTPCmd(&ChopSticksDes);
    osal_task_sleep(MID_INT_TIME);

    //释放
    CtrEndEffectorGripper(engage, release);
    osal_task_sleep(LONG_INT_TIME);

    //回到初始位置
    SetPTPCmd(&Idle);
    osal_task_sleep(MID_INT_TIME);

    //关闭气泵
    CtrEndEffectorGripper(idle, release);
}

void grip_RedSauce(uint8_t num)
{
    PTS *target = (PTS*)&RedSauce2;
	if(num == 2) 
		target = (PTS*)&RedSauce1;
    
    //移动到红色上方
    SetPTPCmd(&target->SetPoint);
    osal_task_sleep(MID_INT_TIME);
    
    //进入抓取位置
    SetPTPCmd(&target->GetPoint);
    osal_task_sleep(SHORT_INT_TIME);

    //抓取
    CtrEndEffectorGripper(engage, hold);
    osal_task_sleep(MID_INT_TIME);

    ///取出红色
    SetPTPCmd(&target->OutPoint);
    osal_task_sleep(MID_INT_TIME);

    //移动到泡面上方
    SetPTPCmd(&SauceDes);
    osal_task_sleep(MID_INT_TIME);

    //释放
    CtrEndEffectorGripper(engage, release);
    osal_task_sleep(LONG_INT_TIME);

    //回到初始位置
    SetPTPCmd(&Idle);
    osal_task_sleep(MID_INT_TIME);

    //关闭气泵
    CtrEndEffectorGripper(idle, release);
}

void grip_GreenSauce(uint8_t num)
{
    PTS *target = (PTS*)&GreenSauce2;
	if(num == 2) 
		target = (PTS*)&GreenSauce1;
    
    //移动到绿色上方
    SetPTPCmd(&target->SetPoint);
    osal_task_sleep(MID_INT_TIME);

    //进入抓取位置
    SetPTPCmd(&target->GetPoint);
    osal_task_sleep(SHORT_INT_TIME);

    //抓取
    CtrEndEffectorGripper(engage, hold);
    osal_task_sleep(MID_INT_TIME);

    //取出绿色
    SetPTPCmd(&target->OutPoint);
    osal_task_sleep(MID_INT_TIME);

    //移动到泡面上方
    SetPTPCmd(&SauceDes);
    osal_task_sleep(MID_INT_TIME);

    //释放
    CtrEndEffectorGripper(engage, release);
    osal_task_sleep(LONG_INT_TIME);

    //回到初始位置
    SetPTPCmd(&Idle);
    osal_task_sleep(MID_INT_TIME);

    //关闭气泵
    CtrEndEffectorGripper(idle, release);
}