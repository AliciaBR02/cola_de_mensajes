/*el servidor almacena y gestiona las claves*/

#include <mqueue.h>
#include <stdio.h>
#include "mensaje.h"
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "operaciones/operaciones.h"

mqd_t q_server;
struct mq_attr attributes = {.mq_msgsize = sizeof(struct message), .mq_maxmsg = 10};

pthread_cond_t cond_message;
pthread_mutex_t mutex_message;
int not_message_copied = 1;

void process_message(struct message *msg) {
    mqd_t q_client;
    struct message msg_resp;

    pthread_mutex_lock(&mutex_message);
    msg_resp = *msg;
    not_message_copied = 0;
    pthread_cond_signal(&cond_message);
    pthread_mutex_unlock(&mutex_message);
    
    switch (msg_resp.op) {
        case 1:
            msg_resp.res = init();
            break;
        case 2:
            msg_resp.res = set_value(msg_resp.key, msg_resp.value1, msg_resp.value2, msg_resp.value3);
            break;
        case 3:
            dprintf(2, "value1 direction: %p", msg_resp.ptr1);
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

    if ((q_server = mq_open("/SERVIDOR", O_CREAT | O_RDONLY, 0700, &attributes)) < 0) {
        perror("mq_open(q_server)");
        return -1;
    }

    pthread_mutex_init(&mutex_message, NULL);
    pthread_cond_init(&cond_message, NULL);

    pthread_attr_init(&attr);
    // attributes -> independent threads
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    while (1) {
        struct message msg;
        struct message *msg_ptr;
        msg_ptr = &msg;
        if (mq_receive(q_server, (char *)msg_ptr, sizeof(struct message), NULL) < 0) {
            perror("mq_receive(q_server)");
            return -1;
        }
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
