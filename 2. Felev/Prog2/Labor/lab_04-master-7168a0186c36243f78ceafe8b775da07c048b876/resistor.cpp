/**
 * \file resistor.cpp
 *   (UTF-8 kodolasu fajl. Allitsa at a megjenetes kodolasat,
 *    ha a tovabbi kommentek nem olvashatok helyesen!)
 *
 * Ohmikus ellenállást modellező osztály megvalósítása
 */

/**
 * Itt kell megvalósítani a resistor.h-ban deklarált nem inline függvényeket.
 * A Jportára ezt a fájlt kell feltölteni.
 */

#include "resistor.h"
#include "iostream"
#include "gtest_lite.h"

Resistor Resistor::operator+(const Resistor& r) const
{
    Resistor result(r.getR() + this->getR());
    return result;
}

double Resistor::defR = 128;
void Resistor::setDef(double r)
{
    defR = r;
}

Resistor::Resistor()
{
    Pr("ctor0");
    this->R = defR;
}

Resistor::Resistor(double r)
{
    Pr("ctor1");
    this->R = r;
}

Resistor::Resistor(const Resistor& rhs)
{
    Pr("copy");
    *this = rhs;
}

Resistor::~Resistor()
{
    Pr("dtor");
}

Resistor Resistor::operator%(const Resistor& r) const
{
    Resistor result(1/(1/r.getR() + 1/this->getR()));
    return result;
}


Resistor operator*(int n, const Resistor& r)
{
    if(n <= 0)
        throw "Z8WK8D";
    Resistor result(r.getR()*n);
    return result;
}

Resistor& Resistor::operator=(const Resistor& rhs)
{
    Pr("assign");
    R = rhs.getR();
    return *this;
}

double Resistor::getI(double u) const
{
    double i = u / this->R;
    return i;
}

double Resistor::getU(double i) const
{
    double u = i * this->R;
    return u;
}

bool Resistor::operator==(const Resistor& r) const
{
    return gtest_lite::almostEQ(this->R, r.getR());
}

std::ostream& operator<<(std::ostream& os, const Resistor& rhs)
{
    os << rhs.getR();
    return os;
}
