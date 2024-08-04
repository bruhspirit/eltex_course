#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"

#define SIZE 256
#define path "contacts.bin"
int id = 0;

int main(int argc, char const *argv[])
{
    CreateIfNotExist();
    Context *context = calloc(1, sizeof(context));

    if (context != 0)
    {
        printf("active %d\n", context->active);
        printf("deleted %d\n", context->deleted);
        printf("id %d\n\n", context->id);
    }
    context->active = 3;
    context->deleted = 5;
    context->id = 6;
    WriteContext(context);
    context = ReadContext();
    if (context != 0)
    {
        printf("active %d\n", context->active);
        printf("deleted %d\n", context->deleted);
        printf("id %d\n", context->id);
    }
    free(context);
    return 0;
}