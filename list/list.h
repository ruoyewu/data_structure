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
bool addNodeAt(LinkedList<T> &list, T x, int index) {
    LLNode<T>* n = new LLNode<T>(x);
    if (index == 0) {
        n->next = list;
        list = n;
        return true;
    }
    LLNode<T>* node = list;
    int p = 0;
    while (p++ < index-1) {
        if (node->next != NULL) {
            node = node->next;
        } else {
            return false;
        }
    }
    n->next = node->next;
    node->next = n;
    return true;
}

template <typename T>
bool removeNodeAt(LinkedList<T> &list, int index) {
    if (list == NULL) {
        return false;
    }
    if (index == 0) {
        list = list->next;
        return true;
    }
    int p = 0;
    LLNode<T>* node = list;
    while (p++ < index-1) {
        if (node->next != NULL) {
            node = node->next;
        } else {
            return false;
        }
    }
    if (node->next != NULL) {
        node->next = node->next->next;
        return true;
    }
    return false;
}

template <typename T>
bool removeNode(LinkedList<T> &list, T x) {
    if (list == NULL) {
        return false;
    }
    if (list->data == x) {
        list = list->next;
        return true;
    }
    LLNode<T>* node = list;
    while (node->next != NULL) {
        if (node->next->data == x) {
            node->next = node->next->next;
            return true;
        } else {
            node = node->next;
        }
    }
    return false;
}

template <typename T>
T getNodeAt(LinkedList<T> &list, int index) {
    if (list == NULL) {
        return NULL;
    }
    int p = 0;
    LLNode<T>* node = list;
    while (p < index) {
        if (node != NULL) {
            node = node->next;
            p++;
        } else {
            break;
        }
    }
    if (node != NULL) {
        return node->data;
    } else {
        return NULL;
    }
}

template <typename T>
int indexOf(LinkedList<T> &list, T x) {
    int p = 0;
    LLNode<T>* node = list;
    while (node != NULL) {
        if (node->data == x) {
            return p;
        } else {
            node = node->next;
            p++;
        }
    }
    return -1;
}

template <typename T>
int sizeOf(LinkedList<T> &list) {
    int size = 0;
    LLNode<T>* node = list;
    while (node != NULL) {
        node = node->next;
        size++;
    }
    return size;
}

template <typename T>
bool empty(LinkedList<T> &list) {
    return list == NULL;
}

template <typename T>
struct DoubleLinkedListNode {
    typedef DoubleLinkedListNode DLLNode, *DLinkedList;

    T data;
    DLLNode* pre;
    DLLNode* next;
};

#endif //DATA_STRUCTURE_ARRAY_LIST_H
