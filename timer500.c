/*
 * timer500.c
 *
 *  Created on: Sep 9, 2021
 *      Author: vewake
 */

#include "timer500.h"
#include "debug.h"
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include "ti_drivers_config.h"
#include "sensor_thread_queue.h"
#include <stddef.h>

static int last_tick_count;

void callback500(Timer_Handle myHandle, int_fast16_t status);

void start500(){
    dbgEvent(TIMER_500_CALLBACK_BEGIN);

    //setup timer
    Timer_Handle timer2;
    Timer_Params params;
    last_tick_count = xTaskGetTickCountFromISR();

    Timer_Params_init(&params);
    params.period = 500000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = callback500;

    timer2 = Timer_open(CONFIG_TIMER_2, &params);

    if (timer2 == NULL) {
        /* Failed to initialized timer */
        fatalError(TIMER_500_CALLBACK_END);
    }

    if (Timer_start(timer2) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        fatalError(TIMER_500_CALLBACK_BEGIN);
    }
}

void callback500(Timer_Handle myHandle, int_fast16_t status){
    //send type 500 and time passed  in microseconds to sensor queue
    //dbgEvent(TIMER_500_CALLBACK_BEGIN);
    Callback_t c;
    c.type = 1;
    c.value = xTaskGetTickCountFromISR() - last_tick_count;
    last_tick_count = last_tick_count + c.value;
    //dbgEvent(TIMER_500_CALLBACK_BEFORE_SEND_QUEUE);
    addSensor(&c);
    //dbgEvent(TIMER_500_CALLBACK_AFTER_SEND_QUEUE);
    //dbgEvent(TIMER_500_CALLBACK_END);
}
