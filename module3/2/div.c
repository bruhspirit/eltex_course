#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
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
int string_to_int(const char *s)
{
    char *endptr;
    long result = strtol(s, &endptr, 10);
    return (int)result;
}


int main(int argc, char const *argv[])
{
	printf("result of div:%d\n", Div(string_to_int(argv[0]), string_to_int(argv[1])));
	return 0;
}