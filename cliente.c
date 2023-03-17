#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <stdio.h>

#include "claves/claves.h"

int main(void) {
    printf("-------- RESULTS OF EXECUTION --------\n\n");
    
    // testing init
    int test_init = client_init();
    printf("Result of init: %d\n\n", test_init);

    // testing set_value
    int test_set_value1 = client_set_value(1, "pencil", 7, 4.12);
    int test_set_value2 = client_set_value(2, "computer", 4, 3.57);
    int test_set_value3 = client_set_value(3, "book", 5, 2.12);
    printf("Insert first element: %d\n", test_set_value1);
    printf("Insert second element: %d \n", test_set_value2);
    printf("Insert third element: %d \n\n", test_set_value3);
    
    // testing get_value
    /*char value1[100];
    int value2;
    double value3;
    int test_get_value1 = client_get_value(1, value1, &value2, &value3);
    printf("Get first element: %d \n", test_get_value1);
    printf("Value1: %s \n", value1);
    printf("Value2: %d \n", value2);
    printf("Value3: %f \n\n", value3);
    int test_get_value2 = client_get_value(2, value1, &value2, &value3);
    printf("Get second element: %d \n", test_get_value2);
    printf("Value1: %s \n", value1);
    printf("Value2: %d \n", value2);
    printf("Value3: %f \n\n", value3);
    int test_get_value3 = client_get_value(3, value1, &value2, &value3);
    printf("Get third element: %d \n", test_get_value3);
    printf("Value1: %s \n", value1);
    printf("Value2: %d \n", value2);
    printf("Value3: %f \n\n", value3);*/

    // testing modify_value
    int test_modify_value1 = client_modify_value(1, "modified_1", 90, 4.12);
    int test_modify_value2 = client_modify_value(2, "modified_2", 4, 3.57);
    int test_modify_value3 = client_modify_value(3, "modified_3", 5, 2.12);
    printf("Modify first element: %d \n", test_modify_value1);
    printf("Modify second element: %d \n", test_modify_value2);
    printf("Modify third element: %d \n\n", test_modify_value3);

    // testing delete_value
    int test_delete_value1 = client_delete_value(1);
    int test_delete_value2 = client_delete_value(2);
    printf("Delete first element: %d \n", test_delete_value1);
    printf("Delete second element: %d \n\n", test_delete_value2);
    
    // testing exist
    int test_exist1 = client_exist(1);
    int test_exist2 = client_exist(2);
    int test_exist3 = client_exist(3);
    printf("Exist first element (should not): %d \n", test_exist1);
    printf("Exist second element (should not): %d \n", test_exist2);
    printf("Exist third element: %d \n\n", test_exist3);

    // testing copy_key
    // NOT OKAY
    int test_copy_key1 = client_copy_key(3, 4);
    printf("Copy third element to fourth element: %d \n", test_copy_key1);

    char invalid_string[258];
    // llenar invalid_string con 256 caracteres 'a'
    for (int i = 0; i < 258; i++) {
        invalid_string[i] = 'a';
    }
    int test_check_value1 = client_set_value(1, invalid_string, 7, 4.12);
    printf("Insert first element with invalid string (should not): %d \n", test_check_value1);

    return 0;
}