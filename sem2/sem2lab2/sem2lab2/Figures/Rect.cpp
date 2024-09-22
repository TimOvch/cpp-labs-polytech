#include <iostream>
#include "Rect.hpp"
#include "Debug.h"

//Конструкторы
Rect::Rect() : Shape()
{
    vertSide = 0;
    horSide = 0;
}

    Rect::Rect(colours inColour, double inVertSide, double inHorSide)
   : Shape(inColour),vertSide(inVertSide), horSide(inHorSide)
{
    setSquare(vertSide*horSide);
    setPerimeter(2*(vertSide+horSide));
}

Rect::Rect(Rect & cop)
    : Shape(cop)
{
    vertSide = cop.getVertSide();
    horSide = cop.getHorSide();
}

//Деструктор
Rect::~Rect(){
#ifdef DebugVersion
    std::cout << "\nNow I am in Rect's destructor!\n";
#endif
}

//Сеттеры
void Rect::setHorSide(double inHorSide){
    horSide = inHorSide;
    setSquare(vertSide*horSide);
    setPerimeter(2*(vertSide+horSide));
}

void Rect::setVertSide(double inVertSide){
    vertSide = inVertSide;
    setSquare(vertSide*horSide);
    setPerimeter(2*(vertSide+horSide));
}

void Rect::setAll(double inVertSide, double inHorSide){
    vertSide = inVertSide;
    horSide = inHorSide;
    setSquare(vertSide*horSide);
    setPerimeter(2*(vertSide+horSide));
}

//Геттеры
double Rect::getHorSide(){
    return horSide;
}

double Rect::getVertSide(){
    return vertSide;
}

//Метод где я
void Rect::WhereAmI1(){
    std::cout << "\nNow I am in class Rect\n";
};

void Rect::WhereAmI(){
    std::cout << "\nNow I am in class Rect\n";
}

void Rect::InFlate(double Delta){
    horSide+= Delta;
    vertSide+= Delta;
    setPerimeter(2*(vertSide+horSide));
    setSquare(vertSide*horSide);
}
