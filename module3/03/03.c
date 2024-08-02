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
    Context *context = ReadContext();
    // Contact *new = CreateContact(context);
    if (context != 0)
    {
        printf("ID %d\n", context->id);
        printf("Count %d\n\n", context->counter);
    }
    context->counter = 4;
    context->id = 4123;
    WriteContext(context);
    context = ReadContext();
    if (context != 0)
    {
        printf("ID %d\n", context->id);
        printf("Count %d\n\n", context->counter);
    }
    free(context);
    return 0;
}