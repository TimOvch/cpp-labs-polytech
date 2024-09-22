#ifndef Rect_hpp
#define Rect_hpp

#include "shape.hpp"

class Rect: public Shape{
    
private:
    double vertSide;
    double horSide;

public:
    //Конструкторы
    Rect();
    
    Rect(colours inColour, double inVertSide, double inHorSide);
    
    Rect(Rect & cop);
    
    //Деструкторы
    ~Rect() override;
    
    //сеттеры
    void setHorSide(double inHorSide);
    
    void setVertSide(double inVertSide);
    
    void setAll(double inVertSide, double inHorSide);
    
    //геттеры
    double getHorSide();

    double getVertSide();
    
    //Метод где я
    void WhereAmI1();
    
    void WhereAmI() override;
    
    void InFlate(double) override;
};

#endif
