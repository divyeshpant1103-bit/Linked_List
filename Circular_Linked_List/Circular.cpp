#include <iostream>
using namespace std;
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
    return temp;
}

node *createnode(int newdata)
{
    node *temp = new node;
    temp->data = newdata;
    temp->next = nullptr;
    return temp;
}

void insertatbeginning(LL *l1, int data)
{
    node *temp = createnode(data);
    if (!l1->head)
    {
        l1->head = temp;
        l1->tail = temp;
        temp->next = temp;
    }
    temp->next = l1->head;
    l1->head = temp;
    l1->tail->next = temp; // l1 ki tail ka next should point the temp;
}
void Insertatend(LL *l1, int data)
{
    node *temp = createnode(data);
    if (!l1->head)
    {
        l1->head = temp;
        l1->tail = temp;
        temp->next = temp;
        return;
    }
    l1->tail->next = temp;
    l1->tail = temp;
    temp->next = l1->head;
}

// We're using do-while here for the same reason as in display: it's a circular list, so there's no nullptr to signal "end of list." 
//The only way to know you've seen every node is to notice you've come back to where you started (head).
void Insertaftervalue(LL *l1, int newdata, int value)
{
    node *temp = createnode(newdata);
    node *curr = l1->head;
    if(curr == nullptr) // If the list is empty, we can't insert after a value.
    {
        cout << "List is empty. Cannot insert after value." << endl;
        return;
    }
    do{
        if(curr->data==value){
            temp->next = curr->next;
            curr->next = temp;
            if(curr == l1->tail) // If we're inserting after the tail, we need to update the tail pointer.
            {
                Insertatend(l1, newdata); // This will handle updating the tail and linking back to head.
            }
            return;
        }
    }while(curr = curr->next, curr != l1->head); // Move to the next node and check if we've looped back to head.
    cout<< "Value " << value << " not found in the list. Cannot insert after it." << endl;
}
void insertbeforevalue(LL *l1,int newdata,int value){
    node *temp = createnode(newdata);
    node *curr = l1->head;
    if(curr==nullptr){
        cout<<"List is empty. Cannot insert before value."<<endl;
        return;
    }
    do{
        if(temp->data==value){
            temp->next = curr;
            
        }
    }
}
void display(LL *l1)
{
    node *temp = l1->head;
    if (temp == nullptr)
        return;

    do
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != l1->head);

    cout << "⟲ (" << l1->head->data << ")" << endl;
}
int main()
{
    LL *l1 = newll();
    insertatbeginning(l1, 10);
    insertatbeginning(l1, 20);
    insertatbeginning(l1, 30);
    display(l1);
    Insertatend(l1, 40);
    display(l1);
    Insertaftervalue(l1, 25, 90);
    display(l1);
}
