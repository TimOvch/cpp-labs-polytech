#include <iostream>
#include "shape.hpp"
#include "Rect.hpp"
#include "Debug.h"

const char* coloursStr[] = {"red","green","blue","yellow","orange","black","white","pink","purple"};

//Конструкторы
Shape::Shape(){
    color = numOfCol;
    square = 0;
    perimeter = 0;
}

Shape::Shape(colours iColour)
  //  : color(iColour)
{
    color = iColour;
    square = 0;
    perimeter = 0;
}

Shape::Shape(Rect& rectan){
    color = rectan.getColor();
    square = rectan.getSquare();
    perimeter = rectan.getPerimeter();
}

//Деструкторы
Shape::~Shape(){
#ifdef DebugVersion
    std::cout << "\nNow I am in Shape's destructor!\n";
#endif
}

// Геттер и сеттер для цвета
colours Shape::getColor(){
    return color;
}

const char* Shape::getColorStr(){
    return coloursStr[color];
}

void Shape::setColor(colours inColour){
    color = inColour;
}

// Геттеры
double Shape::getSquare(){
    return square;
}

double Shape::getPerimeter(){
    return perimeter;
}

//сеттеры
void Shape::setPerimeter(double inPerimeter){
    perimeter = inPerimeter;
}

void Shape::setSquare(double inSquare){
    square = inSquare;
}

//Метод где я
void Shape::WhereAmI1(){
    std::cout << "\nNow I am in class Shape\n";
};

void Shape::WhereAmI(){
    std::cout << "\nNow I am in class Shape\n";
}
