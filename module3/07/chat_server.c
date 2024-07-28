#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <mqueue.h>
#include <unistd.h>
#include "message.h"

int main()
{
    mq_unlink("/chat");
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct msgbuf); 
    attr.mq_curmsgs = 0;

    mqd_t mqdes = mq_open("/chat", O_RDWR | O_CREAT, 0666, &attr);
    if (mqdes == (mqd_t)-1) {
        perror("Error opening message queue");
        exit(EXIT_FAILURE);
    }

    struct msgbuf message;

    while (1) 
    {
        int size = mq_receive(mqdes, (char*)&message, sizeof(message), 0);
        if (size >= 0)
            printf("Received: %s\n", message.mtext);
        else
        {
            perror("Error receiving message");
            continue;
        }

        if (message.mtype == MSG_EXIT) {
            printf("Exit. Shutting down....\n");
            break;
        }

        printf("Type a message: ");

        char msg[256];
        scanf("%256s", msg);
        
        message.mtype = MSG_TYPE;
        snprintf(message.mtext, sizeof(message.mtext), "%s", msg);        
  if (mq_send(mqdes, (char*)&message, sizeof(message), 0) == -1) {            
    perror("Error sending message");
            continue;
        }
    }

    mq_close(mqdes);
   
    return 0;
}