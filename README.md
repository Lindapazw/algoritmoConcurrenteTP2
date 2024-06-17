# algoritmoConcurrenteTP2

# Implementación de Algoritmos con Hilos y Procesos

## Descripción

Este proyecto contiene dos implementaciones en C y C++: una utilizando hilos (threads) y otra utilizando procesos. Los algoritmos reciben como argumentos dos números enteros, `N` y `M`. Tales números serán utilizados para crear `N` hilos/procesos de tipo 1 y `M` hilos/procesos de tipo 2.

### Hilos de Tipo 1

- Muestra por pantalla el mensaje: “Instancia x del hilo 1”, siendo `X` el número de hilo creado (entre 0 y N-1).
- Se suspende por un tiempo aleatorio entre 0 y 2 segundos utilizando la llamada `usleep` o `sleep`.
- Incrementa la variable global `Compartida`.

### Hilos de Tipo 2

- Muestra por pantalla el mensaje: “Instancia y del hilo 2”, siendo `Y` el número de hilo creado (entre 0 y M-1).
- Se suspende por un tiempo aleatorio entre 0 y 2 segundos.
- Lee y muestra por pantalla el valor de la variable global `Compartida`.

Cuando los hilos finalicen su ejecución, el padre debe mostrar por pantalla “Se ha finalizado la ejecución”.

## Instrucciones de Compilación y Ejecución

### Hilos en C

#### Código

Guarda el siguiente código en un archivo llamado `hilos.c`:

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_SLEEP_TIME 2

int Compartida = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *hilo_tipo_1(void *arg) {
    int x = *((int *)arg);
    printf("Instancia %d del hilo 1\n", x);
    usleep((rand() % (MAX_SLEEP_TIME + 1)) * 1000000); // Suspender entre 0 y 2 segundos
    pthread_mutex_lock(&mutex);
    Compartida++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *hilo_tipo_2(void *arg) {
    int y = *((int *)arg);
    printf("Instancia %d del hilo 2\n", y);
    usleep((rand() % (MAX_SLEEP_TIME + 1)) * 1000000); // Suspender entre 0 y 2 segundos
    pthread_mutex_lock(&mutex);
    printf("Valor de Compartida: %d\n", Compartida);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <N> <M>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    pthread_t hilos1[N], hilos2[M];
    int indices1[N], indices2[M];

    srand(time(NULL)); // Inicializar el generador de números aleatorios

    for (int i = 0; i < N; i++) {
        indices1[i] = i;
        if (pthread_create(&hilos1[i], NULL, hilo_tipo_1, &indices1[i]) != 0) {
            perror("Error creando hilo tipo 1");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < M; i++) {
        indices2[i] = i;
        if (pthread_create(&hilos2[i], NULL, hilo_tipo_2, &indices2[i]) != 0) {
            perror("Error creando hilo tipo 2");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N; i++) {
        if (pthread_join(hilos1[i], NULL) != 0) {
            perror("Error esperando hilo tipo 1");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < M; i++) {
        if (pthread_join(hilos2[i], NULL) != 0) {
            perror("Error esperando hilo tipo 2");
            exit(EXIT_FAILURE);
        }
    }

    printf("Se ha finalizado la ejecución\n");
    return 0;
}
```
