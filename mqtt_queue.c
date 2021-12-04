/*
 * mqtt_queue.c
 *
 *  Created on: Sep 29, 2021
 *      Author: Charles
 */


#include "mqtt_queue.h"
#include "debug.h"

#define QUEUE_SIZE 3


void create_mqtt_queue(){
    //create queue;
    mqtt_queue = xQueueCreate(QUEUE_SIZE, sizeof(MQTTMsg_t));
    if(mqtt_queue == NULL)
    {
        fatalError(MQTT_TASK_LOOP);//error
    }
}

void add_to_mqtt_queue(MQTTMsg_t *msg){
    //add to queue
    xQueueSendToBackFromISR(mqtt_queue, msg, 0);
}

void retrieve_from_mqtt_queue(MQTTMsg_t *msg){
    xQueueReceive(mqtt_queue, msg, portMAX_DELAY);
}
