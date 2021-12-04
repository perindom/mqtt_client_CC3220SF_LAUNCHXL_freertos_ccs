#include <control_queue.h>
#include "debug.h"

#define QUEUE_SIZE 5


void create_control_queue(){
    //create queue;
    control_queue = xQueueCreate(QUEUE_SIZE, sizeof(CONTMsg_t));
    if(control_queue == NULL)
    {
        fatalError(MQTT_TASK_LOOP);//error
    }
}

void add_to_control_queue(CONTMsg_t *msg){
    //add to queue
    xQueueSendToBackFromISR(control_queue, msg, 0);
}

void retrieve_from_control_queue(CONTMsg_t *msg){
    xQueueReceive(control_queue, msg, portMAX_DELAY);
}
