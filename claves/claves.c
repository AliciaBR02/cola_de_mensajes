// LIBRERIA COMUNICACIÓN CLIENTE -> SERVIDOR
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include "../mensaje.h"

mqd_t q_server;
//struct mq_attr attributes = {.mq_msgsize = sizeof(struct message), .mq_maxmsg = 10};
char *server_queue_name = "/SERVIDOR";

int open_queue_server() {
    if ((q_server = mq_open(server_queue_name, O_WRONLY)) < 0) {
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

/*int receive_message(struct message *msg) {
    return 0;
}*/

int client_init() {
    if (open_queue_server() == -1) {
        return -1;
    }
    struct message msg;
    msg.op = 1;
    if (send_message(&msg) == -1) {
        return -1;
    }
    mq_close(q_server);
    return 0;
}
/*
int client_init() {
    return 0;
}

int client_set_value() {
    return 0;
}

int client_get_value() {
    return 0;
}
*/