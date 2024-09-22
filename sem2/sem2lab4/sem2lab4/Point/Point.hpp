//
//  Point.hpp
//  sem2lab3
//
//  Created by Тимофей Овчинников on 19.02.2024.
//

#ifndef Point_hpp
#define Point_hpp
#include <iostream>
#include <fstream>

class Point{
    
private:
    int x;
    int y;
    
public:
    //конструкторы
    Point();
    
    Point(int X, int Y);
    
    //геттеры
    int getX() const;
    
    int getY() const;
    
    //сеттеры
    void setX(int X);
    
    void setY(int Y);
    
    void setAll(int X, int Y);
    
    //2b
    Point& operator +=(Point const & a);
    
    Point& operator +=(int const a);
    
    //2c
    Point operator +(Point const & a) const;
    
    Point operator + (int const & a) const;
    
    Point operator -() const;
    
    Point operator +() const;
    
    bool operator ==(Point const & other) const;
    bool operator !=(Point const & other) const;
    
    friend std::ostream& operator<<(std::ostream& stream, Point const& point);
    friend std::istream& operator>>(std::istream& stream, Point& point);
};

Point& operator -=(Point & a, int b);
Point& operator -=(Point & a, Point & b);
Point operator -(Point & a, Point & b) ;
Point operator -(Point & a, const int & b);
Point operator +(const int & a, Point & b);

#endif /* Point_hpp */
