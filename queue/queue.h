//
// Created by 张群 on 2018/9/28.
//

#ifndef DATA_STRUCTURE_QUEUE_H
#define DATA_STRUCTURE_QUEUE_H

#include <iostream>

template <typename T>
struct ArrayQueue {
    T* data;
    int front = 0, rear = 0;

    explicit ArrayQueue(int capacity) {
        data = new T[capacity];
    }
};


template <typename T>
struct LinkedQueueNode {
    typedef LinkedQueueNode<T> LQNode;
    T data;
    LQNode* next;

    explicit LinkedQueueNode(T data) {
        this->data = data;
        this->next = NULL;
    }
};

template <typename T>
using LQNode = LinkedQueueNode<T>;

template <typename T>
using LinkedQueue = LinkedQueueNode<T>*;

template <typename T>
bool enqueue(LinkedQueue<T> &queue, T x) {
    if (queue == NULL) {
        queue = new LQNode<T>(x);
        return true;
    }

    LQNode<T>* node = queue;
    while (true) {
        if (node->next == NULL) {
            node->next = new LQNode<T>(x);
            return true;
        } else {
            node = node->next;
        }
    }
}

template <typename T>
T dequeue(LinkedQueue<T> &queue) {
    if (queue == NULL) {
        return NULL;
    }

    T x = queue->data;
    queue = queue->next;
    return x;
}

template <typename T>
bool empty(LinkedQueue<T> &queue) {
    return queue == NULL;
}
#endif //DATA_STRUCTURE_QUEUE_H
