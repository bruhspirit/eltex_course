#include <stdio.h>
#include <stdarg.h>

double sum(int n, ...)
{
    va_list factor;      // указатель va_list
    va_start(factor, n); // устанавливаем указатель
    double result = 0;
    for (int i = 0; i < n; i++)
    {
        result += va_arg(factor, int); // получаем значение текущего параметра типа int
    }
    va_end(factor); // завершаем обработку параметров
    return result;
}