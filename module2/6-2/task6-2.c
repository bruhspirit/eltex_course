#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <dlfcn.h>
#include "../6-2/structs.h"
#define SIZE 256
int main(int argc, char const *argv[])
{
    void *handle;
    Contact *(*Menu)(Contact *);
    char *error;

    handle = dlopen("/home/V/lib/libtest.so", RTLD_LAZY);
    if (!handle)
    {
        fputs(dlerror(), stderr);
        exit(-1);
    }

    Menu = dlsym(handle, "Menu");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(-1);
    }

    Contact *head = NULL;
    while (1)
    {
        head = (*Menu)(head);
    }

    dlclose(handle);
    return 0;
}