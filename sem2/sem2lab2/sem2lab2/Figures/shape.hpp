#ifndef shape_hpp
#define shape_hpp
class Rect;

extern const char* coloursStr[];

enum colours{
    red,
    green,
    blue,
    yellow,
    orange,
    black,
    white,
    pink,
    purple,
    numOfCol
};

class Shape{
    
private:
    colours color;
    double square;
    double perimeter;
    
public:
    //Конструкторы
    Shape();
    
    Shape(colours iColour);
    
    Shape(Rect& rectan);
    
    //Деструкторы
    virtual ~Shape();
    
    // Геттер и сеттер для цвета
    colours getColor();
    
    const char* getColorStr();
    
    void setColor(colours inColour);
    
    // Геттеры
    double getSquare();
    
    double getPerimeter();
    
    //Метод где я
    void WhereAmI1();
    
    virtual void WhereAmI();
    
    //Чисто виртуальная функция
    virtual void InFlate(double) = 0;
    
protected:
    //сеттеры
    void setPerimeter(double inPerimeter);
    
    void setSquare(double inSquare);
};

#endif
