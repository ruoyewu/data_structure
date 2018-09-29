//
// Created by 张群 on 2018/9/22.
//

#ifndef DATA_STRUCTURE_QUESTION_H
#define DATA_STRUCTURE_QUESTION_H

#include <iostream>
#include "list.h"

// 打印 ArrayList
template <typename T>
void printArrayList(ArrayList<T> &L) {
    for (int i = 0; i < L.length; ++i) {
        std::cout << L.data[i] << " ";
    }
    std::cout << std::endl;
}

// 删除值为 x 元素
template <typename T>
void delete_x(ArrayList<T> &L, T x) {
    int p = 0, i = 0;
    for (i = 0; i < L.length; i++) {
        if (L.data[i] != x) {
            L.data[p++] = L.data[i];
        }
    }
    L.length = p;
}

// 有序表删除重复元素
template <typename T>
void delete_repeat(ArrayList<T> &L) {
    int p = 0, i = 0;
    for (i = 0; i < L.length; i++) {
        if (L.data[i] != L.data[i-1]) {
            L.data[p++] = L.data[i];
        }
    }
    L.length = p;
}

// 有序表查找
// 找到：将其与后继交换
// 找不到：插入并保持有序
template <typename T>
void find_x(ArrayList<T> &L, T x) {
    int from = 0, to = L.length - 1, i;
    while (from <= to) {
        i = (from + to) / 2;
        if (L.data[i] > x) {
            to = i-1;
        }else if (L.data[i] < x) {
            from = i+1;
        }else {
            T tem = L.data[i];
            L.data[i] = L.data[i+1];
            L.data[i+1] = tem;
            return;
        }
    }

    L.length++;
    if (L.data[i] < x) {
        i++;
    }

    for (int j = L.length-1; j > i; j--) {
        L.data[j] = L.data[j-1];
    }
    L.data[i] = x;
}

// 找主元素
template <typename T>
T find_main(ArrayList<T> &L) {
    T m;
    int c = 0;
    for (int i = 0; i < L.length; ++i) {
        if (c == 0) {
            c = 1;
            m = L.data[i];
        }else {
            if (m == L.data[i]) {
                c++;
            } else {
                c--;
            }
        }
    }

    if (c > 0) {
        c = 0;
        for (int i = 0; i < L.length; ++i) {
            if (m == L.data[i]) {
                c++;
            }
        }
    }

    return c > (L.length/2) ? m : -1;
}

#endif //DATA_STRUCTURE_QUESTION_H
