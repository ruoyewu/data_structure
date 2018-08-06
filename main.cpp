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
    Compare<float>* com = new Com();

    LinkedBinaryTree<float> binaryTree(com);

    float preOrder[7] = {1, 2, 3, 4, 5, 6, 7};
    binaryTree.preToPost(preOrder, 7);
    for (int i = 0; i < 7; ++i) {
        cout << preOrder[i] << " ";
    }
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