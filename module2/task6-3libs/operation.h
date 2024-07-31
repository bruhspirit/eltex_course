#include <stdio.h>
#include <stdarg.h>
#ifndef operation_h
#define operation_h

typedef struct
{
    double (*func)(int n, ...);
    char action;
} operation;

#endif