#include <iostream>
#include "singly.hpp"
using namespace std;
int main()
{
    struct LL *l1 = newll();
    InsertAtBeginning(l1, 10);
    InsertAtBeginning(l1, 20);
    InsertAtEnd(l1, 30);
    InsertAtEnd(l1, 40);
    InsertAfterValue(l1, 25, 20);
    InsertBeforeValue(l1, 15, 10);
    InsertAtPosition(l1, 5, 0);
    display(l1);
    cout << endl;
    reverse(l1);
    display(l1);
    return 0;
}