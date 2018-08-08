//
// Created by 张群 on 2018/8/4.
//

#ifndef DATA_STRUCTURE_TREE_H
#define DATA_STRUCTURE_TREE_H

#include <iostream>

template <typename T>
class Tree {
public:
    virtual bool add(T ele) = 0;
    virtual bool find(T ele) = 0;
    virtual bool remove(T ele) = 0;
    virtual int length() = 0;
};

#endif //DATA_STRUCTURE_TREE_H
