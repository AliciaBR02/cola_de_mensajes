# cola_de_mensajes
Este es un pequeño ejercicio de sistemas distrubuidos con cola de mensajes POSIX en el lenguaje C.

## Estructura de datos y funcionalidad real de este programa
El servidor ejecutará una serie de servicios para el almacenamiento de tuplas con formato <clave-valor1-valor2-valor3> donde estos serán un entero, una string, otro entero y un número decimal. La implementación de las funciones que esta gestión se encuentra en operaciones.c

## Comunicación entre el servidor y el cliente
El cliente mandará peticiones al servidor por una interfaz del tipo client_nombredefuncion. Esta interfaz está desarrollada en claves.c, y se emplea como una librería dinámica libclaves.so. Aquí, se abrirán las colas del servidor y el cliente y se realizará el envío de mensajes, y la espera a recibir el resultado de la operación.

El servidor por otra parte ejecutará un bucle infinito a la espera de la llegada de mensajes para así poder tratarlos y ejecutar la petición enviada.

## Compilar y ejecutar
Será necesario abrir dos terminales en linux o MAC.

En la primera habrá que ejecutar el comando
```bash
make re && ./servidor.out
```

Y en la segunda
```bash
./cliente.out
```
por ese orden.

En cliente.c viene implementado un posible ejemplo de un cliente, por lo que tras ejecutar estos comandos, se verá el resultado de este ejemplo.