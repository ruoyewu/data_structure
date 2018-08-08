#include <iostream>
#include "list/ArrayList.h"
#include "stack/Stack.h"
#include "stack/ArrayStack.h"
#include "stack/LinkedStack.h"
#include "tree/Compare.h"
#include "tree/LinkedBinaryTree.h"
#include "tree/BalanceBinaryTree.h"

using namespace std;

void printList(List<float> *list);
void printStack(ArrayStack<float> stack);
void printStack(LinkedStack<float> stack);

int main() {
    class Com : public Compare<float> {
    public:
        int compare(float first, float second) override {
            return static_cast<int>(second - first);
        }
    };

    BalanceBinaryTree<float> balanceTree(new Com());
    for (int i = 0; i < 5; ++i) {
        balanceTree.add((i+1)*3);
    }
    for (int j = 10; j > 5; --j) {
        balanceTree.add(j);
    }

    balanceTree.remove(3);
    balanceTree.remove(9);
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