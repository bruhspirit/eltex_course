#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SEM_KEY 1234 

void P(int semid) {
    struct sembuf sb;
    sb.sem_num = 0; // Номер семафора
    sb.sem_op = -1; // Операция P
    sb.sem_flg = 0;
    semop(semid, &sb, 1);
}

void V(int semid) {
    struct sembuf sb;
    sb.sem_num = 0; // Номер семафора
    sb.sem_op = 1; // Операция V
    sb.sem_flg = 0;
    semop(semid, &sb, 1);
}

int stoi(const char *s)
{
    char *endptr;
    long result = strtol(s, &endptr, 10);
    return (int)result;
}

int main(int argc, char const *argv[]) 
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <amount>\n", argv[0]);
        return 1;
    }

    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(1);
    }

    srand(time(NULL));
     
    int fd[2], n, wstatus, buf, msg, amount = stoi(argv[1]); 
    FILE *fptr;
    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        return 1;
    }

    fptr = fopen("nums.txt", "w");
    if (fptr == NULL) {
        perror("Failed to open file");
        return 1;
    }

    for (int i = 0; i < amount; i++) 
    {
        msg = rand() % 1000;
        fprintf(fptr, "%d\n", msg);
    }    
    fclose(fptr); 

    V(semid);
    pid_t pid = fork();

    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int *active_processes = (int *)shmat(shmid, NULL, 0);
    *active_processes = 0;
    
    if (*active_processes > 2)
    {
        printf("Only 2 processes can work with file!\n");
        exit(-1);
    }

    if (pid == -1) 
    {
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) 
    { 
        printf("File blocked. Parent process works with file...\n");
        P(semid);
        (*active_processes)++;
        if (*active_processes > 2)
        {
            printf("Only 2 processes can work with file.");
            exit(-1);
        }
        close(fd[0]); 
        
        FILE *fptr = fopen("nums.txt", "r");
        if (fptr == NULL) {
            perror("Failed to open file");
            return 1;
        }
     

       
        int count = 0;
        while (count < amount && fscanf(fptr, "%d", &buf) == 1) 
        {
            if (write(fd[1], &buf, sizeof(buf)) == -1)  
            {
                perror("write failed");
                return 1;
            }    
            count++;
        }
        printf("Unblocking...\n");
        (*active_processes)--;
        V(semid);
        close(fd[1]); 
        fclose(fptr); 
        return 0; 
    } 
    else 
    { 
        close(fd[1]); 
        printf("Wait for unblocking...\n");
        P(semid);
        (*active_processes)++;
        if (*active_processes > 2)
        {
            printf("Only 2 processes can work with file.");
            exit(-1);
        }
        FILE *fptr = fopen("nums.txt", "a");
        if (fptr == NULL) {
            perror("Failed to open file");
            return 1;
        }

        for (int i = 0; i < amount; i++)
        {
            if (read(fd[0], &buf, sizeof(buf)) == -1) 
            {
                perror("read failed");
                fclose(fptr);
                return 1;
            }
            fprintf(fptr, "%d\n", buf);
            printf("%d)Read: %d\n", i+1, buf);
        }

        fclose(fptr); 
        close(fd[0]); 
        int child_pid = wait(&wstatus);
        if (child_pid == -1)
        {
            perror("wait failed");
            exit(-1);
        }
        if (!WIFEXITED(wstatus))
        {
            printf("child not exited");
            exit(0);
        } 
        (*active_processes)--;
        V(semid);    
        return 0;
    }
    semctl(semid, 0, IPC_RMID);
}








