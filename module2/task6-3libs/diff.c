#include <stdio.h>
#include <stdarg.h>

double diff(int n, ...)
{
    va_list factor;      // указатель va_list
    va_start(factor, n); // устанавливаем указатель
    double result = va_arg(factor, int);
    for (int i = 1; i < n; i++)
    {
        result -= va_arg(factor, int); // получаем значение текущего параметра типа int
    }
    va_end(factor); // завершаем обработку параметров
    return result;
}