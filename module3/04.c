#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

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

    srand(time(NULL));
    int fd[2], pid, n, wstatus, amount = stoi(argv[1]); 

    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        return 1;
    }

    pid = fork();
    if (pid == -1) 
    {
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) 
    { 
        close(fd[0]); 
        
        for (int i = 0; i < amount; i++) 
        {
            int msg = rand() % 1000;
            if (write(fd[1], &msg, sizeof(msg)) == -1)  
            {
                perror("write failed");
                return 1;
            }
        }
        close(fd[1]); 
        return 0; 
    } 
    else 
    { 
        close(fd[1]); 

        
        int child_pid = wait(&wstatus);
        if (child_pid == -1)
        {
            perror("wait failed");
            exit(-1);
        }
        
        if (!WIFEXITED(wstatus))
        {
            printf("Child did not exit properly\n");
            exit(0);
        }

        FILE *fptr = fopen("nums.txt", "w");
        if (fptr == NULL) {
            perror("Failed to open file");
            return 1;
        }

        int buf;
        for (int i = 0; i < amount; i++)
        {
            if (read(fd[0], &buf, sizeof(buf)) == -1) 
            {
                perror("read failed");
                fclose(fptr);
                return 1;
            }
            printf("%d) Read: %d\n", i + 1, buf);
            fprintf(fptr, "%d\n", buf);
        }

        fclose(fptr); 
        close(fd[0]); 

        return 0;
    }
}