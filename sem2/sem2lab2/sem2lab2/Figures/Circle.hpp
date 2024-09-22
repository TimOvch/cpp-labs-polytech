#ifndef Circle_hpp
#define Circle_hpp

#define _USE_MATH_DEFINES
#include <cmath>
#include "shape.hpp"

class Rect;

class Circle: public Shape{
    
private:
    double radius;
    double diameter;
    
public:
    //Конструкторы
    Circle();
    
    Circle(colours inColour, double inRadius);
    
    Circle(Rect& In);
    
    //Деструкторы
    ~Circle() override;
    
    //Геттер и сеттер радиуса
    double getRadius();
    
    void setRadius(double inRadius);
    
    //Геттер диаметра
    double getDiameter();
    
    //Метод где я
    void WhereAmI1();
    
    void WhereAmI() override;
    
    void InFlate(double) override;
};

#endif
