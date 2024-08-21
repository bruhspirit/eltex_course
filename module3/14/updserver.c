#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5000 
#define MAXLINE 1000 

int main(int argc, char const *argv[]) 
{
    char buffer[256];
    char message[256]; // Allocate sufficient memory for message
    int listenfd, len; 
    struct sockaddr_in servaddr, cliaddr; 

    bzero(&servaddr, sizeof(servaddr)); 

    listenfd = socket(AF_INET, SOCK_DGRAM, 0);         
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET; 

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    while(1) 
    {
        len = sizeof(cliaddr); 
        int n = recvfrom(listenfd, buffer, sizeof(buffer), 
                         0, (struct sockaddr*)&cliaddr, &len);

        if (n > 0) 
        {
            buffer[n] = '\0'; 
            printf("Received: %s\n",buffer); 
            if (strcmp(buffer, "exit") == 0)
                exit(0);
        }

        printf("Type a message (max len - 256 symbols, type exit to quit)\n");
        scanf("%255s", message); // Use the message array directly
        if (strcmp(message, "exit") != 0)
            sendto(listenfd, message, strlen(message), 0, 
                   (struct sockaddr*)&cliaddr, len);
        else 
        {
            sendto(listenfd, message, strlen(message), 0, 
                   (struct sockaddr*)&cliaddr, len);
            exit(0);
        }
    }

    close(listenfd); 
    return 0;
}
