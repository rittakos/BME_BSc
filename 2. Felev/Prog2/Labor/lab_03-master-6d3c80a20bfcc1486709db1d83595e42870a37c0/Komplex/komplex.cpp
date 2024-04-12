/**
 * \file komplex.cpp
 *
 * Komplex osztályt megvalósító függvények definíciója.
 *
 * Folytassa a megvalósítást sorrendben a komplex.h fájlban levő feladatoknak megfelelően!
 *
 */


#include <iostream>         // Valószínű, hogy a kiíráshoz majd kell
#include <iomanip>          // ... és ez is.
#include <cmath>            // az sqrt miatt kell.

#include "komplex.h"        // Ebben van a Komplex osztály, és néhány globális függvény deklarációja


///using namespace std;  // ha nagyon kell, akkor csak itt nyissuk ki a névteret, a headerben soha!

/// Előre elkészített tagfüggvények

/// 0, 1 és 2 paraméteres konstruktor
/// Figyelje meg, hogy a default argumentumokat CSAK a deklarációnál
/// adtuk meg!
Komplex::Komplex(double r, double im) {
    re = r; // ha nincs névütközés, nem kell kiírni a this-t
    this->im = im;
}

///---- Egy példa a konstans tagfüggvényre, ehhez hasonlóan kell
///     elkészíteni a gettereket az 1. feladatban (ELKESZULT=1)
/// Abszolút érték lekérdezése
/// @return - abszolút érték
double Komplex::abs() const 
{ 
	return sqrt(re*re + im*im); 
}

double Komplex::getRe() const
{
	return this->re;
}

double Komplex::getIm() const
{
	return this->im;
}


void Komplex::setRe(double re)
{
	this->re = re;
}

void Komplex::setIm(double im)
{
	this->im = im;
}

#if ELKESZULT >= 3
// 3. feladathoz (ELKESZULT 3)
// összehasonlítás
/// Egyenlőtlenség vizsgálat
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return hamis - ha a képzetes és a valós rész is azonos, egyébként false
bool Komplex::operator==(const Komplex& rhs_k) const
{
	if (this->re == rhs_k.re && this->im == rhs_k.im)
		return true;
	return false;
}

bool Komplex::operator!=(const Komplex& rhs_k) const {  // visszavezetjük az egyenlőség vizsgálatra
    return !(*this == rhs_k);
}
#endif

Komplex Komplex::operator+(const Komplex& rhs_k) const
{
	Komplex result;
	result.re = this->re + rhs_k.re;
	result.im = this->im + rhs_k.im;
	return result;
}

Komplex Komplex::operator+(double rhs_k) const
{
	Komplex result;
	result.re = this->re + rhs_k;
	result.im = this->im;
	return result;
}

Komplex operator+(double lhs_d, const Komplex& rhs_k)
{
	Komplex result;
	result.setRe(rhs_k.getRe() + lhs_d);
	result.setIm(rhs_k.getIm());
	return result;
}

#if ELKESZULT >= 6
// 6. feladathoz (ELKESZULT 6)
// a += művelet viszont módosítja önmagát!
/// Komplex + double
/// @param rhs_d - jobb oldali operandus (double)
/// @return eredeti (bal oldali) objektum ref., amihez hozzáadtuk rhd_d-t
Komplex& Komplex::operator+=(const Komplex& rhs_k)
{
	this->re += rhs_k.re;
	this->im += rhs_k.im;
	return *this;
}

Komplex& Komplex::operator+=(double rhs_d) {
    re += rhs_d;
    return *this;
}
#endif


/*std::ostream& operator<<(std::ostream& os, const Komplex& rhs_k)
{
	double re = rhs_k.getRe();
	double im = rhs_k.getIm();
	if (im >= 0)
		os << re << '+' << im << 'j';
	else 
		os << re << im << 'j';
	return os;
}*/

/*std::istream& operator>>(std::istream& is, Komplex& rhs_k)
{
	double re;
	double im;
	std::string s;
	
	is >> re >> im;

	std::cout << re << '-' << im << std::endl;

	rhs_k.setRe(re);
	rhs_k.setIm(im);
		
	return is;
}*/


/*Komplex Komplex::operator~() const
{
	Komplex result(this->re, -1 * this->im);
	return result;
}*/


/*Komplex Komplex::operator*(const Komplex& rhs_k) const
{
	Komplex result;
	result.re = this->re * rhs_k.re - this->im * rhs_k.im;
	result.im = (this->re * rhs_k.im + this->im * rhs_k.re);
	return result;
}*/


/*Komplex Komplex::operator*(double rhs_d) const
{
	Komplex result;
	result.re = this->re * rhs_d;
	result.im = this->im * rhs_d;
	return result;
}*/


/*Komplex& Komplex::operator*=(const Komplex& rhs_k)
{
	Komplex result;
	result.re = this->re * rhs_k.re - this->im * rhs_k.im;
	result.im = (this->re * rhs_k.im + this->im * rhs_k.re);
	
	this->im = result.im;
	this->re = result.re;
	return *this;
}*/

/*Komplex& Komplex::operator*=(double rhs_d)
{
	this->re *= rhs_d;
	this->im *= rhs_d;
	return *this;
}*/

/*Komplex operator*(double lhs_d, const Komplex& rhs_k)
{
	Komplex result;
	result.setRe(rhs_k.getRe()*lhs_d);
	result.setIm(rhs_k.getIm()*lhs_d);
	return result;
}*/
// ------------------------ Eddig elkészítettük -------------------------
// TODO: A hiányzó tag- és globális függvények itt következnek

