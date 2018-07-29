//
// Created by 张群 on 2018/7/27.
//

#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

template <typename T>
class List {
public:

    virtual int length() = 0;

    virtual int indexAt(T ele) = 0;

    virtual T get(int position) = 0;

    virtual bool add(T ele) = 0;

    virtual bool add(T ele, int position) = 0;

    virtual T removeAt(int position) = 0;

    virtual T remove(T ele) = 0;

    virtual bool empty() = 0;

    virtual void destroy() = 0;
};

#endif //DATA_STRUCTURE_LIST_H
