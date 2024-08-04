#pragma once 
#include <stdio.h>
#include <stdlib.h>
#define SIZE 256

typedef struct Context
{
    int active, deleted, id;
} Context;

typedef struct Phonenumber
{
    char phonenumber[SIZE];
} Phonenumber;

typedef struct Email
{
    char email[SIZE];
} Email;

typedef struct Social
{
    char social[SIZE];
} Social;

typedef struct Person
{
    char name[SIZE],
     lastname[SIZE],
          job[SIZE],
    workplace[SIZE];

    Email emails[SIZE]; Phonenumber phonenumbers[SIZE]; Social socials[SIZE];
    
    int email_counter,  phonenumbers_counter, socials_counter;    
} Person;

typedef struct Contact
{
    Person person;
    int id,deleted,*next;  
} Contact;