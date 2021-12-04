/*
 * subscribe_queue.h
 *
 *  Created on: Oct 14, 2021
 *      Author: vewak
 */

#ifndef PARSING_QUEUE_H_
#define PARSING_QUEUE_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "FreeRTOS.h"
#include "queue.h"

typedef struct subscribe_struct {
    char payload[100];
    int topic;
} subscribe_struct;


//define the UartMessage_t struct here

void create_parsing_queue();

//this should be passed by reference
void addSubscribe(subscribe_struct *m);

//void pass by reference. same signature as addUart
void retrieveSubscribe(subscribe_struct *m);

#endif /* PARSING_QUEUE_H_ */
