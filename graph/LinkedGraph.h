//
// Created by 张群 on 2018/8/10.
//

#ifndef DATA_STRUCTURE_LINKEDGRAPH_H
#define DATA_STRUCTURE_LINKEDGRAPH_H

/**
 * 变形的邻接表法
 * 将一个图中的所有节点使用 List 存放
 * 每个节点中使用 List 存放着它所有的 Next 节点
 * 如果存在从节点 A 到 B 的弧，即称 B 是 A 的一个 Next 节点，
 * 所以每一个 Next 节点代表着一个弧，所以它还有一个 weight 属性
 */

#include "Graph.h"
#include "../list/ArrayList.h"
#include "../queue/ArrayQueue.h"
#include "../tree/BalanceBinaryTree.h"
using namespace std;

template <typename T>
struct GraphNext;
template <typename T>
struct GraphNode;

template <typename T>
struct GraphNext {
    GraphNode<T>* data;
    int weight = 0;

    GraphNext(GraphNode<T>* data, int weight) {
        this->data = data;
        this->weight = weight;
    }
};

template <typename T>
struct GraphNode {
    T data;
    ArrayList<GraphNext<T>*>* next;
    int nextLength = 0;

    explicit GraphNode(T data) {
        this->data = data;
        this->next = new ArrayList<GraphNext<T>*>();
    }

    bool addNext(GraphNode<T>* next, int weight) {
        this->next->add(new GraphNext(next, weight));
        nextLength++;
        return true;
    }

    bool removeNext(GraphNode<T>* next) {
        GraphNext<T>* n;
        for (int i = 0; i < this->nextLength; ++i) {
            if ((n = this->next->get(i))->data == next) {
                this->next->removeAt(i);
                delete n;
                this->nextLength--;
                return true;
            }
        }
        return false;
    }

    GraphNext<T>* getNext(int position) {
        return this->next->get(position);
    }

    ~GraphNode() {
        next->destroy();
        delete next;
    }
};

template <typename T>
class GraphCom : public Compare<GraphNode<T>*> {
public:
    int compare(GraphNode<T>* x, GraphNode<T>* y) {
        return static_cast<int>(y - x);
    }
};


template <typename T>
class LinkedGraph : public Graph<T> {
private:
    ArrayList<GraphNode<T>*>* nodes;

public:
    LinkedGraph() {
        nodes = new ArrayList<GraphNode<T>*>(20);
    }

    bool adjacent(T x, T y) {
        int i;
        return (i = indexAt(x)) >= 0 && indexAt(y, nodes->get(i)->next) >= 0;
    }

    ArrayList<T> neighbors(T x) {
        ArrayList<T> list;

        int i = indexAt(x);
        if (i >= 0) {
            for (int j = 0; j < nodes->get(i)->nextLength; ++j) {
                list.add(nodes->get(i)->getNext(j)->data->data);
            }
        }

        return list;
    }

    bool add(T x) {
        int i = indexAt(x);
        if (i >= 0) {
            return false;
        }
        return nodes->add(new GraphNode<T>(x));
    }

    bool remove(T x) {
        int i = indexAt(x);
        if (i >= 0) {
            GraphNode<T>* n = nodes->get(i);
            nodes->removeAt(i);
            delete n;

            return true;
        }
        return false;
    }

    bool add(T x, T y, int weight) {
        int i = indexAt(x);
        int k = indexAt(y);
        if (i >= 0 && k >= 0) {
            int j = indexAt(y, nodes->get(i)->next);
            if (j < 0) {
                return nodes->get(i)->addNext(nodes->get(k), weight);
            }
        }
        return false;
    }

    bool remove(T x, T y) {
        int i = indexAt(x);
        int k = indexAt(y);
        if (i >= 0) {
            int j = indexAt(y, nodes->get(i)->next);
            if (j >= 0) {
                GraphNext<T>* n = nodes->get(i)->getNext(j);
                return nodes->get(i)->removeNext(nodes->get(k));
            }
        }
        return false;
    }

    T firstNeighbor(T x) {
        int i = indexAt(x);
        if (i >= 0 && !nodes->get(i)->next->empty()) {
            return nodes->get(i)->next->get(0)->data->data;
        }
        return NULL;
    }

    int getWeight(T x, T y) {
        int i = indexAt(x);
        if (i >= 0) {
            int j = indexAt(y, nodes->get(i)->next);
            if (j >= 0) {
                return nodes->get(i)->next->get(j)->weight;
            }
        }
        return -1;
    }

    bool setWeight(T x, T y, int weight) {
        int i = indexAt(x);
        if (i >= 0) {
            int j = indexAt(y, nodes->get(i)->next);
            if (j >= 0) {
                nodes->get(i)->next->get(j)->weight = weight;
                return true;
            }
        }
        return false;
    }

    int** toRectangle() {
        int n = nodes->length();
        int** rec = new int*[n];
        for (int i = 0; i < n; ++i) {
            rec[i] = new int[n];
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < nodes->get(i)->next->length(); ++j) {
                GraphNode<T>* node = nodes->get(i)->next->get(j)->data;
                int weight = nodes->get(i)->next->get(j)->weight;

                int position = indexAt(node);
                if (position >= 0) {
                    rec[i][position] = weight;
                }
            }
        }
        return rec;
    }

    /**
     * 图的广度优先遍历
     */
    void traverseBreadth() {
        if (nodes->empty()) {
            return;
        }
        BalanceBinaryTree<GraphNode<T>*> tree(new GraphCom<T>());
        ArrayQueue<GraphNode<T>*> queue;
        queue.enqueue(nodes->get(0));
        while (!queue.empty()) {
            GraphNode<T>* node = queue.dequeue();
            if (!tree.find(node)) {
                tree.add(node);
                visit(node);
                for (int j = 0; j < node->nextLength; ++j) {
                    queue.enqueue(node->getNext(j)->data);
                }
            }
        }
//        for (int i = 0; i < nodes->length(); ++i) {
//            queue.enqueue(nodes->get(i));
//            while (!queue.empty()) {
//                GraphNode<T>* node = queue.dequeue();
//                if (!tree.find(node)) {
//                    tree.add(node);
//                    visit(node);
//                    for (int j = 0; j < node->nextLength; ++j) {
//                        queue.enqueue(node->getNext(j)->data);
//                    }
//                }
//            }
//        }
    }

    /**
     * 图的深度优先遍历
     */
    void traverseDepth() {
        if (nodes->empty()) {
            return;
        }
        BalanceBinaryTree<GraphNode<T>*> tree(new GraphCom<T>());
        ArrayStack<GraphNode<T>*> stack;
        stack.push(nodes->get(0));
        while (!stack.empty()) {
            GraphNode<T>* node = stack.pop();
            if (!tree.find(node)) {
                tree.add(node);
                visit(node);
                for (int j = 0; j < node->nextLength; ++j) {
                    stack.push(node->getNext(j)->data);
                }
            }
        }
    }

    /**
     * 最短路径 Dijkstra 算法
     * 计算从 v0 点到其他各点的最短路径长度
     */
    void dijkstra(int** arcs, int* dist, int* path, int n) {
        int max = INT_MAX;
        int s[n];
        for (int i = 0; i < n; ++i) {
            s[i] = 0;
            dist[i] = arcs[0][i];
        }
        s[0] = 1;

        int min = -1;
        for (int i = 0; i < n; ++i) {
            if (!s[i]) {
                min == -1 ? (min = i)
                          : (dist[i] < dist[min] ? min = i : min);
            }
        }
        s[min] = 1;

    }

private:
    int indexAt(T x) {
        for (int i = 0; i < nodes->length(); ++i) {
            if (nodes->get(i)->data == x) {
                return i;
            }
        }
        return -1;
    }

    int indexAt(T x, List<GraphNext<T>*>* next) {
        for (int i = 0; i < next->length(); ++i) {
            if (next->get(i)->data->data == x) {
                return i;
            }
        }
        return -1;
    }

    void visit(GraphNode<T>* node) {
        cout << node->data << " ";
    }
};

#endif //DATA_STRUCTURE_LINKEDGRAPH_H
