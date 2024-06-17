#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <unistd.h>
#include <ctime>

// Definir el tiempo máximo de suspensión en segundos
#define MAX_SLEEP_TIME 2

// Variable global compartida entre los hilos
int compartida = 0;

// Mutex para proteger el acceso a la variable compartida
std::mutex mtx;

// Función que ejecutan los hilos de tipo 1
void hilo_tipo_1(int id) {
    // Mostrar el mensaje identificando la instancia del hilo
    std::cout << "Instancia " << id << " del hilo 1\n";
    // Suspender el hilo por un tiempo aleatorio entre 0 y 2 segundos
    usleep((rand() % (MAX_SLEEP_TIME + 1)) * 1000000); // Suspender entre 0 y 2 segundos
    // Bloquear el mutex antes de acceder a la variable compartida
    std::lock_guard<std::mutex> lock(mtx);
    // Incrementar la variable compartida
    compartida++;
}

// Función que ejecutan los hilos de tipo 2
void hilo_tipo_2(int id) {
    // Mostrar el mensaje identificando la instancia del hilo
    std::cout << "Instancia " << id << " del hilo 2\n";
    // Suspender el hilo por un tiempo aleatorio entre 0 y 2 segundos
    usleep((rand() % (MAX_SLEEP_TIME + 1)) * 1000000); // Suspender entre 0 y 2 segundos
    // Bloquear el mutex antes de acceder a la variable compartida
    std::lock_guard<std::mutex> lock(mtx);
    // Mostrar el valor de la variable compartida
    std::cout << "Valor de compartida: " << compartida << "\n";
}

int main(int argc, char *argv[]) {
    // Verificar que se hayan pasado los argumentos correctos
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <N> <M>\n";
        return EXIT_FAILURE;
    }

    // Convertir los argumentos a enteros
    int N = std::atoi(argv[1]);
    int M = std::atoi(argv[2]);

    // Vectores para almacenar los hilos
    std::vector<std::thread> hilos1, hilos2;

    // Inicializar el generador de números aleatorios
    srand(time(NULL));

    // Crear y lanzar N hilos de tipo 1
    for (int i = 0; i < N; i++) {
        hilos1.emplace_back(hilo_tipo_1, i);
    }

    // Crear y lanzar M hilos de tipo 2
    for (int i = 0; i < M; i++) {
        hilos2.emplace_back(hilo_tipo_2, i);
    }

    // Esperar a que todos los hilos de tipo 1 terminen
    for (auto& hilo : hilos1) {
        hilo.join();
    }

    // Esperar a que todos los hilos de tipo 2 terminen
    for (auto& hilo : hilos2) {
        hilo.join();
    }

    // Mostrar mensaje indicando que la ejecución ha finalizado
    std::cout << "Se ha finalizado la ejecución\n";
    return 0;
}
