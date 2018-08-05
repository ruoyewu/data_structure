//
// Created by 张群 on 2018/7/31.
//

#ifndef DATA_STRUCTURE_ARRAYQUEUE_H
#define DATA_STRUCTURE_ARRAYQUEUE_H

#include <iostream>
#include "Queue.h"

template <typename T>
class ArrayQueue : public Queue<T> {
private:
    T* data;
    int maxSize;
    int head = 0;
    int tail = 0;

public:
    explicit ArrayQueue(int maxSize) {
        this->maxSize = maxSize;]
        data = new T[maxSize];
    }

    ArrayQueue() {
        this->maxSize = 4;
        data = new T[maxSize];
    }

    bool empty() {
        return head == tail;
    }

    int length() {
        return tail - head;
    }

    bool enqueue(T ele) {
        if (tail - head >= maxSize) {
            expend();
        }
        if (tail >= maxSize) {
            move();
        }
        data[tail++] = ele;
        return true;
    }

    T dequeue() {
        if (head >= tail) {
            return NULL;
        }
        return data[head++];
    }

private:
    void expend() {
        int size = tail - head;
        int max = maxSize << 1;
        T* newData = new T[max];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[head + i];
        }
        head = 0;
        tail -= head;
        data = newData;
    }

    void move() {
        int size = tail - head;
        for (int i = 0; i < size; ++i) {
            data[i] = data[head+i];
        }
        head = 0;
        tail -= head;
    }
};

#endif //DATA_STRUCTURE_ARRAYQUEUE_H
