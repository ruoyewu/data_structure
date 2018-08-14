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

using namespace std;

void printList(List<float> *list);
void printStack(ArrayStack<float> stack);
void printStack(LinkedStack<float> stack);

int main() {
    LinkedGraph<long> graph;
    for (int i = 0; i < 10; ++i) {
        graph.add(i+1);
    }

    graph.add(1, 3, 3);
    graph.add(1, 5, 5);
    graph.add(1, 7, 7);
    graph.add(5, 9, 45);
    graph.add(9, 8, 72);
    graph.add(7, 8, 56);

    graph.traverseBreadth();
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