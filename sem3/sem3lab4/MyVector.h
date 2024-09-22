#pragma once
#include "shape.h"
#include "iostream"

class Vector : public Shape{
private:
	double x, y;	// Координаты вектора на плоскости
public:
	//========== Три конструктора
	Vector (double c1, double c2);
    Vector(const Vector &v);
	Vector();							// Default
	
	//====== Переопределение операций =====//
	Vector& operator= (const Vector& v);	// Присвоение
    Vector operator+ (const Vector& v) const;

    bool operator==(const Vector &rhs) const;
    bool operator!=(const Vector &rhs) const;
    bool operator<(const Vector &rhs) const;
    bool operator>(const Vector &rhs) const;
    bool operator<=(const Vector &rhs) const;
    bool operator>=(const Vector &rhs) const;

    Vector operator*(const double &num) const;
    double operator*(const Vector &vec) const;

    double getX() const;
    double  getY() const;

    double operator!() const;

	void Out() override;
    double Area() override;
    void Move(Vector &v) override;

    friend Vector operator*(const double & num,const Vector &vec);

    friend class Rect;

    friend std::ostream& operator << (std::ostream &os, const Vector &vec);
};

