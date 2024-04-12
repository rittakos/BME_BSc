/**
 *  \file pont.cpp
 *  Pont osztály tagfüggvényeinek megvalósítása
 */

#include "pont.h"

/// += operator
Pont& Pont::operator+=(const Pont& rhs_p) {
    x += rhs_p.x;
    y += rhs_p.y;
    return *this;
}

/// + operator
Pont Pont::operator+(const Pont& rhs_p) const {
    return Pont(rhs_p.x+x, rhs_p.y+y);
}

/// - operator
Pont Pont::operator-(const Pont& rhs_p) const {
    return Pont(x-rhs_p.x, y-rhs_p.y);
}

Pont& Pont::operator=(Pont& other)
{
    this->x = other.x;
    this->y = other.y;
    return *this;
}

/// Globális << operátor
std::ostream& operator<<(std::ostream& os, const Pont& p) {
    return os << "(" << p.x <<"," << p.y << ")";
}
