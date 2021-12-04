//
// Created by Domin on 10/19/2021.
//

#include "publish_queue.h"
#include "debug.h"

#define QUEUE_SIZE 3


void create_publish_queue(){
    //create queue;
    publish_queue = xQueueCreate(QUEUE_SIZE, sizeof(publish_message_t));
    if(publish_queue == NULL)
    {
        fatalError(MQTT_TASK_LOOP);//error
    }
}

void add_to_publish_queue(publish_message_t *msg){
    //add to queue

    BaseType_t successFullAdd = xQueueSendToBackFromISR(publish_queue, msg, 0);
//    if(successFullAdd != pdTRUE){
//        fatalError(PUBLISH_QUEUE_ADD);
//
//    }
}

void retrieve_publish_queue(publish_message_t *msg){
    xQueueReceive(publish_queue, msg, portMAX_DELAY);
}
