#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd = open("/dev/chardev", O_WRONLY);
    if (fd == -1)
    {
        perror("Failed to open device");
        return 1;
    }
    printf("Input: %s\n", argv[1]);
    write(fd, argv[1], strlen(argv[1]));
    return 0;
}