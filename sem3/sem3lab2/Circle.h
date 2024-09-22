//
// Created by Тимофей Овчинников on 9/7/24.
//

#ifndef SEM3LAB2_CIRCLE_H
#define SEM3LAB2_CIRCLE_H
#include "MyVector.h"

class Circle : public Shape {
    Vector ptCntr;
    double R;
public:
    Circle();
    Circle(const Vector& vec, const double& r);

    void Move(Vector& v) override;
    void Out() override;
    double Area() override;

};


#endif //SEM3LAB2_CIRCLE_H
