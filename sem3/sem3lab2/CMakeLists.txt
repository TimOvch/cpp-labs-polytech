cmake_minimum_required(VERSION 3.25)
project(sem3lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(sem3lab2 main.cpp
        MyString.cpp
        shape.h
        shape.cpp
        MyVector.cpp
        MyVector.h
        Rect.cpp
        Rect.h
        Circle.cpp
        Circle.h
        )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")