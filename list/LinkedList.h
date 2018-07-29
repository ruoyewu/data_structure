//
// Created by 张群 on 2018/7/27.
//

#ifndef DATA_STRUCTURE_LINKEDLIST_H
#define DATA_STRUCTURE_LINKEDLIST_H

#include <iostream>
#include "List.h"

template <typename T>
struct Node {
    T data;
    Node<T> *next;
    Node<T> *pre;

    Node(T data) {
        this->data = data;
        next = NULL;
        pre = NULL;
    }

    Node(T data, Node<T>* pre) {
        this->data = data;
        next = NULL;
        this->pre = pre;
    }
};

template <typename T>
class LinkedList: public List<T> {
private:
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    LinkedList() {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    ~LinkedList() {
        Node<T> *n;
        while (tail != NULL) {
            n = tail->pre;
            delete tail;
            tail = n;
        }
    }

    int length() {
        return size;
    }

    T get(int position) {
        int i = 0;
        Node<T> *n = head;
        while(n != NULL) {
            if (i++ == position) {
                return n->data;
            }
            n = n->next;
        }

        return NULL;
    }

    int indexAt(T ele) {
        int i = 0;
        Node<T> *n = head;
        while(n != NULL) {
            if (n->data == ele) {
                return i;
            }
            n = n->next;
            i ++;
        }
        return -1;
    }

    bool add(T ele) {
        if (head == NULL) {
            tail = head = new Node<T>(ele);
        } else {
            Node<T> *n = new Node<T>(ele, tail);
            tail->next = n;
            tail = n;
        }
        size++;
        return true;
    }

    bool add(T ele, int position) {
        int i = 0;
        Node<T> *n = head;
        Node<T> *node = new Node<T>(ele);
        if (n == NULL) {
            tail = head = node;
        } else if (position == 0) {
            node->next = head;
            head->pre = node;
            head = node;
        }
        else {
            while (n->next != NULL) {
                if (i == position) {
                    Node<T> *pre = n->pre;
                    pre->next = node;
                    node->pre = n->pre;
                    node->next = n;
                    break;
                } else {
                    i++;
                    n = n->next;
                }
            }
            if (i < position) {
                n->next = node;
                node->pre = n;
                tail = node;
            }
        }
        size++;
        return true;
    }

    T removeAt(int position) {
        int i = 0;
        Node<T> *n = head;
        while (n != NULL) {
            if (i++ == position) {
                Node<T> *pre = n->pre;
                if (pre == NULL) {
                    head = n->next;
                } else {
                    pre->next = n->next;
                    n->next->pre = pre;
                }
                T data = n->data;
                delete n;
                size--;
                return data;
            }
            n = n->next;
        }
        return NULL;
    }

    T remove(T ele) {
        Node<T> *n = head;
        while(n != NULL) {
            if (n->data == ele) {
                Node<T> *pre = n->pre;
                if (pre == NULL) {
                    head = n->next;
                } else {
                    pre->next = n->next;
                    n->next->pre = pre;
                }
                T data = n->data;
                delete n;
                size--;
                return data;
            }
            n = n->next;
        }
        return NULL;
    }

    bool empty() {
        return size == 0;
    }

    void destroy() {
        Node<T> *n;
        while (tail != NULL) {
            n = tail->pre;
            delete tail;
            tail = n;
        }
    }
};

#endif //DATA_STRUCTURE_LINKEDLIST_H
