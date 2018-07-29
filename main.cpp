#include <iostream>
#include "list/ArrayList.h"
#include "list/LinkedList.h"

using namespace std;

void printList(List<float> *list);

int main() {
    ArrayList<float> *arr = new ArrayList<float>();
    arr->add(1);
    arr->add(2);
    arr->add(3);
    arr->add(4);
    arr->add(5);
    printList(arr);

    arr->moveLeft(3);
    printList(arr);

    arr->add(6, 0);
    printList(arr);

    arr->removeAt(2);
    printList(arr);

    arr->remove(3);
    printList(arr);
}

void printList(List<float> *list) {
    cout << "size: " << list->length() << endl;
    for (int i = 0; i < list->length(); ++i) {
        cout << list->get(i) << " ";
    }
    cout << endl;
}