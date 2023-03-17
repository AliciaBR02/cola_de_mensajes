#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "sllist/sllist.h"

void write_list_to_file(sllist *list) {
    FILE *f = fopen("data.txt", "w");
    sllist_node *node = list->head;
    while (node != NULL) {
        fprintf(f, "%d %s %d %f\n", node->key, node->value1, node->value2, node->value3);
        node = node->next;
    }
    fclose(f);
}

sllist read_list_from_file(void) {
    FILE *f = fopen("data.txt", "r");
    int key;
    char value1[100];
    int value2;
    double value3;
    sllist list;
    sllist_init(&list);
    
    while (fscanf(f, "%d %s %d %lf", &key, value1, &value2, &value3) != EOF) {
        sllist_add(&list, key, value1, value2, value3);
    }
    fclose(f);
    return list;
}

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
    sllist list = read_list_from_file();
    int result = sllist_exist(&list, key);
    sllist_destroy(&list);
    if (result)
        return 0;
    return -1;
}

int set_value(int key, char *value1, int value2, double value3) {
    sllist list = read_list_from_file();
    if (sllist_exist(&list, key))
        return -1;
    sllist_add(&list, key, value1, value2, value3);
    write_list_to_file(&list);
    sllist_destroy(&list);
    return 0;
}

int get_value(int key, char *value1, int *value2, double *value3) {
    // escribe los valores de la clave key en value1, value2 y value3
    sllist list = read_list_from_file();
    if (!sllist_exist(&list, key))
        return -1;
    sllist_node *node = sllist_get(&list, key);
    strcpy(value1, node->value1);
    *value2 = node->value2;
    *value3 = node->value3;
    sllist_destroy(&list);
    return 0;
}

int modify_value(int key, char *value1, int value2, double value3) {
    sllist list = read_list_from_file();
    if (!sllist_exist(&list, key))
        return -1;
    sllist_set_value(&list, key, value1, value2, value3);
    write_list_to_file(&list);
    sllist_destroy(&list);
    return 0;
}

int delete_value(int key) {
    sllist list = read_list_from_file();
    if (!sllist_exist(&list, key))
        return -1;
    sllist_remove(&list, key);
    write_list_to_file(&list);
    sllist_destroy(&list);
    return 0;
}

int copy_key(int key1, int key2) {
    // copiar key1 en key2 (tanto si key2 existe como si no)
    // si key1 no existe, return -1 y no hago nada
    sllist list = read_list_from_file();
    if (!sllist_exist(&list, key1))
        return -1;
    sllist_node *node = sllist_get(&list, key1);
    sllist_set_value(&list, key2, node->value1, node->value2, node->value3);
    write_list_to_file(&list);
    sllist_destroy(&list);
    return 0;
}

int main(void) {
    init();
    set_value(4, "pen", 3, 1.57);
    copy_key(4, 6);
    /*init();
    set_value(1, "insert", 7, 4.12);
    set_value(2, "computer", 4, 3.57);
    set_value(3, "book", 5, 2.12);
    set_value(4, "pen", 3, 1.57);
    int test_exist1 = exist(1);
    int test_exist2 = exist(2);
    int test_exist3 = exist(3);
    int test_exist4 = exist(4);
    int test_exist5 = exist(5);
    printf("Exist first element: %d \n\n", test_exist1);
    printf("Exist second element: %d \n\n", test_exist2);
    printf("Exist third element (should not): %d \n", test_exist3);
    printf("Exist fourth element: %d \n\n", test_exist4);
    printf("Exist fifth element (should not): %d \n", test_exist5);*/
    return 0;
}