// LIBRERIA COMUNICACIÓN CLIENTE -> SERVIDOR
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include "../mensaje.h"
#include <stdlib.h>
#include <string.h>

mqd_t q_server;
mqd_t q_client;
//struct mq_attr attributes = {.mq_msgsize = sizeof(struct message), .mq_maxmsg = 10};
char *server_queue_name = "/SERVIDOR";
char *client_queue_name = "/Cola-%d", getpid();

int open_queues() {
    if (q_client = mq_open(client_queue_name, O_CREAT | O_RDONLY) < 0) {
        perror("mq_open(q_client)");
        return -1;
    }
    if ((q_server = mq_open(server_queue_name, O_WRONLY)) < 0) {
        mq_close(q_client);
        perror("mq_open(q_server)");
        return -1;
    }
    return 0;
}

int send_message(struct message *msg) {
    if (mq_send(q_server, (const char *)msg, sizeof(msg), 0) < 0) {
        perror("mq_send(q_server)");
        return -1;
    }
    return 0;
}

int receive_message(struct message *msg) {
    return 0;
}

int client_init() {
    if (open_queues() == -1) {
        return -1;
    }
    struct message msg;
    msg.op = 1;
    // copy client queue name in message
    strcpy(msg.client_queue_name, client_queue_name);
    if (send_message(&msg) == -1) {
        return -1;
    }
    // receive message
    mq_close(q_server);
    return 0;
}
/*

int client_set_value() {
    return 0;
}

int client_get_value() {
    return 0;
}
*/