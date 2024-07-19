#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Необходимо для использования strchr

char bit_rights[9];
int int_rights[3];
char char_rights[9];

void letter_permissions_to_bits(char rights[9])
{
    for (int i = 0; i < 9; i++)
    {
        if (rights[i] != 'r' && rights[i] != 'w' && rights[i] != 'x' && rights[i] != '-')
        {
            printf("Ошибка ввода\n");
            exit(-1);
        }
    }
    strcpy(char_rights, rights);

    for (int i = 0; i < 9; i++)
    {
        bit_rights[i] = '0';
    }
    for (int i = 0; i < 9; i++)
    {
        if (char_rights[i] == '-')
            bit_rights[i] == '0';
    }
    if (rights[0] == 'r')
        bit_rights[0] = '1';
    if (rights[1] == 'w')
        bit_rights[1] = '1';
    if (rights[2] == 'x')
        bit_rights[2] = '1';
    if (rights[3] == 'r')
        bit_rights[3] = '1';
    if (rights[4] == 'w')
        bit_rights[4] = '1';
    if (rights[5] == 'x')
        bit_rights[5] = '1';
    if (rights[6] == 'r')
        bit_rights[6] = '1';
    if (rights[7] == 'w')
        bit_rights[7] = '1';
    if (rights[8] == 'x')
        bit_rights[8] = '1';
}

void int_permissions_to_bits(int u, int g, int o)
{
    for (int i = 0; i < 3; i++)
    {
        if (u != 0 && u != 4 && u != 5 && u != 6 && u != 7)
        {
            printf("Ошибка ввода\n");
            exit(-1);
        }
        if (g != 0 && g != 4 && g != 5 && g != 6 && g != 7)
        {
            printf("Ошибка ввода\n");
            exit(-1);
        }
        if (o != 0 && o != 4 && o != 5 && o != 6 && o != 7)
        {
            printf("Ошибка ввода\n");
            exit(-1);
        }
    }
    int_rights[0] = u;
    int_rights[1] = g;
    int_rights[2] = o;
    for (int i = 0; i < 9; i++)
    {
        bit_rights[i] = '0';
    }
    if (u == 0)
    {
        for (int i = 0; i < 3; i++)
            bit_rights[i] = '0';
    }
    if (g == 0)
    {
        for (int i = 3; i < 6; i++)
            bit_rights[i] = '0';
    }
    if (o == 0)
    {
        for (int i = 6; i < 9; i++)
            bit_rights[i] = '0';
    }
    if (u == 4)
    {
        bit_rights[0] = '1';
    }
    if (g == 4)
    {
        bit_rights[3] = '1';
    }
    if (o == 4)
    {
        bit_rights[6] = '1';
    }
    if (u == 5)
    {
        bit_rights[0] = '1';
        bit_rights[2] = '1';
    }
    if (g == 5)
    {
        bit_rights[3] = '1';
        bit_rights[5] = '1';
    }
    if (o == 5)
    {
        bit_rights[6] = '1';
        bit_rights[8] = '1';
    }
    if (u == 6)
    {
        bit_rights[0] = '1';
        bit_rights[1] = '1';
    }
    if (g == 6)
    {
        bit_rights[3] = '1';
        bit_rights[4] = '1';
    }
    if (o == 6)
    {
        bit_rights[6] = '1';
        bit_rights[7] = '1';
    }
    if (u == 7)
    {
        bit_rights[0] = '1';
        bit_rights[1] = '1';
        bit_rights[2] = '1';
    }
    if (g == 7)
    {
        bit_rights[3] = '1';
        bit_rights[4] = '1';
        bit_rights[5] = '1';
    }
    if (o == 7)
    {
        bit_rights[6] = '1';
        bit_rights[7] = '1';
        bit_rights[8] = '1';
    }
}

void bit_permissions_to_letters()
{
    for (int i = 0; i < 9; i++)
    {
        if (bit_rights[i] == '0')
            char_rights[i] = '-';
    }
    if (bit_rights[0] == '1')
        char_rights[0] = 'r';
    if (bit_rights[1] == '1')
        char_rights[1] = 'w';
    if (bit_rights[2] == '1')
        char_rights[2] = 'x';
    if (bit_rights[3] == '1')
        char_rights[3] = 'r';
    if (bit_rights[4] == '1')
        char_rights[4] = 'w';
    if (bit_rights[5] == '1')
        char_rights[5] = 'x';
    if (bit_rights[6] == '1')
        char_rights[6] = 'r';
    if (bit_rights[7] == '1')
        char_rights[7] = 'w';
    if (bit_rights[8] == '1')
        char_rights[8] = 'x';
}

void bit_permissions_to_int()
{
    if (bit_rights[0] == '0' && bit_rights[1] == '0' && bit_rights[2] == '0')
        int_rights[0] = 0;
    if (bit_rights[3] == '0' && bit_rights[4] == '0' && bit_rights[5] == '0')
        int_rights[1] = 0;
    if (bit_rights[6] == '0' && bit_rights[7] == '0' && bit_rights[8] == '0')
        int_rights[2] = 0;

    if (bit_rights[0] == '1' && bit_rights[1] == '0' && bit_rights[2] == '0')
        int_rights[0] = 4;
    if (bit_rights[3] == '1' && bit_rights[4] == '0' && bit_rights[5] == '0')
        int_rights[1] = 4;
    if (bit_rights[6] == '1' && bit_rights[7] == '0' && bit_rights[8] == '0')
        int_rights[2] = 4;

    if (bit_rights[0] == '1' && bit_rights[1] == '0' && bit_rights[2] == '1')
        int_rights[0] = 5;
    if (bit_rights[3] == '1' && bit_rights[4] == '0' && bit_rights[5] == '1')
        int_rights[1] = 5;
    if (bit_rights[6] == '1' && bit_rights[7] == '0' && bit_rights[8] == '1')
        int_rights[2] = 5;

    if (bit_rights[0] == '1' && bit_rights[1] == '1' && bit_rights[2] == '0')
        int_rights[0] = 6;
    if (bit_rights[3] == '1' && bit_rights[4] == '1' && bit_rights[5] == '0')
        int_rights[1] = 6;
    if (bit_rights[6] == '1' && bit_rights[7] == '1' && bit_rights[8] == '0')
        int_rights[2] = 6;

    if (bit_rights[0] == '1' && bit_rights[1] == '1' && bit_rights[2] == '1')
        int_rights[0] = 7;
    if (bit_rights[3] == '1' && bit_rights[4] == '1' && bit_rights[5] == '1')
        int_rights[1] = 7;
    if (bit_rights[6] == '1' && bit_rights[7] == '1' && bit_rights[8] == '1')
        int_rights[2] = 7;
}

void stat(char *path)
{

    char *command = "stat ";
    size_t len1 = strlen(command);
    size_t len2 = strlen(path);
    char *result = malloc(len1 + len2 + 1);
    memcpy(result, command, len1);
    memcpy(result + len1, path, len2 + 1);
    int execute = system(result);
}

void Menu()
{
    printf("Выберите действие.\n");
    printf("1) Задать/изменить права доступа в буквенном виде.\n");
    printf("2) Задать/изменить права доступа в цифровом виде.\n");
    printf("3) Посмотреть права доступа файла.\n");
    int choice = 0;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        char rights[9];
        printf("Введите права в буквенном виде\n");
        scanf("%s", rights);
        letter_permissions_to_bits(rights);
        bit_permissions_to_int();
        printf("Права в цифровом виде: ");
        for (int i = 0; i < 3; i++)
        {
            printf("%d", int_rights[i]);
        }
        printf("\n");
        printf("Права в буквенном виде: ");
        printf(char_rights);
        printf("\n");
        printf("Права в битовом виде: ");
        printf(bit_rights);
        printf("\n");
        break;
    case 2:
        int irights[3];
        char rights_buf[3];
        printf("Введите права в цифровом виде\n");
        scanf("%s", rights_buf);
        for (int i = 0; i < 3; i++)
        {
            irights[i] = rights_buf[i] - '0';
        }
        int_permissions_to_bits(irights[0], irights[1], irights[2]);
        bit_permissions_to_letters();
        printf("Права в цифровом виде: ");
        for (int i = 0; i < 3; i++)
        {
            printf("%d", int_rights[i]);
        }
        printf("\n");
        printf("Права в буквенном виде: ");
        printf(char_rights);
        printf("\n");
        printf("Права в битовом виде: ");
        printf(bit_rights);
        printf("\n");
        break;
    case 3:
        char *path;
        printf("Введите путь к файлу.\n");
        scanf("%s", path);
        stat(path);
        break;
    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    Menu();
    return 0;
}