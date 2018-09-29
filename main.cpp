#include <iostream>
#include <vector>
#include "sort.h"
#include "list/list.h"
#include "list/question.h"
#include "stack/stack.h"
#include "tree/tree.h"

using namespace std;

template <typename T>
int com(T x, T y) {
    return (int) y-x;
}

int main() {
    BTree<int> tree = NULL;
    addNode(tree, 4, com);
    addNode(tree, 3, com);
    addNode(tree, 2, com);
    addNode(tree, 1, com);
    addNode(tree, 6, com);
    addNode(tree, 5, com);
    addNode(tree, 7, com);

    LinkedList<int> list = inOrder(tree);
}