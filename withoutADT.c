#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node *next;
} node;

node *createnode(int val)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = val;
    temp->next = NULL;
    return temp;
}
void insertatbeginning(node **head, int val)
{
    node *temp = createnode(val);
    temp->next = *head;
    *head = temp;
}
void insertatend(node **head, int val)
{
    node *temp = createnode(val);
    if (*head == NULL)
    {
        *head = temp;
        return;
    }
    node *curr = *head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = temp;
}
void insertaftervalue(node **head, int val, int afterval)
{
    node *temp = createnode(val);
    node *curr = *head;
    while (curr != NULL && curr->data != afterval)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        printf("Value %d not found in the list\n", afterval);
        free(temp);
        return;
    }
    temp->next = curr->next;
    curr->next = temp;
}
void insertbeforevalue(node **head, int val, int beforeval)
{
    node *temp = createnode(val);
    if (*head == NULL)
    {
        printf("List is empty\n");
        free(temp);
        return;
    }

    node *curr = *head;
    while (curr->next != NULL && curr->next->data != beforeval)
    {
        curr = curr->next;
    }
    
    if ((*head)->data == beforeval)
    {
        insertatbeginning(head, val);
    }
    else if (curr->next == NULL)
    {
        printf("Value %d not found in the list\n", beforeval);
        free(temp);
        return;
    }
    else
    {
        temp->next = curr->next;
        curr->next = temp;
    }
}
void display(node *head)
{
    node *curr = head;
    while (curr != NULL)
    {
        printf("%d ->", curr->data);
        curr = curr->next;
    }
    return;
}
int main()
{
    node *head = NULL;
    insertatbeginning(&head, 10);
    insertatbeginning(&head, 20);
    display(head);
    printf("\n");
    insertatend(&head, 30);
    display(head);
    printf("\n");
    insertaftervalue(&head, 25, 20);
    display(head);
    printf("\n");
    insertbeforevalue(&head, 15, 10);
    display(head);
    printf("\n");
    insertbeforevalue(&head, 5, 20);
    display(head);
}