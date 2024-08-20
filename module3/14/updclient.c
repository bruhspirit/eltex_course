#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 5000
#define MAXLINE 1000

int main() 
{    
    char buffer[100]; 
    char message[256];  // Allocate sufficient memory for message
    int sockfd;  
    struct sockaddr_in servaddr, cliaddr; 

    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET; 

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        printf("\n Error : Connect Failed \n"); 
        exit(0); 
    } 

    while(1)
    {
        printf("Type a message (max len - 256 symbols, type exit to quit)\n");
        scanf("%255s", message);  // Use the message array directly

        if (strcmp(message, "exit") != 0) {
            sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)NULL, sizeof(servaddr));
        } else {
            sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)NULL, sizeof(servaddr));
            exit(0);
        }

        int n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr*)NULL, NULL); 
        if (n > 0)
        {
            buffer[n] = '\0'; 
            printf("Received: %s\n", buffer); 
            if (strcmp(buffer, "exit") == 0)
                exit(0);
        }  
    }

    close(sockfd); 
}
