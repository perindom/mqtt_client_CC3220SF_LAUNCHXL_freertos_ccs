//
// Created by Domin on 10/19/2021.
//

#ifndef INTER_COMPONENT_COMMUNICATION_CHAIN_QUEUE_H
#define INTER_COMPONENT_COMMUNICATION_CHAIN_QUEUE_H


#include "FreeRTOS.h"
#include "queue.h"
#include "publish_queue.h"

typedef struct chain_data_format {
    int DA;
    int DS;
    int CA;
    int CS;
    int VA;
    int VS;
} chain_data_format_t ;

typedef struct chain_message{
    char topic[TOPIC_STR_LEN];
    chain_data_format_t message;
} chain_message_t;

void create_chain_queue();

void add_to_chain_queue(chain_message_t *msg);

void retreive_chain_queue(chain_message_t *msg);

static QueueHandle_t chain_queue;



#endif //INTER_COMPONENT_COMMUNICATION_CHAIN_QUEUE_H
