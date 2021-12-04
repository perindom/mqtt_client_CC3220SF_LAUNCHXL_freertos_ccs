/*sensor_thread_queue.h*/

#ifndef SENSOR_THREAD_QUEUE_H_
#define SENSOR_THREAD_QUEUE_H_

#include "FreeRTOS.h"
#include "queue.h"

typedef struct Callback{
    int value;//value of distance in mm or time elapsed in microseconds
    int type;//0 for timer70 and 1 for timer500
} Callback_t;

void create_sensor_queue();

void addSensor(Callback_t *c);

void retrieveSensor(Callback_t *c);

static QueueHandle_t sensorQueue;

#endif
