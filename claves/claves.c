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
char *server_queue_name = "/SERVIDOR";
char client_queue_name[20];

struct mq_attr attributes = {.mq_msgsize = sizeof(struct message), .mq_maxmsg = 10};

// auxiliary function to check the length of value1 is correct
int is_value1_valid(char *value1) {
    if (strlen(value1) > 256) {
        return -1;
    }
    return 0;
}

int open_queues() {
    // open server queue and client queue
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
        mq_close(q_server);
        mq_close(q_client);
        mq_unlink(client_queue_name);
        return -1;
    }
    return 0;
}
 /* The structure of the following functions are all the same:
    1- open the queues
    2- create the msg struct to be sent
    3- send msg
    4- receive it
    5- close queues */

int client_init() {
    if (open_queues() == -1) {return -1;}

    struct message msg;
    msg.op = 1;
    strcpy(msg.client_queue_name, client_queue_name);

    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}


int client_set_value(int key, char *value1, int value2, double value3) {
    if (open_queues() < 0) {return -1;}
    if (is_value1_valid(value1) == -1) {return -1;}
    struct message msg;
    msg.op = 2;
    msg.key = key;
    strcpy(msg.value1, value1);
    msg.value2 = value2;
    msg.value3 = value3;    
    strcpy(msg.client_queue_name, client_queue_name);

    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}

int client_get_value(int key, char *value1, int *value2, double *value3) {
    if (open_queues() == -1) {return -1;}
    if (is_value1_valid(value1) < 0) {return -1;}

    // since the server cannot write on data addresses 
    // that are not part of its own program, 
    //  the server will write the values in the message struct and
    //the client will copy them to the pointers entered

    struct message msg;
    msg.op = 3;
    msg.key = key;
    strcpy(msg.client_queue_name, client_queue_name);

    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    strcpy(value1, msg.value1);
    *value2 = msg.value2;
    *value3 = msg.value3;
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}

int client_modify_value(int key, char *value1, int value2, double value3) {
    if (open_queues() == -1) {return -1;}
    if (is_value1_valid(value1) < 0) {return -1;}

    struct message msg;
    msg.op = 4;
    msg.key = key;
    strcpy(msg.value1, value1);
    msg.value2 = value2;
    msg.value3 = value3;    
    strcpy(msg.client_queue_name, client_queue_name);

    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}

int client_delete_value(int key) {
    if (open_queues() == -1) {return -1;}

    struct message msg;
    msg.op = 5;
    msg.key = key;    
    strcpy(msg.client_queue_name, client_queue_name);

    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}

int client_exist(int key) {
    if (open_queues() == -1) {return -1;}

    struct message msg;
    msg.op = 6;
    msg.key = key;
    strcpy(msg.client_queue_name, client_queue_name);

    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}

int client_copy_key(int key1, int key2) {
    if (open_queues() == -1) {return -1;}

    struct message msg;
    msg.op = 7;
    msg.key = key1;
    msg.key2 = key2;
    strcpy(msg.client_queue_name, client_queue_name);

    if (send_message(&msg) < 0) { return -1;}
    if (receive_message(&msg) < 0) { return -1; }
    
    mq_close(q_server);
    mq_close(q_client);
    mq_unlink(client_queue_name);
    
    return msg.res;
}
