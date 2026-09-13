/*
    1.To find the middle of a linked list we have to approach
    a.[Naive Approach] Two Passes - O(n) Time and O(1) Space
    b.[Expected Approach] Hare and Tortoise Algorithm - O(n) Time and O(1) Space

    In navie approch we will find the lenght of the list and then itrate till the length/2
    but in Hare and Tortise Algorithm i will me two pointer one is slow pointer and other is fast point which move the 2 step
    than the slow pointer and when the fast pointer will be at end then the slow pointer will be at the middle
*/

#include <iostream>
using namespace std;
typedef struct Node
{
    int data;
    struct Node *next;
} node;

typedef struct LL
{
    node *head;
    node *tail;
} sl;

sl *newll()
{
    sl *temp = new sl;
    temp->head = nullptr;
    temp->tail = nullptr;
    return temp;
}

node *newnode(int newdata)
{
    node *temp = new node;
    temp->data = newdata;
    temp->next = nullptr;
    return temp;
}

void insertatbeginning(sl *l1, int data)
{
    node *temp = newnode(data);
    temp->next = l1->head;
    l1->head = temp;
    if (!l1->tail)
    {
        l1->tail = temp;
    }
}
int getsize(sl *l1){
    node *temp = l1->head;
    int lenght = 0;
    while(temp!=nullptr){
        lenght++;
        temp = temp->next;
    }
    return lenght++;
}
void middle(sl *l1){
    node *temp = l1->head;
    int l = getsize(l1);
    int mid = l / 2;
    while (mid--)
    {
        temp = temp->next;
    }
    cout << temp->data<<endl;
}
void hare_tortoise(sl *l1){
    node *slow = l1->head;
    node *fast = l1->head;
    while(fast!=nullptr && fast->next!=nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    cout << slow->data;
}

void display(sl *l1)
{
    node *curr = l1->head;
    while (curr != nullptr)
    {
        cout << curr->data << "->";
        curr = curr->next;
    }
    cout << endl;
}

int main()
{
    sl *l1 = newll();
    insertatbeginning(l1, 1);
    insertatbeginning(l1, 2);
    insertatbeginning(l1, 3);
    insertatbeginning(l1, 4);
    insertatbeginning(l1, 5);
    // insertatbeginning(l1, 6);
    display(l1);
    middle(l1);
    hare_tortoise(l1);
    return 0;
}