#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <mqueue.h>
#include <unistd.h>
#include "message.h"

int main()
{
    mqd_t mqdes = mq_open("/chat", O_RDWR);
    struct msgbuf message;
    if (mqdes == (mqd_t)-1) {
        perror("Error opening message queue");
        exit(EXIT_FAILURE);
    }

    while (1) {
        char input[256];

        printf("Type a message (or 'exit' to quit):\n");
        scanf("%256s", input);
        
        if (strcmp(input, "exit") == 0) {  
            message.mtype = MSG_EXIT;
            snprintf(message.mtext, sizeof(message.mtext), "Client exiting.");
            if (mq_send(mqdes, (char*)&message, sizeof(message), 0) == -1) {
                perror("Error sending exit message");
            }
            break;
        }

        message.mtype = MSG_TYPE;
        printf("Sending...\n");
        snprintf(message.mtext, sizeof(message.mtext), "%s", input);

        if (mq_send(mqdes, (char*)&message, sizeof(message), 0) == -1) {
            perror("Error sending message");
            continue;
        }

        printf("Waiting for message...\n");
        if (mq_receive(mqdes, (char*)&message, sizeof(message), NULL) == -1) {
            perror("Error receiving message");
            continue;
        }

        printf("Received: %s\n", message.mtext);
    }

    mq_close(mqdes);
    return 0;
}