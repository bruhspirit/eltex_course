#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../module2/structs.h"
#define SIZE 256

int main(int argc, char const *argv[])
{
    Contact *head = NULL;
    while (1)
    {
        head = Menu(head);
    }
    return 0;
}