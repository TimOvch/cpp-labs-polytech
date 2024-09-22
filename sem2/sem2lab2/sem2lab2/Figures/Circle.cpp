#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "Circle.hpp"
#include "Rect.hpp"
#include "Debug.h"

//Конструкторы
Circle::Circle(){
    radius = 0;
    diameter = 0;
    setColor(numOfCol);
}

Circle::Circle(colours inColour, double inRadius)
    : Shape(inColour),radius(inRadius), diameter(inRadius*2)
{
    setPerimeter(2*M_PI*radius);
    setSquare(M_PI*radius*radius);
}

Circle::Circle(Rect& In)
: Shape(In)
{
    radius = sqrt(getSquare()/M_PI);
    diameter = 2* radius;
    setPerimeter(2*M_PI*radius);
}

//Деструкторы
Circle::~Circle(){
#ifdef DebugVersion
    std::cout << "\nNow I am in Circle's destructor!\n";
#endif
}

//Геттер и сеттер радиуса
double Circle::getRadius(){
    return  radius;
}

void Circle::setRadius(double inRadius){
    radius = inRadius;
    diameter = radius*2;
    setPerimeter(2*M_PI*radius);
    setSquare(M_PI*radius*radius);
}

//Геттер диаметра
double Circle::getDiameter(){
    return  diameter;
}

//Метод где я
void Circle::WhereAmI1(){
    std::cout << "\nNow I am in class Circle\n";
};

void Circle::WhereAmI(){
    std::cout << "\nNow I am in class Circle\n";
}

void Circle::InFlate(double Delta){
    radius+=Delta;
    diameter = radius*2;
    setPerimeter(2*M_PI*radius);
    setSquare(M_PI*radius*radius);
}
