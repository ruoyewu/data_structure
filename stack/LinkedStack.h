//
// Created by 张群 on 2018/7/31.
//

#ifndef DATA_STRUCTURE_LINKEDSTACK_H
#define DATA_STRUCTURE_LINKEDSTACK_H

#include <iostream>
#include "Stack.h"

template <typename T>
struct StackNode {
    T* data;
    StackNode<T>* next;

    explicit StackNode(T* data) {
        this->data = data;
        this->next = NULL;
    }
};

template <typename T>
class LinkedStack : public Stack<T> {
private:
    StackNode<T>* head;
    int size;
public:
    LinkedStack() {
        head = NULL;
        size = 0;
    }

    bool empty() {
        return size == 0;
    }

    int length() {
        return size;
    }

    bool push(T& ele) {
        auto* node = new StackNode<T>(&ele);
        node->next = head;
        head = node;
        size++;
        return true;
    }

    bool push(const T& ele) {

        return true;
    }

    T& pop() {
        if (size == 0) {
            throw -1;
        }
        StackNode<T>* h = head;
        T* ele = h->data;
        head = h->next;
        size --;
        return *ele;
    }

    T& top() {
        if (size == 0) {
            throw -1;
        }
        return *(head->data);
    }

    bool clear() {
        StackNode<T>* h;
        while (size-- > 0) {
            h = head;
            head = h->next;
            delete h;
        }
        return true;
    }
};

#endif //DATA_STRUCTURE_LINKEDSTACK_H
