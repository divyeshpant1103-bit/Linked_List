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
    size_t size;
};

struct LL *newLL()
{
    LL *temp = new LL;
    temp->head = nullptr;
    temp->tail = nullptr;
    temp->size = 0;
    return temp;
}

node *createnode(int newdata)
{
    node *temp = new node;
    temp->data = newdata;
    temp->next = nullptr;
    return temp;
}

void Insertatbeginning(struct LL *l1, int data)
{
    node *temp = createnode(data);

    temp->next = l1->head;
    l1->head = temp;
    if (!l1->tail)
    {
        l1->tail = temp;
    }
    l1->size++;
}
void deleteatbeginning(struct LL *l1)
{
    if (l1->head == nullptr)
    {
        cout << "List is empty" << endl;
        cout << "No node to delete" << endl;
        cout << l1->tail << endl;
        cout << l1->head << endl;
        return;
    }
    node *temp = l1->head;
    l1->head = l1->head->next;
    delete temp;
    l1->size--;
    if (l1->head == nullptr)
    {
        l1->tail = nullptr;
        cout << "List is empty after deletion" << endl;
        cout << l1->tail << endl;
        cout << l1->head << endl;
    }
}
void deleteatend(struct LL *l1)
{
    if (l1->head == nullptr)
    {
        cout << "List is empty" << endl;
        cout << "No node to delete" << endl;
        return;
    }
    if (l1->head->next == nullptr)
    {
        delete l1->head;
        l1->head = nullptr;
        l1->tail = nullptr;
        l1->size--;
        return;
    }
    node *temp = l1->head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = nullptr;
    l1->size--;
}
void deleteatpostion(struct LL *l1, int index)
{
    if (l1->head == nullptr)
    {
        cout << "List is empty" << endl;
        cout << "No node to delete" << endl;
        return;
    }
    if (index == 0)
    {
        deleteatbeginning(l1);
        return;
    }
    node *temp = l1->head;
    for (int i = 0; i < index - 1 && temp != nullptr; i++)
    {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr)
    {
        cout << "Out of bound" << endl;
        return;
    }
    node *todelete = temp->next;
    temp->next = todelete->next;
    delete todelete;
    l1->size--;
    if (temp->next == nullptr)
    {
        l1->tail = temp;
    }
    return;
}
void deleteaaftervalue(struct LL *l1, int value)
{
    if (l1->head == nullptr)
    {
        cout << "List is empty" << endl;
        cout << "No node to delete" << endl;
        return;
    }
    node *temp = l1->head;
    while (temp != nullptr && temp->data != value)
    {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr)
    {
        cout << "Value not found or no node after value" << endl;
        return;
    }
    node *todelete = temp->next;
    temp->next = todelete->next;
    delete todelete;
    l1->size--;
    if (temp->next == nullptr)
    {
        l1->tail = temp;
    }
    return;
}
void deletebeforevalue(struct LL *l1,int value){
    if (l1->head == nullptr || l1->head->data == value) {
        cout << "No node to delete before the given value" << endl;
        return;
    }
    node *temp = l1->head;
    while(temp->next!=nullptr &&temp->next->data!=value){
        temp = temp->next;
    }
    if(temp->next==nullptr){
        cout << "Value not found" << endl;
        return;
    }
    node *todelete = temp;
    if(todelete==l1->head){
        l1->head = l1->head->next;
        delete todelete;
        l1->size--;
        return;
    }
    temp = l1->head;
    while(temp->next!=todelete){
        temp = temp->next;
        
}
void display(struct LL *l1)
{
    node *temp = l1->head;
    while (temp != nullptr)
    {
        cout << temp->data << "->";
        temp = temp->next;
    }
}

int main()
{
    struct LL *l1 = newLL();
    Insertatbeginning(l1, 10);
    Insertatbeginning(l1, 20);
    Insertatbeginning(l1, 30);
    display(l1);
    cout << endl;
    deleteaaftervalue(l1, 30);
    // deleteatend(l1);
    // deleteatend(l1);

    cout << endl;
    display(l1);
    return 0;
}
