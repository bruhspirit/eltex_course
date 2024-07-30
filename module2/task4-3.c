#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 256
int id_counter = 0;
int contacts_counter = 0;

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
    char name[SIZE];
    char lastname[SIZE];
    char job[SIZE];
    char workplace[SIZE];
    Email emails[SIZE];
    Phonenumber phonenumbers[SIZE];
    Social socials[SIZE];
    int email_counter;
    int phonenumbers_counter;
    int socials_counter;
} Person;

typedef struct Contact
{
    int ID;
    Person person;
    struct Contact *left;
    struct Contact *right;
} Contact;

int *Ins_Contact(Person *p, Contact **q)
{
    if (*q == NULL)
    {
        *q = calloc(1, sizeof(Contact));
        if (*q == NULL)
        {
            perror("Failed to allocate memory for Contact");
            exit(EXIT_FAILURE);
        }
        (*q)->left = NULL;
        (*q)->right = NULL;
        (*q)->person = *p;
        (*q)->ID = id_counter++;
        contacts_counter++;
        return 1;
    }

    if (strcmp((*q)->person.name, p->name) > 0)
        Ins_Contact(p, &(*q)->left);
    else
        Ins_Contact(p, &(*q)->right);
}

void Print_Btree(Contact *p)
{
    if (p == NULL)
        return;

    Print_Btree(p->left);

    if (p->ID >= 0)
    {
        printf("ID: %d\n", p->ID);
    }

    if (p->person.name != NULL)
    {
        printf("Name: %s\n", p->person.name);
    }
    if (p->person.lastname != NULL)
    {
        printf("Last Name: %s\n", p->person.lastname);
    }
    if (p->person.workplace != NULL)
    {
        printf("Workplace: %s\n", p->person.workplace);
    }
    if (p->person.job != NULL)
    {
        printf("Job: %s\n", p->person.job);
    }

    if (p->person.email_counter > 0 && p->person.emails != NULL)
    {
        printf("Emails: \n");
        for (int i = 0; i < p->person.email_counter; i++)
        {
            if (p->person.emails[i].email != NULL)
            {
                printf("%d ", i + 1);
                printf("%s\n", p->person.emails[i].email);
            }
        }
    }
    else
    {
        printf("Emails: -\n");
    }

    if (p->person.phonenumbers_counter > 0 && p->person.phonenumbers != NULL)
    {
        printf("Phonenumbers: \n");
        for (int i = 0; i < p->person.phonenumbers_counter; i++)
        {
            if (p->person.phonenumbers[i].phonenumber != NULL)
            {
                printf("%d ", i + 1);
                printf("%s\n", p->person.phonenumbers[i].phonenumber);
            }
        }
    }
    else
    {
        printf("Phonenumbers: -\n");
    }

    if (p->person.socials_counter > 0 && p->person.socials != NULL)
    {
        printf("Social media links: \n");
        for (int i = 0; i < p->person.socials_counter; i++)
        {
            if (p->person.socials[i].social != NULL)
            {
                printf("%d ", i + 1);
                printf("%s\n", p->person.socials[i].social);
            }
        }
    }
    else
    {
        printf("Social media links: -\n");
    }

    Print_Btree(p->right);
}

int *DeleteContact(int id, Contact **node)
{
    Contact *t, *up;
    if (*node == NULL)
        return 0;
    if ((*node)->ID == id)
    {
        if (((*node)->left == NULL) && ((*node)->right == NULL))
        {
            free(*node);
            contacts_counter--;
            *node = NULL;
            printf("Delete List\n");
            return 1;
        }

        if ((*node)->left == NULL)
        {
            t = *node;
            *node = (*node)->right;
            contacts_counter--;
            free(t);
            printf("Delete Left = 0\n");
            return 1;
        }

        if ((*node)->right == NULL)
        {
            t = *node;
            *node = (*node)->left;
            contacts_counter--;
            free(t);
            printf("Delete Right = 0\n");
            return 1;
        }

        up = *node;
        t = (*node)->left;

        while (t->right != NULL)
        {
            up = t;
            t = t->right;
        }

        (*node)->ID = t->ID;
        (*node)->person = t->person;

        if (up != (*node))
        {
            if (t->left != NULL)
                up->right = t->left;
            else
                up->right = NULL;
        }
        else
            (*node)->left = t->left;
        contacts_counter--;
        free(t);
        printf("Delete Two\n");
        return 1;
    }
    if ((*node)->ID < id)
        return DeleteContact(id, &(*node)->right);
    return DeleteContact(id, &(*node)->left);
}

int UpdateContact(int id, Contact **node, Person *p)
{
    Contact *t, *up;
    if (*node == NULL)
        return 0;
    if ((*node)->ID == id)
    {
        (*node)->person = *p;
        return 1;
    }
    if ((*node)->ID < id)
        return UpdateContact(id, &(*node)->right, p);
    return UpdateContact(id, &(*node)->left, p);
}

int AddEmail(int id, Contact **node, char value[SIZE])
{
    Contact *t, *up;
    if (*node == NULL)
    {
        printf("%s\n", "Error: Contact not found");
        return 0;
    }
    if ((*node)->ID == id)
    {
        int added = 0;
        for (int i = 0; i < (*node)->person.email_counter; i++)
        {
            if ((*node)->person.emails[i].email == "-")
            {
                strcpy((*node)->person.emails[i].email, value);
                (*node)->person.email_counter++;
                added = 1;
                break;
            }
        }
        if (added == 0)
        {
            if ((*node)->person.email_counter + 1 < SIZE)
            {
                strcpy((*node)->person.emails[(*node)->person.email_counter++].email, value);
                added = 1;
            }
            else
            {
                printf("%s\n", "Error: Max amount of emails are reached!");
                return 0;
            }
        }
        return 1;
    }
    if ((*node)->ID < id)
        return AddEmail(id, &(*node)->right, value);
    return AddEmail(id, &(*node)->left, value);
}

int UpdateEmail(int id, Contact **node, char value[SIZE], int index)
{
    Contact *t, *up;
    if (*node == NULL)
    {
        printf("%s\n", "Error: Contact not found");
        return 0;
    }
    if ((*node)->ID == id)
    {
        int updated = 0;
        if (index < 0 || index > (*node)->person.email_counter)
        {
            printf("%s\n", "Input error");
            return 0;
        }
        for (int i = 0; i < (*node)->person.email_counter; i++)
        {
            if (index == i)
            {
                strcpy((*node)->person.emails[i].email, value);
                updated = 1;
                if (value == "-")
                    (*node)->person.email_counter--;
                break;
            }
        }
        if (updated == 0)
        {
            printf("%s\n", "Error: Email not found");
            return 0;
        }
        return 1;
    }
    if ((*node)->ID < id)
        return UpdateEmail(id, &(*node)->right, value, index);
    return UpdateEmail(id, &(*node)->left, value, index);
}

int AddPhonenumber(int id, Contact **node, char value[11])
{
    Contact *t, *up;
    if (*node == NULL)
    {
        printf("%s\n", "Error: Contact not found");
        return 0;
    }
    if ((*node)->ID == id)
    {
        int added = 0;
        for (int i = 0; i < (*node)->person.phonenumbers_counter; i++)
        {
            if ((*node)->person.phonenumbers[i].phonenumber == "-")
            {
                strcpy((*node)->person.phonenumbers[i].phonenumber, value);
                (*node)->person.phonenumbers_counter++;
                added = 1;
                break;
            }
        }
        if (added == 0)
        {
            if ((*node)->person.phonenumbers_counter + 1 < SIZE)
            {
                strcpy((*node)->person.phonenumbers[(*node)->person.phonenumbers_counter++].phonenumber, value);
                added = 1;
            }
            else
            {
                printf("%s\n", "Error: Max amount of phonenumbers are reached!");
                return 0;
            }
        }
        return 1;
    }
    if ((*node)->ID < id)
        return AddPhonenumber(id, &(*node)->right, value);
    return AddPhonenumber(id, &(*node)->left, value);
}

int UpdatePhonenumber(int id, Contact **node, char value[11], int index)
{
    Contact *t, *up;
    if (*node == NULL)
    {
        printf("%s\n", "Error: Contact not found");
        return 0;
    }
    if ((*node)->ID == id)
    {
        int updated = 0;
        if (index < 0 || index > (*node)->person.phonenumbers_counter)
        {
            printf("%s\n", "Input error");
            return 0;
        }
        for (int i = 0; i < (*node)->person.phonenumbers_counter; i++)
        {
            if (index == i)
            {
                strcpy((*node)->person.phonenumbers[i].phonenumber, value);
                updated = 1;
                if (value == "-")
                    (*node)->person.phonenumbers_counter--;
                break;
            }
        }
        if (updated == 0)
        {
            printf("%s\n", "Error: Phonenumber not found");
            return 0;
        }
        return 1;
    }
    if ((*node)->ID < id)
        return UpdatePhonenumber(id, &(*node)->right, value, index);
    return UpdatePhonenumber(id, &(*node)->left, value, index);
}

int AddSocial(int id, Contact **node, char value[SIZE])
{
    Contact *t, *up;
    if (*node == NULL)
    {
        printf("%s\n", "Error: Contact not found");
        return 0;
    }
    if ((*node)->ID == id)
    {
        int added = 0;
        for (int i = 0; i < (*node)->person.socials_counter; i++)
        {
            if ((*node)->person.socials[i].social == "-")
            {
                strcpy((*node)->person.socials[i].social, value);
                (*node)->person.socials_counter++;
                added = 1;
                break;
            }
        }
        if (added == 0)
        {
            if ((*node)->person.socials_counter + 1 < SIZE)
            {
                strcpy((*node)->person.socials[(*node)->person.socials_counter++].social, value);
                added = 1;
            }
            else
            {
                printf("%s\n", "Error: Max amount of social medias are reached!");
                return 0;
            }
        }
        return 1;
    }
    if ((*node)->ID < id)
        return AddSocial(id, &(*node)->right, value);
    return AddSocial(id, &(*node)->left, value);
}

int UpdateSocial(int id, Contact **node, char value[SIZE], int index)
{
    Contact *t, *up;
    if (*node == NULL)
    {
        printf("%s\n", "Error: Contact not found");
        return 0;
    }
    if ((*node)->ID == id)
    {
        int updated = 0;
        if (index < 0 || index > (*node)->person.socials_counter)
        {
            printf("%s\n", "Input error");
            return 0;
        }
        for (int i = 0; i < (*node)->person.socials_counter; i++)
        {
            if (index == i)
            {
                strcpy((*node)->person.socials[i].social, value);
                updated = 1;
                if (value == "-")
                    (*node)->person.socials_counter--;
                break;
            }
        }
        if (updated == 0)
        {
            printf("%s\n", "Error: Social media not found");
            return 0;
        }
        return 1;
    }
    if ((*node)->ID < id)
        return UpdateSocial(id, &(*node)->right, value, index);
    return UpdateSocial(id, &(*node)->left, value, index);
}

int IsNumeric(char phonenumber[11])
{
    int is_numeric = 1;
    for (int i = 0; i < strlen(phonenumber); i++)
    {
        if (!isdigit(phonenumber[i]))
        {
            is_numeric = 0;
            break;
        }
    }
    if (!is_numeric)
    {
        printf("%s", "Only numbers!\n");
        return 0;
    }
    return 1;
}

Person *CreatePerson()
{
    Person *p = calloc(1, sizeof(Person));
    if (p == NULL)
    {
        perror("Failed to allocate memory for Contact");
        exit(EXIT_FAILURE);
    }
    char name[SIZE];
    char lastname[SIZE];
    char workplace[SIZE];
    char job[SIZE];
    char email[SIZE];
    char social[SIZE];
    char phonenumber[SIZE];
    int choice;
    printf("%s\n\n", "Type name");
    scanf("%s", name);
    printf("%s\n\n", "Type lastname");
    scanf("%s", lastname);
    printf("%s\n\n", "Type workplace, to skip press \"-\"");
    scanf("%s", workplace);
    printf("%s\n\n", "Type job, to skip press \"-\"");
    scanf("%s", job);
    strcpy(p->name, name), strcpy(p->lastname, lastname), strcpy(p->workplace, workplace), strcpy(p->job, job);
    printf("%s\n\n", "Type an email, to skip press \"-\"");
    scanf("%s", email);
    if (email[0] != '-')
    {
        strcpy(p->emails[0].email, email);
        p->email_counter++;
        while (1)
        {
            printf("%s\n\n", "Type an additional email, to skip press \"-\"");
            scanf("%s", email);
            strcpy(p->emails[p->email_counter++].email, email);
            p->email_counter++;
            if (email[0] == '-')
                break;
        }
    }
    printf("%s\n\n", "Type a phonenumber (11 symbols, only digits), to skip press \"-\"");
    scanf("%s", phonenumber);
    strcpy(p->phonenumbers[0].phonenumber, phonenumber);
    p->phonenumbers_counter++;
    if (phonenumber[0] != '-')
    {
        while (1)
        {
            if (phonenumber[0] != '-')
            {
                if (strlen(phonenumber) <= 11)
                {

                    printf("%s\n\n", "Type a additional phonenumber, to skip press \"-\"");
                    scanf("%s", phonenumber);

                    if (phonenumber[0] == '-')
                    {
                        strcpy(p->phonenumbers[p->phonenumbers_counter++].phonenumber, phonenumber);
                        p->phonenumbers_counter++;
                        break;
                    }

                    if (IsNumeric(phonenumber))
                    {
                        strcpy(p->phonenumbers[p->phonenumbers_counter++].phonenumber, phonenumber);
                        p->phonenumbers_counter++;
                    }
                    else
                    {
                        printf("%s\n\n", "Only digits!");
                        continue;
                    }
                }
                else
                {
                    printf("%s\n\n", "Only 11 symbols");
                }
            }
        }
    }
    printf("%s\n\n", "Type an social media link, to skip press \"-\"");
    scanf("%s", social);
    if (social[0] != '-')
    {
        strcpy(p->socials[0].social, social);
        p->socials_counter++;
        while (1)
        {
            printf("%s\n\n", "Type an additional social media link, to skip press \"-\"");
            scanf("%s", social);
            strcpy(p->socials[p->socials_counter++].social, social);
            p->socials_counter++;
            if (social[0] == '-')
            {
                break;
            }
        }
    }
    return p;
}

Contact *Menu(Contact *node)
{
    printf("%s\n\n", "===CHOOSE ACTION===");
    printf("%s\n", "1) Insert contact");
    printf("%s\n", "2) Delete contact");
    printf("%s\n", "3) Add email");
    printf("%s\n", "4) Delete email");
    printf("%s\n", "5) Update email");
    printf("%s\n", "6) Add phonenumber");
    printf("%s\n", "7) Delete phonenumber");
    printf("%s\n", "8) Update phonenumber");
    printf("%s\n", "9) Add social");
    printf("%s\n", "10) Delete social");
    printf("%s\n", "11) Update social");
    printf("%s\n", "12) Show contats");
    printf("%s\n", "13) Exit");

    int choice;
    int id;
    char value[SIZE];
    int index;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        Person *p = CreatePerson();
        Ins_Contact(p, &node);
        break;
    case 2:
        Print_Btree(node);
        printf("%s\n", "Type ID");
        scanf("%d", &id);
        DeleteContact(id, &node);
        break;
    case 3:
        Print_Btree(node);
        printf("%s\n", "Type ID");
        scanf("%d", &id);
        printf("%s\n", "Type value");
        scanf("%s", &value);
        AddEmail(id, &node, value);
        break;
    case 4:
        Print_Btree(node);
        printf("%s\n", "Type ID");
        scanf("%d", &id);
        printf("%s\n", "Type email index");
        scanf("%d", &index);
        UpdateEmail(id, &node, "-", index - 1);
        break;
    case 5:
        Print_Btree(node);
        printf("%s\n", "Type ID");
        scanf("%d", &id);
        printf("%s\n", "Type email index");
        scanf("%d", &index);
        printf("%s\n", "Type value");
        scanf("%s", &value);
        UpdateEmail(id, &node, value, index - 1);
        break;
    case 6:
        Print_Btree(node);
        printf("%s\n", "Type ID");
        scanf("%d", &id);
        printf("%s\n", "Type value");
        scanf("%s", &value);
        if (strlen(value < 11) && IsNumeric(value) == 1)
            AddPhonenumber(id, &node, value);
        else
            printf("%s\n", "Input error");
        break;

    case 7:
        Print_Btree(node);
        printf("%s\n", "Type ID");
        scanf("%d", &id);
        printf("%s\n", "Type phonenumber index");
        scanf("%d", &index);
        UpdatePhonenumber(id, &node, "-", index - 1);
    case 8:
        Print_Btree(node);
        printf("%s\n", "Type ID");
        scanf("%d", &id);
        printf("%s\n", "Type phonenumber index");
        scanf("%d", &index);
        printf("%s\n", "Type value");
        scanf("%s", &value);
        if (strlen(value < 11) && IsNumeric(value) == 1)
            AddPhonenumber(id, &node, value);
        else
            printf("%s\n", "Input error");
        UpdatePhonenumber(id, &node, value, index - 1);
        break;
    case 9:
        Print_Btree(node);
        printf("%s\n", "Type ID");
        scanf("%d", &id);
        printf("%s\n", "Type value");
        scanf("%s", &value);
        AddSocial(id, &node, value);
        break;
    case 10:
        Print_Btree(node);
        printf("%s\n", "Type ID");
        scanf("%d", &id);
        printf("%s\n", "Type social media index");
        scanf("%d", &index);
        UpdateSocial(id, &node, "-", index - 1);
        break;
    case 11:
        Print_Btree(node);
        printf("%s\n", "Type ID");
        scanf("%d", &id);
        printf("%s\n", "Type social media index");
        scanf("%d", &index);
        printf("%s\n", "Type value");
        scanf("%s", &value);
        UpdateSocial(id, &node, value, index - 1);
        break;
    case 12:
        Print_Btree(node);
        break;
    case 13:
        exit(0);
        break;
    default:
        break;
    }
    return node;
}

int main(int argc, char const *argv[])
{
    Contact *node = NULL;
    while (1)
    {
        node = Menu(node);
    }
    // Person *P = calloc(1, sizeof(Person));
    // if (P == NULL)
    // {
    //     perror("Failed to allocate memory for Person");
    //     return EXIT_FAILURE;
    // }

    // strcpy(P->name, "name");
    // strcpy(P->lastname, "lastname");
    // Ins_Contact(P, &C);
    // strcpy(P->name, "name1");
    // strcpy(P->lastname, "lastname1");
    // Ins_Contact(P, &C);
    // strcpy(P->name, "name2");
    // strcpy(P->lastname, "lastname2");
    // Ins_Contact(P, &C);
    // strcpy(P->name, "name4");
    // strcpy(P->lastname, "lastname4");
    // Print_Btree(C);
    // Print_Btree(C);
    // DeleteContact(1, &C);
    // UpdateContact(2, &C, P);
    // Print_Btree(C);
    // printf("Person Name: %s\n", P->name);
    free(node);
    return 0;
}