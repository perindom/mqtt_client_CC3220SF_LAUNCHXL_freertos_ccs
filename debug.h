/*
 * debug.h
 *
 *  Created on: Sep 7, 2021
 *      Author: Charles Hall
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <FreeRTOS.h>
#include <task.h>
#include "croutine.h"
#include "semphr.h"

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

/* Board Header file */
#include "ti_drivers_config.h"

//#include "sensor_thread_queue.h"
//#include "uart_thread_queue.h"

#include <stdio.h>

//extern void *sensor_task(void *arg0);
//extern void *uart_task(void *arg0);

//GPIO_0 corresponds to P03
//GPIO_1 corresponds to P18
//GPIO_2 corresponds to P21
//GPIO_3 corresponds to P50
//GPIO_4 corresponds to P53
//GPIO_5 corresponds to P61
//GPIO_6 corresponds to P62
//GPIO_7 corresponds to P63

//GPIO_8 corresponds to green LED
//P61

//Declare Constants Here


#define HARDWARE_DEBUG
#define MQTT_DEBUG
#define MQTT_TASK_DEBUG
#define CALLBACK_DEBUG
#define TIMER_1000_DEBUG
//#define TIMER_1500_DEBUG
#define TIMER_70_DEBUG
#define TIMER_500_DEBUG
#define UART_DEBUG
#define TEST_TASK_DEBUG
#define SENSOR_DEBUG
#define QUEUE_DEBUG

#define RESET_HEADER 0x00

#ifdef HARDWARE_DEBUG
#define SET_DETATCH_STATE 0x51
#define SET_SCHEDULE_PARAMS 0x52
#define SET_STACK_SIZE 0x53
#define CREATE_PTHREAD 0x54
#define MALLOC_FAILED_HOOK 0x55
#define STACK_OVERFLOW 0x56
#define SLNETSOC_INIT 0x57
#define OPEN_APP_QUEUE 0x58
#define WIFI_INIT 0x59
#define BEGIN_MAIN_THREAD 0x5A
#endif

#ifdef TIMER_1000_DEBUG
#define TIMER_1000_CALLBACK_BEGIN 0x40
#define TIMER_1000_CALLBACK_END 0x41
#define TIMER_1000_CALLBACK_BEFORE_SEND_QUEUE 0x43
#define TIMER_1000_CALLBACK_AFTER_SEND_QUEUE 0x44

#define FAILED_INIT_TIMER_1000 0x48
#endif

#ifdef TIMER_1500_DEBUG
#define TIMER_500_CALLBACK_BEGIN 0x42
#define TIMER_500_CALLBACK_END 0x45
#define TIMER_500_CALLBACK_BEFORE_SEND_QUEUE 0x46
#define TIMER_500_CALLBACK_AFTER_SEND_QUEUE 0x47

#define FAILED_INIT_TIMER_1500 0x49
#endif


#ifdef TIMER_70_DEBUG
#define TIMER_70_CALLBACK_BEGIN 0x40
#define TIMER_70_CALLBACK_END 0x41
#define TIMER_70_CALLBACK_BEFORE_SEND_QUEUE 0x43
#define TIMER_70_CALLBACK_AFTER_SEND_QUEUE 0x44
#endif

#ifdef TIMER_500_DEBUG
#define TIMER_500_CALLBACK_BEGIN 0x42
#define TIMER_500_CALLBACK_END 0x45
#define TIMER_500_CALLBACK_BEFORE_SEND_QUEUE 0x46
#define TIMER_500_CALLBACK_AFTER_SEND_QUEUE 0x47
#endif

#ifdef SENSOR_DEBUG
#define SENSOR_TASK_BEGIN 0x01
#define SENSOR_TASK_LOOP 0x02
#define SENSOR_TASK_BEFORE_RECEIVE_QUEUE 0x03
#define SENSOR_TASK_AFTER_RECEIVE_QUEUE 0x04
#define SENSOR_TASK_BEFORE_SEND_QUEUE 0x05
#define SENSOR_TASK_AFTER_SEND_QUEUE 0x06
#endif

#ifdef MQTT_TASK_DEBUG
#define MQTT_TASK_BEGIN 0x21
#define MQTT_TASK_LOOP 0x22



#define MQTT_TASK_BEFORE_SUBSCRIBE 0x23
#define MQTT_TASK_AFTER_SUBSCRIBE 0x24

//#define MQTT_TASK_BEFORE_SEND_QUEUE 0x25
//#define MQTT_TASK_AFTER_SEND_QUEUE 0x26

#define MQTT_TASK_BEFORE_RECEIVE_QUEUE 0x2A
#define MQTT_TASK_AFTER_RECEIVE_QUEUE 0x2B

#define MQTT_IF_SUBSCRIBE_ALLOC_ERROR 0x2C
#endif

#ifdef TEST_TASK_DEBUG
#define TEST_TASK_BEFORE_SEND 0x60
#define TEST_TASK_AFTER_SEND 0x61
#endif

#ifdef CALLBACK_DEBUG
#define RETRIEVE_CHAIN_QUEUE_BEFORE 0x62
#define RETRIEVE_CHAIN_QUEUE_AFTER 0x63

#define EXTRACT_DATA_BEGIN 0x64
#define EXTRACT_DATA_END 0x65

#define WHILE_LOOP_t2_ENTER 0x65
#define WHILE_LOOP_t2_EXIT 0x66

#define WHILE_LOOP_t4_ENTER 0x67
#define WHILE_LOOP_t4_EXIT 0x68

#define END_CALLBACK_3 0x69
#endif

#ifdef QUEUE_DEBUG

#define CHAIN_QUEUE_ADD 0x08
#define CHAIN_QUEUE_RETREIVE 0x10

#define PUBLISH_QUEUE_ADD 0x18

#define SENSOR_QUEUE_ADD 0x20

//#define PUBLISH_QUEUE_ADD 0x28
#endif


#ifdef UART_DEBUG
/*#define UART_TASK_BEGIN 0x08
#define UART_TASK_LOOP 0x10
#define UART_TASK_BEFORE_RECEIVE_QUEUE 0x18
#define UART_TASK_AFTER_RECEIVE_QUEUE 0x20
#define UART_TASK_BEFORE_SEND_QUEUE 0x28
#define UART_TASK_AFTER_SEND_QUEUE 0x30
#define UART_TASK_BEFORE_ADD_QUEUE 0x31
#define UART_TASK_AFTER_ADD_QUEUE 0x32
#define UART_TASK_BEFORE_RETRIEVE_QUEUE 0x33
#define UART_TASK_AFTER_RETRIEVE_QUEUE 0x34*/

#define UART_OPEN_ERROR 0x35
#define UART_CONTROL_ERROR_INIT 0x36
#define UART_CONTROL_ERROR 0x37
#define UART_SNPRINTF 0x38
#define UART_REALLOCATE_MEM 0x39
#define UART_SEND_MESSAGE 0x3A

#define UART_AFTER_INIT 0x3B
#define UART_AFTER_FREE 0x3C
#endif


#ifdef MQTT_DEBUG
#define CREATE_MQTT_QUEUE 0x71
#define BEGIN_MQTT_OPERATION_EVENT 0x72
#define BEGIN_MQTT_RECV_EVENT 0x73
#define BEGIN_MQTT_DISCONNECT_EVENT 0x74

#define MQTT_INIT 0x76
#define MQTT_SUBSCRIBE_TOPICS 0x77
#define MQTT_CREATE_CLIENT 0x78

#define MQTT_BEFORE_RECEIVE 0x05
#define MQTT_AFTER_RECEIVE 0x0B

#define MQTT_PUBLISH_BEGIN 0x09
#define MQTT_PUBLISH_END 0x0A

#define MQTT_DISCONNECT_EVENT 0x0C
#define MQTT_CONNECT_EVENT 0x0D

#define MQTT_DEINIT_EVENT 0x0E

#define MQTT_BUTTON_SHORT_PRESS 0x0F
#define MQTT_BUTTON_LONG_PRESS 0x10
#define MQTT_BUTTON_SEND 0x11
#define MQTT_END_ITERATION 0x12
#define MQTT_REPEAT_ITERATION 0x13

#endif
//void dbgInitTest();

void dbgEvent(unsigned int event);

void setGPIOs(unsigned int event);
bool checkGPIOs(unsigned int event);
void fatalError(unsigned int event);
void vFlashCoRoutine( CoRoutineHandle_t xHandle, UBaseType_t uxIndex );
void errorLED(Timer_Handle myHandle, int_fast16_t status);




#endif /* DEBUG_H_ */
