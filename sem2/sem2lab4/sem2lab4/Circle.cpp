#include "Circle.hpp"
#include <iostream>

Circle::Circle(Point Center, int Radius)
: center(Center), radius(Radius)
{}

Circle::Circle(Circle&& a){
    center = a.center;
    radius = a.radius;
}

Circle& Circle::operator =(Circle&& a){
    center = a.center;
    radius = a.radius;
    return *this;
}

void Circle::SetCircle(Point Center, int Radius){
    center = Center;
    radius = Radius;
}

Point Circle::GetPoint() const{
    return center;
}

int Circle::GetRadius() const{
    return radius;
}

double Circle::getSquare(){
    return M_PI*(double)radius*(double)radius;
}

bool Circle::operator==(Circle const & other) const{
    return (center == other.center && radius == other.radius);
}

bool Circle::operator!=(Circle const & other) const{
    return !(center == other.center && radius == other.radius);
}

std::ostream& operator<<(std::ostream& stream, Circle const& circle){
    stream << circle.center << " "<< circle.radius;
    return stream;
}

std::istream& operator>>(std::istream& stream, Circle& circle){
    stream >> circle.center >> circle.radius;
    return stream;
}
