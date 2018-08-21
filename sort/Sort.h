//
// Created by 张群 on 2018/8/20.
//

#ifndef DATA_STRUCTURE_SORT_H
#define DATA_STRUCTURE_SORT_H

#include <iostream>
#include <stack>
#include "../stack/ArrayStack.h"
#include "../stack/LinkedStack.h"
using namespace std;

template <typename T>
void swap(T* ele, int f, int t);

/**
 * 直接插入排序
 * 将一个数组分为两个部分，前半部分有序，后半部分待排序，那么最初前半部分只有一个元素
 * 然后依次将后半部分的每个元素插入到前半部分使得前半部分所含元素每次递增 1
 * 完成 n-1 次插入就可以完成排序
 * 每次插入，要在前半部分有序的序列中找到要插入的元素的位置
 * 然后使前半部分从这个位置开始的所有元素后移一位，最后将待插入元素放到这个位置
 *
 * 如下：
 * i 代表当前待插入元素在数组中的位置，从 1 至 n-1
 * j 带包当前待插入元素在前半部分有序数组的位置，从 i 开始进行递减判断，同时将判断的元素后移一位
 * 最后将 j 位置的数据设为最初 i 位置的待插入元素
 *
 * 稳定
 */
template <typename T>
void sortInsert(T* ele, int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        T e = ele[i];
        for (j = i; j > 0 && ele[j-1] > e; --j) {
            ele[j] = ele[j-1];
        }
        ele[j] = e;
    }
}

/**
 * 折半插入排序
 * 基于直接插入排序，在 "在前半部分有序序列中查找待插入元素位置" 这里做了改进
 * 使用折半查找而不是顺序查找，一般情况下能够加快待插入位置的查找
 */
template <typename T>
void sortInsertMid(T* ele, int n) {
    int i, j, low, high, mid;
    for (i = 1; i < n; i++) {
        T e = ele[i];
        low = 0;
        high = i-1;
        while (low <= high) {
            mid = (low+high) / 2;
            if (ele[mid] > e)
                high = mid-1;
            else
                low = mid+1;
        }
        mid = high > low ? high : low;
        for (j = i; j > mid; --j) {
            ele[j] = ele[j-1];
        }
        ele[j] = e;
    }
}

/**
 * 希尔排序，又缩小增量排序
 * 使用的是插入排序的原理，只不过希尔排序通过变更增量的方式，进行了多趟插入排序
 * 即插入排序可以认为希尔排序的一种特殊情况，增量只有一个且为 1
 * 而希尔排序中，通过多次不同的增量排序，以提高排序能力
 *
 * 如下的 d 代表每次的增量，可以看到 d 是一个 {n, n/2, n/4, ... 1} 的一个整数数列
 * 对于这个数列中的每一个数字，都要进行一次直接插入排序，即对于一个数组 {0, 1, ... n} 而言
 * 如果当前的 d 是 3，那么在插入排序中，当对第 i 个元素进行插入的时候，不是将它插入到 {0, ... i-1} 这个序列中
 * 而是插入到 {0, 3, 6, ... i-3} 这个序列中
 *
 * 仅适用于顺序存储线性表（因为涉及到随机存取）
 */
template <typename T>
void sortShell(T* ele, int n) {
    int d, i, j;
    for (d = n/2; d >= 1; d /= 2) {
        for (i = d; i < n; ++i) {
            T e = ele[i];
            for (j = i; j > d && ele[j-d] > e; j -= d) {
                ele[j] = ele[j-d];
            }
            ele[j < 0 ? 0 : j] = e;
        }
    }
}


/**
 * 冒泡排序
 */
template <typename T>
void sortBobble(T* ele, int n) {
    bool f;
    for (int i = 1; i < n; ++i) {
        f = false;
        for (int j = i; j < n; ++j) {
            if (ele[j] < ele[j-1]) {
                swap(ele, j, j-1);
                f = true;
            }
        }
        if (!f) {
            return;
        }
    }
}

/**
 * 快速排序
 */
template <typename T>
int partition(T* ele, int l, int h) {
    int k = ele[l];

    while (l < h) {
        while (l < h && ele[h] >= k)
            h--;
        ele[l] = ele[h];
        while (l < h && ele[l] <= k)
            l++;
        ele[h] = ele[l];
    }
    ele[l] = k;
    return l;
}

template <typename T>
void sortQuick(T* ele, int l, int h) {
    if (l >= h) {
        return;
    }

    int p = partition(ele, l, h);

    sortQuick(ele, l, p-1);
    sortQuick(ele, p+1, h);
}

template <typename T>
void sortQuick(T* ele, int n) {
    sortQuick<T>(ele, 0, n-1);
}

/**
 * 快速排序的非递归实现
 * 基本思想：使用一定的数据结构（栈/队列）保存每次的划分，然后依次取出划分进行排序
 */
struct Divide {
    int low;
    int high;

    Divide(int low, int high) {
        this->low = low;
        this->high = high;
    }
};

template <typename T>
void sortQuickNR(T* ele, int n) {
    stack<Divide> stack;
    Divide d(0, n-1);
    stack.push(d);

    while (!stack.empty()) {
        d = stack.top();stack.pop();

        int p = partition(ele, d.low, d.high);
        if (p > d.low+1) {
            stack.push(Divide(d.low, p-1));
        }
        if (d.high > p+1) {
            stack.push(Divide(p+1, d.high));
        }

        for (int i = 0; i < n; ++i) {
            cout << ele[i] << " ";
        }
        cout << endl;
    }
}


/**
 * 交换
 * @tparam T
 * @param ele
 * @param f
 * @param t
 */
template <typename T>
void swap(T* ele, int f, int t) {
    T e = ele[f];
    ele[f] = ele[t];
    ele[t] = e;
}

#endif //DATA_STRUCTURE_SORT_H
