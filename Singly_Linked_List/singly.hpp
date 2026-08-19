#ifndef SINGLY_HPP
#define SINGLY_HPP
typedef struct Node
{
    int data;
    struct Node *next;
} node;
struct LL
{
    struct Node *head;
    struct Node *tail;
};
struct LL *newll();

Node *newnode(int newdata);

void InsertAtBeginning(struct LL *l1, int newdata);
void InsertAtEnd(struct LL *l1, int newdata);
void InsertAfterValue(struct LL *l1, int newdata, int value);
void InsertBeforeValue(struct LL *l1, int newdata, int value);
void InsertAtPosition(struct LL *l1, int newdata, int index);
void display(struct LL *l1);
void reverse(struct LL *l1);

#endif