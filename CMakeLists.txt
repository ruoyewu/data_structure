cmake_minimum_required(VERSION 3.8)
project(data_structure)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp list/List.h list/ArrayList.h list/LinkedList.h)
add_executable(data_structure ${SOURCE_FILES})