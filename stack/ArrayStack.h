//
// Created by 张群 on 2018/7/31.
//

#ifndef DATA_STRUCTURE_ARRAYSTACK_H
#define DATA_STRUCTURE_ARRAYSTACK_H

#include <iostream>
#include "Stack.h"

template <typename T>
class ArrayStack : public Stack<T>{
private:
    long* data;
    int size = 0;
    int maxSize = 4;
public:
    explicit ArrayStack(int maxSize) {
        this->maxSize = maxSize;
        data = new long[maxSize];
    }

    ArrayStack() {
        data = new long[maxSize];
    }

    bool empty() {
        return this->size == 0;
    }

    int length() {
        return this->size;
    }

    bool push(T& ele) {
        if (size >= maxSize) {
            expend();
        }
        data[size++] = (long)&ele;
        return true;
    }

    bool push(const T& ele) {
        if (size >= maxSize) {
            expend();
        }
        data[size++] = (long)&ele;
        return true;
    }

    T& pop() {
        if (size > 0) {
            return *(T*)data[--size];
        }
        throw -1;
    }

    T& top() {
        if (size > 0) {
            return *(T*)data[size - 1];
        }
        throw -1;
    }

    bool clear() {
        delete data;
        maxSize = 4;
        data = new long[maxSize];
        size = 0;
        return true;
    }
private:
    void expend() {
        int max = maxSize << 1;
        long* newData = new long[max];
        for (int i = 0; i < maxSize; ++i) {
            newData[i] = data[i];
        }
        data = newData;
        maxSize = max;
    }

    void reduce() {
        int max = size;
        T* newData = new T[max];
        for (int i = 0; i < max; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        maxSize = max;
    }
};

#endif //DATA_STRUCTURE_ARRAYSTACK_H
