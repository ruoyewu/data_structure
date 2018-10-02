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
//    BBTree<int> tree = NULL;
//    addNode(tree, 7, com);
//    addNode(tree, 6, com);
//    addNode(tree, 5, com);
//    addNode(tree, 4, com);
//    addNode(tree, 3, com);
//    addNode(tree, 2, com);
//    addNode(tree, 1, com);
//
//    removeNode(tree, 2, com);
//    removeNode(tree, 3, com);
//    removeNode(tree, 1, com);


    int c = 1;
    Tree<int> tree = new TreeNode<int>(c++);

    for (int i = 0; i < 3; ++i) {
        TreeNode<int>* ni = new TreeNode<int>(c++);
        for (int j = 0; j < 3; ++j) {
            addNode(ni->children, new TreeNode<int>(c++));
        }
        addNode(tree->children, ni);
    }

    convertToBT(tree);
}