#ifndef _CLAVES_H_
#define _CLAVES_H_

#include <mqueue.h>
#include <stdio.h>
#include "../mensaje.h"

int open_queue_sever();
int send_message(struct message *msg);
int client_init();
#endif