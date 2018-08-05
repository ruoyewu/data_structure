//
// Created by 张群 on 2018/8/5.
//

#ifndef DATA_STRUCTURE_LINKEDTREE_H
#define DATA_STRUCTURE_LINKEDTREE_H

#include "Tree.h"
#include "Compare.h"
#include "../stack/ArrayStack.h"
#include "../list/ArrayList.h"
#include "../queue/ArrayQueue.h"

template <typename T>
struct BinaryTreeNode {
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(T ele) {
        data = ele;
        left = NULL;
        right = NULL;
    }
};

template <typename T>
class LinkedBinaryTree : public Tree<T> {
private:
    BinaryTreeNode* root;
    Compare<T> com;
    ArrayList<T>* visitList;
    int size;
public:
    explicit LinkedBinaryTree(Compare<T> com) {
        this->com = com;
        root = NULL;
        visitList = new ArrayList<T>();
        size = 0;
    }

    bool add(T ele) {
        BinaryTreeNode* n = root;
        if (n == NULL) {
            root = new BinaryTreeNode(ele);
        }else {
            while(true) {
                int res = com.compare(n->data, ele);
                if (res <= 0) {
                    if (n->left != NULL) {
                        n = n->left;
                    }else {
                        n->left = new BinaryTreeNode(ele);
                        break;
                    }
                }else {
                    if (n->right != NULL) {
                        n = n->right;
                    }else {
                        n->right = new BinaryTreeNode(ele);
                        break;
                    }
                }
            }
        }
        size++;
        return true;
    }

    void clearOut() {
        visitList->clear();
    }

    List<T>* getOut() {
        return visitList;
    }

    /*
     * 先序遍历，递归
     */
    void preOrder1(BinaryTreeNode* node) {
        if (node != NULL) {
            visit(node);
            preOrder1(node->left);
            preOrder1(node->right);
        }
    }

    /**
     * 先序遍历，非递归
     */
    void preOrder(BinaryTreeNode* node) {
        if (node != NULL) {
            auto* stack = new ArrayStack<BinaryTreeNode*>();
            while (node != NULL || !stack->empty()) {
                if (node != NULL) {
                    visit(node);
                    stack->push(node);
                    node = node->left;
                }else {
                    node = stack->pop();
                    node = node->right;
                }
            }
        }
    }

    /*
     * 中序遍历，递归
     */
    void inOrder1(BinaryTreeNode* node) {
        if (node != NULL) {
            inOrder1(node->left);
            visit(node);
            inOrder1(node->right);
        }
    }

    /**
     * 中序遍历，非递归
     */
    void inOrder(BinaryTreeNode* node) {
        if (node != NULL) {
            auto* stack = new ArrayStack<BinaryTreeNode*>();
            while (node != NULL || !stack->empty()) {
                if (node != NULL) {
                    stack->push(node);
                    node = node->left;
                }else {
                    node = stack->pop();
                    visit(node);
                    node = node->right;
                }
            }
        }
    }

    /**
     * 后序遍历，递归
     */
    void postOrder1(BinaryTreeNode* node) {
        if (node != NULL) {
            postOrder1(node->left);
            postOrder1(node->right);
            visit(node);
        }
    }

    /**
     * 后序遍历，非递归
     * 对于一个节点，如果它没有孩子，则直接访问并出栈，否则将孩子入栈
     * 对于一个父节点，只有访问过它的孩子之后才能访问当前节点
     */
    void postOrder(BinaryTreeNode* node) {
        if (node != NULL) {
            auto* stack = new ArrayStack<BinaryTreeNode*>();
            BinaryTreeNode* pre;
            BinaryTreeNode* cur;
            stack->push(node);
            while (!stack->empty()) {
                cur = stack->top();
                if (cur->left == NULL && cur->right == NULL) {
                    visit(cur);
                    stack->pop();
                    pre = cur;
                } else if (pre != NULL && (pre == cur->left || pre == cur->right)) {
                    visit(cur);
                    stack->pop();
                    pre = cur;
                } else {
                    if (cur->right != NULL) {
                        stack->push(cur->right);
                    }
                    if (cur->left != NULL) {
                        stack->push(cur->left);
                    }
                }
            }
        }
    }

    /**
     * 层序遍历，使用队列
     */
    void levelOrder(BinaryTreeNode* node) {
        if (node != NULL) {
            auto* queue = new ArrayQueue<BinaryTreeNode*>();
            queue->enqueue(node);
            while (!queue->empty()) {
                node = queue->dequeue();
                visit(node);
                if (node->left != NULL) {
                    queue->enqueue(node->left);
                }
                if (node->right != NULL) {
                    queue->enqueue(node->right);
                }
            }
        }
    }

private:
    void visit(BinaryTreeNode* node) {
        visitList->add(node->data);
    }
};

#endif //DATA_STRUCTURE_LINKEDTREE_H
