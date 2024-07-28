#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define SIZE 256
int items = 0;
typedef struct Queue
{
    int priority;
    char message[SIZE];
    struct Queue *next;
    struct Queue *prev;
} Queue;

int GeneratePriority()
{
    int priority = rand() % SIZE;
    return priority;
}

void GenerateMessage(char *message)
{

    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int length = SIZE;
    while (length-- > 0)
    {
        size_t index = (double)rand() / RAND_MAX * (sizeof charset - 1);
        *message++ = charset[index];
    }
    *message = '\0';
}

Queue *GenerateAndInsertItem(Queue **head)
{
    Queue *newItem = calloc(sizeof(Queue), 1);
    Queue *tmp = head;
    newItem->priority = GeneratePriority();
    GenerateMessage(newItem->message);
    if (NULL == *head)
    {
        newItem->prev = newItem;
        newItem->next = newItem;
        head = newItem;
        items++;
    }
    else
    {
        do
        {
            if (newItem->priority < tmp->priority)
            {
                newItem->prev = tmp->prev;
                newItem->next = tmp;
                tmp->prev->next = newItem;
                tmp->prev = newItem;
                items++;
                if (tmp == head)
                    return newItem;
                return head;
            }
            tmp = tmp->next;
        } while (tmp != head);

        newItem->next = tmp;
        newItem->prev = tmp->prev;
        tmp->prev->next = newItem;
        tmp->prev = newItem;
        items++;
    }
    return head;
}

void PrintList(Queue *head)
{
    Queue *tmp = head;
    if (NULL == head)
    {
        printf("List empty!\n\n");
        return;
    }
    printf("\n%d %s", items, "items in queue.\n\n");
    do
    {
        printf("%d ", tmp->priority);
        printf(": %s\n", tmp->message);
        tmp = tmp->next;
    } while (tmp != head);
    printf("\n");
}

Queue *PopItem(struct Queue *head)
{
    Queue *tmp = head;
    if (NULL == head)
    {
        printf("Queue is empty!\n\n");
        return 0;
    }
    printf("Message: %s Priority: %d\n\n", head->message, head->priority);
    tmp = tmp->next;
    tmp->prev = head->prev;
    free(head);
    items--;
    return head;
}

Queue *DeleteByPriorityMoreOrEqualThan(struct Queue *head, int priority)
{
    Queue *tmp = head;
    if (NULL == head)
    {
        printf("Queue empty!\n");
        return head;
    }
    do
    {
        if (priority <= tmp->priority)
        {
            if (tmp->next == tmp->prev)
            {
                printf("Message: %s Priority: %d\n", tmp->message, tmp->priority);
                items--;
                printf("%s", "100\% of queue\n\n");
                free(tmp);
                return head;
            }
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            if (tmp == head)
                head = head->next;
            printf("Message: %s Priority: %d\n", tmp->message, tmp->priority);
            free(tmp);
            items--;
            return head;
        }
        tmp = tmp->next;
    } while (tmp != head);

    return NULL;
}

Queue *DeleteByPriority(struct Queue *head, int priority)
{
    Queue *tmp = head;
    if (NULL == head)
    {
        printf("Queue empty!\n");
        return head;
    }
    do
    {
        if (priority == tmp->priority)
        {
            if (tmp->next == tmp->prev)
            {
                printf("Message: %s Priority: %d\n\n", tmp->message, tmp->priority);
                items--;
                free(tmp);
                return NULL;
            }
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            if (tmp == head)
                head = head->next;
            printf("Message: %s Priority: %d\n\n", tmp->message, tmp->priority);
            items--;
            free(tmp);
            return head;
        }
        tmp = tmp->next;
    } while (tmp != head);
    return NULL;
}

Queue *DeleteOperations(int op, Queue *head)
{
    Queue *tmp;
    int priority;
    printf("%s\n", "Type priority (0-255)");
    scanf("%d", &priority);
    int items_buf = items;
    int deleted = 0;
    if (priority < 0 || priority > 255)
    {
        printf("%s\n", "Input error!");
        return head;
    }
    if (op == 0)
    {
        tmp = DeleteByPriority(head, priority);
        printf("%d %s\n", (1 / items_buf) * 100, "%");
    }
    else if (op == 1)
    {
        tmp = DeleteByPriorityMoreOrEqualThan(head, priority);
        printf("%d %s\n", (1 / items_buf) * 100, "%");
    }
    else if (op == 2)
    {
        for (int i = 0; i < items_buf; i++)
        {
            tmp = DeleteByPriority(head, priority);
            if (tmp != NULL)
                deleted++;
            else
            {
                if (deleted > 0)
                    printf("%d %s\n", (1 / items_buf) * 100, "%");
                else
                    printf("Queue does not contain item with this priority: %d!\n", priority);

                return head;
            }
        }
        printf("%d %s\n", (1 / items_buf) * 100, "%");
    }
    else if (op == 3)
    {
        for (int i = 0; i < items_buf; i++)
        {
            tmp = DeleteByPriorityMoreOrEqualThan(head, priority);
            if (tmp != NULL)
            {
                items_buf--;
                deleted++;
            }

            else
            {
                if (deleted > 0)
                    printf("%d %s\n", (1 / items_buf) * 100, "%%");
                else
                    printf("Queue does not contain item with this priority: %d!\n", priority);

                return head;
            }
        }
        printf("%d %s\n", (1 / items_buf) * 100, "%%");
    }
    else
    {
        printf("%s\n", "Invalid operation!");
        return head;
    }
    if (tmp != NULL)
        head = tmp;
    return head;
}

Queue *GenerateQueue(Queue *head)
{
    int amount;
    printf("%s\n", "Type amount");
    scanf("%d", &amount);
    if (amount < 0)
        printf("Input error");
    else
        for (int i = 0; i < amount; i++)
            head = GenerateAndInsertItem(head);
    return head;
}

Queue *Menu(Queue *head)
{
    int choice;
    printf("%s\n\n", "===SELECT AN ACTION===");
    printf("%s\n", "1) Generate queue");
    printf("%s\n", "2) Pop item");
    printf("%s\n", "3) Select and delete item with set priority");
    printf("%s\n", "4) Select and delete item with priority is more or equal than set");
    printf("%s\n", "5) Select and delete all items with set priority");
    printf("%s\n", "6) Select and delete all items with priority is more or equal than set");
    printf("%s\n", "7) Print queue");
    printf("%s\n", "8) Exit");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        head = GenerateQueue(head);
        PrintList(head);
        break;
    case 2:
        head = PopItem(head);
        break;
    case 3:
        head = DeleteOperations(0, head);
        break;
    case 4:
        head = DeleteOperations(1, head);
        break;
    case 5:
        head = DeleteOperations(2, head);
        break;
    case 6:
        head = DeleteOperations(3, head);
        break;
    case 7:
        PrintList(head);
        break;
    case 8:
        exit(0);
        break;
    default:
        break;
    }
    return head;
}

int main(int argc, char const *argv[])
{
    Queue *head = calloc(sizeof(Queue), 1);
    srand(time(NULL) + getpid());
    while (1)
    {
        head = Menu(head);
    }
    return 0;
}