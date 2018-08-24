//
// Created by 张群 on 2018/8/15.
//

#ifndef DATA_STRUCTURE_QUERY_H
#define DATA_STRUCTURE_QUERY_H

#include <iostream>

template <typename T>
struct Table {
    T* elem;
    int length;
};

/**
 * 一般线性表顺序查找
 * 查找平均长度：
 * 成功：(n+1)/2
 * 失败：n+1
 */
template <typename T>
int search_normal(Table<T> table, T key) {
    table.elem[0] = key;
    int i;
    for (i = table.length-1; table.elem[i] != key; --i);
    return i;
}

/**
 * 有序线性表顺序查找
 * 查找平均长度：
 * 成功：(n+1)2
 * 失败：n/2 + n/(n+1)
 */
template <typename T>
int search_order(Table<T> table, T key) {
    for (int i = 0; i < table.length; ++i) {
        if (table.elem[i] == key) {
            return i;
        }
        if (table.elem[i] > key) {
            return -1;
        }
    }
    return -1;
}

/**
 * 有序线性表折半查找
 * 查找平均长度：
 * 成功：(n+1)/n * log2(n+1) - 1
 * 失败：根据具体的查找树的形状
 */
template <typename T>
int search_middle(Table<T> table, T key) {
    int low = 0, high = table.length-1, mid;
    while (low <= high) {
        mid = (low+high) / 2;
        if (table.elem[mid] > key) {
            low = mid+1;
        } else if (table.elem[mid] < key) {
            high = mid-1;
        } else {
            return mid;
        }
    }
    return -1;
}

template <typename T>
int search_middle_recursive(Table<T> table, T key, int low, int high) {
    if (low > high)
        return -1;
    int mid = (low+high) / 2;
    if (table.elem[mid] > key)
        return search_middle_recursive(table, key, low, mid-1);
    if (table.elem[mid] < key)
        return search_middle_recursive(table, key, mid+1, high);
    return mid;
}

/**
 * 分块查找
 * 条件：块间有序，块内随意
 * 方法：先根据每个块的关键字，找到对应的块，然后在块内进行顺序查找
 */
template <typename T>
struct Block {
    // 每个块包含的元素
    Table<T>* tables;
    // 每个块中的最大关键字
    T* indexes;
    // 块的个数
    int length;
};

template <typename T>
int search_block(Block<T> block, T key) {
    int b = -1, low = 0, high = block.length-1, mid;
    while (low <= high) {
        mid = (low+high) / 2;
        if (block.indexes[mid] == key) {
            b = mid;
            break;
        } else if (block.indexes[mid] > key) {
            low = mid+1;
        } else if (block.indexes[mid] < key) {
            high = mid-1;
        }
    }
    if (b == -1) {
        b = low > high ? low : high;
    }
    if (b >= 0 && b < block.length) {
        for (int i = 0; i < block.tables[b].length; ++i) {
            if (block.tables[b].elem[i] == key) {
                return b * block.length + i;
            }
        }
    }

    return -1;
}


/**
 * 字符串模式匹配
 */
struct String {
private:
    const char* data;
public:
    int length;

    String() {
        this->data = "\0";
        this->length = 0;
    }

    explicit String(const char* data) {
        this->data = data;
        this->length = getLength(data);
    }

    String& operator=(const char* data) {
        this->data = data;
        this->length = getLength(data);
        return *this;
    }

    char operator[](int position) {
        return data[position];
    }

    friend std::ostream& operator<< (std::ostream &s, const String& str) {
        s << str.data << std::endl;
        return s;
    }

private:
    int getLength(const char* data) {
        int i;
        for (i = 0; data[i] != '\0'; i++);
        return i;
    }
};

int index(String S, String T) {
    int i = 0, j = 0;
    while (i < S.length && j < T.length) {
        if (S[i] == T[j]) {
            i++;
            j++;
        }else {
            j = 0;
            i = i-j+1;
        }
    }

    if (j >= T.length)
        return i - T.length;
    return -1;
}

/**
 * 使用 KMP 算法进行字符串匹配
 * 使用这种方法需要首先求得一个 NEXT 数组，保存着在 T 的第 i 位匹配失败后应该往后移的位数
 */

// NEXT 数组代表着从 T[0] 到 T[i] 的子串中前缀和后缀的最大匹配长度
/**
 * 在求 NEXT 的过程中，i 指向当前判断的 T 的位置，j 是前缀与后缀相等的最大长度
 * 即在 T[0]..T[i-1] 这一段字符串中，T[0]..T[j-1] 与 T[i-j]..T[j-1] 两段相等，且不存在另一个更大的 j
 * 那么再这个已知的前提下进行判断，如果 T[i] == T[j]，就意味着在 T[0]..T[i] 子串中，存在
 * T[0]..T[j] 与 T[i-j+1]..T[i] 相等，那么直接得 next[i+1] = j
 * 如果 T[i] 与 T[j] 不相等，那么需要找到在 T[0]..T[i-1] 中第二长的前缀与后缀匹配的长度
 * 即找到一个 k ，使得 T[0]..T[k-1] == T[i-k]..T[i-1]，且 k<j
 * 那么就可以得到，T[0]..T[k-1] == T[i-k]..T[i-1] == T[j-k]..T[j-1]，
 * 于是得知，这个 k 就是在 i=j 的时候的 j 的值，即 next[j]，因为 j = next[i]
 * 那么找到这个 k 之后，就需要判断 T[k] 是否等于 T[i] ，如上判断 T[j] == T[i] 一样，完成一次循环
 *
 * 关于初值：
 * 上面的一个求 next 的过程是基于一个初值完成的，首先设 i=0 ，j=-1
 * 设当一个字符串没有公共头前缀和尾前缀的时候 next 为 -1，那么当 j==-1 的时候，意味着必须要将 i 往后移了
 * 此时 next[i] = 0，然后判断之后的 T[0]..T[i] 之间的 j，那么置 next[0]=-1 ，就可以保证当不存在 j 的时候
 * 即 j==0 的时候，j 会变成 -1，然后进入 if 语句
 */
int* getNext(String T) {
    int len = T.length;
    int* next = new int[len+1];
    int i = 0, j = -1;
    next[0] = -1;
    while (i < len) {
        if (j == -1 || T[i] == T[j]) {
            ++i;++j;
            next[i] = j;
        }else {
            j = next[j];
        }
    }

    return next;
}

int indexKmp(String S, String T) {
    int* next = getNext(T);
    int i = 0, j = 0, sl = S.length, tl = T.length;

    while (i < sl && j < tl) {
        if (j == -1 || S[i] == T[j]) {
            i++;j++;
        }else {
            j = next[j];
        }
    }
    delete[] next;

    if (j == tl) {
        return i-j;
    }
    return -1;
}
#endif //DATA_STRUCTURE_QUERY_H
