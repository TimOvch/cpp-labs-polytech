//
// Created by Тимофей Овчинников on 9/6/24.
//

#include "Rect.h"

void swap(double&fr, double&sc){
    double temp = fr;
    fr=sc;
    sc=temp;
}

Rect::Rect()
:ptLT(),ptRB(),Shape()
{}

Rect::Rect(const double &left, const double &top, const double &right, const double &bottom)
:ptLT(left,top), ptRB(right,bottom)
{
    Check();
}

void Rect::Inflate(const double &coef) {
    Inflate(coef,coef,coef,coef);
}

void Rect::Inflate(const double &width, const double &height) {
    Inflate(width,width,height,height);
}

void Rect::Inflate(const double &left, const double &rigth, const double &top, const double &bottom) {
    ptRB.x+=rigth;
    ptRB.y-=bottom;
    ptLT.x-=left;
    ptLT.y+=top;
    Check();
}

void Rect::Check() {
    if (ptLT.x > ptRB.x){
        swap(ptLT.x, ptRB.x);
    }
    if(ptRB.y > ptLT.y){
        swap(ptRB.y, ptLT.y);
    }
}

void Rect::Out() {
    std::cout <<'\n' << "Rect (T: " <<ptLT.y << ", L: " << ptLT.x << ", B: " << ptRB.y << ", R: " << ptRB.x <<")";
}

Rect::Rect(const Vector& ptLT1, const Vector& ptRB1)
:ptLT(ptLT1),ptRB(ptRB1), Shape()
{
    Check();
}

double Rect::Area() {
    return (ptRB.x - ptLT.x) * (ptLT.y - ptRB.y);
}

void Rect::Move(Vector &v) {
    ptRB = ptRB+v;
    ptLT = ptLT +v;
}

