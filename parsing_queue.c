/*
 * subscribe_queue.c
 *
 *  Created on: Oct 14, 2021
 *      Author: vewake
 */

#include <parsing_queue.h>
#define QUEUE_SIZE 3

static QueueHandle_t subscribeQueue;

void create_parsing_queue(){

    subscribeQueue = xQueueCreate(QUEUE_SIZE, sizeof(subscribe_struct));
    if(subscribeQueue == NULL)
    {
        //fatalError(UART_TASK_BEFORE_RETRIEVE_QUEUE);
    }
}

void addSubscribe(subscribe_struct *m){
    //add to queue
    //dbgEvent should wrap around this functions call, not take place in this function
    xQueueSendToBack(subscribeQueue, m, portMAX_DELAY);
}

void retrieveSubscribe(subscribe_struct *m){
    //block and return value from queue
    xQueueReceive(subscribeQueue, m, portMAX_DELAY);
}

