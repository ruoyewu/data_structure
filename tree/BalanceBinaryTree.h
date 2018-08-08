//
// Created by 张群 on 2018/8/7.
//

#ifndef DATA_STRUCTURE_BALANCEBINARYTREE_H
#define DATA_STRUCTURE_BALANCEBINARYTREE_H

#include "Tree.h"
#include "Compare.h"
#include "../stack/ArrayStack.h"

template <typename T>
struct BalanceTreeNode {
    T data;
    int level;
    BalanceTreeNode<T>* left;
    BalanceTreeNode<T>* right;

    explicit BalanceTreeNode(T ele) {
        data = ele;
        left = NULL;
        right = NULL;
        level = 1;
    }
};

template <typename T>
struct BalanceFindNode {
    BalanceTreeNode<T>* node;
    bool left;
    BalanceFindNode(BalanceTreeNode<T>* node, bool left) {
        this->node = node;
        this->left = left;
    }
};

template <typename T>
class BalanceBinaryTree : public Tree<T> {
private:
    BalanceTreeNode<T>* root;
    Compare<T>* com;
    int size;

public:
    explicit BalanceBinaryTree(Compare<T>* compare) {
        root = NULL;
        com = compare;
        size = 0;
    }

    ~BalanceBinaryTree() {
        delete root;
        delete com;
    }

    /**
     * 在平衡树中插入节点
     * @param ele 插入节点值
     * @return true：插入成功，false：插入失败
     */
    bool add(T ele) {
        BalanceTreeNode<T>* node = root;
        if (node == NULL) {
            root = new BalanceTreeNode(ele);
        }else {
            ArrayStack<BalanceFindNode<T>*> stack;
            bool preLeft = true;
            while(true) {
                if (node == NULL) {
                    BalanceFindNode<T>* pre = stack.top();
                    (pre->left ? pre->node->left : pre->node->right) = new BalanceTreeNode(ele);
                    while (!stack.empty()) {
                        BalanceFindNode<T>* n = stack.pop();
                        int b = computeBalance(n->node);
                        // 已知在插入当前节点之前是平衡树，所以插入一个节点之后，平衡因子的范围是 -2 -1 0 1 2
                        // 且只在 abs(b) == 2 的时候才会失衡，此时需要重新调整
                        // 并且 b == 2 代表左树高，b == -2 代表右树高
                        if (abs(b) == 2) {
                            BalanceFindNode<T>* p;
                            /**
                             * 插入节点引起的不平衡有四种，即 ll lr rl rr
                             * 其中第一个 l(r) 代表插入节点在当前节点的 左子树(右子树)
                             * 第二个 l(r) 代表插入节点在当前节点的 左孩子(右孩子) 的 左子树(右子树)
                             *
                             * 首先判断栈是否为空，以此来决定当前节点的父节点
                             * 若 b > 0 即 b == 2，则意味着插入的节点在 node 的左子树，所以首先是 l 型
                             * 然后判断 preLeft 即判断插入的节点在 node 的左孩子的左子树还是右子树
                             * 若 preLeft == true ，则类型是 ll 型，执行 ll 变换
                             * 其他同理
                             */
                            (stack.empty()
                             ? root
                             : (p = stack.top(), p->left ? p->node->left : p->node->right))
                                    =
                                    b > 0 ? (
                                            preLeft
                                            ? ll(n->node) : lr(n->node)
                                    ) : (
                                            preLeft
                                            ? rl(n->node) : rr(n->node)
                                    );
                        }
                        preLeft = n->left;
                        delete n;
                    }
                    break;
                }else {
                    int res = com->compare(node->data, ele);
                    if (res < 0) {
                        stack.push(new BalanceFindNode(node, true));
                        node = node->left;
                    }else if (res > 0){
                        stack.push(new BalanceFindNode(node, false));
                        node = node->right;
                    }else {
                        return false;
                    }
                }
            }
        }
        size++;
        return true;
    }

    /**
     * 在平衡二叉树中删除某个节点，首先要将这个节点删除，并且，从被删除的节点上溯到根节点，
     * 以及直到被用来替换已删除节点的位置的节点，所有这些在删除过程中被访问的节点，其平衡因子都有可能改变
     * 所以需要从最底层节点开始依次完成各个子树的平衡，一直到根节点，所以这里使用栈保存在删除路径（即删除
     * 过程中访问过的路径），具体调整步骤类似插入过程中的动作
     * @param ele 待删除元素
     * @return true：删除成功， false：删除失败
     */
    bool remove(T ele) {
        BalanceTreeNode<T>* node = root;
        if (node == NULL) {
            return false;
        }else {
            ArrayStack<BalanceFindNode<T>*> stack;
            while (node != NULL) {
                int res = com->compare(node->data, ele);
                if (res > 0) {
                    stack.push(new BalanceFindNode(node, false));
                    node = node->right;
                }else if (res < 0) {
                    stack.push(new BalanceFindNode(node, true));
                    node = node->left;
                }else {
                    /**
                     * 找到待删除节点并删除
                     * 同时将删除过程中所有经过的节点加入栈中，供之后平衡树的时候回溯
                     * 删除节点的过程分为四种情况
                     */
                    if (node->left == NULL && node->right == NULL) {
                        if (stack.empty()) {
                            root = NULL;
                        }else {
                            BalanceFindNode<T>* pre = stack.top();
                            (pre->left ? pre->node->left : pre->node->right) = NULL;
                        }
                    }else if (node->left == NULL) {
                        if (stack.empty()) {
                            root = node->right;
                            stack.push(new BalanceFindNode(root, false));
                        }else {
                            BalanceFindNode<T>* pre = stack.top();
                            (pre->left ? pre->node->left : pre->node->right) = node->right;
                        }
                    }else if (node->right == NULL) {
                        if (stack.empty()) {
                            root = node->left;
                            stack.push(new BalanceFindNode(root, true));
                        }else {
                            BalanceFindNode<T>* pre = stack.top();
                            (pre->left ? pre->node->left : pre->node->right) = node->left;
                        }
                    }else {
                        BalanceTreeNode<T>* r = node->left;
                        stack.push(new BalanceFindNode(node, true));
                        while (r->right != NULL) {
                            stack.push(new BalanceFindNode(r, false));
                            r = r->right;
                        }
                        node->data = r->data;
                        BalanceFindNode<T>* pre = stack.top();
                        (pre->left ? pre->node->left : pre->node->right) = r->left;
                        delete r;
                    }

                    // 删除节点完成之后，沿着访问路径回溯，依次修改当前结构，使之平衡
                    while (!stack.empty()) {
                        BalanceFindNode<T>* n = stack.pop();
                        int b = computeBalance(n->node);
                        if (abs(b) == 2) {
                            /**
                             * abs(b) == 2 表示不平衡，需要调整
                             *
                             * 删除节点引起的不平衡有 6 种，即 l0 l1 l-1 r0 r1 r-1
                             * 其中的 l(r) 指删除的节点在当前节点的 左子树(右子树)
                             * 0(1)(-1) 代表当前节点的 右孩子(左孩子) 的平衡因子为 0(1)(-1)
                             *
                             * 同时，它们有对应关系
                             * ll = r0(r1)
                             * lr = r-1
                             * rr = l0(l-1)
                             * rl = l1
                             *
                             * 首先栈是否为空
                             * 然后判断 b 的值，当 b == 2 时，意味着删除的节点在 node 的右子树
                             * 然后判断 node 对应的孩子的平衡因子，确定不平衡类型
                             * 最后根据对应关系调用函数完成调整
                             */
                            BalanceFindNode<T>* p;
                            (stack.empty()
                             ? root     // 到达根节点
                             : (p = stack.pop(), p->left ? p->node->left : p->node->right)) // 未达根节点
                                    = b > 0 ? (
                                            computeBalance(n->node->left) > -1 ? ll(n->node) : lr(n->node)
                                    ) : (
                                            computeBalance(n->node->right) < 1 ? rr(n->node) : rl(n->node)
                                    );
                        }
                    }
                    size--;
                    return true;
                }
            }
            return false;
        }
    }

    bool find(T ele) {
        BalanceTreeNode<T>* node = root;
        while (node != NULL) {
            int res = com->compare(node->data, ele);
            if (res > 0) {
                node = node->right;
            }else if (res < 0) {
                node = node->left;
            }else {
                return true;
            }
        }
        return false;
    }
    
    int length() {
        return size;
    }

private:
    int computeBalance(BalanceTreeNode<T>* node) {
        int l = node->left == NULL ? 0 : node->left->level;
        int r = node->right == NULL ? 0 : node->right->level;
        node->level = max(l, r) + 1;
        return l - r;
    }

    BalanceTreeNode<T>* ll(BalanceTreeNode<T>* node) {
        BalanceTreeNode<T>* left = node->left;
        node->left = left->right;
        computeBalance(node);
        left->right = node;
        computeBalance(left);
        return left;
    }

    BalanceTreeNode<T>* lr(BalanceTreeNode<T>* node) {
        node->left = rr(node->left);
        computeBalance(node);
        return ll(node);
    }

    BalanceTreeNode<T>* rl(BalanceTreeNode<T>* node) {
        node->right = ll(node->right);
        computeBalance(node);
        return rr(node);
    }

    BalanceTreeNode<T>* rr(BalanceTreeNode<T>* node) {
        BalanceTreeNode<T>* right = node->right;
        node->right = right->left;
        computeBalance(node);
        right->left = node;
        computeBalance(right);
        return right;
    }

    int max(int a, int b) {
        return b > a ? b : a;
    }

    int abs(int a) {
        return a > 0 ? a : -a;
    }
};

#endif //DATA_STRUCTURE_BALANCEBINARYTREE_H
