#include "sensor_task.h"
#include "sensor_thread_state.h"
#include "sensor_thread_queue.h"


void *sensor_task(void *arg0){


    //dbgEvent(SENSOR_TASK_BEGIN);

    //dbgEvent(SENSOR_TASK_LOOP);
    while(1){
        updateSensorState();
    }

}
