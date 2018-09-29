//
// Created by 张群 on 2018/9/25.
//

#ifndef DATA_STRUCTURE_STACK_H
#define DATA_STRUCTURE_STACK_H

#include <iostream>

/**
 * 数组实现栈
 * @tparam T
 */
template <typename T>
struct ArrayStack {
    T* data = NULL;
    int top = -1;
    int capacity = 0;

    explicit ArrayStack(int capacity) {
        this->data = new T[capacity];
        this->capacity = capacity;
    }
};

template <typename T>
void push(ArrayStack<T> &S, T x) {
    if (++S.top < S.capacity) {
        S.data[S.top] = x;
    }else {
        throw "overflow";
    }
}

template <typename T>
T pop(ArrayStack<T> &S) {
    if (S.top >= 0) {
        return S.data[S.top--];
    }else {
        throw "overflow";
    }
}

template <typename T>
T top(ArrayStack<T> &S) {
    if (S.top >= 0) {
        return S.data[S.top];
    }else {
        throw "overflow";
    }
}

template <typename T>
bool emptyStack(ArrayStack<T> &S) {
    return S.top == -1;
}

/**
 * 共享栈
 * @tparam T
 */
template <typename T>
struct ShareArrayStack {
    typedef ShareArrayStack SAStack;

    T* data = NULL;
    int top1 = -1;
    int top2 = 0;
    int capacity = 0;

    explicit ShareArrayStack(int capacity) {
        this->data = new T[capacity];
        this->capacity = capacity;
        this->top1 = -1;
        this->top2 = capacity;
    }
};

template <typename T>
struct LinkedStackNode {
    typedef LinkedStackNode *LinkedStack, LSNode;

    explicit LinkedStackNode(T data) {
        this->data = data;
        this->next = NULL;
    }

    T data;
    LSNode* next = NULL;
};

template <typename T>
using LSNode = LinkedStackNode<T>;

template <typename T>
using LinkedStack = LinkedStackNode<T>*;

template <typename T>
bool push(LinkedStack<T> &stack, T x) {
    if (stack == NULL) {
        stack = new LSNode<T>(x);
        return true;
    }

    LSNode<T>* node = new LSNode<T>(x);
    node->next = stack;
    stack = node;
    return true;
}

template <typename T>
T pop(LinkedStack<T> &stack) {
    if (stack == NULL) {
        return NULL;
    }

    T x = stack->data;
    stack = stack->next;
    return x;
}

template <typename T>
T top(LinkedStack<T> &stack) {
    if (stack == NULL) {
        return NULL;
    }

    return stack->data;
}

template <typename T>
bool empty(LinkedStack<T> &stack) {
    return stack == NULL;
}
#endif //DATA_STRUCTURE_STACK_H
