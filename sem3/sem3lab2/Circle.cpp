//
// Created by Тимофей Овчинников on 9/7/24.
//

#include "Circle.h"
#include "iostream"
#include "cmath"

Circle::Circle():
Shape(), ptCntr(), R()
{}

Circle::Circle(const Vector &vec,const double& r):
Shape(), ptCntr(vec), R(r)
{}

void Circle::Move(Vector &v) {
    ptCntr = v + ptCntr;
}

void Circle::Out() {
    std::cout <<'\n' << "Circle (R: " << R << ")";
    ptCntr.Out();
}

double Circle::Area() {
    return M_PI*R*R;
}
