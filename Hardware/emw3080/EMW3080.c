#include <string.h>
#include <at.h>
#include <EMW3080.h>
#include <osal.h>

#define emw3080_cmd_timeout (20 * 1000)
#define emw3080_cmd_buflen 512
#define emw3080_cmd_index "\r\n+MQTTRECV:0"

static bool_t emw3080_atcmd(const char *cmd, const char *index)
{
    int ret = 0;
    ret = at_command((unsigned char *)cmd, strlen(cmd), index, NULL, 0, emw3080_cmd_timeout);
    if (ret >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool_t emw3080_atcmd_response(const char *cmd, const char *index, char *buf, int len)
{
    int ret = 0;
    ret = at_command((unsigned char *)cmd, strlen(cmd), index, (char *)buf, len, emw3080_cmd_timeout);
    if (ret >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool_t emw3080_atcmd_ok(const char *cmd)
{
    bool_t ret;
    ret = emw3080_atcmd(cmd, "OK");
    return ret;
}

static bool_t emw3080_wifi_connect(void)
{
    bool_t ret;
    char cmd[emw3080_cmd_buflen];
    (void)memset(cmd, 0, emw3080_cmd_buflen);
    (void)snprintf(cmd, emw3080_cmd_buflen, "AT+WJAP=%s,%s\r", CONFIG_EMW3080_SSID, CONFIG_EMW3080_PSW);
    ret = emw3080_atcmd(cmd, "+WEVENT:STATION_UP");
    return ret;
}

static bool_t emw3080_set_auth(void)
{
    bool_t ret;
    char cmd[emw3080_cmd_buflen];
    (void)memset(cmd, 0, emw3080_cmd_buflen);
    (void)snprintf(cmd, emw3080_cmd_buflen, "AT+MQTTAUTH=%s,%s\r", MQTT_DEVICE_ID, MQTT_PASSWORD);
    ret = emw3080_atcmd_ok(cmd);
    return ret;
}

static bool_t emw3080_set_cid(void)
{
    bool_t ret;
    char cmd[emw3080_cmd_buflen];
    (void)memset(cmd, 0, emw3080_cmd_buflen);
    (void)snprintf(cmd, emw3080_cmd_buflen, "AT+MQTTCID=%s\r", MQTT_CLIENT_ID);
    ret = emw3080_atcmd_ok(cmd);
    return ret;
}

static bool_t emw3080_set_sock(void)
{
    bool_t ret;
    char cmd[emw3080_cmd_buflen];
    (void)memset(cmd, 0, emw3080_cmd_buflen);
    (void)snprintf(cmd, emw3080_cmd_buflen, "AT+MQTTSOCK=%s\r", MQTT_SOCKET);
    ret = emw3080_atcmd_ok(cmd);
    return ret;
}

static bool_t emw3080_set_pub(void)
{
    bool_t ret;
    char cmd[emw3080_cmd_buflen];
    (void)memset(cmd, 0, emw3080_cmd_buflen);
    (void)snprintf(cmd, emw3080_cmd_buflen, "AT+MQTTPUB=$oc/devices/%s/sys/properties/report,1\r", MQTT_DEVICE_ID);
    ret = emw3080_atcmd_ok(cmd);
    return ret;
}

static bool_t emw3080_sub_command(void)
{
    bool_t ret;
    char cmd[emw3080_cmd_buflen];
    (void)memset(cmd, 0, emw3080_cmd_buflen);
    (void)snprintf(cmd, emw3080_cmd_buflen, "AT+MQTTSUB=0,$oc/devices/%s/sys/commands/#,0\r", MQTT_DEVICE_ID);
    ret = emw3080_atcmd(cmd, "+MQTTEVENT:0,SUBSCRIBE,SUCCESS");
    return ret;
}

int emw3080_rcvdeal(void *args, void *data, size_t datalen)
{
    int ret = 0;
    char *rcvdata = data;
    char *json_string;
    if (datalen < strlen(emw3080_cmd_index))
    {
        LINK_LOG_DEBUG("%s:invalid frame:%d byte:%s\n\r", __FUNCTION__, datalen, (char *)rcvdata);
        return ret;
    }
    json_string = strchr(rcvdata, '{');
    printf("[RCV][JSON]%s\r\n", json_string);
    if (json_string == NULL)
        return ret;
    (void)memset(emw3080_rcv_data, 0, 1024);
    strcpy(emw3080_rcv_data, json_string);
    ret = osal_semp_post(mqtt_rcv_sync);
    return ret;
}

bool_t emw3080_wifi_init(void)
{
    emw3080_atcmd_ok("AT+FACTORY\r");
    osal_task_sleep(1000 * 2);
    emw3080_atcmd_ok("AT\r");
    emw3080_atcmd_ok("AT+UARTE=OFF\r");
    emw3080_atcmd_ok("AT+WEVENT=ON\r");
    return (emw3080_wifi_connect());
}

bool_t emw3080_ntp(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second)
{
    int i = 0;
    bool_t ret;
    char buf[emw3080_cmd_buflen];
    (void)memset(buf, 0, emw3080_cmd_buflen);
    emw3080_atcmd_ok("AT+SNTPCFG=+8,ntp.ntsc.ac.cn\r");
    ret = emw3080_atcmd_response("AT+SNTPTIME\r", "OK", buf, emw3080_cmd_buflen);
    if (!ret)
        return ret;
    for (i = 0; i < emw3080_cmd_buflen; i++)
        if (buf[i] == ':')
            break;
    for (int j = 0; j < emw3080_cmd_buflen; j++)
        if (buf[j] >= '0')
            buf[j] -= '0';
    i += 3;
    *year = buf[i] * 10 + buf[i + 1];
    i += 3;
    *month = buf[i] * 10 + buf[i + 1];
    i += 3;
    *day = buf[i] * 10 + buf[i + 1];
    i += 3;
    *hour = buf[i] * 10 + buf[i + 1];
    i += 3;
    *minute = buf[i] * 10 + buf[i + 1];
    i += 3;
    *second = buf[i] * 10 + buf[i + 1];
    return ret;
}

bool_t emw3080_mqtt_init(void)
{
    bool_t ret;
    emw3080_set_auth();
    emw3080_set_cid();
    emw3080_set_sock();
    emw3080_atcmd_ok("AT+MQTTCAVERIFY=OFF,OFF\r");
    emw3080_atcmd_ok("AT+MQTTSSL=OFF\r");
    emw3080_atcmd_ok("AT+MQTTRECONN=ON\r");
    emw3080_atcmd_ok("AT+MQTTAUTOSTART=OFF\r");
    emw3080_atcmd_ok("AT+MQTTKEEPALIVE=120\r");
    emw3080_atcmd_ok("AT+MQTTEVENT=ON\r");
    ret = emw3080_atcmd("AT+MQTTSTART\r", "+MQTTEVENT:CONNECT,SUCCESS");
    if (!ret)
        return ret;
    emw3080_set_pub();
    emw3080_sub_command();
    at_oobregister("emw3080rcv", emw3080_cmd_index, strlen(emw3080_cmd_index), emw3080_rcvdeal, NULL);
    return ret;
}

bool_t emw3080_publish(const char *payload)
{
    bool_t ret;
    char cmd[emw3080_cmd_buflen];
    (void)memset(cmd, 0, emw3080_cmd_buflen);
    (void)snprintf(cmd, emw3080_cmd_buflen, "AT+MQTTSEND=%d\r", strlen(payload));
    ret = emw3080_atcmd(cmd, ">");
    if (ret)
        ret = emw3080_atcmd(payload, "+MQTTEVENT:PUBLISH,SUCCESS");
    return ret;
}
