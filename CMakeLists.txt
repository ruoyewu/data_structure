cmake_minimum_required(VERSION 3.8)
project(data_structure)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp list/List.h list/ArrayList.h list/LinkedList.h stack/Stack.h stack/ArrayStack.h stack/LinkedStack.h queue/Queue.h queue/ArrayQueue.h stack/demo.h tree/Tree.h tree/Compare.h tree/LinkedBinaryTree.h tree/BalanceBinaryTree.h graph/Graph.h graph/LinkedGraph.h)
add_executable(data_structure ${SOURCE_FILES})