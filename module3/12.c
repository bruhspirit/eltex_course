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
#include <sys/shm.h>
#include <string.h> 
#include <signal.h>
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


void handle_sigint(int sig) 
{
    keep_running = 0;
    kill(pid, SIGINT);    
}

int main()
{
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

    char pathname[] = "12.c"; 
    key_t key;
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }

    int nums_amount = rand() % 10;

    if((input_shmid = shmget(key,sets_amount*nums_amount*sizeof(int),0666|IPC_CREAT|IPC_EXCL)) < 0)
    {
  
        if(errno != EEXIST)
        {
            printf("Can\'t create shared memory\n");
            exit(-1);
        } 
        else 
        {
            if((input_shmid = shmget(key, sets_amount*nums_amount*sizeof(int), 0)) < 0)
            {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
        }
    }

    if((output_shmid = shmget(key,sets_amount*2*sizeof(int),0666|IPC_CREAT|IPC_EXCL)) < 0)
    {
  
        if(errno != EEXIST)
        {
            printf("Can\'t create shared memory\n");
            exit(-1);
        } 
        else 
        {
            if((output_shmid = shmget(key, sets_amount*2*sizeof(int), 0)) < 0)
            {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
        }
    }

    pid = fork();

    if (pid == -1) 
    {
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) 
    { 
        int iter = 1;
        while(1)
        {   
            P(semid);
            
            int min = 999, max = 0;

            if((input_array = (int *)shmat(input_shmid, NULL, 0)) == (int *)(-1))
            {
                printf("Can't attach shared memory\n");
                exit(-1);
            }
            for (int i = 0; i < sets_amount; i++)
                for (int j = 0; j < nums_amount; j++)
                {
                    if (input_array[i * nums_amount + j] < min)
                        min = input_array[i * nums_amount + j];
                    if (input_array[i * nums_amount + j] > max)
                        max = input_array[i * nums_amount + j];
                }    

            if((output_array = (int *)shmat(output_shmid, NULL, 0)) == (int *)(-1))
            {
                printf("Can't attach shared memory\n");
                exit(-1);
            } 
            output_array[(iter - 1) * 2] = min; 
            output_array[(iter - 1) * 2 + 1] = max;  
            printf("Min: %d\n", output_array[(iter - 1) * 2]);
            printf("Max: %d\n", output_array[(iter - 1) * 2 + 1]);
            iter++;

            V(semid); 
        }
       
        
    }
    else
    {
        void (*oldHandler)(int) = signal(SIGINT, handle_sigint);
        int iter = 1;
        while(1)
        {
            P(semid);
            if (keep_running == 0)
                break;
            printf("Generating random numbers sets. Iteration: %d\n", iter);  
            if((input_array = (int *)shmat(input_shmid, NULL, 0)) == (int *)(-1))
            {
                printf("Can't attach shared memory\n");
                exit(-1);
            }

            for (int i = 0; i < sets_amount; i++)
                for (int j = 0; j < nums_amount; j++)
                {
                    input_array[i * nums_amount + j] = rand() % 1000;
                }   
            if (keep_running == 0)
                break; 
            sleep(1);
            iter++; 
            V(semid);
        }
        
        printf("\nProcessed %d datasets\n", iter - 2);  

    }
    semctl(semid, 0, IPC_RMID); 
}