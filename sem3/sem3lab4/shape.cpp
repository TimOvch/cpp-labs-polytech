//
// Created by Тимофей Овчинников on 9/7/24.
//

#include "shape.h"
#include "iostream"


int Shape::count = 0;
Shape* Shape::shapes[1000];

void Shape::PrintCount() {
    std::cout << '\n' << "Shapes count: " << count;
}

Shape::Shape() {
    if(count<1000) {
        shapes[count] = this;
        count++;
    }
}

Shape::~Shape() {
    int numDel = 0;
    for(int i = 0; i < count; i++){
        if(shapes[i] == this){
            numDel = i;
            break;
        }
    }

    for(int i = numDel; i < count-1; i++){
        shapes[i] = shapes[i+1];
    }

    count--;
}

int Shape::GetCount() {
    return count;
}

