/*
 * timer70.c
 *
 *  Created on: Sep 9, 2021
 *      Author: vewake
 */

#include "timer70.h"
#include "debug.h"
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/ADC.h>
#include "ti_drivers_config.h"
#include "sensor_thread_queue.h"
#include <stddef.h>

void callback70(Timer_Handle myHandle, int_fast16_t status);

#define ADC_SAMPLE_COUNT  (10)
#define VOLT_MM_RATIO 1//15844.1558

#define THREADSTACKSIZE   (768)

void start70(){
    dbgEvent(TIMER_70_CALLBACK_BEGIN);

    //setup timer
    Timer_Handle timer1;
    Timer_Params params;

    GPIO_init();
    //Timer_init();

    Timer_Params_init(&params);
    params.period = 70000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = callback70;

    timer1 = Timer_open(CONFIG_TIMER_1, &params);

    if (timer1 == NULL) {
        /* Failed to initialized timer */
        fatalError(TIMER_70_CALLBACK_BEGIN);
    }

    if (Timer_start(timer1) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        fatalError(TIMER_70_CALLBACK_BEGIN);
    }
}

int convert_To_mm(/*Input from IR Sensor*/){
    //convert input to mm
    ADC_Handle   adc;
    ADC_Params   params;
    int_fast16_t res;


    ADC_Params_init(&params);
    adc = ADC_open(CONFIG_ADC_0, &params);

    if (adc == NULL) {
        ADC_close(adc);
        return -1;//error
    }
    // Blocking mode conversion
    uint16_t adcValue0;
    int adcValue0MicroVolt;

    res = ADC_convert(adc, &adcValue0);

    if (res == ADC_STATUS_SUCCESS) {

        adcValue0MicroVolt = ADC_convertRawToMicroVolts(adc, adcValue0);
        //convert based on calibration
        ADC_close(adc);
        adcValue0MicroVolt = adcValue0MicroVolt/VOLT_MM_RATIO;
        return adcValue0MicroVolt;
    }
    else {
        ADC_close(adc);
        return -1;//error
    }

}

void callback70(Timer_Handle myHandle, int_fast16_t status){
    //send type 70 and distance to sensor queue
    //dbgEvent(TIMER_70_CALLBACK_BEGIN);

    Callback_t c;
    c.type = 0;
    c.value = convert_To_mm();

    //dbgEvent(TIMER_70_CALLBACK_BEFORE_SEND_QUEUE);
    addSensor(&c);

    //dbgEvent(TIMER_70_CALLBACK_AFTER_SEND_QUEUE);
    //dbgEvent(TIMER_70_CALLBACK_END);
}
