// includes

int init() {
    // inicializar el servicio de elementos clave-valor1-valor2-valor3
    // mediantes este servicio se destruyen todas las tuplas que estuvieran almacenadas previamente
    // if success return 0
    return -1;
}

int set_value(int key, char *value1, int value2, double value3) {
    // se inserta el elemento key-value1-value2-value3
    // se consdiera error si la clave ya existía -> return -1
    // si hay error de comunicaciones, return -1
    // si success -> return 0;
}

int get_value(int key, char *value1, int *value2, double *value3) {
    // se obtiene el elemento key-value1-value2-value3
    // return value1, value2, value3 -> return 0
    // return -1 si hay error -> si no existe el elemento con dicha clave o por fallo de comunicaciones
}

int modify_value(int key, char *value1, int value2, double value3) {
    // se modifican los valores asociados a la key
    // return -1 si hay error -> si no existe el elemento con dicha clave o por fallo de comunicaciones
    // return 0 si success
}

int delete_key(int key) {
    // se elimina el elemento con dicha clave
    // return -1 si hay error -> si no existe el elemento con dicha clave o por fallo de comunicaciones
    // return 0 si success
}

int exist(int key) {
    // return 1 si existe el elemento con dicha clave
    // return 0 si no existe el elemento con dicha clave
    // return -1 si hay error -> por fallo de comunicaciones
}

int copy_key(int key1, int key2) {
    // se copia el elemento con clave key1 y se le asigna la clave key2
    // si no existe la key, se crea una nueva y se copia el valor
    // si existe, se cambia el valor
    // return 0 si success
    // return -1 si hay error -> por fallo de comunicaciones
}