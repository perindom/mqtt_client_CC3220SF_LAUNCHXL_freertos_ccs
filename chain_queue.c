//
// Created by Domin on 10/19/2021.
//

#include "chain_queue.h"
#include "debug.h"

#define QUEUE_SIZE 3


void create_chain_queue(){
    //create queue;
    chain_queue = xQueueCreate(QUEUE_SIZE, sizeof(chain_message_t));
    if(chain_queue == NULL)
    {
        fatalError(MQTT_TASK_LOOP);//error
    }
}

void add_to_chain_queue(chain_message_t *msg){
    //add to queue
    BaseType_t successFullAdd = xQueueSendToBackFromISR(chain_queue, msg, 0);
    if(successFullAdd != pdTRUE){
        fatalError(CHAIN_QUEUE_ADD);

    }
}

void retreive_chain_queue(chain_message_t *msg){
    xQueueReceive(chain_queue, msg, portMAX_DELAY);
}
