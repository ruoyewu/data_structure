//
// Created by 张群 on 2018/8/16.
//

#ifndef DATA_STRUCTURE_BTREE_H
#define DATA_STRUCTURE_BTREE_H

#include "Tree.h"
#include "Compare.h"
#include "../list/ArrayList.h"
#include "../stack/ArrayStack.h"

/**
 * B- 树性质：
 * 1 根节点至少有两个孩子
 * 2 除了根节点以外，所有内部节点至少有 (m/2)（向上取整）个孩子
 * 3 所有的外部节点在同一层
 */

template <typename T>
struct BTreeNode {
    ArrayList<T>* index;
    ArrayList<BTreeNode<T>*>* children;

    BTreeNode() {
        index = new ArrayList<T>();
        children = new ArrayList<BTreeNode<T>*>();
    }
};

template <typename T>
class BTree : Tree<T> {
private:
    BTreeNode<T>* root;
    Compare<T>* com;
    int m;
    int size;
public:
    BTree(int m, Compare<T>* com) {
        this->m = m;
        this->com = com;
        this->size = 0;
        this->root = NULL;
    }

    int length() {
        return size;
    }

    bool add(T ele) {
        // 待添加的元素的左孩子
        BTreeNode<T>* lc = NULL;
        // 待添加的元素的右孩子
        BTreeNode<T>* rc = NULL;
        // 保存查找路径的栈
        ArrayStack<BTreeNode<T>*> stack;
        BTreeNode<T>* node = root;
        if (node == NULL) {
            root = new BTreeNode<T>();
            root->index->add(ele, 0);
            root->children->add(lc, 0);
            root->children->add(rc, 0);
            size++;
            return true;
        }

        // 查询节点要添加的位置
        while (node != NULL) {
            BTreeNode<T>* child = find(ele, node);
            if (child == node) {
                // 表示 ele 在 node 中存在，添加失败
                return false;
            }else {
                // 找到 ele 在 node 中的子树的位置，返回其子树，可能为 NULL
                stack.push(node);
                node = child;
            }
        }

        bool isAdd = false;
        while (!stack.empty()) {
            node = stack.pop();
            // 将节点添加到对应的位置
            // 同时删去当前位置原本对应的子树，并在当前位置插入对应的节点的左右子树
            int p = insert(ele, node->index);
            node->children->removeAt(p);
            node->children->add(rc, p);
            node->children->add(lc, p);
            // 检测插入新元素后是否溢出
            // 如果溢出，需要调整节点
            // 否则，完成添加后直接返回
            if (isFull(node)) {
                lc = node;
                rc = new BTreeNode<T>();
                int mid = m/2;

                // 构建新的待添加元素
                ele = node->index->get(mid);

                // 构建新的右子树
                int i;
                for (i = mid+1; i < m; ++i) {
                    rc->index->add(lc->index->get(i));
                    rc->children->add(lc->children->get(i));
                }
                rc->children->add(lc->children->get(i));

                // 构建新的左子树
                lc->index->removeAt(mid, m-1);
                lc->children->removeAt(mid+1, m);
            } else {
                isAdd = true;
                // 如果插入了当前节点之后不超过 B- 树的最大子树个数
                // 则视为插入结束
                break;
            }
        }

        if (!isAdd) {
            root = new BTreeNode<T>();
            root->index->add(ele, 0);
            root->children->add(rc, 0);
            root->children->add(lc, 0);
        }

        size++;
        return true;
    }

    bool find(T ele) {
        return true;
    }

    bool remove(T ele) {
        return true;
    }

private:
    BTreeNode<T>* find(T key, BTreeNode<T>* root) {
        int i;
        for (i = 0; i < root->index->length(); ++i) {
            int res = com->compare(key, root->index->get(i));
            if (res == 0) {
                return root;
            }
            if (res > 0) {
                break;
            }
        }
        return root->children->get(i);
    }

    int insert(T key, ArrayList<T>* list) {
        int i;
        for (i = 0; i < list->length() && com->compare(key, list->get(i)) < 0; ++i);
        list->add(key, i);
        return i;
    }

    bool isFull(BTreeNode<T>* node) {
        return node->index->length() == m;
    }
};

#endif //DATA_STRUCTURE_BTREE_H
