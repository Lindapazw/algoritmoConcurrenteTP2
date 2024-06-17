#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <cstdlib>
#include <ctime>

#define MAX_SLEEP_TIME 2

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <N> <M>\n";
        return EXIT_FAILURE;
    }

    int N = std::atoi(argv[1]);
    int M = std::atoi(argv[2]);

    // Usar mmap para crear una variable compartida entre procesos
    int *compartida = static_cast<int*>(mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    if (compartida == MAP_FAILED) {
        perror("mmap");
        return EXIT_FAILURE;
    }
    *compartida = 0;

    srand(time(NULL)); // Inicializar el generador de números aleatorios

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return EXIT_FAILURE;
        } else if (pid == 0) {
            // Proceso hijo tipo 1
            std::cout << "Instancia " << i << " del proceso 1\n";
            usleep((rand() % (MAX_SLEEP_TIME + 1)) * 1000000); // Suspender entre 0 y 2 segundos
            (*compartida)++;
            munmap(compartida, sizeof(int));
            return 0; // Termina el proceso hijo
        }
    }

    for (int i = 0; i < M; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return EXIT_FAILURE;
        } else if (pid == 0) {
            // Proceso hijo tipo 2
            std::cout << "Instancia " << i << " del proceso 2\n";
            usleep((rand() % (MAX_SLEEP_TIME + 1)) * 1000000); // Suspender entre 0 y 2 segundos
            std::cout << "Valor de compartida: " << *compartida << "\n";
            munmap(compartida, sizeof(int));
            return 0; // Termina el proceso hijo
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < N + M; i++) {
        wait(NULL);
    }

    std::cout << "Se ha finalizado la ejecución\n";
    munmap(compartida, sizeof(int));
    return 0;
}
