/*
 * mqtt_thread.h
 *
 *  Created on: Sep 29, 2021
 *      Author: Charles
 */

#ifndef MQTT_QUEUE_H_
#define MQTT_QUEUE_H_


#include "FreeRTOS.h"
#include "queue.h"

typedef struct test_data_format {
    int DA;
    int DS;
    int CA;
    int CS;
    int VA;
    int VS;
} test_data_format;

typedef struct MQTTMsg{
    int topic;
    test_data_format message;
} MQTTMsg_t;

enum{
    Topic_DC,
    Topic_CV,
    Topic_VD
};

void create_mqtt_queue();

void add_to_mqtt_queue(MQTTMsg_t *msg);

void retrieve_from_mqtt_queue(MQTTMsg_t *msg);

static QueueHandle_t mqtt_queue;


#endif /* MQTT_QUEUE_H_ */
