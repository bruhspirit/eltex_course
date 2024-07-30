#define SIZE 256

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
    struct Contact *next;
    struct Contact *prev;
} Contact;

Contact *InsertEmail(char email[SIZE], Contact *head, int target);
Contact *InsertPhonenumber(char number[SIZE], Contact *head, int target);
Contact *InsertSocial(char social[SIZE], Contact *head, int target);
Contact *InsertContact(Person *person, Contact *head);
Contact *DeleteContact(int target, Contact *head);
Contact *UpdateEmail(int target, Contact *head, int num, char value[SIZE]);
Contact *UpdatePhonenumber(int id, Contact *head, int num, char value[SIZE]);
Contact *UpdateSocial(int id, Contact *head, int num, char value[SIZE]);
void PrintList(Contact *head);
Person *CreateContact();
Contact *Menu(Contact *head);