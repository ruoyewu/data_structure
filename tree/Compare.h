//
// Created by 张群 on 2018/8/5.
//

#ifndef DATA_STRUCTURE_COMPARE_H
#define DATA_STRUCTURE_COMPARE_H

template <typename T>
class Compare {
public:
    virtual int compare(T first, T second) = 0;
};

#endif //DATA_STRUCTURE_COMPARE_H
