#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../6-1/structs.h"
#define SIZE 256
int id_counter = 0;
int contact_counter = 0;

Contact *InsertEmail(char email[SIZE], Contact *head, int target)
{
    Contact *tmp = head;
    if (NULL == head)
    {
        printf("Contact list is empty\n");
        return head;
    }
    else
    {
        int count = 0;
        do
        {
            if (target == count)
            {
                if (tmp->person.email_counter + 1 < SIZE)
                {
                    for (int i = 0; i < tmp->person.email_counter; i++)
                    {
                        if (strcmp(tmp->person.emails[i].email, "") == 0)
                        {
                            strcpy(tmp->person.emails[i].email, email);
                            tmp->person.email_counter++;
                            return tmp;
                        }
                    }
                    strcpy(tmp->person.emails[tmp->person.email_counter].email, email);
                    count++;
                    tmp->person.email_counter++;
                    return tmp;
                }

                else
                {
                    printf("Maximum amount of emails are reached already\n");
                    return head;
                }
            }
            tmp = tmp->next;
        } while (tmp != head);
    }
    printf("List does not contain contact with this id %d!\n", target);
    return head;
}

Contact *InsertPhonenumber(char number[SIZE], Contact *head, int target)
{
    Contact *tmp = head;
    if (NULL == head)
    {
        printf("Contact list is empty\n");
        return head;
    }
    else
    {
        int count = 0;
        do
        {
            if (target == count)
            {
                if (tmp->person.phonenumbers_counter + 1 < SIZE)
                {
                    for (int i = 0; i < tmp->person.phonenumbers_counter; i++)
                    {
                        if (strcmp(tmp->person.phonenumbers[i].phonenumber, "") == 0)
                        {
                            strcpy(tmp->person.phonenumbers[i].phonenumber, number);
                            tmp->person.phonenumbers_counter++;
                            return tmp;
                        }
                    }
                    strcpy(tmp->person.phonenumbers[tmp->person.phonenumbers_counter].phonenumber, number);
                    count++;
                    tmp->person.phonenumbers_counter++;
                }

                else
                    printf("Maximum amount of emails are reached already\n");
                return tmp;
            }
            tmp = tmp->next;
        } while (tmp != head);
    }
    printf("List does not contain contact with this id%d!\n", target);
    return head;
}

Contact *InsertSocial(char social[SIZE], Contact *head, int target)
{
    Contact *tmp = head;
    if (NULL == head)
    {
        printf("Contact list is empty\n");
        return head;
    }
    else
    {
        do
        {
            int count = 0;
            if (target == count)
            {
                if (tmp->person.socials_counter + 1 < SIZE)
                {
                    for (int i = 0; i < tmp->person.socials_counter; i++)
                    {
                        if (strcmp(tmp->person.socials[i].social, "") == 0)
                        {
                            strcpy(tmp->person.socials[i].social, social);
                            tmp->person.socials_counter++;
                            return tmp;
                        }
                    }
                    strcpy(tmp->person.socials[tmp->person.socials_counter].social, social);
                    count++;
                    tmp->person.socials_counter++;
                }
                else
                    printf("Maximum amount of emails are reached already\n");
                return tmp;
            }
            tmp = tmp->next;
        } while (tmp != head);
    }
    printf("List does not contain contact with this id%d!\n", target);
    return head;
}

Contact *InsertContact(Person *person, Contact *head)
{
    Contact *newItem;
    newItem = malloc(sizeof(Contact));
    newItem->person = *person;
    newItem->ID = id_counter;
    printf("Type name\n");
    char buf[SIZE];
    scanf("%s", buf);
    strcpy(newItem->person.name, buf);

    printf("Type lastname\n");
    scanf("%s", buf);
    strcpy(newItem->person.lastname, buf);

    printf("Type workplace, - to skip\n");
    scanf("%s", buf);
    strcpy(newItem->person.workplace, buf);

    printf("Type job, - to skip\n");
    scanf("%s", buf);
    strcpy(newItem->person.job, buf);

    id_counter++;
    if (NULL == head)
    {
        newItem->prev = newItem;
        newItem->next = newItem;
        head = newItem;
    }
    else
    {
        newItem->next = head;
        newItem->prev = head->prev;
        head->prev->next = newItem;
        head->prev = newItem;
    }
    contact_counter++;
    printf("Added new contact!\n");
    return head;
}

Contact *DeleteContact(int target, Contact *head)
{
    Contact *tmp = head;
    if (NULL == head)
    {
        printf("List empty!\n");
        return head;
    }
    int count = 0;
    do
    {
        if (target == count)
        {
            if (contact_counter == 1)
            {
                free(tmp);
                return NULL;
            }

            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            if (tmp == head)
                head = head->next;
            printf("Deleted Contact, ID:%d!\n", target);
            contact_counter--;
            free(tmp);
            return head;
        }
        count++;
        tmp = tmp->next;
    } while (tmp != head);
    printf("List does not contain contact with this id%d!\n", target);
    return head;
}

Contact *UpdateEmail(int target, Contact *head, int num, char value[SIZE])
{
    Contact *tmp = head;
    if (NULL == head)
    {
        printf("List empty!\n");
        return head;
    }
    do
    {
        if (target == tmp->ID)
        {
            if (tmp->person.email_counter > 0 && tmp->person.email_counter > num)
            {
                strcpy(tmp->person.emails[num].email, value);
                printf("Email deleted\n");
                return head;
            }
            else
            {
                printf("This contact has no emails\n");
                return head;
            }
        }
        tmp = tmp->next;
    } while (tmp != head);
    printf("Error\n");
    return head;
}

Contact *UpdatePhonenumber(int id, Contact *head, int num, char value[SIZE])
{
    Contact *tmp = head;
    if (NULL == head)
    {
        printf("List empty!\n");
        return head;
    }
    do
    {
        if (id == tmp->ID)
        {
            if (tmp->person.phonenumbers_counter > 0 && tmp->person.phonenumbers_counter > num)
            {
                strcpy(tmp->person.phonenumbers[num].phonenumber, value);
                printf("Phonenumber deleted\n");
                return head;
            }
            else
            {
                printf("This contact has no emails\n");
                return head;
            }
        }
        tmp = tmp->next;
    } while (tmp != head);
    printf("Error");
    return head;
}

Contact *UpdateSocial(int id, Contact *head, int num, char value[SIZE])
{
    Contact *tmp = head;
    if (NULL == head)
    {
        printf("List empty!\n");
        return head;
    }
    do
    {
        if (id == tmp->ID)
        {
            if (tmp->person.socials_counter > 0 && tmp->person.socials_counter > num)
            {
                strcpy(tmp->person.socials[num].social, value);
                printf("Social Media deleted\n");
                return head;
            }
            else
            {
                printf("This contact has no emails\n");
                return head;
            }
        }
        tmp = tmp->next;
    } while (tmp != head);
    printf("Error");
    return head;
}

void PrintList(Contact *head)
{
    Contact *tmp = head;
    if (head == NULL)
    {
        printf("List empty!\n");
        return;
    }
    int count = 1;
    do
    {
        if (tmp != NULL)
        {
            printf("%d ", count);
            printf("Name: %s", tmp->person.name);
            printf("\n");
            printf("Lastname: %s", tmp->person.lastname);
            printf("\n");
            printf("Workplace: %s", tmp->person.workplace);
            printf("\n");
            printf("Job: %s", tmp->person.job);
            printf("\n");
            printf("Emails:");
            printf("\n");
            if (tmp->person.email_counter > 0)
                for (int i = 0; i < SIZE; i++)
                {
                    if (strcmp(tmp->person.emails[i].email, ""))
                    {
                        printf("%s", tmp->person.emails[i].email);
                        printf("\n");
                    }
                }
            else
                printf("-\n");
            printf("Phonenumbers:\n");
            if (tmp->person.phonenumbers_counter > 0)
                for (int i = 0; i < SIZE; i++)
                {
                    if (strcmp(tmp->person.phonenumbers[i].phonenumber, ""))
                    {
                        printf("%s", tmp->person.phonenumbers[i].phonenumber);
                        printf("\n");
                    }
                }
            else
                printf("-\n");
            printf("Social medias:\n");
            if (tmp->person.socials_counter > 0)
                for (int i = 0; i < SIZE; i++)
                {
                    if (strcmp(tmp->person.socials[i].social, ""))
                    {
                        printf("%s", tmp->person.socials[i].social);
                        printf("\n");
                    }
                }
            else
                printf("-\n");
        }
        tmp = tmp->next;
    } while (tmp != head);
}

Person *CreateContact()
{
    Person *p = malloc(sizeof(Person));

    while (1)
    {
        char buffer[256];
        printf("%s", "Type email, to skip press \"-\"):\n ");
        scanf("%s", buffer);
        if (strlen(buffer) >= SIZE)
        {
            printf("%s", "Only 256 symbols\n");
            continue;
        }
        if (strlen(buffer) == 1 && buffer[0] == '-')
        {
            break;
        }
        strcpy(p->emails[p->email_counter].email, buffer);
        p->email_counter++;
        while (1)
        {
            printf("%s", "Type email, to end press  \"-\"):\n ");
            scanf("%s", buffer);
            if (strlen(buffer) == 1 && buffer[0] == '-')
            {
                break;
            }
            strcpy(p->emails[p->email_counter].email, buffer);
            p->email_counter++;
        }
        break;
    }

    while (1)
    {
        char buffer[11];
        printf("%s", "Type phonenumber, to skip press \"-\"):\n ");
        scanf("%s", buffer);
        if (strlen(buffer) == 1 && buffer[0] == '-')
        {
            break;
        }
        if (strlen(buffer) >= 11)
        {
            printf("%s", "Only 11 symbols!\n");
            continue;
        }
        bool is_numeric = true;
        for (int i = 0; i < strlen(buffer); i++)
        {
            if (!isdigit(buffer[i]))
            {
                is_numeric = false;
                break;
            }
        }
        if (!is_numeric)
        {
            printf("%s", "Only numbers!\n");
            continue;
        }

        strcpy(p->phonenumbers[p->phonenumbers_counter].phonenumber, buffer);
        p->phonenumbers_counter++;
        while (1)
        {
            printf("%s", "Type phonenumber, to end press \"-\"):\n ");
            scanf("%s", buffer);
            if (strlen(buffer) == 1 && buffer[0] == '-')
            {
                break;
            }

            strcpy(p->phonenumbers[p->phonenumbers_counter].phonenumber, buffer);
            p->phonenumbers_counter++;
        }
        break;
    }

    while (1)
    {
        char buffer[11];
        printf("%s", "Type link to social media, to skip press \"-\"):\n ");
        scanf("%s", buffer);
        if (strlen(buffer) >= 256)
        {
            printf("%s", "Only 256 symbols!\n");
            continue;
        }
        if (strlen(buffer) == 1 && buffer[0] == '-')
        {
            break;
        }
        strcpy(p->socials[p->socials_counter].social, buffer);
        p->socials_counter++;
        while (1)
        {
            printf("%s", "Type link to social media, to end press \"-\"):\n ");
            scanf("%s", buffer);
            if (strlen(buffer) == 1 && buffer[0] == '-')
            {
                break;
            }
            strcpy(p->socials[p->socials_counter].social, buffer);
            p->socials_counter++;
        }
        break;
    }

    return p;
}

Contact *Menu(Contact *head)
{
    int target;
    int count = 1;
    Contact *tmp = head;
    int choice;
    printf("Choose action\n");
    printf("1) Insert contact\n");
    printf("2) Print contacts\n");
    printf("3) Delete contacts\n");
    printf("4) Update contact name\n");
    printf("5) Update contact lastname\n");
    printf("6) Update contact workplace\n");
    printf("7) Update contact job\n");
    printf("8) Insert email\n");
    printf("9) Insert phonenumber\n");
    printf("10) Insert social\n");
    printf("11) Delete email\n");
    printf("12) Delete phonenumber\n");
    printf("13) Delete social\n");
    printf("14) Update email\n");
    printf("15) Update phonenumber\n");
    printf("16) Update social\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        Person *p = malloc(sizeof(Person));
        p = CreateContact();
        head = InsertContact(p, head);
        break;
    case 2:
        PrintList(head);
        break;
    case 3:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        int target;
        printf("Choose contact to delete\n");
        scanf("%d", &target);
        if (target > 0 && target < contact_counter)
            DeleteContact(target - 1, head);
        else
            printf("Input error\n");
        count = 0;
        break;
    case 4:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact to update\n");

        scanf("%d", &target);
        printf("Type name\n");
        char new_name[SIZE];
        scanf("%s", new_name);
        do
        {
            if (target - 1 == count)
            {
                strcpy(tmp->person.name, new_name);
            }
            count++;
            tmp = tmp->next;
        } while (tmp != head);
        break;
    case 5:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact to update\n");

        scanf("%d", &target);
        printf("Type lastname\n");
        char new_lastname[SIZE];
        scanf("%s", new_lastname);
        do
        {
            if (target - 1 == count)
            {
                strcpy(tmp->person.lastname, new_lastname);
            }
            count++;
            tmp = tmp->next;
        } while (tmp != head);
        break;
    case 6:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact to update\n");

        scanf("%d", &target);
        printf("Type workplace\n");
        char new_workplace[SIZE];
        scanf("%s", new_workplace);
        do
        {
            if (target - 1 == count)
            {
                strcpy(tmp->person.workplace, new_workplace);
            }
            count++;
            tmp = tmp->next;
        } while (tmp != head);
        break;
    case 7:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact to update\n");

        scanf("%d", &target);
        printf("Type job\n");
        char new_job[SIZE];
        scanf("%s", new_job);
        do
        {
            if (target - 1 == count)
            {
                strcpy(tmp->person.job, new_job);
            }
            count++;
            tmp = tmp->next;
        } while (tmp != head);
        break;
    case 8:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact\n");
        scanf("%d", &target);
        char email[SIZE];
        printf("Type value\n");
        scanf("%s", email);
        if (strlen(email) >= SIZE)
        {
            printf("%s", "Only 256 symbols!\n");
            break;
        }
        if (target > 0 && target < contact_counter)
            InsertEmail(email, head, target - 1);
        else
            printf("Input error\n");
        count = 0;
        break;
    case 9:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact\n");
        scanf("%d", &target);
        char number[SIZE];
        printf("Type value\n");
        scanf("%s", number);
        bool is_numeric = true;
        for (int i = 0; i < strlen(number); i++)
        {
            if (!isdigit(number[i]))
            {
                is_numeric = false;
                break;
            }
        }
        if (!is_numeric)
        {
            printf("%s", "Only numbers!\n");
            break;
        }
        if (strlen(number) >= 11)
        {
            printf("%s", "Only 11 symbols!\n");
            break;
        }
        if (target > 0 && target < contact_counter)
            InsertPhonenumber(number, head, target - 1);
        else
            printf("Input error\n");
        count = 0;
        break;
    case 10:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact\n");
        scanf("%d", &target);
        char social[SIZE];
        printf("Type value\n");
        scanf("%s", social);
        if (strlen(social) >= SIZE)
        {
            printf("%s", "Only 256 symbols!\n");
            break;
        }
        if (target > 0 && target < contact_counter)
            InsertSocial(social, head, target - 1);
        else
            printf("Input error\n");
        count = 0;
        break;
    case 11:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact\n");
        scanf("%d", &target);
        int c = 0;
        int ec = 1;
        int target_email;
        printf("Choose email\n");
        if (tmp->person.email_counter > 0)
            for (int i = 0; i < SIZE; i++)
            {
                if (strcmp(tmp->person.emails[i].email, ""))
                {
                    printf("%d ", ec);
                    printf("%s", tmp->person.emails[i].email);
                    printf("\n");
                }
                ec++;
            }
        scanf("%d", &target_email);
        if (target > 0 && target < contact_counter)
        {
            tmp = head;
            do
            {
                if (c == target - 1)
                    UpdateEmail(target, head, target_email - 1, "");
                c++;
                tmp = tmp->next;
            } while (tmp != head);
        }
        else
        {
            printf("Input error\n");
            return 0;
        }
        count = 0;
        break;
    case 12:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact\n");
        scanf("%d", &target);
        int cn = 0;
        int en = 1;
        int target_number;
        printf("Choose phonenumber\n");
        if (tmp->person.phonenumbers_counter > 0)
            for (int i = 0; i < SIZE; i++)
            {
                if (strcmp(tmp->person.phonenumbers[i].phonenumber, ""))
                {
                    printf("%d ", en);
                    printf("%s", tmp->person.phonenumbers[i].phonenumber);
                    printf("\n");
                    en++;
                }
            }
        scanf("%d", &target_number);
        if (target > 0 && target < contact_counter)
        {
            tmp = head;
            do
            {
                if (cn == target - 1)
                    UpdatePhonenumber(target, head, target_number - 1, "");
                cn++;
                tmp = tmp->next;
            } while (tmp != head);
        }
        else
        {
            printf("Input error\n");
            return 0;
        }
        count = 0;
        break;
    case 13:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact\n");
        scanf("%d", &target);
        int cs = 0;
        int sc = 1;
        int target_social;
        printf("Choose social\n");
        if (tmp->person.socials_counter > 0)
            for (int i = 0; i < SIZE; i++)
            {
                if (strcmp(tmp->person.socials[i].social, ""))
                {
                    printf("%d ", sc);
                    printf("%s", tmp->person.socials[i].social);
                    printf("\n");
                    sc++;
                }
            }
        scanf("%d", &target_social);
        if (target > 0 && target < contact_counter)
        {
            tmp = head;
            do
            {
                if (cs == target - 1)
                    UpdateSocial(target, head, target_social - 1, "");
                cs++;
                tmp = tmp->next;
            } while (tmp != head);
        }
        else
        {
            printf("Input error\n");
            return 0;
        }
        count = 0;
        break;
    case 14:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact\n");
        scanf("%d", &target);
        int ce = 0;
        int ecu = 1;
        int target_email_to_update;
        printf("Choose email\n");
        if (tmp->person.email_counter > 0)
            for (int i = 0; i < SIZE; i++)
            {
                if (strcmp(tmp->person.emails[i].email, ""))
                {
                    printf("%d ", ecu);
                    printf("%s", tmp->person.emails[i].email);
                    printf("\n");
                }
                ecu++;
            }
        scanf("%d", &target_email_to_update);
        char new_email[SIZE];
        printf("Type email\n");
        scanf("%s", new_email);
        if (target > 0 && target < contact_counter)
        {
            tmp = head;
            do
            {
                if (ce == target - 1)
                    UpdateEmail(target, head, target_email_to_update - 1, new_email);
                ce++;
                tmp = tmp->next;
            } while (tmp != head);
        }
        else
        {
            printf("Input error\n");
            return 0;
        }
        count = 0;
        break;
    case 15:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact\n");
        scanf("%d", &target);
        int cnn = 0;
        int enn = 1;
        int target_number_to_update;
        printf("Choose phonenumber\n");
        if (tmp->person.phonenumbers_counter > 0)
            for (int i = 0; i < SIZE; i++)
            {
                if (strcmp(tmp->person.phonenumbers[i].phonenumber, ""))
                {
                    printf("%d ", enn);
                    printf("%s", tmp->person.phonenumbers[i].phonenumber);
                    printf("\n");
                    enn++;
                }
            }
        scanf("%d", &target_number);
        char new_number[11];
        printf("Type phonenumber\n");
        scanf("%s", new_number);
        if (target > 0 && target < contact_counter)
        {
            tmp = head;
            do
            {
                if (cnn == target - 1)
                    UpdatePhonenumber(target, head, target_number - 1, new_number);
                cnn++;
                tmp = tmp->next;
            } while (tmp != head);
        }
        else
        {
            printf("Input error\n");
            return 0;
        }
        count = 0;
        break;
    case 16:
        do
        {
            if (tmp != NULL)
            {
                printf("%d ", count);
                printf("Name: %s", tmp->person.name);
                printf("\n");
                printf("Lastname: %s", tmp->person.lastname);
                printf("\n");
                printf("Workplace: %s", tmp->person.workplace);
                printf("\n");
                printf("Job: %s", tmp->person.job);
                printf("\n");
            }
            tmp = tmp->next;
        } while (tmp != head);
        printf("Choose contact\n");
        scanf("%d", &target);
        int scs = 0;
        int ssc = 1;
        int target_social_to_update;
        printf("Choose social\n");
        if (tmp->person.socials_counter > 0)
            for (int i = 0; i < SIZE; i++)
            {
                if (strcmp(tmp->person.socials[i].social, ""))
                {
                    printf("%d ", ssc);
                    printf("%s", tmp->person.socials[i].social);
                    printf("\n");
                }
                ssc++;
            }
        scanf("%d", &target_social);
        printf("Type social\n");
        char new_social[256];
        scanf("%s", new_social);
        if (target > 0 && target < contact_counter)
        {
            tmp = head;
            do
            {
                if (scs == target - 1)
                    UpdateSocial(target, head, target_social_to_update - 1, new_social);
                scs++;
                tmp = tmp->next;
            } while (tmp != head);
        }
        else
        {
            printf("Input error\n");
            return 0;
        }
        count = 0;
        break;
    case 17:
        break;
    default:
        printf("Input error\n");
        break;
    }
    return head;
}