/*sensor_thread_queue.c*/

#include "sensor_thread_queue.h"
#include "debug.h"

#define QUEUE_SIZE 3


void create_sensor_queue(){
    //create queue;
    sensorQueue = xQueueCreate(QUEUE_SIZE, sizeof(Callback_t));
    if(sensorQueue == NULL)
    {
        //fatalError(SENSOR_TASK_LOOP);//error
    }
}

void addSensor(Callback_t *c){
    //add to queue
    BaseType_t successFullAdd = xQueueSendToBackFromISR(sensorQueue, c, 0);
//    if(successFullAdd != pdTRUE){
//        fatalError(SENSOR_QUEUE_ADD);
//    }
}

void retrieveSensor(Callback_t *c){
    xQueueReceive(sensorQueue, c, portMAX_DELAY);
}
