# algoritmoConcurrenteTP2

###  Implementación de Algoritmos con Hilos y Procesos

### Descripción

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

### Compilación
Compila el código con el siguiente comando:

```c
g++ -o procesos puntob.cpp
```

### Ejecución
Ejecuta el programa con los argumentos N y M:

```c
./procesos 5 5
```
