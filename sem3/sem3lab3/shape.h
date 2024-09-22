//
// Created by Тимофей Овчинников on 9/7/24.
//

#ifndef SEM3LAB2_SHAPE_H
#define SEM3LAB2_SHAPE_H

class Vector;

class Shape{
    static int count;

public:
    static Shape* shapes[1000];
    Shape();
    virtual ~Shape();

    static int GetCount();
    static void PrintCount();
    virtual void Move(Vector &v) = 0;
    virtual void Out() = 0;
    virtual double Area() = 0;
};

#endif //SEM3LAB2_SHAPE_H
