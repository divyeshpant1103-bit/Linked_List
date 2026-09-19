#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} node;

node *newnode(int newdata)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = newdata;
    temp->next = NULL;
    return temp;
}

void insertatbeginning(node **head, node **tail, int data)
{
    node *temp = newnode(data);
    if (*head == NULL)
    { // FIX: handle empty list first, no dereference of NULL
        temp->next = temp;
        *head = temp;
        *tail = temp;
        return;
    }
    temp->next = *head;
    *head = temp;
    (*tail)->next = *head; // FIX: tail's next must follow the new head
}

void insertatend(node **head, node **tail, int data)
{
    node *temp = newnode(data);
    if (*head == NULL)
    {
        temp->next = temp; // FIX: self-loop for single-node circular list
        *head = temp;
        *tail = temp;
        return;
    }
    (*tail)->next = temp;
    *tail = temp;
    (*tail)->next = *head;
}
void insertatposition(node **head, node **tail, int data, int position)
{
    if (position == 1)
    {
        insertatbeginning(head, tail, data);
        return;
    }
    node *curr = *head;
    for (int i = 1; i < position - 1 && curr->next != *head; i++)
    {
        curr = curr->next;
    }
    node *temp = newnode(data);
    temp->next = curr->next;
    curr->next = temp;
    if (curr == *tail) 
    {
        *tail = temp;
    }
}
void deleteatbeginning(node **head, node **tail)
{
    if (*head == NULL)
    {
        printf("Circular linked list is empty\n");
        return;
    }
    node *temp = *head;
    if (*head == *tail) // only one node in the list
    {
        *head = NULL;
        *tail = NULL;
        free(temp);
        return;
    }
    *head = (*head)->next;
    (*tail)->next = *head; // maintain circular link
    free(temp);
}
void deleteatend(node **head,node **tail)
{
    if (*head == NULL)
    {
        printf("Circular linked list is empty\n");
        return;
    }
    node *temp = *head;
    if (*head == *tail) // only one node in the list
    {
        *head = NULL;
        *tail = NULL;
        free(temp);
        return;
    }
    while (temp->next != *tail)
    {
        temp = temp->next;
    }
    temp->next = *head; // maintain circular link
    free(*tail);
    *tail = temp;
}
void deleteatposition(node **head, node **tail, int position)
{
    if (*head == NULL)
    {
        printf("Circular linked list is empty\n");
        return;
    }
    if (position == 1)
    {
        deleteatbeginning(head, tail);
        return;
    }
    node *curr = *head;
    for (int i = 1; i < position - 1 && curr->next != *head; i++)
    {
        curr = curr->next;
    }
    node *temp = curr->next;
    curr->next = temp->next;
    if (temp == *tail) // if deleting the tail
    {
        *tail = curr;
    }
    free(temp);
}
void display(node *head, node *tail)
{
    if (head == NULL)
    {
        printf("Circular linked list is empty\n");
        return;
    }
    node *temp = head;
    do
    {
        printf("%d->", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("NULL\n");
}

int main()
{
    node *head = NULL;
    node *tail = NULL;
    insertatbeginning(&head, &tail, 10);
    insertatbeginning(&head, &tail, 20);
    display(head, tail);
    printf("\n");
    insertatend(&head, &tail, 30);
    insertatposition(&head, &tail, 25, 3);
    display(head, tail);
    return 0;
}