#include <stdio.h>
#include <stdarg.h>
#include "operation.h"

double div(int n, ...);
double diff(int n, ...);
double mult(int n, ...);
double sum(int n, ...);

int main(int argc, char const *argv[])
{
    operation o;
    int args_count = 0;
    int args[10];
    char actions[4] = {'+', '-', '*', '/'};
    double result = 0;
    while (1)
    {
        printf("%s", "Введите количество аргументов (от 2 до 10)\n");
        scanf("%d", &args_count);
        if (args_count >= 2 && args_count <= 10)
            break;
    }
    for (int i = 0; i < args_count; i++)
    {
        printf("%s", "Введите аргумент\n");
        scanf("%d", &args[i]);
    }
    while (1)
    {
        printf("%s", "Введите действие (+, -, *, /)\n");
        scanf("%c", &o.action);
        if (o.action == actions[0] || o.action == actions[1] || o.action == actions[2] || o.action == actions[3])
            break;
    }
    switch (o.action)
    {
    case '+':
        o.func = sum;
        break;
    case '-':
        o.func = diff;
        break;
    case '*':
        o.func = mult;
        break;
    case '/':
        o.func = div;
        break;
    default:
        break;
    }
    switch (args_count)
    {
    case 2:
        result = o.func(2, args[0], args[1]);
        break;
    case 3:
        result = o.func(3, args[0], args[1], args[2]);
        break;
    case 4:
        result = o.func(4, args[0], args[1], args[2], args[3]);
        break;
    case 5:
        result = o.func(5, args[0], args[1], args[2], args[3], args[4]);
        break;
    case 6:
        result = o.func(6, args[0], args[1], args[2], args[3], args[4], args[5]);
        break;
    case 7:
        result = o.func(7, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
        break;
    case 8:
        result = o.func(8, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
        break;
    case 9:
        result = o.func(9, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
        break;
    case 10:
        result = o.func(10, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
        break;
    default:
        break;
    }
    printf("%f", result);
    printf("%s", "\n");
    return 0;
}