//
// Created by 张群 on 2018/7/31.
//

#ifndef DATA_STRUCTURE_STACK_H
#define DATA_STRUCTURE_STACK_H

#include <iostream>
using namespace std;

template <typename T>
class Stack {
public:
    virtual bool empty() = 0;
    virtual int length() = 0;
    virtual bool push(T ele) = 0;
    virtual T pop() = 0;
    virtual T top() = 0;
    virtual bool clear() = 0;
};

#endif //DATA_STRUCTURE_STACK_H
