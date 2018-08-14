//
// Created by 张群 on 2018/8/10.
//

#ifndef DATA_STRUCTURE_GRAPH_H
#define DATA_STRUCTURE_GRAPH_H

#include "../list/List.h"
#include "../list/ArrayList.h"

template <typename T>
class Graph {
public:
    virtual bool adjacent(T x, T y) = 0;
    virtual ArrayList<T> neighbors(T x) = 0;
    virtual bool add(T x) = 0;
    virtual bool remove(T x) = 0;
    virtual bool add(T x, T y, int weight) = 0;
    virtual bool remove(T x, T y) = 0;
    virtual T firstNeighbor(T x) = 0;
    virtual int getWeight(T x, T y) = 0;
    virtual bool setWeight(T x, T y, int weight) = 0;
};

#endif //DATA_STRUCTURE_GRAPH_H
