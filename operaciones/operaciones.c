#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int init() {
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        f = fopen("data.txt", "w");
        fclose(f);
    } else {
        fclose(f);
    }
    return 0;
}

int exist(int key) {
    FILE *f = fopen("data.txt", "r");
    // read the file line by line and check if the first number is key
    int k;
    char v1[100];
    int v2;
    double v3;
    while (fscanf(f, "%d %s %d %lf", &k, v1, &v2, &v3) != EOF) {
        if (k == key) {
            fclose(f);
            return 0;
        }
    }
}

int set_value(int key, char *value1, int value2, double value3) {
    // append the key, value1, value2 and value3 to the file
    if (exist(key) == 0)
        return -1;
    FILE *f = fopen("data.txt", "a");
    fprintf(f, "%d %s %d %lf\n", key, value1, value2, value3);
    fclose(f);
    return 0;
}

int get_value(int key, char *value1, int *value2, double *value3) {

    FILE *f = fopen("data.txt", "r");
    // read the file line by line and check if the first number is key
    int k;
    char v1[100];
    int v2;
    double v3;
    while (fscanf(f, "%d %s %d %lf", &k, v1, &v2, &v3) != EOF) {
        if (k == key) {
            strcpy(value1, v1);
            *value2 = v2;
            *value3 = v3;
            fclose(f);
            return 0;
        }
    }
    return -1;
}



int delete_value(int key) {
    // borra la clave key del archivo
    FILE *f = fopen("data.txt", "r");
    FILE *f2 = fopen("data2.txt", "w");
    int k;
    char v1[100];
    int v2;
    double v3;
    while (fscanf(f, "%d %s %d %lf\n", &k, v1, &v2, &v3) != EOF) {
        if (k != key) {
            fprintf(f2, "%d %s %d %lf\n", k, v1, v2, v3);
        }
    }
    fclose(f);
    fclose(f2);
    remove("data.txt");
    rename("data2.txt", "data.txt");
    return 0;
}
int modify_value(int key, char *value1, int value2, double value3) {
    int exists = exist(key);
    if (exists == -1)
        return -1;
    delete_value(key);
    set_value(key, value1, value2, value3);    
    return 0;
}
int copy_key(int key1, int key2) {
    // copiar key1 en key2 (tanto si key2 existe como si no)
    // si key1 no existe, return -1 y no hago nada
    int exists = exist(key1);
    if (exists == -1)
        return -1;
    char value1[256];
    int value2;
    double value3;
    get_value(key1, value1, &value2, &value3);
    set_value(key2, value1, value2, value3);
    return 0;
}
/*
int main(void) {
    init();
    int t = set_value(1, "insert", 7, 4.12);
    printf("Set value: %d \n", t);
    int s = modify_value(1, "modify", 8, 5.12);
    printf("Modify value: %d \n", s);
    char value1[100];
    int value2;
    double value3;
    int r = get_value(1, value1, &value2, &value3);
    printf("Get value: %d \n", r);
    printf("Value1: %s \n", value1);
    printf("Value2: %d \n", value2);
    printf("Value3: %lf \n", value3);
    int p = copy_key(1, 2);
    printf("Copy key: %d \n", p);
    return 0;
}*/