/*sensor_task.h*/

#ifndef SENSOR_THREAD_H_

#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/Timer.h>

/* Driver configuration */
#include "ti_drivers_config.h"

#include "debug.h"

#include "timer70.h"
#include "timer500.h"

#include "sensor_thread_state.h"

void *sensor_task(void *arg0);

#endif
