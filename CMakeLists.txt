cmake_minimum_required(VERSION 3.12)
project(data_structure)

set(CMAKE_CXX_STANDARD 14)

include_directories(list)
include_directories(query)
include_directories(sort)

add_executable(data_structure
        query/query.h
        sort/sort.h
        main.cpp list/list.h list/question.h stack/stack.h queue/queue.h tree/tree.h)
