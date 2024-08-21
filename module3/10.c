#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

int stoi(const char *s)
{
    char *endptr;
    long result = strtol(s, &endptr, 10);
    return (int)result;
}

int main(int argc, char const *argv[]) 
{
    sem_unlink("/sem");
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <amount>\n", argv[0]);
        return 1;
    }

    sem_t *sem = sem_open("/sem", O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }   
    sem_init(sem, 1, 0);  
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

    pid_t pid = fork();


    if (pid == -1) 
    {
        perror("fork failed");
        return 1;
    } 

  

    else if (pid == 0) 
    { 
        printf("File blocked. Parent process works with file...\n");
       
        
        
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
        sem_post(sem);

        close(fd[1]); 
        fclose(fptr); 
        return 0; 
    } 
    else 
    { 
        
        close(fd[1]); 
        printf("Wait for unblocking...\n");
        sem_wait(sem); 
        
        

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
        return 0;
    }
}








