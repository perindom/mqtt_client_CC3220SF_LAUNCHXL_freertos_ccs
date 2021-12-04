/*
 * mqttclient_if.c
 *
 *  Created on: Jan 22, 2020
 *      Author: a0227533
 */

#include <mqtt_if.h>

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <mqueue.h>

#include "chain_queue.h"
#include "sensor_thread_queue.h"
#include "debug.h"
#include "parsing_queue.h"
#include "json_files/jsmn.h"
#include "publish_queue.h"
#include "control_queue.h"

#include "debug_if.h"

#define TOKENSC 13
#define TOKENSA 5
#define STRINGLENGTH 100
#define TOPICLENGTH 16

#define MAXNODES 10

enum{
    MQTT_STATE_IDLE,
    MQTT_STATE_INITIALIZED,
    MQTT_STATE_CONNECTED
};

#define MQTT_EVENT_RECV MQTT_EVENT_MAX  // event for when receiving data from subscribed topics

#define MQTTAPPTHREADSIZE   2048

// structure for linked list elements to manage the topics
struct Node
{
    MQTTClient_SubscribeParams topicParams;
    MQTT_IF_TopicCallback_f topicCB;
    struct Node* next;
};

struct msgQueue
{
    int   event;
    char* topic;
    char* payload;
};

static struct mqttContext
{
    mqd_t msgQueue;
    pthread_mutex_t *moduleMutex;
    MQTTClient_Handle mqttClient;
    MQTT_IF_EventCallback_f eventCB;
    struct Node* head;
    int moduleState;
    uint8_t clientDisconnectFlag;
} mMQTTContext = {NULL, NULL, NULL, NULL, NULL, MQTT_STATE_IDLE, 0};

int IRmessages = 0;
int count = 0;
int avg =0;

// Callback invoked by the internal MQTT library to notify the application of MQTT events
void MQTTClientCallback(int32_t event, void *metaData, uint32_t metaDateLen, char *data, uint32_t dataLen)
{
    switch((MQTTClient_EventCB)event)
    {
        case MQTTClient_OPERATION_CB_EVENT:
        {
            switch(((MQTTClient_OperationMetaDataCB *)metaData)->messageType)
            {
                case MQTTCLIENT_OPERATION_CONNACK:
                {
                    LOG_TRACE("MQTT CLIENT CB: CONNACK\r\n");
                    //queueElement.event = MQTT_EVENT_CONNACK;
                    break;
                }

                case MQTTCLIENT_OPERATION_EVT_PUBACK:
                {
                    LOG_TRACE("MQTT CLIENT CB: PUBACK\r\n");
                    //queueElement.event = MQTT_EVENT_PUBACK;
                    break;
                }

                case MQTTCLIENT_OPERATION_SUBACK:
                {
                    LOG_TRACE("MQTT CLIENT CB: SUBACK\r\n");
                    //queueElement.event = MQTT_EVENT_SUBACK;
                    break;
                }

                case MQTTCLIENT_OPERATION_UNSUBACK:
                {
                    LOG_TRACE("MQTT CLIENT CB: UNSUBACK\r\n");
                    //queueElement.event = MQTT_EVENT_UNSUBACK;
                    break;
                }
            }
            break;
        }

        case MQTTClient_RECV_CB_EVENT:
        {
            LOG_TRACE("MQTT CLIENT CB: RECV CB\r\n");
            //LOG_INFO("MQTTCLIENTCALLBACK BEGIN\r\n");

            MQTTClient_RecvMetaDataCB *receivedMetaData;

            receivedMetaData = (MQTTClient_RecvMetaDataCB *)metaData;

            // copying received topic data locally to send over msg queue

            char topic[TOPICLENGTH];

            int i = 0;
            while (i < receivedMetaData->topLen){
                topic[i] = receivedMetaData->topic[i];
                i++;
            }

            topic[i] = '\0';

            char payload[STRINGLENGTH];

            i = 0;
            //j = 0;
            while (i < dataLen){
                payload[i] = data[i];
                i++;
                //j++;
            }
            payload[i] = '\0';

            //LOG_INFO("TOPIC: %s \tPAYLOAD: %s\r\n", topic, payload);

            if((strcmp(topic, "Sensor") == 0) || (strcmp(topic, "Average") == 0)){

                static jsmn_parser p;
                static jsmntok_t t[TOKENSA];

                jsmn_init(&p);
                int r = jsmn_parse(&p, payload, strlen(payload), t, TOKENSA);

                if((strcmp(topic, "Sensor") == 0))
                {
                    //input sensor count
                    char temp[STRINGLENGTH];
                    int i = t[2].start;
                    int j = 0;
                    while (i < t[2].end){
                        temp[j] = payload[i];
                        i++;
                        j++;
                    }
                    temp[j] = '\0';

                    //count = sensorCount
                    count = atoi(temp);

                    IRmessages = IRmessages + 1;
                }
                else
                {
                    //publish
                    char temp[STRINGLENGTH];
                    int i = t[2].start;
                    int j = 0;
                    while (i < t[2].end){
                        temp[j] = payload[i];
                        i++;
                        j++;
                    }
                    temp[j] = '\0';

                    //avg = sensorAvg
                    avg = atoi(temp);

                    LOG_INFO("{ \"IR messages\": %d, \"Sensor Count\": %d , \"Avg Sensor Value\": %d }", IRmessages, count, avg);

                    //IRmessages = 0;
                    //count = 0;
                }

            }
            else if (strcmp(topic, "Control") == 0) {
                static jsmn_parser p;
                static jsmntok_t t[TOKENSA];

                jsmn_init(&p);
                int r = jsmn_parse(&p, payload, strlen(payload), t, TOKENSA);

                char temp[STRINGLENGTH];
                int i = t[2].start;
                temp[0] = payload[i];
                int msg = atoi(temp);

                LOG_INFO("{ \"Order\": %d }", msg);


                CONTMsg_t control_message;
                control_message.message = msg;
                control_message.topic = control;

                add_to_control_queue(&control_message);

            }

            else if ((strcmp(topic, "Topic_CV") == 0) || (strcmp(topic, "Topic_DC") == 0) || (strcmp(topic, "Topic_VD") == 0)){

                subscribe_struct m;
                m.topic = 0;
                strcpy(m.payload, payload);

                //subscribe_struct m;
                dbgEvent(MQTT_TASK_BEFORE_SUBSCRIBE);
                //retrieveSubscribe(&m);
                dbgEvent(MQTT_TASK_AFTER_SUBSCRIBE);

                char payload[STRINGLENGTH];
                strcpy(payload, m.payload);

                jsmn_parser p;
                jsmntok_t t[TOKENSC];

                jsmn_init(&p);
                int r = jsmn_parse(&p, payload, strlen(payload), t, TOKENSC);

                char temp[STRINGLENGTH];
                int i = t[2].start;
                int j = 0;
                while (i < t[2].end){
                    temp[j] = m.payload[i];
                    i++;
                    j++;
                }
                temp[j] = '\0';

                chain_data_format_t recieved_data;
                recieved_data.DA = atoi(temp);

                i = t[4].start;
                j = 0;
                while (i < t[4].end){
                    temp[j] = m.payload[i];
                    i++;
                    j++;
                }
                temp[j] = '\0';

                recieved_data.DS = atoi(temp);


                i = t[6].start;
                j = 0;
                while (i < t[6].end){
                    temp[j] = m.payload[i];
                    i++;
                    j++;
                }
                temp[j] = '\0';

                recieved_data.CA = atoi(temp);

                i = t[8].start;
                j = 0;
                while (i < t[8].end){
                    temp[j] = m.payload[i];
                    i++;
                    j++;
                }
                temp[j] = '\0';

                recieved_data.CS = atoi(temp);
                i = t[10].start;
                j = 0;
                while (i < t[10].end){
                    temp[j] = m.payload[i];
                    i++;
                    j++;
                }
                temp[j] = '\0';

                recieved_data.VA = atoi(temp);

                i = t[12].start;
                j = 0;
                while (i < t[12].end){
                    temp[j] = m.payload[i];
                    i++;
                    j++;
                }
                temp[j] = '\0';

                recieved_data.VS = atoi(temp);

                chain_message_t chainMessage;
                chainMessage.message = recieved_data;

                add_to_chain_queue(&chainMessage);
                LOG_INFO("DA: %d, DS: %d, CA: %d, CS: %d, VA: %d, VS: %d\r\n", recieved_data.DA, recieved_data.DS, recieved_data.CA, recieved_data.CS, recieved_data.VA, recieved_data.VS);

            }

            break;
        }
        case MQTTClient_DISCONNECT_CB_EVENT:
        {
            LOG_TRACE("MQTT CLIENT CB: DISCONNECT\r\n");

            break;
        }
    }
}

// Helper function used to compare topic strings and accounts for MQTT wild cards
int MQTTHelperTopicMatching(char *s, char *p)
{
    char *s_next = (char*)-1, *p_next;

    for(; s_next; s=s_next+1, p=p_next+1)
    {
        int len;

        if(s[0] == '#')
            return 1;

        s_next = strchr(s, '/');
        p_next = strchr(p, '/');

        len = ((s_next) ? (s_next - s) : (strlen(s))) + 1;
        if(s[0] != '+')
        {
            if(memcmp(s, p, len) != 0)
                return 0;
        }
    }
    return (p_next)?0:1;
}

// This is the application thread for the MQTT module that signals
void *MQTTAppThread(void *threadParams)
{
    int ret;
    struct msgQueue queueElement;

    while(1)
    {
        mq_receive(mMQTTContext.msgQueue, (char*)&queueElement, sizeof(struct msgQueue), NULL);

        ret = 0;

        if(queueElement.event == MQTT_EVENT_RECV)
        {
            LOG_TRACE("MQTT APP THREAD: RECV TOPIC = %s", queueElement.topic);

            pthread_mutex_lock(mMQTTContext.moduleMutex);

            if(mMQTTContext.head != NULL){

                struct Node* tmp = mMQTTContext.head;

                // check what queueElement.topic to invoke the appropriate topic callback event for the user
                while(ret == 0){
                    ret = MQTTHelperTopicMatching(tmp->topicParams.topic, queueElement.topic);
                    if(ret == 1){

                        LOG_DEBUG("TOPIC MATCH %s\r\n", queueElement.topic);

                        tmp->topicCB(queueElement.topic, queueElement.payload);
                        break;
                    }
                    tmp = tmp->next;
                    if(tmp == NULL){
                        LOG_INFO("Cannot invoke CB for topic not in topic list\r\n");
                        LOG_INFO("TOPIC: %s \tPAYLOAD: %s\r\n", queueElement.topic, queueElement.payload);
                        break;
                    }
                }
            }

            pthread_mutex_unlock(mMQTTContext.moduleMutex);

            free(queueElement.topic);
            free(queueElement.payload);
        }
        // when MQTT_IF_Deinit is called we must close the message queue and terminate the MQTTAppThread
        else if(queueElement.event == MQTT_EVENT_DESTROY)
        {
            LOG_TRACE("MQTT APP THREAD: DESTROY\r\n");

            mMQTTContext.eventCB(queueElement.event);

            ret = mq_close(mMQTTContext.msgQueue);
            if(ret < 0){
                LOG_ERROR("msg queue close error %d", ret);
            }
            pthread_exit(0);
        }
        else if(queueElement.event == MQTT_EVENT_SERVER_DISCONNECT){

            LOG_TRACE("MQTT APP THREAD: DISCONNECT\r\n");

            int tmp;    // tmp is to avoid invoking the eventCB while mutex is still locked to prevent deadlock
            pthread_mutex_lock(mMQTTContext.moduleMutex);

            // checks if the disconnect event came because the client called disconnect or the server disconnected
            if(mMQTTContext.clientDisconnectFlag == 1){
                tmp = 1;
                mMQTTContext.clientDisconnectFlag = 0;
            }
            else{
                tmp = 0;
            }
            pthread_mutex_unlock(mMQTTContext.moduleMutex);

            if(tmp == 1){
                mMQTTContext.eventCB(MQTT_EVENT_CLIENT_DISCONNECT);
            }
            else{
                mMQTTContext.eventCB(queueElement.event);
            }
        }
        else if(queueElement.event == MQTT_EVENT_CONNACK){

            LOG_TRACE("MQTT APP THREAD: CONNACK\r\n");

            pthread_mutex_lock(mMQTTContext.moduleMutex);

            // in case the user re-connects to a server this checks if there is a list of topics to
                // automatically subscribe to the topics again
            if(mMQTTContext.head != NULL){

                struct Node* curr = mMQTTContext.head;
                struct Node* prev;
                struct Node* tmp;

                // iterate through the linked list until the end is reached
                while(curr != NULL){

                    tmp = curr;

                    ret = MQTTClient_subscribe(mMQTTContext.mqttClient, &curr->topicParams, 1);
                    // if subscribing to a topic fails we must remove the node from the list since we are no longer subscribed
                    if(ret < 0){

                        LOG_ERROR("SUBSCRIBE FAILED: %s", curr->topicParams.topic);

                        // if the node to remove is the head update the head pointer
                        if(curr == mMQTTContext.head){
                            mMQTTContext.head = curr->next;
                            curr = curr->next;
                        }
                        else if(curr->next != NULL){
                            prev->next = curr->next;
                            curr = curr->next->next;
                        }
                        else{
                            prev->next = curr->next;
                            curr = curr->next;
                        }

                        // delete the node from the linked list
                        free(tmp->topicParams.topic);
                        free(tmp);
                    }
                    else{
                        prev = curr;
                        curr = curr->next;
                    }
                }
            }
            pthread_mutex_unlock(mMQTTContext.moduleMutex);
            // notify the user of the connection event
            mMQTTContext.eventCB(queueElement.event);
        }
        else{

            LOG_TRACE("MQTT APP THREAD: OTHER\r\n");
            // if the module received any other event nothing else needs to be done except call it
            mMQTTContext.eventCB(queueElement.event);
        }
    }
}

// this thread is for the internal MQTT library and is required for the library to function
void *MQTTContextThread(void *threadParams)
{
    int ret;

    LOG_TRACE("CONTEXT THREAD: RUNNING\r\n");

    MQTTClient_run((MQTTClient_Handle)threadParams);

    LOG_TRACE("CONTEXT THREAD: MQTTClient_run RETURN\r\n");

    pthread_mutex_lock(mMQTTContext.moduleMutex);

    ret = MQTTClient_delete(mMQTTContext.mqttClient);
    if(ret < 0){
        LOG_ERROR("client delete error %d", ret);
    }

    LOG_TRACE("CONTEXT THREAD: MQTT CLIENT DELETED")

    mMQTTContext.moduleState = MQTT_STATE_INITIALIZED;

    pthread_mutex_unlock(mMQTTContext.moduleMutex);

    LOG_TRACE("CONTEXT THREAD EXIT\r\n");

    pthread_exit(0);

    return(NULL);
}

int MQTT_IF_Init(MQTT_IF_InitParams_t initParams)
{
    int ret;
    mq_attr attr;
    pthread_attr_t threadAttr;
    struct sched_param schedulingparams;
    pthread_t mqttAppThread = (pthread_t) NULL;

    if(mMQTTContext.moduleState != MQTT_STATE_IDLE){
        LOG_ERROR("library only supports 1 active init call\r\n");
        return -1;
    }

    // the mutex is to protect data in the mMQTTContext structure from being manipulated or accessed at the wrong time
    static pthread_mutex_t tempMutex;
    mMQTTContext.moduleMutex = &tempMutex;
    if(mMQTTContext.moduleMutex == NULL){
        LOG_ERROR("malloc failed: mutex\r\n");
        return -1;
    }

    ret = pthread_mutex_init(mMQTTContext.moduleMutex, (const pthread_mutexattr_t *)NULL);
    if (ret != 0){
        LOG_ERROR("mutex init failed\r\n");
        return ret;
    }

    pthread_mutex_lock(mMQTTContext.moduleMutex);
    // initializing the message queue for the MQTT module
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct msgQueue);
    mMQTTContext.msgQueue = mq_open("msgQueue", O_CREAT, 0, &attr);
    if(((int)mMQTTContext.msgQueue) <= 0){
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return (int)mMQTTContext.msgQueue;
    }

    pthread_attr_init(&threadAttr);
    schedulingparams.sched_priority = initParams.threadPriority;
    ret = pthread_attr_setschedparam(&threadAttr, &schedulingparams);
    ret |= pthread_attr_setstacksize(&threadAttr, initParams.stackSize);
    ret |= pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
    ret |= pthread_create(&mqttAppThread, &threadAttr, MQTTAppThread, NULL);
    if(ret == 0){
        mMQTTContext.moduleState = MQTT_STATE_INITIALIZED;
    }
    pthread_mutex_unlock(mMQTTContext.moduleMutex);

    return ret;
}

int MQTT_IF_Deinit(MQTTClient_Handle mqttClientHandle)
{
    int ret;
    struct msgQueue queueElement;

    pthread_mutex_lock(mMQTTContext.moduleMutex);
    if(mMQTTContext.moduleState != MQTT_STATE_INITIALIZED){
        if(mMQTTContext.moduleState == MQTT_STATE_CONNECTED){
            LOG_ERROR("call disconnect before calling deinit\r\n");
            pthread_mutex_unlock(mMQTTContext.moduleMutex);
            return -1;
        }
        else if(mMQTTContext.moduleState == MQTT_STATE_IDLE){
            LOG_ERROR("init has not been called\r\n");
            pthread_mutex_unlock(mMQTTContext.moduleMutex);
            return -1;
        }
    }

    queueElement.event = MQTT_EVENT_DESTROY;

    // since user called MQTT_IF_Deinit send the signal to the app thread so it may terminate itself
    ret = mq_send(mMQTTContext.msgQueue, (const char*)&queueElement, sizeof(struct msgQueue), 0);
    if(ret < 0){
        LOG_ERROR("msg queue send error %d", ret);
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return -1;
    }

    struct Node* tmp = mMQTTContext.head;

    // in case the user did not unsubscribe to topics this loop will free any memory that was allocated
    while(tmp != NULL){
        free(tmp->topicParams.topic);
        mMQTTContext.head = tmp->next;
        free(tmp);
        tmp = mMQTTContext.head;
    }

    // setting the MQTT module state back so that user can call init if they wish to use it again
    mMQTTContext.moduleState = MQTT_STATE_IDLE;
    pthread_mutex_unlock(mMQTTContext.moduleMutex);

    return 0;
}

MQTTClient_Handle MQTT_IF_Connect(MQTT_IF_ClientParams_t mqttClientParams, MQTTClient_ConnParams mqttConnParams, MQTT_IF_EventCallback_f mqttCB)
{
    int ret;
    pthread_attr_t threadAttr;
    struct sched_param priParam;
    pthread_t mqttContextThread = (pthread_t) NULL;
    MQTTClient_Params clientParams;

    pthread_mutex_lock(mMQTTContext.moduleMutex);
    // if the user has not called init this will return error since they're trying to connect without intializing the module
    if(mMQTTContext.moduleState != MQTT_STATE_INITIALIZED){

        if(mMQTTContext.moduleState == MQTT_STATE_CONNECTED){
            LOG_ERROR("mqtt library is already connected to a broker\r\n");
        }
        else{
            LOG_ERROR("must call init before calling connect\r\n");
        }
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return (MQTTClient_Handle)-1;
    }

    // copying the event callback the user registered for the module context
    mMQTTContext.eventCB = mqttCB;

    // preparing the data for MQTTClient_create
    clientParams.blockingSend = mqttClientParams.blockingSend;
    clientParams.clientId = mqttClientParams.clientID;
    clientParams.connParams = &mqttConnParams;
    clientParams.mqttMode31 = mqttClientParams.mqttMode31;

    mMQTTContext.mqttClient = MQTTClient_create(MQTTClientCallback, &clientParams);
    if(mMQTTContext.mqttClient == NULL){
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return (MQTTClient_Handle)-1;
    }

    pthread_attr_init(&threadAttr);
    priParam.sched_priority = 2;
    ret = pthread_attr_setschedparam(&threadAttr, &priParam);
    ret |= pthread_attr_setstacksize(&threadAttr, MQTTAPPTHREADSIZE);
    ret |= pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
    ret |= pthread_create(&mqttContextThread, &threadAttr, MQTTContextThread, NULL);
    if(ret != 0){
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return (MQTTClient_Handle)-1;
    }

    // if the user included additional parameters for the client MQTTClient_set will be called
    if(mqttClientParams.willParams != NULL){
        MQTTClient_set(mMQTTContext.mqttClient, MQTTClient_WILL_PARAM, mqttClientParams.willParams, sizeof(MQTTClient_Will));
    }

    if(mqttClientParams.username != NULL){
        MQTTClient_set(mMQTTContext.mqttClient, MQTTClient_USER_NAME, mqttClientParams.username, strlen(mqttClientParams.username));
    }

    if(mqttClientParams.password != NULL){
        MQTTClient_set(mMQTTContext.mqttClient, MQTTClient_PASSWORD, mqttClientParams.password, strlen(mqttClientParams.password));
    }

    if(mqttClientParams.cleanConnect == false){
        MQTTClient_set(mMQTTContext.mqttClient, MQTTClient_CLEAN_CONNECT, &mqttClientParams.cleanConnect, sizeof(mqttClientParams.cleanConnect));
    }

    if(mqttClientParams.keepaliveTime > 0){
        MQTTClient_set(mMQTTContext.mqttClient, MQTTClient_KEEPALIVE_TIME, &mqttClientParams.keepaliveTime, sizeof(mqttClientParams.keepaliveTime));
    }

    ret = MQTTClient_connect(mMQTTContext.mqttClient);
    if(ret < 0){
        LOG_ERROR("connect failed: %d\r\n", ret);
    }
    else{
        mMQTTContext.moduleState = MQTT_STATE_CONNECTED;
    }
    pthread_mutex_unlock(mMQTTContext.moduleMutex);

    if(ret < 0){
        return (MQTTClient_Handle)ret;
    }
    else{
        return mMQTTContext.mqttClient;
    }
}

int MQTT_IF_Disconnect(MQTTClient_Handle mqttClientHandle)
{
    int ret;

    pthread_mutex_lock(mMQTTContext.moduleMutex);
    if(mMQTTContext.moduleState != MQTT_STATE_CONNECTED){
        LOG_ERROR("not connected to broker\r\n");
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return -1;
    }

    mMQTTContext.clientDisconnectFlag = 1;

    ret = MQTTClient_disconnect(mqttClientHandle);
    if(ret < 0){
        LOG_ERROR("disconnect error %d", ret);
    }
    else{
        mMQTTContext.moduleState = MQTT_STATE_INITIALIZED;
    }
    pthread_mutex_unlock(mMQTTContext.moduleMutex);

    return ret;
}

struct Node *myNodeAlloc(){
    static struct Node Nodes[MAXNODES];
    static int nodesAllocated = 0;

    if(nodesAllocated == MAXNODES){
        fatalError(MQTT_IF_SUBSCRIBE_ALLOC_ERROR);
    }
    else{
        nodesAllocated++;
        return (&Nodes[nodesAllocated-1]);
    }
}

int MQTT_IF_Subscribe(MQTTClient_Handle mqttClientHandle, char* topic, unsigned int qos, MQTT_IF_TopicCallback_f topicCB)
{
    int ret = 0;
    struct Node* topicEntry = NULL;

    pthread_mutex_lock(mMQTTContext.moduleMutex);
    if(mMQTTContext.moduleState == MQTT_STATE_IDLE){
        LOG_ERROR("user must call MQTT_IF_Init before using the MQTT module\r\n");
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return -1;
    }

    // preparing the topic node to add it to the linked list that tracks all the subscribed topics
    topicEntry = myNodeAlloc();//(struct Node*)malloc(sizeof(struct Node));
    if(topicEntry == NULL){
        LOG_ERROR("malloc failed: list entry\n\r");
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return -1;
    }

    static char tempTopic[TOPICLENGTH];
    topicEntry->topicParams.topic = &tempTopic;

    int i = 0;
    while (i < (strlen(topic)+1)){
        topicEntry->topicParams.topic[i] = topic[i];
        i++;
    }
    topicEntry->topicParams.topic[i] = '\0';

    topicEntry->topicParams.qos = qos;
    topicEntry->topicCB = topicCB;

    // adding the topic node to the linked list
    topicEntry->next = mMQTTContext.head;
    mMQTTContext.head = topicEntry;

    if(mMQTTContext.moduleState == MQTT_STATE_CONNECTED){
        ret = MQTTClient_subscribe(mMQTTContext.mqttClient, &topicEntry->topicParams, 1);
        // if the client fails to subscribe to the node remove the topic from the list
        if(ret < 0){
            LOG_ERROR("subscribe failed %d. removing topic from list", ret);
            free(topicEntry->topicParams.topic);
            free(topicEntry);
        }
    }

    pthread_mutex_unlock(mMQTTContext.moduleMutex);
    return ret;
}

int MQTT_IF_Unsubscribe(MQTTClient_Handle mqttClientHandle, char* topic)
{
    int ret = 0;

    pthread_mutex_lock(mMQTTContext.moduleMutex);
    if(mMQTTContext.moduleState != MQTT_STATE_CONNECTED){
        LOG_ERROR("not connected to broker\r\n");
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return -1;
    }

    MQTTClient_UnsubscribeParams unsubParams;
    unsubParams.topic = topic;

    ret = MQTTClient_unsubscribe(mMQTTContext.mqttClient, &unsubParams, 1);
    if(ret < 0){
        LOG_ERROR("unsub failed\r\n");
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return ret;
    }
    else{
        // since unsubscribe succeeded the topic linked list must be updated to remove the topic node
        struct Node* curr = mMQTTContext.head;
        struct Node* prev;

        while(curr != NULL){

            // compare the current topic to the user passed topic
            ret = MQTTHelperTopicMatching(curr->topicParams.topic, topic);
            // if there is a match update the node pointers and remove the node
            if(ret == 1){

                if(curr == mMQTTContext.head){
                    mMQTTContext.head = curr->next;
                }
                else{
                    prev->next = curr->next;
                }
                free(curr->topicParams.topic);
                free(curr);
                pthread_mutex_unlock(mMQTTContext.moduleMutex);
                return ret;
            }
            prev = curr;
            curr = curr->next;
        }
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
    }

    LOG_ERROR("topic does not exist\r\n");
    pthread_mutex_unlock(mMQTTContext.moduleMutex);
    return -1;
}

int MQTT_IF_Publish(MQTTClient_Handle mqttClientParams, char* topic, char* payload, unsigned short payloadLen, int flags)
{
    pthread_mutex_lock(mMQTTContext.moduleMutex);
    if(mMQTTContext.moduleState != MQTT_STATE_CONNECTED){
        //fatalError(MQTT_CONNECT_EVENT);
        LOG_ERROR("not connected to broker\r\n");
        pthread_mutex_unlock(mMQTTContext.moduleMutex);
        return -1;
    }
    pthread_mutex_unlock(mMQTTContext.moduleMutex);

    return MQTTClient_publish(mqttClientParams,
                              (char*)topic,
                              strlen((char*)topic),
                              (char*)payload,
                              payloadLen,
                              flags);
}
