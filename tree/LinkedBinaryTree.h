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
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;

    explicit BinaryTreeNode(T ele) {
        data = ele;
        left = NULL;
        right = NULL;
    }
};

template <typename T>
class LinkedBinaryTree : public Tree<T> {
private:
    BinaryTreeNode<T>* root;
    Compare<T>* com;
    ArrayList<T>* visitList;
    int size;
public:
    explicit LinkedBinaryTree(Compare<T>* compare) {
        com = compare;
        root = NULL;
        visitList = new ArrayList<T>();
        size = 0;
    }

    ~LinkedBinaryTree() {
        visitList->destroy();
        delete visitList;
        delete com;
        delete root;
    }

    bool add(T ele) {
        BinaryTreeNode<T>* n = root;
        if (n == NULL) {
            root = new BinaryTreeNode(ele);
        }else {
            while(true) {
                int res = com->compare(n->data, ele);
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
    void preOrder1(BinaryTreeNode<T>* node) {
        if (node != NULL) {
            visit(node);
            preOrder1(node->left);
            preOrder1(node->right);
        }
    }

    /**
     * 先序遍历，非递归
     */
    void preOrder(BinaryTreeNode<T>* node) {
        if (node != NULL) {
            ArrayStack<BinaryTreeNode<T>*> stack;
            while (node != NULL || !stack.empty()) {
                if (node != NULL) {
                    visit(node);
                    stack.push(node);
                    node = node->left;
                }else {
                    node = stack.pop();
                    node = node->right;
                }
            }
        }
    }

    /*
     * 中序遍历，递归
     */
    void inOrder1(BinaryTreeNode<T>* node) {
        if (node != NULL) {
            inOrder1(node->left);
            visit(node);
            inOrder1(node->right);
        }
    }

    /**
     * 中序遍历，非递归
     */
    void inOrder(BinaryTreeNode<T>* node) {
        if (node != NULL) {
            ArrayStack<BinaryTreeNode<T>*> stack;
            while (node != NULL || !stack.empty()) {
                if (node != NULL) {
                    stack.push(node);
                    node = node->left;
                }else {
                    node = stack.pop();
                    visit(node);
                    node = node->right;
                }
            }
        }
    }

    /**
     * 后序遍历，递归
     */
    void postOrder1(BinaryTreeNode<T>* node) {
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
    void postOrder(BinaryTreeNode<T>* node) {
        if (node != NULL) {
            ArrayStack<BinaryTreeNode<T>*> stack;
            BinaryTreeNode<T>* pre;
            BinaryTreeNode<T>* cur;
            stack.push(node);
            while (!stack.empty()) {
                cur = stack.top();
                if (cur->left == NULL && cur->right == NULL) {
                    visit(cur);
                    stack.pop();
                    pre = cur;
                } else if (pre != NULL && (pre == cur->left || pre == cur->right)) {
                    visit(cur);
                    stack.pop();
                    pre = cur;
                } else {
                    if (cur->right != NULL) {
                        stack.push(cur->right);
                    }
                    if (cur->left != NULL) {
                        stack.push(cur->left);
                    }
                }
            }
        }
    }

    /**
     * 对于后序遍历而言，父节点的前驱节点一定是它的右孩子（如果有的话）
     * 对于一个根节点而言，它的第一个访问节点一定是左子树的最左节点（如果有左子树）
     * 或者是右子树的最左节点（如果没有左子树）
     */
    void postOrder2(BinaryTreeNode<T>* node) {
        if (node != NULL) {
            ArrayStack<BinaryTreeNode<T>*> stack;
            BinaryTreeNode<T>* pre;
            while (node != NULL || !stack.empty()) {
                if (node != NULL) {
                    stack.push(node);
                    node = node->left;
                }else {
                    node = stack.top();
                    if (node->right != NULL && node->right != pre) {
                        node = node->right;
                        stack.push(node);
                        node = node->left;
                    }else {
                        node = stack.pop();
                        visit(node);
                        pre = node;
                        node = NULL;
                    }
                }
            }
        }
    }

    /**
     * 层序遍历，使用队列
     */
    void levelOrder(BinaryTreeNode<T>* node) {
        if (node != NULL) {
            ArrayQueue<BinaryTreeNode<T>*> queue;
            queue.enqueue(node);
            while (!queue.empty()) {
                node = queue.dequeue();
                visit(node);
                if (node->left != NULL) {
                    queue.enqueue(node->left);
                }
                if (node->right != NULL) {
                    queue.enqueue(node->right);
                }
            }
        }
    }

    /**
     * 层序遍历，自下而上，自右而左
     * 即将原有的层序遍历逆序访问
     */
    void levelOrderReverse(BinaryTreeNode<T>* node) {
        if (node != NULL) {
            levelOrder(node);
            visitList->reverse(0, visitList->length() - 1);
        }
    }

    /**
     * 非递归求树的层数
     */
    int height(BinaryTreeNode<T>* node) {
        if (node != NULL) {
            ArrayQueue<BinaryTreeNode<T>*> queue;
            // curr 保存当前层的剩余节点个数，next 保存下一层的节点个数，h 保存当前扫描的层数
            // 遍历完成之后，h 即树的层数
            int curr = 1, next = 0, h = 0;
            queue.enqueue(node);

            while (!queue.empty()) {
                node = queue.dequeue();
                if (node->left != NULL) {
                    next++;
                    queue.enqueue(node->left);
                }
                if (node->right != NULL) {
                    next++;
                    queue.enqueue(node->right);
                }

                // 判断当前层是否扫描完
                if (--curr == 0) {
                    curr = next;
                    next = 0;
                    h++;
                }
            }

            return h;
        }
        return 0;
    }

    /**
     * 使用先序遍历和中序遍历建立二叉树，递归
     *
     */
    void build(T* preOrder, T* inOrder, int n) {
        root = buildTree(preOrder, inOrder, 0, 0, n-1, n-1);
    }

    /**
     * 判断是否是完全二叉树
     */
    bool isComplete(BinaryTreeNode<T>* node) {
        if (node != NULL) {
            bool isNull = false;
            ArrayQueue<BinaryTreeNode<T>*> queue;
            queue.enqueue(node);

            while (!queue.empty()) {
                node = queue.dequeue();
                if (node == NULL && isNull) {
                    return false;
                }else if (node == NULL) {
                    isNull = true;
                    continue;
                }
                queue.enqueue(node->left);
                queue.enqueue(node->right);
            }

            return true;
        }
        return false;
    }

    /**
     * 满二叉树，根据前序遍历得后序遍历，递归
     */
    void preToPost(T* preOrder, int n) {
        preToPost(preOrder, 0, n-1);
    }

    /**
     * 求所有叶节点带权路径的长度和
     * 使用非递归后序遍历，每次找到一个叶节点，栈中保存的即是路径，然后依次取出并求路径长度即可
     */
    float getWPL(BinaryTreeNode* node) {
        float len = 0;
        if (node != NULL) {
            ArrayStack<T> stack;
            BinaryTreeNode* pre;
            while (node != NULL || !stack.empty()) {
                if (node != NULL) {
                    stack.push(node);
                    node = node->left;
                }else {
                    node = stack.top();
                    if (node->right != NULL && node->right != pre) {
                        stack.push(node->right);
                        node = node->right->left;
                    }else {
                        node = stack.pop();
                        if (node->left == NULL && node->right == NULL) {
                            // 叶子节点，计算路径
                            ArrayStack<T> s;
                            float l = 0;
                            while (!stack.empty()) {
                                s.push(stack.pop());
                            }
                            while (!s.empty()) {
                                BinaryTreeNode* n = s.pop();
                                l += n->data;
                                stack.push(n);
                            }
                            len += l;
                        }
                        pre = node;
                        node = NULL;
                    }
                }
            }
        }
        return len;
    }

private:
    BinaryTreeNode<T>* buildTree(T* preOrder, T* inOrder, int l1, int l2, int h1, int h2) {
        T ele = preOrder[l1];
        BinaryTreeNode<T>* node = new BinaryTreeNode(ele);

        int i;
        for (i = l2; inOrder[i] != ele; i++);
        int ll = i - l2, rl = h2 - i;
        if (ll) {
            node->left = buildTree(preOrder, inOrder, l1+1, l1+ll, l2, l2+ll-1);
        }
        if (rl) {
            node->right = buildTree(preOrder, inOrder, h1-rl+1, h1, h2-rl+1, h2);
        }

        return node;
    }

    void preToPost(T* preOrder, int l, int r) {
        if (l < r) {
            // 将第一个元素移到末尾
            T i0 = preOrder[l];
            for (int i = l; i < r; ++i) {
                preOrder[i] = preOrder[i+1];
            }
            preOrder[r] = i0;

            int len = (r-l) / 2;
            if (len > 0) {
                preToPost(preOrder, l, l+len-1);
                preToPost(preOrder, l+len, r-1);
            }
        }
    }

    void visit(BinaryTreeNode<T>* node) {
        visitList->add(node->data);
    }
};

#endif //DATA_STRUCTURE_LINKEDTREE_H
