// LIBRERIA COMUNICACIÓN CLIENTE -> SERVIDOR
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include "../mensaje.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

mqd_t q_server;
mqd_t q_client;
//struct mq_attr attributes = {.mq_msgsize = sizeof(struct message), .mq_maxmsg = 10};
char *server_queue_name = "/SERVIDOR";
char client_queue_name[20];

struct mq_attr attributes = {.mq_msgsize = sizeof(struct message), .mq_maxmsg = 10};
// concat client pid to client queue name

int open_queues() {
    sprintf(client_queue_name, "/CLIENTE-%d", getpid());
    q_client = mq_open(client_queue_name, O_CREAT | O_RDWR, 0700, &attributes);
    if (q_client < 0) {
        perror("mq_open(q_client)");
        return -1;
    }
    q_server = mq_open(server_queue_name, O_WRONLY);
    if (q_server < 0) {
        mq_close(q_client);
        perror("mq_open(q_server)");
        return -1;
    }
    return 0;
}

int send_message(struct message *msg) {
    if (mq_send(q_server, (const char *)msg, sizeof(*msg), 0) < 0) {
        perror("mq_send(q_server)");
        return -1;
    }
    return 0;
}

int receive_message(struct message *msg) {
    if (mq_receive(q_client, (char *)msg, sizeof(*msg), NULL) < 0) {
        perror("mq_receive(q_client)");
        return -1;
    }
    return 0;
}

int client_init() {
    if (open_queues() == -1) {
        return -1;
    }
    struct message msg;
    msg.op = 5;
    strcpy(msg.value1, "hola\0");
    msg.value2 = 1;
    // copy client queue name in message
    
    strcpy(msg.client_queue_name, client_queue_name);
    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}


int client_set_value(int key, char *value1, int value2, double value3) {
    if (open_queues() == -1) {
        return -1;
    }
    struct message msg;
    msg.op = 2;
    msg.key = key;
    strcpy(msg.value1, value1);
    msg.value2 = value2;
    msg.value3 = value3;
    // copy client queue name in message
    
    strcpy(msg.client_queue_name, client_queue_name);
    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}

int client_get_value(int key, char *value1, int *value2, double *value3) {
    if (open_queues() == -1) {
        return -1;
    }
    struct message msg;
    msg.op = 3;
    msg.key = key;
    // los punteros a los valores se pasan por referencia
    // copy client queue name in message
    
    strcpy(msg.client_queue_name, client_queue_name);
    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}

int client_modify_value(int key, char *value1, int value2, double value3) {
    if (open_queues() == -1) {
        return -1;
    }
    struct message msg;
    msg.op = 4;
    msg.key = key;
    strcpy(msg.value1, value1);
    msg.value2 = value2;
    msg.value3 = value3;
    // copy client queue name in message
    
    strcpy(msg.client_queue_name, client_queue_name);
    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}

int client_delete_value(int key) {
    if (open_queues() == -1) {
        return -1;
    }
    struct message msg;
    msg.op = 5;
    msg.key = key;
    // copy client queue name in message
    
    strcpy(msg.client_queue_name, client_queue_name);
    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}

int client_copy_key(int key1, int key2) {
    if (open_queues() == -1) {
        return -1;
    }
    struct message msg;
    msg.op = 5;
    msg.key = key1;
    msg.key2 = key2;
    // copy client queue name in message
    
    strcpy(msg.client_queue_name, client_queue_name);
    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}