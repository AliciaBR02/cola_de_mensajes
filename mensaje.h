#ifndef _MENSAJE_H_
#define _MENSAJE_H_
#define MAX 256

struct peticion {
    int op;
    int key;
    char value1[MAX];
    int value2;
    double value3;
};

#endif