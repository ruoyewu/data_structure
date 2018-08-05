#include <iostream>
#include "list/ArrayList.h"
#include "stack/Stack.h"
#include "stack/ArrayStack.h"
#include "stack/LinkedStack.h"
#include "tree/Compare.h"
#include "tree/LinkedBinaryTree.h"

using namespace std;

void printList(List<float> *list);
void printStack(ArrayStack<float> stack);
void printStack(LinkedStack<float> stack);

int main() {
//    string str;
//
//    cout << calculate(string("3.2 1.5 + 123 *"));

    class Com : public Compare<float> {
    public:
        int compare(float first, float second) override {
            return static_cast<int>(second - first);
        }
    };
    Com com;

    auto* binaryTree = new LinkedBinaryTree<float>(com);

//    LinkedStack<float> *stack = new LinkedStack<float>();
//    stack->push(1);
//    stack->push(2);
//    stack->push(3);
//
//    stack->push(4);
//    printStack(*stack);
//
//    stack->push(5);
//    printStack(*stack);
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