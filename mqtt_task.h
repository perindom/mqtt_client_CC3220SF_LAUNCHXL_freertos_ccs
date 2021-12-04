/*
 * mqtt_task.h
 *
 *  Created on: Oct 11, 2021
 *      Author: Charles
 */

#ifndef MQTT_TASK_H_
#define MQTT_TASK_H_


#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/Timer.h>

/* Driver configuration */
#include "ti_drivers_config.h"

#include "debug.h"

#include "timer70.h"
#include "timer500.h"

#include "mqtt_thread_state.h"
#include "mqtt_queue.h"
#include "parsing_queue.h"

void *publish_task(void *arg0);

#endif /* MQTT_TASK_H_ */
