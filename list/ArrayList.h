//
// Created by 张群 on 2018/7/27.
//

#ifndef DATA_STRUCTURE_ARRAYLIST_H
#define DATA_STRUCTURE_ARRAYLIST_H

#include <iostream>
#include "List.h"

template <typename T>
class ArrayList : public List<T> {
private:
    T* data;
    int size;
    int maxSize;
public:
    ArrayList() {
        size = 0;
        maxSize = 4;
        data = new T[size];
    }

    explicit ArrayList(int size) {
        data = new T[size];
        this->size = 0;
        maxSize = size;
    }

    explicit ArrayList(List<T>& origin) {
        int size = origin.length();
        data = new T[size];
        for (int i = 0; i < size; ++i) {
            data[i] = origin.get(i);
        }
        this->size = size;
        maxSize = size;
    }

    int length() {
        return size;
    }

    T get(int position) {
        if (position < size) {
            return data[position];
        }else {
            return NULL;
        }
    }

    int indexAt(T ele) {
        for (int i = 0; i < size; ++i) {
            if (data[i] == ele) {
                return i;
            }
        }
        return -1;
    }

    bool add(T ele) {
        if (size >= maxSize) {
            if (!expend()) {
                return false;
            }
        }

        data[size++] = ele;

        return true;
    }

    bool add(T ele, int position) {
        if (position >= size) {
            return add(ele);
        }

        if (size >= maxSize) {
            if (!expend()) {
                return false;
            }
        }

        for (int i = size; i > position; --i) {
            data[i] = data[i - 1];
        }
        data[position] = ele;
        size++;

        return true;
    }

    T removeAt(int position) {
        if (position < size) {
            for (int i = position; i < size - 1; ++i) {
                data[i] = data[i + 1];
            }
            T re = data[size-1];
            data[--size] = NULL;
            return re;
        }else {
            return NULL;
        }
    }

    T remove(T ele) {
        int position = indexAt(ele);
        if (position > 0) {
            return removeAt(position);
        } else {
            return NULL;
        }
    }

    bool empty() {
        return size == 0;
    }

    bool clear() {
        size = 0;
        return true;
    }

    void destroy() {
        delete[] data;
    }

    // 删除所有的元素 ele
    bool removeAll1(T ele) {
        int j = 0;
        for (int i = 0; i < size; ++i) {
            if (data[i] != ele) {
                data[j++] = data[i];
            }
        }
        size = j;
        return true;
    }

    bool removeAll2(T ele) {
        int i = 0, j = 0;
        while (j < size) {
            if (data[i] == ele) {
                i++;
            } else {
                data[j-i] = data[j];
            }
            j++;
        }
        size -= i;
        return true;
    }

    // 删除在某一范围的所有元素
    bool removeRange(T from, T to) {
        if (to > from) {
            return false;
        }
        int i = 0, j = 0;
        while (j < size) {
            if (data[i] >= from && data[i] <= to) {
                i++;
            } else {
                data[j-i] = data[j];
            }
            j++;
        }
        size -= i;
        return true;
    }

    // 有序表中删除值重复的元素
    bool removeRepeat() {
        if (size == 0) {
            return false;
        }
        T pre = data[0];
        int j = 0;
        for (int i = 1; i < size; ++i) {
            if (data[i] == pre) {
                j++;
            }else {
                pre = data[i];
                data[i-j] = data[i];
            }
        }
        return true;
    }

    /**
     * 循环左移 n 个距离
     * @param n
     * @return
     * 三种解决方案：
     * 1 使用 i -> (i + n) % size 的映射方式，将原先的 data 映射到新的数组上，时间复杂度 O(n), 空间复杂度 O(size)
     * 2 使用三重逆序，首先将 (0, size) 逆序，然后将 (0, n) 逆序，再将 (n, size) 逆序，时间复杂度 O(n), 空间复杂度 O(1)
     * 3 使用临时数组保存前 n 个数据，然后删除前 n 个数据，再将其添加到表尾，时间复杂度 O(n), 空间复杂度 O(n)
     * 故选择第二种方法实现
     */
    bool moveLeft(int n) {
        reverse(0, n - 1);
        reverse(n, size - 1);
        reverse(0, size - 1);
        return true;
    }

    /*
     * 找主元素，满足 sizeOf(x) > size/2
     */
    T findMainEle() {
        if (size == 0) {
            return NULL;
        }

        T c = data[0];
        int count = 1;
        for (int i = 1; i < size; ++i) {
            if (data[i] == c) {
                count++;
            }else {
                if (count > 0) {
                    count--;
                } else {
                    count = 1;
                    c = data[i];
                }
            }
        }

        if (count > 0) {
            return c;
        }

        return NULL;
    }

    void reverse(int from, int to) {
        int mid = (to - from + 1) / 2;
        for (int i = 0; i < mid; ++i) {
            T tem = data[from + i];
            data[from + i] = data[to - i];
            data[to - i] = tem;
        }
    }

private:

    bool expend() {
        maxSize = maxSize * 2;
        T* newData = new T[maxSize];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        data = newData;
        return true;
    }
};

#endif //DATA_STRUCTURE_ARRAYLIST_H
