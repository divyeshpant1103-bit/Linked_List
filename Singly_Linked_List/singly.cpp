#include <iostream>
#include "singly.hpp"
using namespace std;


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

void InsertAtBeginning(struct LL *l1, int newdata)
{
    node *temp = newnode(newdata);
    temp->next = l1->head;//point the temp->next in head
    l1->head = temp;      // point head to the temp;
    if (!l1->tail)        // l1->tail is null means the list was empty before insertion, so we need to update the tail to point to the new node
    {
        l1->tail = temp;
    }
}

void InsertAtEnd(struct LL *l1, int newdata)
{
    node *temp = newnode(newdata);
    if (!l1->head) // if the list is empty,then we need to update both head and tail to point to the new node
    {
        l1->head = temp;
        l1->tail = temp;
    }
    else
    {
        l1->tail->next = temp; // link the new node to the end of the listl
        l1->tail = temp;       // update the tail to point to the new node
    }
}

void InsertAfterValue(struct LL *l1, int newdata, int value)
{
    node *curr = l1->head;
    if (curr == nullptr) // check if the list is empty
    {
        cout << "List is empty";
        return;
    }
    while (curr != NULL && curr->data != value)
    { // travers the list to find the node with the specified value
        curr = curr->next;
    }
    if (curr == nullptr)
    { // if the value is not found in the list,print a message and return
        cout << "NO SUCH Value Found";
        return;
    }
    node *temp = newnode(newdata);
    temp->next = curr->next;
    curr->next = temp;
    if (curr == l1->tail)
    { // if the new node is inserted after the tail,update the tail to point to the new node
        l1->tail = temp;
    }
}

void InsertBeforeValue(struct LL *l1, int newdata, int value)
{
    node *curr = l1->head;
    if (curr == nullptr)
    {
        cout << "List is empty";
        return;
    }
    if (curr->data == value)
    {
        InsertAtBeginning(l1, newdata);
        return;
    }
    while (curr->next != NULL && curr->next->data != value)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        cout << "no such value";
        return;
    }
    node *temp = newnode(newdata);
    temp->next = curr->next;
    curr->next = temp;
}

void InsertAtPosition(struct LL *l1, int newdata, int index)
{
    node *curr = l1->head;
    if (curr == nullptr)
    {
        cout << "List is empty";
        return;
    }
    if(index==0){
        InsertAtBeginning(l1, newdata);
        return;
    }
    for (int i = 0; i < index - 1&& curr!= nullptr; i++)
    {
        curr = curr->next;
    }
    if(curr==nullptr){
        cout << "Out of bound";
    }
    node *temp = newnode(newdata);
    temp->next = curr->next;
    curr->next = temp;
    if (curr==l1->tail)
    {
        l1->tail = temp;
    }
}

void display(struct LL *l1)
{
    node *curr = l1->head;
    while (curr != nullptr)
    {
        cout << curr->data << "->";
        curr = curr->next;
    }
}
void reverse(struct LL *l1)
{
    node *prev = nullptr;
    node *curr = l1->head;
    node *next = nullptr;
    
    while (curr != nullptr)
    {
        next = curr->next; // store the next node
        curr->next = prev; // reverse the link
        prev = curr;       // move prev and curr one step forward
        curr = next;
    }
    l1->head = prev; // update the head to point to the new first node
    if(l1->tail==nullptr){
        l1->tail=l1->head; // if the list was empty,update the tail to point to the new first node
    }
}
