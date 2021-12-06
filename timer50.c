/*
 * timer50.c
 *
 *  Created on: Sep 9, 2021
 *      Author: vewake
 */
#include "timer50.h"


void callback50(Timer_Handle myHandle, int_fast16_t status);

#define THREADSTACKSIZE   (768)

void start50(){

    //setup timer
    Timer_Handle timer1;
    Timer_Params params;

    Timer_Params_init(&params);
    params.period = 50000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = callback50;

    timer1 = Timer_open(CONFIG_TIMER_1, &params);

    if (timer1 == NULL) {
        /* Failed to initialized timer */
        fatalError(0x00);
    }

    if (Timer_start(timer1) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        fatalError(0x00);
    }
}

void callback50(Timer_Handle myHandle, int_fast16_t status){
    CONTMsg_t timer_message;
    timer_message.topic = timer;
    timer_message.message = CLAW_OPEN;

    add_to_control_queue(&timer_message);
}
