#ifndef __EMW3080_H
#define __EMW3080_H

#define CONFIG_EMW3080_SSID         "Terabits_2.4G" //"Saxon"
#define CONFIG_EMW3080_PSW          "terabits"      //"abcd1234"
// 设备ID
// 5f3e791a5d28ab02bd85ce95_dev01
// 设备密钥
// 12345678

// clientId:
// 5f3e791a5d28ab02bd85ce95_dev01_0_0_2020082021
// username:
// 5f3e791a5d28ab02bd85ce95_dev01
// password:
// b97bc3a1c878dcc1d9cb7b7c8f232557e069b40fb4ebf218db52c09718084027

#define MQTT_DEVICE_ID              "5f3e791a5d28ab02bd85ce95_dev01"
#define MQTT_CLIENT_ID              "5f3e791a5d28ab02bd85ce95_dev01_0_0_2020082021"
#define MQTT_PASSWORD               "b97bc3a1c878dcc1d9cb7b7c8f232557e069b40fb4ebf218db52c09718084027"            
#define MQTT_SOCKET                 "iot-mqtts.cn-north-4.myhuaweicloud.com,1883"


extern char emw3080_rcv_data[1024];
extern osal_semp_t mqtt_rcv_sync;

bool_t emw3080_wifi_init(void);
bool_t emw3080_ntp(uint8_t* year, uint8_t* month, uint8_t* day, uint8_t* hour, uint8_t* minute, uint8_t* second);
bool_t emw3080_mqtt_init(void);
bool_t emw3080_publish(const char* payload);
#endif
