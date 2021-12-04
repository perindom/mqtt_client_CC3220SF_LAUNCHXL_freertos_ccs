/*
 * testRoverTask_state.c
 *
 *  Created on: Oct 13, 2021
 *      Author: Charles
 */
#include "testRoverTask_state.h"

void updateState(){
    //static UARTMessage_t s;

    static MQTTMsg_t testMsg;
    //static Callback_t c;
    //retrieveSensor(&c);

    //waitForTimer()

    switch(state){

    case PUB1 :
        testMsg.topic = Topic_DC;
        add_to_mqtt_queue(&testMsg);
        state = PUB2;
        break;

    case PUB2 :
        testMsg.topic = Topic_DC;
        add_to_mqtt_queue(&testMsg);
        state = PUB3;
        break;

    case PUB3 :
        testMsg.topic = Topic_DC;
        add_to_mqtt_queue(&testMsg);
        state = PUB4;
        break;
    case PUB4 :
        testMsg.topic = Topic_DC;
        add_to_mqtt_queue(&testMsg);
        state = PUB5;
        break;
    case PUB5 :
        testMsg.topic = Topic_DC;
        add_to_mqtt_queue(&testMsg);
        state = PUB6;
        break;
    case PUB6 :
        testMsg.topic = Topic_DC;
        add_to_mqtt_queue(&testMsg);
        state = PUB7;
        break;

    case PUB7 :
        testMsg.topic = Topic_DC;
        add_to_mqtt_queue(&testMsg);
        state = PUB8;
        break;
    case PUB8 :
        testMsg.topic = Topic_DC;
        add_to_mqtt_queue(&testMsg);
        state = PUB9;
        break;
    case PUB9 :
        testMsg.topic = Topic_DC;
        add_to_mqtt_queue(&testMsg);
        state = PUB10;
        break;
    case PUB10 :
        testMsg.topic = Topic_DC;
        add_to_mqtt_queue(&testMsg);
        state = PUB1;
        break;
    default :
        state = PUB1;
    }
}

