#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node *next;
} node;

node *createnode(int newdata)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = newdata;
    temp->next = NULL;
    return temp;
}
node* addtwonumbers(node *head1,node *head2){
    node *temp1 = head1;
    node *temp2 = head2;
    node *dummynode = createnode(-1);
    int carry = 0;
    node *curr=dummynode;
    while(temp1!=NULL || temp2!=NULL){
        int sum = carry;
        if(temp1!=NULL){
            sum+=temp1->data;
            temp1=temp1->next;
        }
        if(temp2!=NULL){
            sum+=temp2->data;
            temp2=temp2->next;
        }
        carry = sum/10;
        node *newnode = createnode(sum%10);
        curr->next=newnode;
        curr=curr->next;
    }

    if(carry>0){
        node *newnode = createnode(carry);
        curr->next=newnode;
        curr=curr->next;
    }
    return dummynode->next;
}
void insertatend(node **head, int value)
{
    node *temp = createnode(value);
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
void display(node *head)
{
    node *curr = head;
    while (curr != NULL)
    {
        printf("%d", curr->data);
        curr = curr->next;
    }
    printf("\n");
}
int main()
{
    node *head1 = NULL;
    node *head2 = NULL;
    insertatend(&head1, 2);
    insertatend(&head1, 4);
    insertatend(&head1, 3);
    display(head1);
    insertatend(&head2, 5);
    insertatend(&head2, 6);
    insertatend(&head2, 4);
    display(head2);
    node *result = addtwonumbers(head1, head2);
    display(result);
}