/*
 * testRoverTask.c
 *
 *  Created on: Oct 13, 2021
 *      Author: Charles
 */

#include "testRoverTask.h"
#include "debug.h"


void *test_task(void *arg0){
    //this thread does not have a while loop
    static chain_message_t initialMessage;
    snprintf(initialMessage.topic, TOPIC_STR_LEN, "Topic_DC");
    chain_data_format_t chainCounts;
    chainCounts.DA = 0;
    chainCounts.DS = 0;
    chainCounts.CA = 0;
    chainCounts.CS = 0;
    chainCounts.VA = 0;
    chainCounts.VS = 0;
    initialMessage.message = chainCounts;
    dbgEvent(TEST_TASK_BEFORE_SEND);


    add_to_chain_queue(&initialMessage);
    dbgEvent(TEST_TASK_AFTER_SEND);

}

