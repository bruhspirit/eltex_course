#include <stdio.h>
#include <stdarg.h>

typedef struct  {
  void (*function)(void); // Указатель на функцию
  struct operationNode* next; // Указатель на следующий узел
} operationNode;

int sum(int n, ...) {
    int result = 0;
    va_list factor; //указатель va_list
    va_start(factor, n); // устанавливаем указатель
    for(int i = 0; i < n; i++) {
        result += va_arg(factor, int); // получаем значение текущего параметра типа int
    }
    va_end(factor); // завершаем обработку параметров
    return result;
}

int calculate(int (*operation) (int n, ...), int n, ...)
{

}

void calculator(int (*calculate) (int (*operation) (int n, ...), int n, ...), int n, ...)
{

}

int main(int argc, char const *argv[])
{
    int result = sum(8, 2, 3, 4, 5, 6, 7, 8, 9); // передаём 8 аргументов
    printf("%d", result);
    return 0;
}

