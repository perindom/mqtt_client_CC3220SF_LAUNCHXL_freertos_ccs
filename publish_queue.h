//
// Created by Domin on 10/19/2021.
//

#ifndef INTER_COMPONENT_COMMUNICATION_PUBLISH_QUEUE_H
#define INTER_COMPONENT_COMMUNICATION_PUBLISH_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"

#define TOPIC_STR_LEN 16
#define MAX_STR_LEN 100

enum {board_D, board_C, board_V};

typedef struct publish_message {
    char topic[TOPIC_STR_LEN];
    char json_string[MAX_STR_LEN];
} publish_message_t ;


void create_publish_queue();

void add_to_publish_queue(publish_message_t *msg);

void retrieve_publish_queue(publish_message_t *msg);

static QueueHandle_t publish_queue;



#endif //INTER_COMPONENT_COMMUNICATION_PUBLISH_QUEUE_H
