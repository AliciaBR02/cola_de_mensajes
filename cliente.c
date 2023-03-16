#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <stdio.h>

#include "claves/claves.h"

int main(void) {
    int test1 = client_init();
    int test2 = client_set_value(40, "probando", 8, 4.12);
    return 0;
}