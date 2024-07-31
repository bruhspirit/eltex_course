#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void square()
{

    int amount;
    printf("Type amount of squares\n");
    scanf("%d", &amount);
    int sides[amount];
    for (int i = 0; i < amount; i++)
    {
        printf("Type side lenght\n");
        scanf("%d", &sides[i]);
    }
    int child_sides = amount / 2;
    int fork_res = fork();
    int wstatus;
    if (fork_res == -1)
    {
        perror("fork failed");
        exit(-1);
    }
    if (fork_res == 0)
    {
        printf("Counted by child process: %d\n", getpid());
        for (int i = 0; i < child_sides; i++)
        {
            printf("%d) %d\n", i + 1, sides[i] * sides[i]);
        }
    }
    else
    {
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
        printf("Counted by parent process: %d\n", getpid());
        for (int i = child_sides; i < amount; i++)
        {
            printf("%d) %d\n", i + 1, sides[i] * sides[i]);
        }
    }
}

int main(int argc, char const *argv[])
{
    square();
    return 0;
}
