//
// Created by 张群 on 2018/9/28.
//

#ifndef DATA_STRUCTURE_TREE_H
#define DATA_STRUCTURE_TREE_H

#include <iostream>
#include "../list/list.h"
#include "../stack/stack.h"
#include "../queue/queue.h"

template <typename T>
struct BinaryTreeNode {
    typedef BinaryTreeNode BTNode, *BTree;

    T data;
    BTNode* lc = NULL;
    BTNode* rc = NULL;

    explicit BinaryTreeNode(T data) {
        this->data = data;
    }
};

template <typename T>
using BTNode = BinaryTreeNode<T>;

template <typename T>
using BTree = BinaryTreeNode<T>*;

template <typename T>
bool addNode(BTree<T> &Tree, T x, int (*com)(T, T)) {
    BTNode<T>* node = Tree;
    if (node == NULL) {
        Tree = new BTNode<T>(x);
        return true;
    }

    while (true) {
        int c = com(node->data, x);
        if (c > 0) {
            if (node->rc != NULL) {
                node = node->rc;
            } else {
                node->rc = new BTNode<T>(x);
                break;
            }
        } else if (c < 0) {
            if (node->lc != NULL) {
                node = node->lc;
            } else {
                node->lc = new BTNode<T>(x);
                break;
            }
        } else {
            return false;
        }
    }

    return true;
}


template <typename T>
LinkedList<T> preOrder(BTree<T> &tree) {
    LinkedList<T> list = NULL;
    LinkedStack<BTree<T>> stack = NULL;

    push(stack, tree);

    while (!empty(stack)) {
        BTNode<T>* node = pop(stack);
        addNode(list, node->data);

        if (node->rc != NULL) {
            push(stack, node->rc);
        }
        if (node->lc != NULL) {
            push(stack, node->lc);
        }
    }

    return list;
}

template <typename T>
LinkedList<T> inOrder(BTree<T> &tree) {
    LinkedList<T> list = NULL;
    LinkedStack<BTree<T>> stack = NULL;

    BTNode<T>* node = tree;

    while (!empty(stack) || node != NULL) {
        if (node != NULL) {
            push(stack, node);
            node = node->lc;
        } else {
            node = pop(stack);
            addNode(list, node->data);
            node = node->rc;
        }
    }

    return list;
}

template <typename T>
LinkedList<T> postOrder(BTree<T> &tree) {
    LinkedList<T> list = NULL;
    LinkedStack<BTree<T>> stack = NULL;

    BTNode<T>* node = tree;
    BTNode<T>* pre = NULL;

    while (node != NULL || !empty(stack)) {
        if (node != NULL) {
            push(stack, node);
            node = node->lc;
        } else {
            node = top(stack);
            if (node->rc != NULL && node->rc != pre) {
                node = node->rc;
                push(stack, node);
                node = node->lc;
            } else {
                node = pop(stack);
                addNode(list, node->data);
                pre = node;
                node = NULL;
            }
        }
    }

    return list;
}

template <typename T>
LinkedList<T> levelOrder(BTree<T> &tree) {
    LinkedList<T> list = NULL;
    LinkedQueue<BTree<T>> queue = NULL;

    enqueue(queue, tree);

    while (!empty(queue)) {
        BTNode<T>* node = dequeue(queue);
        addNode(list, node->data);
        if (node->lc != NULL) {
            enqueue(queue, node->lc);
        }
        if (node->rc != NULL) {
            enqueue(queue, node->rc);
        }
    }

    return list;
}
#endif //DATA_STRUCTURE_TREE_H
