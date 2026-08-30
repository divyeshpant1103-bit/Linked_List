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
}
void reverse(struct LL *l1, int k)
{
    node *curr = l1->head;
    node *prevGroupTail = nullptr; // tail of the previously reversed group
    node *newHead = nullptr;       // becomes the list's new head (set once)

    while (curr != nullptr)
    {
        node *groupStart = curr; // this node becomes the tail of this group
        node *prev = nullptr;
        node *next = nullptr;
        int counter = 0;

        while (curr != nullptr && counter < k)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            counter++;
        }
        // prev = new head of this group, groupStart = new tail of this group

        if (prevGroupTail == nullptr)
            newHead = prev; // first group sets the overall new head
        else
            prevGroupTail->next = prev; // link previous group's tail to this group

        prevGroupTail = groupStart; // remember this group's tail for next iteration
    }

    l1->head = newHead;
    l1->tail = prevGroupTail;
}
