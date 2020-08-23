#include <user_main.h>

char emw3080_rcv_data[1024];
//树莓派通讯用数据
char RasPi_rcv_byte;
char RasPi_rcv_data[64];
osal_semp_t RasPi_rcv_sync;

osal_semp_t mqtt_rcv_sync;

osal_semp_t report_sync;

t_status status;

static int app_report_task_entry()
{
    char rawstr[64];

    emw3080_wifi_init();
    emw3080_mqtt_init();
    while (1)
    {
        if (osal_semp_pend(report_sync, cn_osal_timeout_forever))
        {
            char *cjson_str = NULL;
            cJSON *root = cJSON_CreateObject();
            cJSON *item = cJSON_CreateObject();
            cJSON *properties = cJSON_CreateObject();
            cJSON *services = cJSON_CreateArray();

            (void)memset(rawstr, 0, 64);
            (void)snprintf(rawstr, 64, "%d", status.id);
            cJSON_AddItemToObject(properties, "id", cJSON_CreateRaw(rawstr));

            (void)memset(rawstr, 0, 64);
            (void)snprintf(rawstr, 64, "%d", status.result_red_sauces);
            cJSON_AddItemToObject(properties, "RedSauces", cJSON_CreateRaw(rawstr));

            (void)memset(rawstr, 0, 64);
            (void)snprintf(rawstr, 64, "%d", status.result_green_sauces);
            cJSON_AddItemToObject(properties, "GreenSauces", cJSON_CreateRaw(rawstr));

            (void)memset(rawstr, 0, 64);
            (void)snprintf(rawstr, 64, "%d", status.result_chop_sticks);
            cJSON_AddItemToObject(properties, "ChopSticks", cJSON_CreateRaw(rawstr));

            cJSON_AddItemToObject(item, "service_id", cJSON_CreateString("Result"));
            cJSON_AddItemToObject(item, "properties", properties);
            cJSON_AddItemToObject(services, "item", item);
            cJSON_AddItemToObject(root, "services", services);
            cjson_str = cJSON_PrintUnformatted(root);
            printf("\r\n[CJSON]%s\r\n", cjson_str);
            emw3080_publish(cjson_str);
            free(cjson_str);
            cJSON_Delete(root);
        }
    }
    return 0;
}

static int app_cmd_task_entry()
{
    while (1)
    {
        if (osal_semp_pend(mqtt_rcv_sync, cn_osal_timeout_forever))
        {
        }
    }
    return 0;
}

static void infrared_interrupt_entry()
{
    printf("\r\n[IR]triggered\r\n");
    __HAL_GPIO_EXTI_CLEAR_FLAG(IR_INT_Pin);
    osal_semp_post(status.conveyor_task_sync);
}

void task_complete(void)
{
    printf("[ID]%d\r\n", status.id);
    status.id++;
    status.result_red_sauces = -1;
    status.result_green_sauces = -1;
    status.result_chop_sticks = -1;
}

static int conveyor_task_entry()
{
    osal_semp_create(&status.conveyor_task_sync, 1, 0);
    conveyor_init();
    start_conveyor();
    osal_int_connect(IR_INT_EXTI_IRQn, 1, 0, infrared_interrupt_entry, NULL);
    while (1)
    {
        if (osal_semp_pend(status.conveyor_task_sync, cn_osal_timeout_forever))
        {
            printf("[CONVEYOR]task Start\r\n");
            osal_task_sleep(50);
            if (stop_conveyor())
                RasPi_request();
            else
                osal_semp_post(status.dobot_task_sync);
        }
    }
}

static int RasPi_cmd_task_entry()
{
    osal_semp_create(&RasPi_rcv_sync, 1, 0);
    RasPi_uart_init(115200);
    while (1)
    {
        if (osal_semp_pend(RasPi_rcv_sync, cn_osal_timeout_forever))
        {
            printf("[RPI]task Start\r\n");
            printf("[RPI][RCV]:%s\r\n", RasPi_rcv_data);
            status.result_red_sauces = RasPi_rcv_data[0] - '0';
            status.result_green_sauces = RasPi_rcv_data[1] - '0';
            status.result_chop_sticks = RasPi_rcv_data[2] - '0';
            printf("[RPI][RESULT]:RedSauces-%d,GreenSauces-%d,ChopSticks-%d\r\n", status.result_red_sauces, status.result_green_sauces, status.result_chop_sticks);
            osal_semp_post(report_sync);
            start_conveyor();
        }
    }
    return 0;
}

static int dobot_task_entry()
{
    dobot_init();
    osal_semp_create(&status.dobot_task_sync, 1, 0);
    while (1)
    {
        if (osal_semp_pend(status.dobot_task_sync, cn_osal_timeout_forever))
        {
            printf("[DOBOT]task Start\r\n");
            if ((status.result_red_sauces == 0) && osal_semp_pend(status.sync_red_sauces, cn_osal_timeout_forever))
            {
                grip_RedSauce(status.rest_red_sauces);
                status.rest_red_sauces--;
            }
            if ((status.result_green_sauces == 0) && osal_semp_pend(status.sync_green_sauces, cn_osal_timeout_forever))
            {
                grip_GreenSauce(status.rest_green_sauces);
                status.rest_green_sauces--;
            }
            if ((status.result_chop_sticks == 0) && osal_semp_pend(status.sync_chop_sticks, cn_osal_timeout_forever))
            {
                grip_ChopSticks(status.rest_chop_sticks);
                status.rest_chop_sticks--;
            }
            task_complete();
            start_conveyor();
        }
    }
    return 0;
}

//F2按键中断控制物料补齐
static void load_supply_entry()
{
    printf("\r\n[F2]Reload\r\n");
    __HAL_GPIO_EXTI_CLEAR_FLAG(KEY2_Pin);
    for (int i = 0; i < 2; i++)
    {
        if (status.rest_red_sauces == i)
        {
            osal_semp_post(status.sync_red_sauces);
            status.rest_red_sauces++;
        }
        if (status.rest_green_sauces == i)
        {
            osal_semp_post(status.sync_green_sauces);
            status.rest_green_sauces++;
        }
        if (status.rest_chop_sticks == i)
        {
            osal_semp_post(status.sync_chop_sticks);
            status.rest_chop_sticks++;
        }
    }
}

int standard_app_demo_main()
{
    osal_semp_create(&mqtt_rcv_sync, 1, 0);
    osal_semp_create(&report_sync, 1, 0);

    (void)memset(&status, 0, sizeof(status));
    status.id = 1;
    status.rest_red_sauces = 2;
    status.rest_green_sauces = 2;
    status.rest_chop_sticks = 2;
    osal_semp_create(&status.sync_red_sauces, 2, 2);
    osal_semp_create(&status.sync_green_sauces, 2, 2);
    osal_semp_create(&status.sync_chop_sticks, 2, 2);

    osal_int_connect(EXTI3_IRQn, 4, 0, load_supply_entry, NULL);

    osal_task_create("report_task", app_report_task_entry, NULL, 0x1000, NULL, 11);
    // osal_task_create("cmd_task", app_cmd_task_entry, NULL, 0x600, NULL, 12);
    osal_task_create("resp_task", RasPi_cmd_task_entry, NULL, 0x400, NULL, 13);
    osal_task_create("dobot_task", dobot_task_entry, NULL, 0x400, NULL, 13);
    osal_task_create("conveyor_task", conveyor_task_entry, NULL, 0x400, NULL, 9);
    return 0;
}
