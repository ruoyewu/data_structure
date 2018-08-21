#include <iostream>
#include <vector>
#include "list/ArrayList.h"
#include "stack/Stack.h"
#include "stack/ArrayStack.h"
#include "stack/LinkedStack.h"
#include "tree/Compare.h"
#include "tree/LinkedBinaryTree.h"
#include "tree/BalanceBinaryTree.h"
#include "graph/LinkedGraph.h"
#include "tree/BTree.h"
#include "query/Query.h"
#include "sort/Sort.h"

using namespace std;

void printList(List<float> *list);
void printStack(ArrayStack<float> stack);
void printStack(LinkedStack<float> stack);

int main() {
    int ele[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    int n = 10;
    sortQuickNR<int>(ele, n);

    for (int i = 0; i < n; ++i) {
        cout << ele[i] << " ";
    }
    cout << endl;
}

void printList(List<float> *list) {
    cout << "size: " << list->length() << endl;
    for (int i = 0; i < list->length(); ++i) {
        cout << list->get(i) << " ";
    }
    cout << endl;
}

void printStack(ArrayStack<float> stack) {
    cout << "address: " << &stack << "\tsize: " << sizeof(stack) << endl;
    cout << "size: " << stack.length() << endl;
    while (!stack.empty()) {
        cout << stack.pop() << " ";
    }
    cout << endl;
}

void printStack(LinkedStack<float> stack) {
    cout << "address: " << &stack << "\tsize: " << sizeof(stack) << endl;
    cout << "size: " << stack.length() << endl;
    while (!stack.empty()) {
        cout << stack.pop() << " ";
    }
    cout << endl;
}