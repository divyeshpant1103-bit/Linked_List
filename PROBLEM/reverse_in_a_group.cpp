#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node *next;
} node;
struct LL
{
    node *head;
    node *tail;
};

struct LL *newll()
{
    LL *temp = new LL;
    temp->head = nullptr;
    temp->tail = nullptr;
    return temp; // return the newly created Linked List
}

Node *newnode(int newdata)
{
    Node *temp = new node;
    temp->data = newdata;
    temp->next = nullptr;
    return temp; // return the newly created node
}
void insertatbeginning(struct LL *l1, int data)
{
    node *temp = newnode(data);
    temp->next = l1->head;
    if (!l1->tail)
    {
        l1->tail = temp;
    }
    l1->head = temp;
}
void reverse_in_group(struct LL *l1, int k){
    node *curr = l1->head;
    node *grouphead = nullptr;
    node *prevgrouptail = nullptr;
    while(curr!=NULL){
        int count = 0;
        node *temp = curr;/*need to store the current node to check if there are k nodes in the group otherwise it 
        will reverse the remaining nodes which are less than k*/
        while (temp != NULL && count < k)
        {
            temp = temp->next;
            count++;
        }
        if(count<k){//if the number of nodes in the group is less than k then we will not reverse the remaining nodes and link the previous group tail to the current node
            if(prevgrouptail!=NULL){//if the previous group tail is not null then we will link the previous group tail to the current node
                prevgrouptail->next = curr;
            }
            break;
        }
        node *groupstart = curr;
        node *prev = nullptr;
        node *next = nullptr;
        for (int i = 0; i < k;i++){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        if(grouphead==nullptr){//if the group head is null then we will set the group head to the previous node which is the new head of the reversed group
            grouphead = prev;
        }else{//if the group head is not null then we will link the previous group tail to the previous node which is the new head of the reversed group
            prevgrouptail->next = prev;
        }
        prevgrouptail = groupstart;
    }
    if(grouphead!=nullptr){
        l1->head = grouphead;
    }
}
void display(struct LL *l1)
{
    node *curr = l1->head;
    while (curr != nullptr)
    {
        printf("%d->", curr->data);
        curr = curr->next;
    }
}
int main()
{
    struct LL *l1 = newll();
    insertatbeginning(l1, 5);
    insertatbeginning(l1, 4);
    insertatbeginning(l1, 3);
    insertatbeginning(l1, 2);
    insertatbeginning(l1, 1);
    display(l1);
    printf("\n");
    reverse_in_group(l1, 4);
    display(l1);
}