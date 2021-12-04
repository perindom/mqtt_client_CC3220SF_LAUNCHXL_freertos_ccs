/*
 * mqtt_thread_state.h
 *
 *  Created on: Oct 11, 2021
 *      Author: Charles
 */

#ifndef MQTT_THREAD_STATE_H_
#define MQTT_THREAD_STATE_H_

#include "mqtt_queue.h"
#ifdef testmove
//#include "mqtt_task.h"
#include <mqtt_if.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <mqueue.h>

#include <ti/drivers/net/wifi/simplelink.h>
#include <ti/drivers/net/wifi/slnetifwifi.h>

#include <ti/drivers/SPI.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

#include <ti/net/mqtt/mqttclient.h>

#include "network_if.h"
#include "uart_term.h"
#include "mqtt_if.h"
#include "debug_if.h"
#include "debug.h"

#include "ti_drivers_config.h"
//#include "uart_thread_queue.h"
void updateState2();
void updateState();
void pushButtonPublishHandler(uint_least8_t index);
void pushButtonConnectionHandler(uint_least8_t index);
int detectLongPress();
void mqttSubscribe();
int WifiInit();


extern int32_t ti_net_SlNet_initConfig();

#define APPLICATION_NAME         "MQTT client"
#define APPLICATION_VERSION      "2.0.0"

#define SL_TASKSTACKSIZE            2048
#define SPAWN_TASK_PRIORITY         9

// un-comment this if you want to connect to an MQTT broker securely
//#define MQTT_SECURE_CLIENT

#define MQTT_MODULE_TASK_PRIORITY   2
#define MQTT_MODULE_TASK_STACK_SIZE 2048

#define MQTT_WILL_TOPIC             "jesus_cc32xx_will_topic"
#define MQTT_WILL_MSG               "will_msg_works"
#define MQTT_WILL_QOS               MQTT_QOS_0
#define MQTT_WILL_RETAIN            false

#define MQTT_CLIENT_PASSWORD        "_ofjpm-_vCP8"
#define MQTT_CLIENT_USERNAME        "pguezqig"
#define MQTT_CLIENT_KEEPALIVE       0
#define MQTT_CLIENT_CLEAN_CONNECT   true
#define MQTT_CLIENT_MQTT_V3_1       true
#define MQTT_CLIENT_BLOCKING_SEND   true

/*#ifndef MQTT_SECURE_CLIENT
#define MQTT_CONNECTION_FLAGS           MQTTCLIENT_NETCONN_URL
#define MQTT_CONNECTION_ADDRESS         "mqtt.eclipse.org"
#define MQTT_CONNECTION_PORT_NUMBER     1883*/
#ifndef MQTT_SECURE_CLIENT
#define MQTT_CONNECTION_FLAGS           MQTTCLIENT_NETCONN_URL
#define MQTT_CONNECTION_ADDRESS         "driver.cloudmqtt.com"
#define MQTT_CONNECTION_PORT_NUMBER     18645
#else
#define MQTT_CONNECTION_FLAGS           MQTTCLIENT_NETCONN_IP4 | MQTTCLIENT_NETCONN_SEC
#define MQTT_CONNECTION_ADDRESS         "192.168.178.67"
#define MQTT_CONNECTION_PORT_NUMBER     8883
#endif

enum APP_STATE{
    APP_MQTT_PUBLISH,
    APP_MQTT_CON_TOGGLE,
    APP_MQTT_DEINIT,
    APP_BTN_HANDLER
};
enum states{INIT_SPEED, UPDATE_SPEED, PUBLISH_SPEED};

static int state = INIT_SPEED;
#endif
//static int sensorTotal = 0;
//static int sensorCount = 0;




#endif /* MQTT_THREAD_STATE_H_ */
