//
// Created by Domin on 10/19/2021.
//

#ifndef INTER_COMPONENT_COMMUNICATION_CHAIN_TASK_H
#define INTER_COMPONENT_COMMUNICATION_CHAIN_TASK_H

#include "chain_queue.h"
#include "publish_queue.h"
#include "debug.h"

#include "mqtt_if.h"

void *chain_task(void *arg0);

#endif //INTER_COMPONENT_COMMUNICATION_CHAIN_TASK_H
