//
//  Circle.hpp
//  sem2lab4
//
//  Created by Тимофей Овчинников on 29.02.2024.
//

#ifndef Circle_hpp
#define Circle_hpp

#include <stdio.h>
#include "Point.hpp"

class Circle{
private:
    Point center;
    int radius;
public:
    Circle() = default;
    Circle(Circle const&other) = default;
    Circle(Point Center, int Radius);
    Circle(Circle&& a);
    ~Circle() = default;
    Circle& operator =(Circle const &a) = default;
    Circle& operator =(Circle&& a);
    void SetCircle(Point Center, int Radius);
    Point GetPoint() const;
    int GetRadius() const;
    double getSquare();
    bool operator==(Circle const & other) const;
    bool operator!=(Circle const & other) const;
    
    friend std::ostream& operator<<(std::ostream& stream, Circle const& circle);
    friend std::istream& operator>>(std::istream& stream, Circle& circle);
};

#endif /* Circle_hpp */
