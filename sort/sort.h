//
// Created by 张群 on 2018/8/20.
//

#ifndef DATA_STRUCTURE_SORT_H
#define DATA_STRUCTURE_SORT_H

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

template <typename T>
void swap(T* ele, int f, int t);

template <typename T>
void print(T* ele, int n);

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
 * 双向冒泡排序
 */
template <typename T>
void sortBubbleRL(T* ele, int n) {
    bool f;
    // 只需要 n/2 次遍历即可
    for (int i = 1; i < n/2; i++) {
        // 先将最大的元素冒泡到尾端
        for (int j = i; j < n; ++j) {
            if (ele[j] < ele[j-1]) {
                swap(ele, j, j-1);
                f = true;
            }
        }
        // 再将最小的元素冒泡到头部
        for (int j = n-i-1; j >= i; j--) {
            if (ele[j] > ele[j+1]) {
                swap(ele, j, j+1);
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
 * 找到数组中第 k 小的元素
 * 利用快速排序的划分思想
 */
template <typename T>
T findK(T* ele, int n, int k) {
    int start = 0, end = n-1;
    while (true) {
        int p = partition(ele, start, end);
        if (p == k-1) {
            return ele[p];
        }else if (p > k-1) {
            end = p-1;
        }else if (p < k-1) {
            start = p+1;
        }
    }
}


/**
 * 选择排序
 */

/**
 * 简单选择排序
 *
 * 不稳定
 */
template <typename T>
void sortSelect(T* ele, int n) {
    for (int i = 0; i < n-1; ++i) {
        int min = i;
        for (int j = i+1; j < n; ++j) {
            if (ele[min] > ele[j]) {
                min = j;
            }
        }
        if (min != i)
            swap(ele, i, min);
    }
}

/**
 * 堆排序
 * 使用大根堆（小根堆）的方式，每次找到待排序集合中的最大（最小）值
 * 使用堆排序要经历 建堆、拿出根、调整堆 这样一系列的过程
 */

/**
 * 调整堆
 * 调整以 k 为根节点的子树成为大根堆
 * 从 k 节点开始，比较其与子节点的大小，在这三个值中（k k的左孩子 k 的右孩子）找到最大的那个使之成为根节点
 * 然后再移动 k 到其有变动的子节点上，继续使之成为大根堆
 */
template <typename T>
void adjustHeap(T* ele, int n, int k) {
    T t = ele[k];
    for (int i = 2*k+1; i < n; i = i*2+1) {
        if (i < n-1 && ele[i] < ele[i+1])
            i++;
        if (ele[i] <= t)
            break;
        else {
            ele[k] = ele[i];
            k = i;
        }
    }
    ele[k] = t;
}

template <typename T>
void sortHeap(T* ele, int n) {
    for (int i = n/2 - 1; i >= 0; i--) {
        adjustHeap(ele, n, i);
    }

    for (int i = n-1; i > 0; i--) {
        swap(ele, i, 0);
        adjustHeap(ele, i, 0);
    }
}


/**
 * 二路归并排序
 * 利用合并两个有序数组的方法，从仅含单个元素的数组开始，依次将两个相邻的子数组合并
 * 最终完成整个数组的合并（即排序）
 */
template <typename T>
void merge(T* ele, T* tem, int l, int m, int h) {
    int i, j, k;
    for (i = l; i <= h; ++i) {
        tem[i] = ele[i];
    }
    for (i = l, j = m+1, k = l; i <= m && j <= h; ) {
        if (tem[i] <= tem[j]) {
            ele[k++] = tem[i++];
        }else {
            ele[k++] = tem[j++];
        }
    }
    while (i <= m)
        ele[k++] = tem[i++];
    while (j <= h)
        ele[k++] = tem[j++];
}

template <typename T>
void sortMerge(T* ele, int n) {
    int s = 2, i;
    int tem[n];
    print<T>(ele, n);
    while (s <= n) {
        i = 0;
        while (i+s <= n) {
            int m = i + s/2 - 1;
            merge<T>(ele, tem, i, m, i+s-1);
            i += s;
        }
        if (i < n-1) {
            merge<T>(ele, tem, i, i + s/2 - 1, n-1);
        }
        s *= 2;
    }

    s /= 2;
    if (s < n) {
        merge<T>(ele, tem, 0, s-1, n-1);
    }
}


/**
 * 基数排序
 */
int getBit(int n) {
    int b = 0;
    while (n > 9) {
        n /= 10;
        b++;
    }
    return b;
}

int getBit(int n, int b) {
    for (int i = 0; i < b; ++i) {
        n /= 10;
    }
    return n % 10;
}

void sortRadix(int* ele, int n) {
    vector<vector<int>> vec;
    for (int i = 0; i < 10; ++i) {
        vec.emplace_back();
    }

    int maxBit = 0;
    for (int i = 0; i < n; ++i) {
        int b = getBit(ele[n]);
        if (b > maxBit) {
            maxBit = b;
        }
    }

    for (int i = 0; i <= maxBit; ++i) {
        for (vector<int> v : vec) {
            v.clear();
        }

        for (int j = 0; j < n; ++j) {
            vec[getBit(ele[j], i)].push_back(ele[j]);
        }

        int k = 0;
        for (vector<int> v : vec) {
            for (int l : v) {
                ele[k++] = l;
            }
        }
    }
}


/**
 * 计数排序
 */

/**
 * 计数排序，基于比较
 */
template <typename T>
void sortCount(T* ele, int n) {
    int count[n];
    T tem[n];
    for (int i = 0; i < n; ++i) {
        count[i] = 0;
        tem[i] = ele[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (ele[i] > ele[j]) {
                count[i]++;
            }else {
                count[j]++;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        ele[count[i]] = tem[i];
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

template <typename T>
void print(T* ele, int n) {
    for (int i = 0; i < n; ++i) {
        cout << ele[i] << " ";
    }
    cout << endl;
}

#endif //DATA_STRUCTURE_SORT_H
