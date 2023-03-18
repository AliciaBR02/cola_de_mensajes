#include <mqueue.h>
#include <stdio.h>
#include "mensaje.h"
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "operaciones/operaciones.h"

// server queue
mqd_t q_server;
struct mq_attr attributes = {.mq_msgsize = sizeof(struct message), .mq_maxmsg = 10};

// threads and mutexes
pthread_cond_t cond_message;
pthread_mutex_t mutex_message;
int not_message_copied = 1;

// function to process the message and execute the requested operation
void process_message(struct message *msg) {
    mqd_t q_client;
    struct message msg_resp;

    // wait until the message is copied to the thread
    pthread_mutex_lock(&mutex_message);
    msg_resp = *msg;
    not_message_copied = 0;
    pthread_cond_signal(&cond_message);
    pthread_mutex_unlock(&mutex_message);
    
    // execute the requested operation
    switch (msg_resp.op) {
        case 1:
            msg_resp.res = init();
            break;
        case 2:
            msg_resp.res = set_value(msg_resp.key, msg_resp.value1, msg_resp.value2, msg_resp.value3);
            break;
        case 3:
            msg_resp.res = get_value(msg_resp.key, msg_resp.value1, &msg_resp.value2, &msg_resp.value3);
            break;
        case 4:
            msg_resp.res = modify_value(msg_resp.key, msg_resp.value1, msg_resp.value2, msg_resp.value3);
            break;
        case 5:
            msg_resp.res = delete_value(msg_resp.key);
            break;
        case 6:
            msg_resp.res = exist(msg_resp.key);
            break;
        case 7:
            msg_resp.res = copy_key(msg_resp.key, msg_resp.key2);
            break;
        default:
            msg_resp.res = -1;
            break;
    }
    
    // send the response to the client
    q_client = mq_open(msg_resp.client_queue_name, O_WRONLY);
    if (q_client < 0) {
        perror("mq_open(q_client)");
        mq_close(q_server);
    }
    if (mq_send(q_client, (const char *)&msg_resp, sizeof(msg_resp), 0) < 0) {
        perror("mq_send(q_client)");
        mq_close(q_server);
        mq_close(q_client);
    }
}

int main(void) {
    pthread_t thread;
    pthread_attr_t attr;

    // create the server queue
    if ((q_server = mq_open("/SERVIDOR", O_CREAT | O_RDONLY, 0700, &attributes)) < 0) {
        perror("mq_open(q_server)");
        return -1;
    }

    // initialize the mutex and condition variables
    pthread_mutex_init(&mutex_message, NULL);
    pthread_cond_init(&cond_message, NULL);

    pthread_attr_init(&attr);
    // attributes => independent threads
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // infinite loop to receive messages
    while (1) {
        // message struct to write the received message
        struct message msg;
        struct message *msg_ptr;
        msg_ptr = &msg;

        if (mq_receive(q_server, (char *)msg_ptr, sizeof(struct message), NULL) < 0) {
            perror("mq_receive(q_server)");
            return -1;
        }
        
        // create a thread to process the message received
        if (pthread_create(&thread, &attr, (void *)process_message, (void *)&msg) == 0) {
            pthread_mutex_lock(&mutex_message);
            while (not_message_copied == 1) {
                pthread_cond_wait(&cond_message, &mutex_message);
            }
            not_message_copied = 1;
            pthread_mutex_unlock(&mutex_message);
        }
        
    }
    return 0;
}
