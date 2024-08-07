#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "message.h"

int main() 
{
    key_t key = ftok("chat", 0);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msgbuf message;

    while (1) 
    {
        
        msgrcv(msgid, &message, sizeof(message), MSG_TYPE, 0);
        printf("Recieved: %s\n", message.mtext);

        if (message.mtype == MSG_EXIT) 
        {
            printf("Exit. Shutting down....\n");
            break;
        }

        char *msg;
        printf("%s\n", "Type a message:");
        scanf("%256s", msg);
        snprintf(message.mtext, sizeof(message.mtext), msg);
        message.mtype = MSG_TYPE; 
        msgsnd(msgid, &message, sizeof(message), 0);
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}