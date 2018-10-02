//
// Created by 张群 on 2018/9/28.
//

#ifndef DATA_STRUCTURE_TREE_H
#define DATA_STRUCTURE_TREE_H

#include <iostream>
#include <cmath>
#include "../list/list.h"
#include "../stack/stack.h"
#include "../queue/queue.h"

/**
 * 二叉树
 * @tparam T
 */
template <typename T>
struct BinaryTreeNode {
    typedef BinaryTreeNode BTNode, *BTree;

    T data;
    BTNode* lc = NULL;
    BTNode* rc = NULL;

    explicit BinaryTreeNode(T data) {
        this->data = data;
    }
};

template <typename T>
using BTNode = BinaryTreeNode<T>;

template <typename T>
using BTree = BinaryTreeNode<T>*;


template <typename T>
bool addNode(BTree<T> &tree, T x, int (*com)(T, T)) {
    BTNode<T>* node = tree;
    if (node == NULL) {
        tree = new BTNode<T>(x);
        return true;
    }

    while (true) {
        int c = com(node->data, x);
        if (c > 0) {
            if (node->rc != NULL) {
                node = node->rc;
            } else {
                node->rc = new BTNode<T>(x);
                break;
            }
        } else if (c < 0) {
            if (node->lc != NULL) {
                node = node->lc;
            } else {
                node->lc = new BTNode<T>(x);
                break;
            }
        } else {
            return false;
        }
    }

    return true;
}

template <typename T>
bool removeNode(BTree<T> &tree, T x, int (*com(T, T))) {
    BTNode<T>* node = tree;
    BTNode<T>* parent = NULL;
    bool isLeft = false;
    while (node != NULL) {
        int c = com(node->data, x);
        if (c > 0) {
            parent = node;
            isLeft = false;
            node = node->rc;
        } else if (c < 0) {
            parent = node;
            isLeft = true;
            node = node->lc;
        } else {
            break;
        }
    }

    if (node == NULL) {
        return false;
    }

    if (node->lc == NULL) {
        if (parent == NULL) {
            // 删除的是根节点
            tree = node->rc;
        } else {
            // 非根节点且没有左子树，直接使用右子树替代之
            isLeft ? (parent->lc = node->rc) : (parent->rc = node->rc);
        }
    } else if (node->rc == NULL) {
        if (parent == NULL) {
            // 删除根节点
            tree = node->lc;
        } else {
            // 非根节点且没有右子树，使用左子树替代之
            isLeft ? (parent->lc = node->lc) : (parent->rc = node->lc);
        }
    } else {
        // 左右子树均在，使用左子树的最右结点替代之
        BTNode<T>* n = node->lc;
        BTNode<T>* np = NULL;
        while (n->rc != NULL) {
            np = n;
            n = n->rc;
        }
        if (np == NULL) {
            // 左孩子没有右子树，则直接使用左孩子替代之
            if (parent == NULL) {
                n->rc = node->rc;
                tree = n;
            } else {
                n->rc = node->rc;
                isLeft ? (parent->lc = n) : (parent->rc = n);
            }
        } else {
            // 左孩子有右子树，则在左子树中删除最右节点，并将最右节点的值赋给待删除结点
            np->rc = n->lc;
            node->data = n->data;
        }
    }
    return true;
}

template <typename T>
bool findNode(BTree<T> &tree, T x, int (*com(T, T))) {
    BTNode<T>* node = tree;
    while (node != NULL) {
        int c = com(node->data, x);
        if (c > 0) {
            node = node->rc;
        } else if (c < 0) {
            node = node->lc;
        } else {
            return true;
        }
    }
    return false;
}

template <typename T>
int sizeOf(BTree<T> &tree) {
    if (tree == NULL) {
        return 0;
    }
    BTNode<T>* node = tree;
    LinkedQueue<BTree<T>> queue = NULL;
    enqueue(queue, node);
    int count = 0;

    while (!empty(queue)) {
        node = dequeue(queue);
        count++;

        if (node->lc != NULL) {
            enqueue(queue, node->lc);
        }
        if (node->rc != NULL) {
            enqueue(queue, node->rc);
        }
    }

    return count;
}

template <typename T>
LinkedList<T> preOrder(BTree<T> &tree) {
    LinkedList<T> list = NULL;
    LinkedStack<BTree<T>> stack = NULL;

    push(stack, tree);

    while (!empty(stack)) {
        BTNode<T>* node = pop(stack);
        addNode(list, node->data);

        if (node->rc != NULL) {
            push(stack, node->rc);
        }
        if (node->lc != NULL) {
            push(stack, node->lc);
        }
    }

    return list;
}

template <typename T>
LinkedList<T> inOrder(BTree<T> &tree) {
    LinkedList<T> list = NULL;
    LinkedStack<BTree<T>> stack = NULL;

    BTNode<T>* node = tree;

    while (!empty(stack) || node != NULL) {
        if (node != NULL) {
            push(stack, node);
            node = node->lc;
        } else {
            node = pop(stack);
            addNode(list, node->data);
            node = node->rc;
        }
    }

    return list;
}

template <typename T>
LinkedList<T> postOrder(BTree<T> &tree) {
    LinkedList<T> list = NULL;
    LinkedStack<BTree<T>> stack = NULL;

    BTNode<T>* node = tree;
    BTNode<T>* pre = NULL;

    while (node != NULL || !empty(stack)) {
        if (node != NULL) {
            push(stack, node);
            node = node->lc;
        } else {
            node = top(stack);
            if (node->rc != NULL && node->rc != pre) {
                node = node->rc;
                push(stack, node);
                node = node->lc;
            } else {
                node = pop(stack);
                addNode(list, node->data);
                pre = node;
                node = NULL;
            }
        }
    }

    return list;
}

template <typename T>
LinkedList<T> levelOrder(BTree<T> &tree) {
    LinkedList<T> list = NULL;
    LinkedQueue<BTree<T>> queue = NULL;

    enqueue(queue, tree);

    while (!empty(queue)) {
        BTNode<T>* node = dequeue(queue);
        addNode(list, node->data);
        if (node->lc != NULL) {
            enqueue(queue, node->lc);
        }
        if (node->rc != NULL) {
            enqueue(queue, node->rc);
        }
    }

    return list;
}


template <typename T>
struct BalanceBinaryTreeNode {
    T data;
    int ch = 1;
    BalanceBinaryTreeNode* lc;
    BalanceBinaryTreeNode* rc;

    explicit BalanceBinaryTreeNode(T x) {
        this->data = x;
        this->lc = NULL;
        this->rc = NULL;
    }
};

template <typename T>
using BBTNode = BalanceBinaryTreeNode<T>;

template <typename T>
using BBTree = BalanceBinaryTreeNode<T>*;


template <typename T>
bool addNode(BBTree<T> &tree, T x, int (*com) (T, T)) {
    if (tree == NULL) {
        tree = new BBTNode<T>(x);
        return true;
    }

    LinkedStack<BBTree<T>> nodeStack = NULL;
    LinkedStack<bool> leftStack = NULL;
    BBTNode<T>* node = tree;

    // 先根据二叉排序树的方法插入结点，若已存在则返回 false
    while (node != NULL) {
        int c = com(node->data, x);
        if (c > 0) {
            push(nodeStack, node);
            push(leftStack, false);
            node = node->rc;
        } else if (c < 0) {
            push(nodeStack, node);
            push(leftStack, true);
            node = node->lc;
        } else {
            return false;
        }
    }
    top(leftStack) ? (top(nodeStack)->lc = new BBTNode<T>(x))
                    : (top(nodeStack)->rc = new BBTNode<T>(x));

    // 然后从当前节点往前回溯到根节点，若出现不平衡则调整
    bool isLeft, lastLeft;
    while (!empty(nodeStack)) {
        // 从栈中以此取出一组数据，即从新添加点到根节点的路径
        node = pop(nodeStack);
        lastLeft = isLeft;
        isLeft = pop(leftStack);

        computeCH(node);
        int dL = node->lc == NULL ? 0 : node->lc->ch;
        int dR = node->rc == NULL ? 0 : node->rc->ch;
        int d = dL - dR;

        // 若产生不平衡，则调整
        if (abs(d) == 2) {
            if (isLeft) {
                lastLeft ? ll(node) : lr(node);
            } else {
                lastLeft ? rl(node) : rr(node);
            }

            if (!empty(nodeStack)) {
                top(leftStack) ? (top(nodeStack)->lc = node)
                               : (top(nodeStack)->rc = node);
            } else {
                tree = node;
            }
        }
    }

    return true;
}

template <typename T>
bool findNode(BBTree<T> &tree, T x, int (*com) (T, T)) {
    if (tree == NULL) {
        return false;
    }

    BBTNode<T>* node = tree;
    while (node != NULL) {
        int c = com(node->data, x);
        if (c > 0) {
            node = node->rc;
        } else if (c < 0) {
            node = node->lc;
        } else {
            return true;
        }
    }
    return false;
}

template <typename T>
bool removeNode(BBTree<T> &tree, T x, int (*com) (T, T)) {
    if (tree == NULL) {
        return false;
    }

    LinkedStack<BBTree<T>> nodeStack = NULL;
    LinkedStack<bool> leftStack = NULL;
    BBTNode<T>* node = tree;

    // 先找到待删除的结点的位置
    while (node != NULL) {
        int c = com(node->data, x);
        if (c > 0) {
            push(nodeStack, node);
            push(leftStack, false);
            node = node->rc;
        } else if (c < 0) {
            push(nodeStack, node);
            push(leftStack, true);
            node = node->lc;
        } else {
            break;
        }
    }
    // node 为空说明待删除结点不存在
    if (node == NULL) {
        return false;
    }

    // 待删除结点是根节点，需要单独考虑
    if (empty(nodeStack)) {
        // 原本的树必然是平衡的，所以如果根节点只有一个孩子的话，这个孩子必然也是平衡的
        // 所以直接使孩子替代之
        if (node->lc == NULL && node->rc == NULL) {
            tree = NULL;
            return true;
        } else if (node->lc == NULL) {
            tree = tree->rc;
            return true;
        } else if (node->rc == NULL) {
            tree = tree->lc;
            return true;
        } else {
            // 有两个孩子的话，找到左子树的最右结点替代之
            // 并保存这个路径
            push(nodeStack, node);
            push(leftStack, true);
            BBTNode<T>* n = node->lc;

            while (n->rc != NULL) {
                push(nodeStack, n);
                push(leftStack, false);
                n = n->rc;
            }

            node->data = n->data;
            node = top(nodeStack);
            node->lc = n->lc;
            if (!top(leftStack)) {
                node->rc = NULL;
            }
        }
    } else {
        BBTNode<T>* p = top(nodeStack);
        bool pLeft = top(leftStack);
        // 再判断待删除结点是否有孩子
        if (node->lc == NULL && node->rc == NULL) {
            pLeft ? (p->lc = NULL) : (p->rc = NULL);
        } else if (node->lc == NULL) {
            pLeft ? (p->lc = node->rc) : (p->rc = node->rc);
        } else if (node->rc == NULL) {
            pLeft ? (p->lc = node->lc) : (p->rc = node->lc);
        } else {
            // 同上，找到左子树最右节点替代之
            push(nodeStack, node);
            push(leftStack, true);
            BBTNode<T>* n = node->lc;

            while (n->rc != NULL) {
                push(nodeStack, n);
                push(leftStack, false);
                n = n->rc;
            }

            node->data = n->data;
            node = top(nodeStack);
            node->lc = n->lc;
            if (!top(leftStack)) {
                node->rc = NULL;
            }
        }
    }

    // 然后还是照添加结点的时候的方式
    // 一步步回溯到根节点
    bool isLeft;
    while (!empty(nodeStack)) {
        // 从栈中以此取出一组数据，即从新添加点到根节点的路径
        node = pop(nodeStack);
        isLeft = pop(leftStack);

        computeCH(node);
        int d = computeBalance(node);

        // 若产生不平衡，则调整
        if (abs(d) == 2) {
            if (isLeft) {
                int dr = computeBalance(node->rc);
                if (dr == 0 || dr == -1) {
                    rr(node);
                } else {
                    rl(node);
                }
            } else {
                int dl = computeBalance(node->lc);
                if (dl == 0 || dl == 1) {
                    ll(node);
                } else {
                    lr(node);
                }
            }

            if (!empty(nodeStack)) {
                top(leftStack) ? (top(nodeStack)->lc = node)
                               : (top(nodeStack)->rc = node);
            } else {
                tree = node;
            }
        }
    }
    return true;
}

template <typename T>
int sizeOf(BBTree<T> &tree) {
    if (tree == NULL) {
        return 0;
    }
    BTNode<T>* node = tree;
    LinkedQueue<BTree<T>> queue = NULL;
    enqueue(queue, node);
    int count = 0;

    while (!empty(queue)) {
        node = dequeue(queue);
        count++;

        if (node->lc != NULL) {
            enqueue(queue, node->lc);
        }
        if (node->rc != NULL) {
            enqueue(queue, node->rc);
        }
    }

    return count;
}

template <typename T>
void ll(BBTree<T> &tree) {
    BBTNode<T>* l = tree->lc;
    tree->lc = l->rc;
    computeCH(tree);
    l->rc = tree;
    computeCH(l);
    tree = l;
}

template <typename T>
void lr(BBTree<T> &tree) {
    rr(tree->lc);
    ll(tree);
}

template <typename T>
void rr(BBTree<T> &tree) {
    BBTNode<T>* r = tree->rc;
    tree->rc = r->lc;
    computeCH(tree);
    r->lc = tree;
    computeCH(r);
    tree = r;
}

template <typename T>
void rl(BBTree<T> &tree) {
    ll(tree->rc);
    rr(tree);
}

template <typename T>
void computeCH(BBTree<T> &node) {
    // 计算当前节点的平衡数
    if (node->lc == NULL && node->rc == NULL) {
        node->ch = 1;
        return;
    }
    if (node->lc == NULL) {
        node->ch = node->rc->ch + 1;
    } else if (node->rc == NULL) {
        node->ch = node->lc->ch + 1;
    } else {
        node->ch = max(node->lc->ch, node->rc->ch) + 1;
    }
}

template <typename T>
int computeBalance(BBTree<T> &node) {
    int dL = node->lc == NULL ? 0 : node->lc->ch;
    int dR = node->rc == NULL ? 0 : node->rc->ch;
    return dL - dR;
}


/**
 * 一般树
 * @tparam T
 */
template <typename T>
struct TreeNode {
    T data;
    LinkedList<TreeNode<T>*> children;

    explicit TreeNode(T data) {
        this->data = data;
        this->children = NULL;
    }
};

template <typename T>
using TNode = TreeNode<T>;

template <typename T>
using Tree = TreeNode<T>*;


/*
 * 孩子兄弟表示树
 */
template <typename T>
struct ChildBrotherTreeNode {
    T data;
    ChildBrotherTreeNode* child;
    ChildBrotherTreeNode* brother;

    explicit ChildBrotherTreeNode(T data) {
        this->data = data;
        this->child = NULL;
        this->brother = NULL;
    }
};

template <typename T>
using CBTNode = ChildBrotherTreeNode<T>;

template <typename T>
using CBTree = ChildBrotherTreeNode<T>*;

template <typename T>
BTree<T> convertToBT(Tree<T> tree) {
    BTree<T> bTree = NULL;
    if (tree != NULL) {
        LinkedStack<Tree<T>> treeStack = NULL;
        LinkedStack<BTree<T>> bTreeStack = NULL;
        push(treeStack, tree);
        bTree = new BTNode<T>(tree->data);
        push(bTreeStack, bTree);

        while (!empty(treeStack)) {
            TreeNode<T>* tNode = pop(treeStack);
            int tLength = sizeOf(tNode->children);
            BTNode<T>* bNode = pop(bTreeStack);

            for (int i = 0; i < tLength; ++i) {
                TreeNode<T>* iNode = getNodeAt(tNode->children, i);
                if (i == 0) {
                    bNode->lc = new BTNode<T>(iNode->data);
                    bNode = bNode->lc;
                    push(treeStack, iNode);
                    push(bTreeStack, bNode);
                } else {
                    bNode->rc = new BTNode<T>(iNode->data);
                    bNode = bNode->rc;
                    push(treeStack, iNode);
                    push(bTreeStack, bNode);
                }
            }
        }
    }

    return bTree;
}

// question

template <typename T>
int computeWeight(BTree<T> &tree) {
    bool isLevel = true;
    int sum = 0;

    if (isLevel) {
        // 使用层序
        LinkedQueue<BTree<T>> queue = NULL;
        enqueue(queue, tree);
        int left = 1, lel = 1, nextL = 0;
        BTNode<T>* node;
        while (!empty(queue)) {
            node = dequeue(queue);
            if (node->lc == NULL && node->rc == NULL) {
                sum += lel;
            } else {
                if (node->lc != NULL) {
                    enqueue(queue, node->lc);
                    nextL++;
                }
                if (node->rc != NULL) {
                    enqueue(queue, node->rc);
                    nextL++;
                }
            }

            left--;
            if (left == 0) {
                left = nextL;
                nextL = 0;
                lel++;
            }
        }
    } else {
        // 使用后序
    }

    return sum;
}


#endif //DATA_STRUCTURE_TREE_H
