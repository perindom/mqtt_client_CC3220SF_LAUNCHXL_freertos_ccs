//
// Created by Domin on 10/19/2021.
//

#include "chain_task.h"

void *chain_task(void *arg0){

    int boardName = board_C;

    chain_message_t chainMessage;
    publish_message_t publishMessage;


    while(1)
    {
        dbgEvent(RETRIEVE_CHAIN_QUEUE_BEFORE);
        retreive_chain_queue(&chainMessage);
        dbgEvent(RETRIEVE_CHAIN_QUEUE_AFTER);

        chain_data_format_t chainCounts = chainMessage.message;

        switch(boardName){
        // indicate successful publish of the previous board
        // and publish attempt of the current board
            case board_D :
                snprintf(publishMessage.topic, TOPIC_STR_LEN, "Topic_DC");
                chainCounts.VS += 1;
                chainCounts.DA += 1;
                break;

            case board_C :
                snprintf(publishMessage.topic, TOPIC_STR_LEN, "Topic_CV");
                chainCounts.DS += 1;
                chainCounts.CA += 1;
                break;

            case board_V :
                snprintf(publishMessage.topic, TOPIC_STR_LEN, "Topic_VD");
                chainCounts.CS += 1;
                chainCounts.VA += 1;
                break;
        }

        int cx = snprintf(publishMessage.json_string, MAX_STR_LEN,
                          "{ \"DA\": %d, \"DS\": %d, \"CA\": %d, \"CS\": %d, \"VA\": %d, \"VS\": %d }",
                          chainCounts.DA,
                          chainCounts.DS,
                          chainCounts.CA,
                          chainCounts.CS,
                          chainCounts.VA,
                          chainCounts.VS);
        if (cx < 0)
        {
            //Error condition
            //while(1);
        }
        add_to_publish_queue(&publishMessage);
    }
}
