//
// Created by Тимофей Овчинников on 9/8/24.
//

#include "MyStack.h"
//#include "cmath"
//#include "stdexcept"
//
//template<class T> MyStack<T>::MyStack() {
//    size = 0;
//    capacity = 2;
//
//    arr = new T[capacity];
//}
//
//template<class T> MyStack<T>::~MyStack() {
//    delete []arr;
//}
//
//template<class T> MyStack<T>::MyStack(const MyStack &stk) {
//    size = stk.size;
//    capacity = stk.capacity;
//
//    arr = new T[stk.capacity];
//
//    for(int i = 0; i < size; i++){
//        arr[i] = stk.arr[i];
//    }
//}
//
//template<class T> void MyStack<T>::resize(const int &ncap) {
//    T* copy = new T[ncap];
//
//    for(int i = 0; i < size; i++){
//        copy[i] = arr[i];
//    }
//
//    delete[] arr;
//    arr = copy;
//    capacity = ncap;
//}
//
//template<class T> void MyStack<T>::Push(const T &item) {
//    if(size == capacity){
//        if(capacity > 100000){
//            throw StackOverflow();
//        }
//        resize(2*capacity);
//    }
//    arr[size++] = item;
//}
//
//template<class T> T MyStack<T>::Pop() {
//    if(size == 0){
//        throw StackUnderflow();
//    }
//
//    T item = arr[--size];
//    if((size > 0) && (size == ceil(capacity/4.))){
//        resize(capacity/2);
//    }
//
//    return item;
//}
//
//template<class T> size_t MyStack<T>::Capacity() const {
//    return capacity;
//}
//
//template<class T> size_t MyStack<T>::GetSize() const {
//    return size;
//}
//template<class T> T MyStack<T>::operator[](size_t i) {
//    if (i < size){
//        return arr[i];
//    }
//    throw std::out_of_range("Index out of range");
//}