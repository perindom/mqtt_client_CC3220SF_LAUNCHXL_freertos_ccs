/*sensor_thread_state.c*/

#include "sensor_thread_state.h"
#include "sensor_thread_queue.h"
#include "publish_queue.h"
#include <stdio.h>


void updateSensorState(){
    //static UARTMessage_t s;
    static publish_message_t toSend;
    static Callback_t c;
    retrieveSensor(&c);

    switch(state){

    case INIT_AVERAGE :
        sensorTotal = 0;
        sensorCount = 0;
        if(c.type == 1){
            state = UPDATE_AVERAGE;
        }
        break;

    case UPDATE_AVERAGE :
        if(c.type == 0){
            sensorTotal = sensorTotal + c.value;
            sensorCount = sensorCount + 1;

            snprintf(toSend.json_string, MAX_STR_LEN, "{ \"sensor count\": %d, \"Sensor\": %d }", sensorCount, c.value);//turn to json
            dbgEvent(SENSOR_TASK_BEFORE_SEND_QUEUE);
            snprintf(toSend.topic, TOPIC_STR_LEN, "Sensor");
            add_to_publish_queue(&toSend);//publish queue
            dbgEvent(SENSOR_TASK_AFTER_SEND_QUEUE);
        }
        else{
            static int average;
            if(sensorCount == 0)
                average = 0;
            else
                average = sensorTotal/sensorCount;

            snprintf(toSend.json_string, MAX_STR_LEN, "{ \"Sensor Avg\": %d, \"Time\": %d }", average, c.value);
            dbgEvent(SENSOR_TASK_BEFORE_SEND_QUEUE);
            snprintf(toSend.topic, TOPIC_STR_LEN, "Average");
            add_to_publish_queue(&toSend);//publish queue
            dbgEvent(SENSOR_TASK_AFTER_SEND_QUEUE);
            state = INIT_AVERAGE;
        }
        break;
    default :
        state = INIT_AVERAGE;
    }
}
