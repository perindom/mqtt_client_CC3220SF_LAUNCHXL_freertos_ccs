#ifndef CONTROL_QUEUE_H_
#define CONTROL_QUEUE_H_


#include "FreeRTOS.h"
#include "queue.h"

typedef enum {
    CLAW_OPEN,
    CLAW_CLOSE,
    KICK,
    DONE
} order_t;

enum {
    timer,
    control
};

typedef struct CONTMsg{
    int topic;
    int message;
} CONTMsg_t;

void create_control_queue();

void add_to_control_queue(CONTMsg_t *msg);

void retrieve_from_control_queue(CONTMsg_t *msg);

static QueueHandle_t control_queue;


#endif /* CONTROL_QUEUE_H_ */
