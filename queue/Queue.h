//
// Created by 张群 on 2018/7/31.
//

#ifndef DATA_STRUCTURE_QUEUE_H
#define DATA_STRUCTURE_QUEUE_H

template <typename T>
class Queue {
public:
    virtual bool empty() = 0;
    virtual int length() = 0;
    virtual bool enqueue(T ele) = 0;
    virtual T dequeue() = 0;
    virtual T getHead() = 0;
};

#endif //DATA_STRUCTURE_QUEUE_H
