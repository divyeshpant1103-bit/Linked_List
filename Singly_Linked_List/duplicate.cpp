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

sl *newLL()
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
// this function is useful only when the linked list is sorted in ascending order
void removeduplicate(sl *l1)
{
    node *prev = l1->head;
    node *curr = l1->head->next;
    while (curr != nullptr)
    {
        if (prev->data == curr->data)
        {
            prev->next = curr->next; // if found duplicate then we will remove the current node and link the previous node to the next node of current node
            delete curr;
            curr = prev->next;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}
void remove_duplicate_in_unsorted(sl *l1)
{
    node *prev = l1->head;
    node *curr = l1->head->next;
    
    while (curr != nullptr)
    {
        int duplicate = 0;
        node *temp = l1->head;
        while (temp != curr)
        {
            
            if (temp->data == curr->data)
            {
                duplicate = 1;
                break;
            }
            temp = temp->next;
        }
      
        if (duplicate)
        {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
    return;
}

void diplay(sl *l1)
{
    node *curr = l1->head;
    while (curr != nullptr)
    {
        cout << curr->data << "->";
        curr = curr->next;
    }
}
int main()
{
    sl *l1 = newLL();
    l1->head = newnode(1);
    l1->head->next = newnode(3);
    l1->head->next->next = newnode(2);
    l1->head->next->next->next = newnode(3);
    l1->head->next->next->next->next = newnode(3);
    l1->head->next->next->next->next->next = newnode(4);
    l1->head->next->next->next->next->next->next = newnode(4);
    l1->head->next->next->next->next->next->next->next = newnode(5);
    cout << "Before removing duplicates: ";
    diplay(l1);
    remove_duplicate_in_unsorted(l1);
    cout<< "\nAfter removing duplicates: ";
    diplay(l1);
}