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

sl *newll(){
    sl *temp = new sl;
    temp->head = nullptr;
    temp->tail = nullptr;
    return temp;
}
void display(sl *l1);
node *newnode(int newdata)
{
    node *temp = new node;
    temp->data = newdata;
    temp->next = nullptr;
    return temp;
}

void insertatbeginning(sl *l1,int data){
    node *temp = newnode(data);
    temp->next = l1->head;
    l1->head = temp;
    if(!l1->tail){
        l1->tail = temp;
    }
}

void reverse(sl *l1){
    node *prev = nullptr;
    node *curr = l1->head;
    node *next = nullptr;
    while(curr!=nullptr){
        next = curr->next;//store the next node
        curr->next = prev;//linking the current node to the previous node
        prev = curr;//updating the previous node to the current node
        curr = next;//updating the current node to the next node   
      
    }
  
    l1->head = prev;
}

void display(sl *l1){
    node *curr = l1->head;
    while(curr!=nullptr){
        cout<<curr->data<<"->";
        curr = curr->next;
    }
}

int main(){
    sl *l1 = newll();
    insertatbeginning(l1,1);
    insertatbeginning(l1,2);
    insertatbeginning(l1,3);
    insertatbeginning(l1,4);
    insertatbeginning(l1,5);
    display(l1);
    cout<<endl;
    reverse(l1);
    display(l1);
}