#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <stdio.h>

#include "claves/claves.h"

int main(void) {
    client_init();
    return 0;
}