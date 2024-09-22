//
// Created by Тимофей Овчинников on 9/6/24.
//

#ifndef SEM3LAB2_RECT_H
#define SEM3LAB2_RECT_H

#include "MyVector.h"
#include <iostream>

class Rect : public Shape{
private:
    Vector ptLT, ptRB;

    void Check();

public:
    Rect();
    Rect(const Vector& ptLT1, const Vector& ptRB1);
    Rect(const double &left, const double &top, const double &right, const double &bottom);

    void Inflate(const double &coef=1);
    void Inflate(const double &width, const double &height);
    void Inflate(const double &left, const double &rigth , const double &top, const double &bottom);

    [[nodiscard]] double distanceFromOrigin() const;

    void Out() override;
    double Area() override;
    void Move(Vector&v) override;
};


#endif //SEM3LAB2_RECT_H
