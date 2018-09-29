//
// Created by 张群 on 2018/9/21.
//

#ifndef DATA_STRUCTURE_ARRAY_LIST_H
#define DATA_STRUCTURE_ARRAY_LIST_H

#include <iostream>

template <typename T>
struct ArrayList {
    T* data;
    int length;

    explicit ArrayList(int n) {
        data = new T[n];
        length = 0;
    }
};



template <typename T>
struct LinkedListNode {
    typedef LinkedListNode LLNode, *LinkedList;

    explicit LinkedListNode(T x) {
        this->data = x;
        next = NULL;
    }

    T data;
    LLNode* next;
};

template <typename T>
using LLNode = LinkedListNode<T>;

template <typename T>
using LinkedList = LinkedListNode<T>*;

template <typename T>
bool addNode(LinkedList<T> &list, T x) {
    if (list == NULL) {
        list = new LinkedListNode<T>(x);
        return true;
    }

    LLNode<T>* node = list;
    while (true) {
        if (node->next == NULL) {
            node->next = new LinkedListNode<T>(x);
            break;
        } else {
            node = node->next;
        }
    }

    return true;
}

template <typename T>
struct DoubleLinkedListNode {
    typedef DoubleLinkedListNode DLLNode, *DLinkedList;

    T data;
    DLLNode* pre;
    DLLNode* next;
};

#endif //DATA_STRUCTURE_ARRAY_LIST_H
