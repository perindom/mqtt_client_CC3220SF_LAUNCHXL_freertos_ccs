/*
 * claw_control.h
 *
 *  Created on: Nov 27, 2021
 *      Author: Domin
 */

#ifndef CLAW_CONTROL_H_
#define CLAW_CONTROL_H_

/* For usleep() */
#include <unistd.h>
#include <stddef.h>
#include "debug.h"

/* Driver Header files */
#include <ti/drivers/PWM.h>

/* Driver configuration */
#include "ti_drivers_config.h"
#include "control_queue.h"
#include "publish_queue.h"
#include "timer50.h"

enum {
    IDLE_STATE,
    MOVING_STATE,
    DONE_STATE
};

enum {
    OPENING,
    KICKING,
    RETRACTING
};


#endif /* CLAW_CONTROL_H_ */
