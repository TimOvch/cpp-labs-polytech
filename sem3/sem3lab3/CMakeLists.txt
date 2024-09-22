cmake_minimum_required(VERSION 3.25)
project(sem3lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(sem3lab3 main.cpp
        MyString.cpp
        MyVector.cpp
        shape.cpp
        MyStack.h
        MyStack.cpp)
