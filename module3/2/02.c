#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int Sum(int arg1, int arg2)
{
    return arg1 + arg2;
}
int Div(int arg1, int arg2)
{
    if (arg2 != 0)
        return arg1 / arg2;
    else
    {
        printf("Invalid argument\n");
        exit(-1);
    }
}
int Diff(int arg1, int arg2)
{
    return arg1 - arg2;
}
int Mult(int arg1, int arg2)
{
    return arg1 * arg2;
}

int SkipSpaces(char *command, int i)
{
    while (command[i] == ' ')
    {
        i++;
    }
    return i;
}

int string_to_int(const char *s)
{
    char *endptr;
    long result = strtol(s, &endptr, 10);
    return (int)result;
}

void Menu()
{
    printf("Type a command\n");
    printf("1) sum arg1 arg2\n");
    printf("2) diff arg1 arg2\n");
    printf("3) div arg1 arg2\n");
    printf("4) mult arg1 arg2\n");
    printf("5) Control + C to exit\n");
}

void Execute(char *c)
{
    char *command = malloc(sizeof(char) * 100);
    char *arg1 = malloc(sizeof(char) * 100);
    char *arg2 = malloc(sizeof(char) * 100);
    int i = 0;
    while (c[i] == ' ')
    {
        i++;
    }
    while (c[i] != ' ' && i < strlen(c))
    {
        command[strlen(command)] = c[i];
        i++;
    }
    i = SkipSpaces(c, i);
    while (c[i] != ' ' && i < strlen(c))
    {
        arg1[strlen(arg1)] = c[i];
        i++;
    }

    i = SkipSpaces(c, i);

    while (c[i] != ' ' && i < strlen(c))
    {
        arg2[strlen(arg2)] = c[i];
        i++;
    }
    if (!strcmp(command, "sum") != 0 && !strcmp(command, "diff") != 0 && !strcmp(command, "mult") != 0 && !strcmp(command, "div") != 0)
    {
        printf("Error occured: Invalid command\n");
        exit(-1);
    }

    if (strcmp(arg1, "-") == 0 || strcmp(arg2, "-") == 0)
    {
        printf("Error occured: Invalid argument\n");
        exit(-1);
    }
    int a1 = string_to_int(arg1), a2 = string_to_int(arg2);
    if (strcmp(command, "sum") == 0)
        printf("result of sum: %d\n", Sum(a1, a2));
    if (strcmp(command, "diff") == 0)
        printf("result of diff: %d\n", Diff(a1, a2));
    if (strcmp(command, "mult") == 0)
        printf("result of sum: %d\n", Mult(a1, a2));
    if (strcmp(command, "div") == 0)
        printf("result of div: %d\n", Div(a1, a2));
}

void Interpretator()
{
    Menu();
    char *command = malloc(sizeof(char) * 100);
    fgets(command, 100, stdin);

    int fork_res = fork();
    int wstatus;
    if (fork_res == -1)
    {
        perror("fork failed");
        exit(-1);
    }
    if (fork_res == 0)
    {
        Execute(command);
        exit(0);
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
        Interpretator();
    }
}

int main(int argc, char const *argv[])
{
    Interpretator();
    return 0;
}
