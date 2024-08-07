#ifndef MESSAGE_H
#define MESSAGE_H

#include <sys/types.h>

#define MSG_TYPE 1
#define MSG_ENQ  2
#define MSG_EXIT  3

struct msgbuf 
{
    long mtype;      
    char mtext[256]; 
};

#endif 