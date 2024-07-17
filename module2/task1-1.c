#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define SIZE 256

typedef struct
{
    char name[SIZE];
    char lastname[SIZE];
    char job[SIZE];
    char workplace[SIZE];
} Person;

typedef struct
{
    char phonenumber[SIZE];
} Phonnumber;

typedef struct
{
    char email[SIZE];
} Email;

typedef struct
{
    char social[SIZE];
} Social;

typedef struct
{
    int ID;
    Person person;
    Email emails[SIZE];
    Phonnumber phonenumbers[SIZE];
    Social socials[SIZE];
    int email_counter;
    int phonenumbers_counter;
    int socials_counter;
} Contact;

Contact *list[SIZE];
int id = 0;
int users = 0;

void pushToContacts(Contact *c)
{
    if (users >= SIZE)
    {
        printf("%s", "Недостаточно места!\n ");
        return;
    }
    list[users] = c;
    users++;
    return;
}

Person createPerson()
{
    Person *p = (Person *)malloc(sizeof(Person));
    char buffer[256];
    printf("%s", "Введите имя:\n ");
    scanf("%s", buffer);
    strcpy(p->name, buffer);
    printf("%s", "Введите фамилию:\n ");
    scanf("%s", buffer);
    strcpy(p->lastname, buffer);
    printf("%s", "Введите место работы (чтобы пропустить нажмите \"-\"):\n ");
    scanf("%s", buffer);
    strcpy(p->workplace, buffer);
    printf("%s", "Введите должность(чтобы пропустить нажмите \"-\"):\n ");
    scanf("%s", buffer);
    strcpy(p->job, buffer);
    return *p;
}

Contact createEmails(Contact *c)
{
    while (1)
    {
        char buffer[256];
        printf("%s", "Введите адрес электронной почты(чтобы пропустить нажмите \"-\"):\n ");
        scanf("%s", buffer);
        if (strlen(buffer) >= SIZE)
        {
            printf("%s", "Адрес электронной почты может состоять максимум из 256 символов\n");
            continue;
        }
        if (strlen(buffer) == 1 && buffer[0] == '-')
        {
            return *c;
        }
        strcpy(c->emails[c->email_counter].email, buffer);
        c->email_counter++;
        while (1)
        {
            printf("%s", "Введите дополнительный адрес электронной почты(чтобы закончить нажмите \"-\"):\n ");
            scanf("%s", buffer);
            if (strlen(buffer) == 1 && buffer[0] == '-')
            {
                break;
            }
            strcpy(c->emails[c->email_counter].email, buffer);
            c->email_counter++;
        }
        break;
    }
    return *c;
}

Contact createPN(Contact *c)
{
    while (1)
    {
        char buffer[11];
        printf("%s", "Введите номер телефона (чтобы пропустить нажмите \"-\"):\n ");
        scanf("%s", buffer);
        if (strlen(buffer) == 1 && buffer[0] == '-')
        {
            break;
        }
        if (strlen(buffer) >= 11)
        {
            printf("%s", "Номер телефона может состоять максимум из 11 символов\n");
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
            printf("%s", "Номер телефона может состоять только из цифр\n");
            continue;
        }

        strcpy(c->phonenumbers[c->phonenumbers_counter].phonenumber, buffer);
        c->phonenumbers_counter++;
        while (1)
        {
            printf("%s", "Введите дополнительный номер телефона(чтобы закончить нажмите \"-\"):\n ");
            scanf("%s", buffer);
            if (strlen(buffer) == 1 && buffer[0] == '-')
            {
                break;
            }
            strcpy(c->phonenumbers[c->phonenumbers_counter].phonenumber, buffer);
            c->phonenumbers_counter++;
        }
        break;
    }
    return *c;
}

Contact createSocials(Contact *c)
{
    while (1)
    {
        char buffer[11];
        printf("%s", "Введите ссылку на социальную сеть (чтобы пропустить нажмите \"-\"):\n ");
        scanf("%s", buffer);
        if (strlen(buffer) >= 256)
        {
            printf("%s", "Ссылку на социальную сеть может состоять из максимум 256 символов\n");
            continue;
        }
        if (strlen(buffer) == 1 && buffer[0] == '-')
        {
            break;
        }
        strcpy(c->socials[c->socials_counter].social, buffer);
        c->socials_counter++;
        while (1)
        {
            printf("%s", "Введите дополнительную ссылку на социальную сеть (чтобы закончить нажмите \"-\"):\n ");
            scanf("%s", buffer);
            if (strlen(buffer) == 1 && buffer[0] == '-')
            {
                break;
            }
            strcpy(c->socials[c->socials_counter].social, buffer);
            c->socials_counter++;
        }
        break;
    }
    return *c;
}

Contact createContact()
{
    Contact *c = (Contact *)malloc(sizeof(Contact));
    Person *p = (Person *)malloc(sizeof(Person));
    *p = createPerson();
    *c = createEmails(c);
    *c = createPN(c);
    *c = createSocials(c);
    c->person = *p;
    c->ID = id;
    id++;
    return *c;
}

void removeFromList()
{
    int counter = 1;
    int choice = 0;
    if (list[0] == NULL)
    {
        printf("%s", "Список контактов пуст\n");
        return;
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (list[i] == NULL)
            break;
        printf("%d", counter);
        counter++;
        printf("%s", ") ");
        printf("%s", "Имя, фамилия: ");
        printf("%s", list[i]->person.name);
        printf("%s", " ");
        printf("%s", list[i]->person.lastname);
        printf("%s", "\n");
    }

    printf("%s", "Введите номер контакта, который требуется удалить\n");
    scanf("%d", &choice);
    if (choice <= 0 || choice >= SIZE)
    {
        printf("%s", "Неверный номер контакта.\n");
        return;
    }
    for (int i = 1; i < SIZE; i++)
    {
        int z = i - 1;
        if (z == choice - 1)
        {
            for (int j = z; j < SIZE; j++)
            {
                if (j + 1 < SIZE)
                    list[j] = list[j + 1];
            }
        }
    }
    printf("%s", "Контакт удален\n");
}

void editName(int z)
{
    char new_value[256];
    printf("%s", "Введите новое значение:\n");
    scanf("%s", &new_value);
    strcpy(list[z]->person.name, new_value);
}

void editLastName(int z)
{
    char new_value[256];
    printf("%s", "Введите новое значение:\n");
    scanf("%s", &new_value);
    strcpy(list[z]->person.lastname, new_value);
}

void editJob(int z)
{
    char new_value[256];
    printf("%s", "Введите новое значение:\n");
    scanf("%s", &new_value);
    strcpy(list[z]->person.job, new_value);
}

void editWorkPlace(int z)
{
    char new_value[256];
    printf("%s", "Введите новое значение:\n");
    scanf("%s", &new_value);
    strcpy(list[z]->person.workplace, new_value);
}

void addEmail(int z)
{
    char new_value[256];
    printf("%s", "Введите новое значение:\n");
    scanf("%s", &new_value);
    strcpy(list[z]->emails[list[z]->email_counter].email, new_value);
    list[z]->email_counter++;
}

void addPN(int z)
{
    char new_value[256];
    printf("%s", "Введите новое значение:\n");
    scanf("%s", &new_value);
    strcpy(list[z]->phonenumbers[list[z]->phonenumbers_counter].phonenumber, new_value);
    list[z]->phonenumbers_counter++;
}

void addSocial(int z)
{
    char new_value[256];
    printf("%s", "Введите новое значение:\n");
    scanf("%s", &new_value);
    strcpy(list[z]->socials[list[z]->socials_counter].social, new_value);
    list[z]->socials_counter++;
}

void editEmail(int z)
{
    int counter = 1;
    int choice = 0;
    if (list[z]->email_counter == 0)
    {
        printf("%s", "У данного контакта нет ни 1 почты\n");
        return;
    }
    for (int i = 0; i < list[z]->email_counter; i++)
    {
        printf("%d", counter);
        printf("%s", ") ");
        printf("%s", list[z]->emails[i].email);
        printf("%s", "\n");
        counter++;
    }
    char new_value[256];
    printf("%s", "Введите номер почты для изменения\n");
    scanf("%d", &choice);
    if (choice > list[z]->email_counter || choice <= 0)
    {
        printf("%s", "Неверный порядковый номер\n");
        return;
    }

    printf("%s", "Введите новое значение\n");
    scanf("%s", &new_value);
    if (strlen(new_value) >= SIZE)
    {
        printf("%s", "Адрес электронной почты может состоять максимум из 256 символов\n");
        return;
    }
    for (int i = 0; i < list[z]->email_counter; i++)
        if (i == choice - 1)
        {
            strcpy(list[z]->emails[i].email, new_value);
            break;
        }
}

void editPN(int z)
{
    int counter = 1;
    int choice = 0;
    if (list[z]->phonenumbers_counter == 0)
    {
        printf("%s", "У данного контакта нет телефонных номеров\n");
        return;
    }
    for (int i = 0; i < list[z]->phonenumbers_counter; i++)
    {
        printf("%d", counter);
        printf("%s", ") ");
        printf("%s", list[z]->phonenumbers[i].phonenumber);
        printf("%s", "\n");
        counter++;
    }
    char new_value[256];
    printf("%s", "Введите порядковый номер телефона для изменения\n");
    scanf("%d", &choice);
    if (choice > list[z]->phonenumbers_counter || choice <= 0)
    {
        printf("%s", "Неверный порядковый номер\n");
        return;
    }

    printf("%s", "Введите новое значение\n");
    scanf("%s", &new_value);
    if (strlen(new_value) >= 11)
    {
        printf("%s", "Телефонный номер может состоять максимум из 11 символов\n");
        return;
    }
    for (int i = 0; i < list[z]->phonenumbers_counter; i++)
        if (i == choice - 1)
        {
            strcpy(list[z]->phonenumbers[i].phonenumber, new_value);
            break;
        }
}

void editSocial(int z)
{
    int counter = 1;
    int choice = 0;
    if (list[z]->socials_counter == 0)
    {
        printf("%s", "У данного контакта нет социальных сетей\n");
        return;
    }
    for (int i = 0; i < list[z]->socials_counter; i++)
    {
        printf("%d", counter);
        printf("%s", ") ");
        printf("%s", list[z]->socials[i].social);
        printf("%s", "\n");
        counter++;
    }
    char new_value[256];
    printf("%s", "Введите номер ссылки для изменения\n");
    scanf("%d", &choice);
    if (choice > list[z]->socials_counter || choice <= 0)
    {
        printf("%s", "Неверный порядковый номер\n");
        return;
    }

    printf("%s", "Введите новое значение\n");
    scanf("%s", &new_value);
    if (strlen(new_value) >= SIZE)
    {
        printf("%s", "Ссылка может состоять максимум из 256 символов\n");
        return;
    }
    for (int i = 0; i < list[z]->socials_counter; i++)
        if (i == choice - 1)
        {
            strcpy(list[z]->socials[i].social, new_value);
            break;
        }
}

void removeEmail(int z)
{
    int counter = 1;
    int choice = 0;
    if (list[z]->email_counter == 0)
    {
        printf("%s", "У данного контакта нет ни 1 почты\n");
        return;
    }
    for (int i = 0; i < list[z]->email_counter; i++)
    {
        printf("%d", counter);
        printf("%s", ") ");
        printf("%s", list[z]->emails[i].email);
        printf("%s", "\n");
        counter++;
    }
    char new_value[256];
    printf("%s", "Введите номер почты для удаления\n");
    scanf("%d", &choice);
    if (choice > list[z]->email_counter || choice <= 0)
    {
        printf("%s", "Неверный порядковый номер\n");
        return;
    }
    for (int i = 0; i < list[z]->email_counter; i++)
        if (i == choice - 1)
        {
            for (int j = i; j < SIZE; j++)
            {
                if (j + 1 < SIZE)
                    strcpy(list[z]->emails[j].email, list[z]->emails[j + 1].email);
            }
            list[z]->email_counter--;
            break;
        }
}

void removeSocial(int z)
{
    int counter = 1;
    int choice = 0;
    if (list[z]->socials_counter == 0)
    {
        printf("%s", "У данного контакта нет ни 1 почты\n");
        return;
    }
    for (int i = 0; i < list[z]->socials_counter; i++)
    {
        printf("%d", counter);
        printf("%s", ") ");
        printf("%s", list[z]->socials[i].social);
        printf("%s", "\n");
        counter++;
    }
    char new_value[256];
    printf("%s", "Введите номер ссылки для удаления\n");
    scanf("%d", &choice);
    if (choice > list[z]->socials_counter || choice <= 0)
    {
        printf("%s", "Неверный порядковый номер\n");
        return;
    }
    for (int i = 0; i < list[z]->socials_counter; i++)
        if (i == choice - 1)
        {
            for (int j = i; j < SIZE; j++)
            {
                if (j + 1 < SIZE)
                    strcpy(list[z]->socials[j].social, list[z]->socials[j + 1].social);
            }
            list[z]->socials_counter--;
            break;
        }
}

void removePN(int z)
{
    int counter = 1;
    int choice = 0;
    if (list[z]->phonenumbers_counter == 0)
    {
        printf("%s", "У данного контакта нет ни 1 почты\n");
        return;
    }
    for (int i = 0; i < list[z]->phonenumbers_counter; i++)
    {
        printf("%d", counter);
        printf("%s", ") ");
        printf("%s", list[z]->phonenumbers[i].phonenumber);
        printf("%s", "\n");
        counter++;
    }
    char new_value[256];
    printf("%s", "Введите номер ссылки для удаления\n");
    scanf("%d", &choice);
    if (choice > list[z]->phonenumbers_counter || choice <= 0)
    {
        printf("%s", "Неверный порядковый номер\n");
        return;
    }
    for (int i = 0; i < list[z]->phonenumbers_counter; i++)
        if (i == choice - 1)
        {
            for (int j = i; j < SIZE; j++)
            {
                if (j + 1 < SIZE)
                    strcpy(list[z]->phonenumbers[j].phonenumber, list[z]->phonenumbers[j + 1].phonenumber);
            }
            list[z]->phonenumbers_counter--;
            break;
        }
}

void updateContact()
{
    int counter = 1;
    int choice = 0;
    if (list[0] == NULL)
    {
        printf("%s", "Список контактов пуст\n");
        return;
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (list[i] == NULL)
            break;
        printf("%d", counter);
        counter++;
        printf("%s", ") ");
        printf("%s", "Имя, фамилия: ");
        printf("%s", list[i]->person.name);
        printf("%s", " ");
        printf("%s", list[i]->person.lastname);
        printf("%s", "\n");
    }

    printf("%s", "Введите номер контакта, который требуется отредактировать\n");
    scanf("%d", &choice);
    if (choice <= 0 || choice >= SIZE)
    {
        printf("%s", "Неверный номер контакта.\n");
        return;
    }
    int z = 0;
    for (int i = 1; i < SIZE; i++)
    {
        z = i - 1;
        if (z == choice - 1)
        {
            break;
        }
    }
    printf("%s", "Выберите действие:\n");
    printf("%s", "1) Изменить имя\n");
    printf("%s", "2) Изменить фамилию\n");
    printf("%s", "3) Изменить место работы\n");
    printf("%s", "4) Изменить должность\n");
    printf("%s", "5) Добавить почту\n");
    printf("%s", "6) Удалить почту\n");
    printf("%s", "7) Изменить почту\n");
    printf("%s", "8) Добавить номер телефона\n");
    printf("%s", "9) Удалить номер телефона\n");
    printf("%s", "10) Изменить номер телефона\n");
    printf("%s", "11) Добавить ссылку на соц.сеть\n");
    printf("%s", "12) Удалить ссылку на соц.сеть\n");
    printf("%s", "13) Изменить ссылку на соц.сеть\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        editName(z);
        break;
    case 2:
        editLastName(z);
        break;
    case 3:
        editWorkPlace(z);
        break;
    case 4:
        editJob(z);
        break;
    case 5:
        addEmail(z);
        break;
    case 6:
        removeEmail(z);
        break;
    case 7:
        editEmail(z);
        break;
    case 8:
        addPN(z);
        break;
    case 9:
        removePN(z);
        break;
    case 10:
        editPN(z);
        break;
    case 11:
        addSocial(z);
        break;
    case 12:
        removeSocial(z);
        break;
    case 13:
        editSocial(z);
        break;
    default:
        break;
    }
}

void print()
{
    int counter = 1;
    if (list[0] == NULL)
    {
        printf("%s", "Список пуст\n");
        return;
    }

    for (int i = 0; i < SIZE; i++)
    {
        if (list[i] == NULL)
            return;
        printf("%d", counter);
        counter++;
        printf("%s", ") ");
        printf("%s", "Имя, фамилия: ");
        printf("%s", list[i]->person.name);
        printf("%s", " ");
        printf("%s", list[i]->person.lastname);
        printf("%s", "\n");

        printf("%s", ") ");
        printf("%s", "Место работы, должность: ");
        if (list[i]->person.workplace[0] == '-' && strlen(list[i]->person.workplace) == 1)
            printf("%s", "Не заполнено, ");
        else
            printf("%s", list[i]->person.workplace);
        printf("%s", " ");
        if (list[i]->person.job[0] == '-' && strlen(list[i]->person.job) == 1)
            printf("%s", "Не заполнено, ");
        else
            printf("%s", list[i]->person.job);
        printf("%s", "\n");

        printf("%s", "Email: \n");
        if (list[i]->email_counter > 0)
            for (int j = 0; j < list[i]->email_counter; j++)
            {
                printf("%d", j + 1);
                printf("%s", ") ");
                printf("%s", list[i]->emails[j].email);
                printf("%s", "\n");
            }
        else
            printf("%s", "Не заполнено\n");

        printf("%s", "Номера телефонов: \n");
        if (list[i]->phonenumbers_counter > 0)
            for (int j = 0; j < list[i]->phonenumbers_counter; j++)
            {
                printf("%d", j + 1);
                printf("%s", ") ");
                printf("%s", list[i]->phonenumbers[j].phonenumber);
                printf("%s", "\n");
            }
        else
            printf("%s", "Не заполнено\n");

        printf("%s", "Социальные сети: \n");
        if (list[i]->socials_counter > 0)
            for (int j = 0; j < list[i]->socials_counter; j++)
            {
                printf("%d", j + 1);
                printf("%s", ") ");
                printf("%s", list[i]->socials[j].social);
                printf("%s", "\n");
            }
        else
            printf("%s", "Не заполнено\n");
    }
}

void menu()
{
    int choice = 0;
    while (choice != 5)
    {
        printf("%s", "Выберите действие:\n ");
        printf("%s", "1. Добавить контакт\n ");
        printf("%s", "2. Удалить контакт\n ");
        printf("%s", "3. Обновить данные о контакте\n ");
        printf("%s", "4. Открыть контактную книгу\n");
        printf("%s", "5. Выход из программы\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            Contact *c = (Contact *)malloc(sizeof(Contact));
            *c = createContact();
            pushToContacts(c);
            break;
        case 2:
            removeFromList();
            break;
        case 3:
            updateContact();
            break;
        case 4:
            print();
            break;
        case 5:
            break;
        default:
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    menu();
    return 0;
}
