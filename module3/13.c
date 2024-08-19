#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <string.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define SEM_KEY 1234 
#define sets_amount 10

pid_t pid;
int keep_running = 1;

void P(int semid) {
    struct sembuf sb;
    sb.sem_num = 0; 
    sb.sem_op = -1; 
    sb.sem_flg = 0;
    semop(semid, &sb, 1);
}

void V(int semid) {
    struct sembuf sb;
    sb.sem_num = 0; 
    sb.sem_op = 1; 
    sb.sem_flg = 0;
    semop(semid, &sb, 1);
}

void handle_sigint(int sig) {
    keep_running = 0;
    kill(pid, SIGINT);    
}

int main() {
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666), 
        wstatus,
        input_shmid, 
        output_shmid,
        *input_array,
        *output_array;

    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(1);
    }

    srand(time(NULL));

    // Генерация случайного количества чисел
    int nums_amount = rand() % 10 + 1; // Добавляем +1, чтобы избежать нуля

    // Создание разделяемой памяти
    input_shmid = shm_open("input", O_CREAT | O_RDWR, 0666);
    ftruncate(input_shmid, sets_amount * nums_amount * sizeof(int));
    output_shmid = shm_open("output", O_CREAT | O_RDWR, 0666);
    ftruncate(output_shmid, sets_amount * 2 * sizeof(int)); // Исправлено: должно быть output_shmid

    if (input_shmid == -1 || output_shmid == -1) {
        perror("shm_open");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) { 
        int iter = 1;
        while(keep_running) {  
            P(semid);
            int min = 999, max = 0;

            // Присоединение к разделяемой памяти
            input_array = mmap(0, sets_amount * nums_amount * sizeof(int), PROT_READ, MAP_SHARED, input_shmid, 0);
            if (input_array == MAP_FAILED) {
                perror("mmap input");
                exit(1);
            }

            for (int i = 0; i < sets_amount; i++) {
                for (int j = 0; j < nums_amount; j++) {
                    if (input_array[i * nums_amount + j] < min) {
                        min = input_array[i * nums_amount + j];
                    }
                    if (input_array[i * nums_amount + j] > max) {
                        max = input_array[i * nums_amount + j];
                    }
                }    
            }    

            output_array = mmap(0, sets_amount * 2 * sizeof(int), PROT_WRITE, MAP_SHARED, output_shmid, 0);
            if (output_array == MAP_FAILED) {
                perror("mmap output");
                exit(1);
            }

            output_array[(iter - 1) * 2] = min; 
            output_array[(iter - 1) * 2 + 1] = max;  
            iter++;
            V(semid); 
        }
    } else {
        void (*oldHandler)(int) = signal(SIGINT, handle_sigint);
        int iter = 1;
        while(keep_running) {

            P(semid);
            printf("Generating random numbers sets. Iteration: %d\n", iter);  

            input_array = mmap(0, sets_amount * nums_amount * sizeof(int), PROT_WRITE, MAP_SHARED, input_shmid, 0);
            if (input_array == MAP_FAILED) {
                perror("mmap input");
                exit(1);
            }

            for (int i = 0; i < sets_amount; i++) {
                for (int j = 0; j < nums_amount; j++) {
                    input_array[i * nums_amount + j] = rand() % 1000;
                }   
            }

            sleep(1);
            output_array = mmap(0, sets_amount * 2 * sizeof(int), PROT_READ, MAP_SHARED, output_shmid, 0);
            if (output_array == MAP_FAILED) {
                perror("mmap output");
                exit(1);
            }

            printf("Min: %d\n", output_array[(iter - 1) * 2]);
            printf("Max: %d\n", output_array[(iter - 1) * 2 + 1]);
            iter++; 
            V(semid);
        }
        
        printf("\nProcessed %d datasets\n", iter - 1);  
    }

    semctl(semid, 0, IPC_RMID); 
    shm_unlink("input"); // Освобождение ресурсов
    shm_unlink("output");
}
