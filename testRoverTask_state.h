/*
 * testRoverTask_state.h
 *
 *  Created on: Oct 13, 2021
 *      Author: Charles
 */

#ifndef TESTROVERTASK_STATE_H_
#define TESTROVERTASK_STATE_H_

#include "mqtt_queue.h"

void updateState();

enum states{PUB1, PUB2, PUB3, PUB4, PUB5, PUB6, PUB7, PUB8, PUB9, PUB10};

static int state = PUB1;


#endif /* TESTROVERTASK_STATE_H_ */
