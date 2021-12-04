/*sensor_thread_state.h*/

#ifndef SENSOR_THREAD_STATE_H_
#define SENSOR_THREAD_STATE_H_

#include "sensor_thread_queue.h"
#include "debug.h"

void updateSensorState();

enum states{INIT_AVERAGE, UPDATE_AVERAGE};

static int state = INIT_AVERAGE;

static int sensorTotal = 0;
static int sensorCount = 0;

#endif
