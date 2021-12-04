/*
 * timer50.h
 *
 *  Created on: Sep 9, 2021
 *      Author: vewake
 */

#ifndef TIMER50_H_
#define TIMER50_H_
#include "debug.h"
#include "publish_queue.h"
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/ADC.h>
#include "ti_drivers_config.h"

#include <stddef.h>
#include "control_queue.h"

void start50();

#endif /* TIMER50_H_ */
