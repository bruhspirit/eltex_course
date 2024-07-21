#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *decimal_to_binary(int decimal_num)
{
    static char binary_num[9];
    int i = 7;

    if (decimal_num == 0)
    {
        strcpy(binary_num, "00000000");
        return binary_num;
    }

    while (decimal_num > 0)
    {
        binary_num[i--] = (decimal_num % 2) + '0';
        decimal_num /= 2;
    }

    while (i >= 0)
    {
        binary_num[i--] = '0';
    }
    binary_num[8] = '\0';

    return binary_num;
}

char *IPToBinary(char *ip)
{
    char *ip_binary = (char *)malloc(32);
    char *token;
    char gatewayIPCopy[50];

    strcpy(gatewayIPCopy, ip);

    token = strtok(gatewayIPCopy, ".");
    if (token != NULL)
    {
        long result = strtol(token, NULL, 10);
        strcat(ip_binary, decimal_to_binary(result));
    }
    while (token != NULL)
    {
        token = strtok(NULL, "."); // Продолжайте разбиение,  указав NULL
        if (token != NULL)
        {
            long result = strtol(token, NULL, 10);
            strcat(ip_binary, decimal_to_binary(result));
        }
    }
    return ip_binary;
}

int CheckSubnet(char *gatewayIP, char *destIP, char *netmask)
{
    char *gatewayIP_binary = (char *)malloc(32);
    char *destIP_binary = (char *)malloc(32);
    char *netmask_binary = (char *)malloc(32);

    gatewayIP_binary = IPToBinary(gatewayIP);
    destIP_binary = IPToBinary(destIP);
    netmask_binary = IPToBinary(netmask);

    char *gatewayIP_net = (char *)malloc(32);
    char *destIP_net = (char *)malloc(32);
    for (int i = 0; i < 32; i++)
    {
        if (gatewayIP_binary[i] == '1' && netmask_binary[i] == '1')
            gatewayIP_net[i] = '1';
        else
            gatewayIP_net[i] = '0';

        if (destIP_binary[i] == '1' && netmask_binary[i] == '1')
            destIP_net[i] = '1';
        else
            destIP_net[i] = '0';
    }
    if (gatewayIP_net == destIP_net)
        return 1;
    else
        return 0;
}

char *GenerateIP()
{
    char *IP = (char *)malloc(15);
    char buf[3];
    for (int i = 0; i < 4; i++)
    {
        int oct = (rand() % (255 - 0 + 1));
        snprintf(buf, sizeof buf, "%d", oct);
        strcat(IP, buf);
        if (i != 3)
            strcat(IP, ".");
    }
    return IP;
}

void Simulation(char *gatewayIP, int packages, char *netmask)
{

    int gateway_packages = 0;
    int other_packages = 0;
    for (int i = 0; i < packages; i++)
    {
        char *destIP = (char *)malloc(15);
        strcpy(destIP, GenerateIP());
        int res = CheckSubnet(gatewayIP, destIP, netmask);
        if (res == 1)
            gateway_packages++;
        else
            other_packages++;
    }
    printf("Cгенерировано %d пакетов. \n ", packages);
    printf("%d пакетов предназначены для своей сети (%d\%\). \n ", gateway_packages, gateway_packages / packages * 100);
    printf("%d пакетов предназначены для других сетей (%d\%\). \n ", other_packages, other_packages / packages * 100);
}

void Menu()
{
    char *gatewayIP = (char *)malloc(15);
    int packages;
    char *netmask = (char *)malloc(15);

    printf("Введите IP-адрес шлюза\n");
    scanf("%s", gatewayIP);
    printf("Введите маску подсети\n");
    scanf("%s", netmask);
    printf("Введите количество пакетов\n");
    scanf("%d", &packages);
    Simulation(gatewayIP, packages, netmask);
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    Menu();
    return 0;
}
