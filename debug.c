/*
 * debug.c
 *
 *  Created on: Sep 7, 2021
 *      Author: Charles Hall
 *
 *      LED Flashing Routine Referenced from: https://www.freertos.org/coroutine-example-code.html
 */

#include "debug.h"



void dbgEvent(unsigned int event){

    if(event <= 127){
        GPIO_write(CONFIG_GPIO_7, 1);
        setGPIOs(event);
        GPIO_write(CONFIG_GPIO_7, 0);

    }
}


void setGPIOs(unsigned int event){

    //Extracting binary values from event

    if((event % 2) == 1){
        GPIO_write(CONFIG_GPIO_0, 1);
    }
    else{
        GPIO_write(CONFIG_GPIO_0, 0);
    }


    if((event >> 1) % 2 == 1){
        GPIO_write(CONFIG_GPIO_1, 1);
    }
    else{
        GPIO_write(CONFIG_GPIO_1, 0);
    }

    if((event >> 2) % 2 == 1){
        GPIO_write(CONFIG_GPIO_2, 1);
    }
    else{
        GPIO_write(CONFIG_GPIO_2, 0);
    }
    if((event >> 3) % 2 == 1){
        GPIO_write(CONFIG_GPIO_3, 1);
    }

    else{
        GPIO_write(CONFIG_GPIO_3, 0);
    }

    if((event >> 4) % 2 == 1){
        GPIO_write(CONFIG_GPIO_4, 1);
    }
    else{
        GPIO_write(CONFIG_GPIO_4, 0);
    }

    if((event >> 5) % 2 == 1){
        GPIO_write(CONFIG_GPIO_5, 1);
    }
    else{
        GPIO_write(CONFIG_GPIO_5, 0);
    }

    if((event >> 6) % 2 == 1){
        GPIO_write(CONFIG_GPIO_6, 1);
    }
    else{
        GPIO_write(CONFIG_GPIO_6, 0);
    }

}




void fatalError(unsigned int event){

    //Use freertos end task

    dbgEvent(event);

    vTaskSuspendAll();

    taskDISABLE_INTERRUPTS();

    while(1){
        int i;
        for(i=0; i < 1000000000000000; i++){}
            GPIO_toggle(CONFIG_GPIO_8);
        }


}


void vFlashCoRoutine( CoRoutineHandle_t xHandle,
                 UBaseType_t uxIndex )
{
   // Co-routines must start with a call to crSTART().
   crSTART( xHandle );

   for( ;; )
   {
      // Delay for a fixed period.
      crDELAY( xHandle, 100 );

      // Flash an LED.
      GPIO_toggle(CONFIG_GPIO_8);
   }

   // Co-routines must end with a call to crEND().
   crEND();
}

void initTestTask(void *pvParameters){
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

    for( ;; )
    {
        /* Task code goes here. */
       /*dbgEvent(TIMER_70_CALLBACK_BEGIN);
       vTaskDelay(10);
       dbgEvent(TIMER_70_CALLBACK_LOOP);
       vTaskDelay(10);
       dbgEvent(TIMER_70_CALLBACK_BEFORE_SEND_QUEUE);
       vTaskDelay(10);
       dbgEvent(TIMER_70_CALLBACK_AFTER_SEND_QUEUE);
       vTaskDelay(10);

       dbgEvent(TIMER_500_CALLBACK_BEGIN);
       vTaskDelay(10);
       dbgEvent(TIMER_500_CALLBACK_LOOP);
       vTaskDelay(10);
       dbgEvent(TIMER_500_CALLBACK_BEFORE_SEND_QUEUE);
       vTaskDelay(10);
       dbgEvent(TIMER_500_CALLBACK_AFTER_SEND_QUEUE);
       vTaskDelay(10);*/

#ifdef SENSOR_DEBUG
       dbgEvent(SENSOR_TASK_BEGIN);
       vTaskDelay(10);
       dbgEvent(SENSOR_TASK_LOOP);
       vTaskDelay(10);
       dbgEvent(SENSOR_TASK_BEFORE_RECEIVE_QUEUE);
       vTaskDelay(10);
       dbgEvent( SENSOR_TASK_AFTER_RECEIVE_QUEUE);
       vTaskDelay(10);
       dbgEvent( SENSOR_TASK_BEFORE_SEND_QUEUE);
       vTaskDelay(10);
       dbgEvent( SENSOR_TASK_AFTER_SEND_QUEUE);
       vTaskDelay(10);

      /* dbgEvent(UART_TASK_BEGIN);
       vTaskDelay(10);
       dbgEvent(UART_TASK_LOOP);
       vTaskDelay(10);
       dbgEvent(UART_TASK_BEFORE_RECEIVE_QUEUE);
       vTaskDelay(10);
       dbgEvent( UART_TASK_AFTER_RECEIVE_QUEUE);
       vTaskDelay(10);
       dbgEvent( UART_TASK_BEFORE_SEND_QUEUE);
       vTaskDelay(10);
       dbgEvent( UART_TASK_AFTER_SEND_QUEUE);
       vTaskDelay(10);*/
#endif
    }

}






