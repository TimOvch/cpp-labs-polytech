#include "stdafx.h"
#include "MyVector.h"
#include "float.h"

double Vector::getX() const{
    return x;
}

double  Vector::getY() const{
   return y;
}

std::ostream& operator << (std::ostream &os, const Vector &vec)
{
    return os << "(x:" << vec.x << ", y:" << vec.y << ")";
}

Vector::Vector (double c1, double c2):
Shape()
{
	x=c1;   y=c2;
}

Vector::Vector ():
Shape()
{
	x = y = 0.;
}

void Vector::Out()
{
	cout << "\nVector:  x = " << x << ",  y = " << y;
}

Vector::Vector(const Vector &v):
Shape()
{
    // *this = v;

    x = v.x;
    y = v.y;
}

//====== Переопределение операций =====//
Vector& Vector::operator= (const Vector& v)	// Присвоение
{
	if (this == &v)
		return *this;
	x = v.x;
	y = v.y;
	return *this;
}

Vector Vector::operator+(const Vector &v) const {
    Vector res(x+v.x, y+v.y);
    return res;
}

double Vector::operator!() const {
    return pow(x*x + y*y, 0.5);
}

bool Vector::operator<(const Vector &rhs) const {
    return !(*this) < !rhs;
}

bool Vector::operator>(const Vector &rhs) const {
    return rhs < *this;
}

bool Vector::operator<=(const Vector &rhs) const {
    return !(rhs < *this);
}

bool Vector::operator>=(const Vector &rhs) const {
    return !(*this < rhs);
}

bool Vector::operator==(const Vector &rhs) const {
    return fabs(x - rhs.x) < DBL_EPSILON &&
            fabs(y - rhs.y) < DBL_EPSILON;
}

bool Vector::operator!=(const Vector &rhs) const {
    return !(rhs == *this);
}

Vector Vector::operator*(const double &num) const {
    return Vector(x*num, y*num);
}

Vector operator*(const double & num,const Vector &vec){
    return Vector(vec.x*num, vec.y*num);
}

double Vector::operator*(const Vector &vec) const {
    return x*vec.x + y*vec.y;
}

double Vector::Area() {
    return 0;
}

void Vector::Move(Vector &v) {
    x+=v.x;
    y+=v.y;
}
