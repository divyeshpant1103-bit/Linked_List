// Program to insert/delete nodes in a doubly linked list
// at the beginning, end, and any position
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} node;

node *newnode(int newdata)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = newdata;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void insertatbeginning(node **head, int data)
{
    node *temp = newnode(data);
    temp->next = *head;
    if (*head != NULL)
    {
        (*head)->prev = temp;
    }
    *head = temp;
}

void insertatend(node **head, int data)
{
    node *temp = newnode(data);
    if (*head == NULL)
    {
        *head = temp;
        return; // FIX: without this, execution fell through and corrupted the list
    }
    node *curr = *head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = temp;
    temp->prev = curr;
}

void insertatposition(node **head, int data, int position)
{
    if (position == 1)
    {
        insertatbeginning(head, data);
        return;
    }
    node *curr = *head;
    for (int i = 1; i < position - 1 && curr != NULL; i++)
    {
        curr = curr->next;
    }
    if (curr == NULL) // position greater than length of list
    {
        printf("Position is greater than the length of the linked list\n");
        return;
    }
    node *temp = newnode(data); // FIX: allocate only once we know it's needed (avoids leak)
    temp->next = curr->next;
    curr->next = temp;
    temp->prev = curr;
    if (temp->next != NULL)
    {
        temp->next->prev = temp;
    }
}

void deleteatbeginning(node **head)
{
    if (*head == NULL)
    {
        printf("Linked list is empty\n");
        return;
    }
    node *temp = *head;
    *head = (*head)->next;
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    free(temp);
}

void deleteatend(node **head)
{
    if (*head == NULL)
    {
        printf("Linked list is empty\n");
        return;
    }
    node *temp = *head;
    if (temp->next == NULL) // only one node in the list
    {
        *head = NULL;
        free(temp);
        return;
    }
    while (temp->next != NULL) // FIX: loop on temp->next, not *head
    {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp); // FIX: actually free the removed node
}

void deleteatposition(node **head, int position)
{
    if (*head == NULL)
    {
        printf("Linked list is empty\n");
        return;
    }
    if (position == 1)
    {
        deleteatbeginning(head);
        return;
    }
    node *curr = *head;
    for (int i = 1; i < position && curr != NULL; i++)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        printf("Position is greater than the length of the linked list\n");
        return;
    }
    if (curr->prev != NULL)
    {
        curr->prev->next = curr->next;
    }
    if (curr->next != NULL)
    {
        curr->next->prev = curr->prev;
    }
    free(curr);
}

void display(node *head)
{
    node *temp = head;
    while (temp != NULL)
    {
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    node *head = NULL;
    int ch;
    while (1)
    {
        printf("\n1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at any position\n");
        printf("4. Display\n");
        printf("5. Delete at end\n");
        printf("6. Delete at beginning\n");
        printf("7. Delete at any position\n");
        printf("0. Quit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        int data, position;

        switch (ch)
        {
        case 1:
            printf("Enter the data to insert at beginning: ");
            scanf("%d", &data);
            insertatbeginning(&head, data);
            break;
        case 2:
            printf("Enter the data to insert at end: ");
            scanf("%d", &data);
            insertatend(&head, data);
            break;
        case 3:
            printf("Enter the data to insert: ");
            scanf("%d", &data);
            printf("Enter the position to insert the data: ");
            scanf("%d", &position);
            insertatposition(&head, data, position);
            break;
        case 4:
            display(head);
            break;
        case 5:
            deleteatend(&head);
            break;
        case 6:
            deleteatbeginning(&head);
            break;
        case 7:
            printf("Enter the position to delete: ");
            scanf("%d", &position);
            deleteatposition(&head, position);
            break;
        case 0:
            printf("Exiting the program........\n");
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}