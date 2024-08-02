#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include "contact_structures.h"

#define SIZE 256
#define path "contacts.bin"

void CreateIfNotExist()
{
    if ((open(path, O_EXCL) != -1))
        printf("File exists.\n\n");
    else
    {
        printf("File not exist. Trying to create...\n");
        if ((open(path, O_CREAT, 0666) == -1))
        {
            printf("Error: file not created.\n");
            exit(-1);
        }
        printf("File created successfully.\n\n");
    }
}
Person *CreatePerson()
{
    Person *new = calloc(1, sizeof(Person));
    int c, is_numeric = 1;
    char buf[SIZE];
    printf("Type a name (256 symbols):\n");
    scanf("%256s", buf);
    strcpy(new->name, buf);
    printf("Type a lastname (256 symbols):\n");
    scanf("%256s", buf);
    strcpy(new->lastname, buf);
    printf("Type a workplace(256 symbols, \"-\" to skip):\n");
    scanf("%256s", buf);
    strcpy(new->workplace, buf);
    printf("Type a job(256 symbols, \"-\" to skip):\n");
    scanf("%256s", buf);
    strcpy(new->job, buf);
    while (1)
    {
        printf("Type an email(256 symbols, \"-\" to end or skip):\n");
        c = scanf("%256s", buf);
        if (c == 1 && buf[0] == '-')
            break;
        if (new->email_counter < SIZE)
        {
            strcpy(new->emails[new->email_counter].email, buf);
            new->email_counter++;
        }
        else
        {
            printf("%s", "Max amount of emails is reached!\n");
            break;
        }
    }
    while (1)
    {
        printf("Type an phonenumber(11 symbols, \"-\" to end or skip):\n");
        c = scanf("%11s", buf);
        if (c == 1 && buf[0] == '-')
            break;
        for (int i = 0; i < strlen(buf); i++)
        {
            if (!isdigit(buf[i]))
            {
                is_numeric = 0;
                break;
            }
        }
        if (!is_numeric)
            printf("%s", "Only numbers!\n");
        else
        {
            if (new->phonenumbers_counter < SIZE)
            {
                strcpy(new->phonenumbers[new->phonenumbers_counter].phonenumber, buf);
                new->phonenumbers_counter++;
            }
            else
            {
                printf("%s", "Max amount of phonenumbers is reached!\n");
                break;
            }
        }
    }
    while (1)
    {
        printf("Type an social media link(256 symbols, \"-\" to end or skip):\n");
        c = scanf("%256s", buf);
        if (c == 1 && buf[0] == '-')
            break;
        if (new->socials_counter < SIZE)
        {
            strcpy(new->socials[new->socials_counter].social, buf);
            new->socials_counter++;
        }
        else
        {
            printf("%s", "Max amount of social media links is reached!\n");
            break;
        }
    }
    return new;
}

Contact *CreateContact(Context *context)
{
    Contact *new = calloc(1, sizeof(Contact));
    Person *person = CreatePerson();
    new->person = *person;
    new->id = context->id;
    return new;
}

int WriteContext(Context *context)
{
    int F = open(path, O_RDWR);
    if (F == -1)
    {
        printf("Error while opening the file.\n");
        close(F);
        return 0;
    }
    lseek(F, 0, SEEK_SET);
    int res = write(F, &context->id, 4);
    if (res == -1)
    {
        printf("Error while writing.\n");
        close(F);
        return 0;
    }
    lseek(F, 1, SEEK_SET);
    res = write(F, &context->counter, 4);
    if (res == -1)
    {
        printf("Error while writing.\n");
        close(F);
        return 0;
    }
    close(F);
    return 1;
}

Context *ReadContext()
{
    Context *context = calloc(1, sizeof(Context));
    if ((open(path, O_EXCL) != -1))
    {
        int F = open(path, O_RDWR);
        if (F == -1)
        {
            printf("Error while opening the file.\n");
            close(F);
            return 0;
        }
        lseek(F, 0, SEEK_SET);
        read(F, &context->id, 4);
        lseek(F, 4, SEEK_SET);
        read(F, &context->counter, 4);
    }

    return context;
}