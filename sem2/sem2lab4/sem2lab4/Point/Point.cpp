#include "Point.hpp"

//конструкторы
Point::Point(){
    x = 0;
    y = 0;
}

Point::Point(int X, int Y){
    setAll(X, Y);
}

//геттеры
int Point::getX() const{
    return x;
}

int Point::getY() const{
    return y;
}

//сеттеры
void Point::setX(int X){
    x = X;
}

void Point::setY(int Y){
    y = Y;
}

void Point::setAll(int X, int Y){
    setX(X);
    setY(Y);
}

//2b
Point& Point::operator +=(Point const & a){
    x+=a.x;
    y+=a.y;
    
    return *this;
}

Point& Point::operator +=(int const a){
    x+=a;
    y+=a;
    
    return *this;
}

//2c
Point Point::operator +(Point const & a) const{
    return Point{x+a.x,y+a.y};
}

Point Point::operator + (int const & a) const{
    return Point{x+a,y+a};
}

Point Point::operator -() const{
    return Point{-x,-y};
}

Point Point::operator +() const{
    return Point{x,y};
}

//2b
Point& operator -=(Point & a, int b){
    a.setX(a.getX()-b);
    a.setY(a.getY()-b);
    
    return a;
}

Point& operator -=(Point & a, Point & b){
    a.setX(a.getX()-b.getX());
    a.setY(a.getY()-b.getY());
    
    return a;
}

//2c
Point operator -(Point & a, Point & b){
    return Point{a.getX()-b.getX(),a.getY()-b.getY()};
}

Point operator -(Point & a, const int & b){
    return Point{a.getX()-b,a.getY()-b};
}

Point operator -(const int & b, Point & a){
    return a-b;
}

Point operator +(const int & a, Point & b){
    return Point{b.getX()+a,b.getY()+a};
}

bool Point::operator ==(Point const & other) const{
    return (x == other.x && y == other.y);
}

bool Point::operator !=(Point const & other) const{
    return !(x == other.x && y == other.y);
}

std::ostream& operator<<(std::ostream& stream, Point const& point){
    stream << point.x << " "<< point.y;
    return stream;
}

std::istream& operator>>(std::istream& stream, Point& point){
    stream >> point.x >> point.y;
    return stream;
}
