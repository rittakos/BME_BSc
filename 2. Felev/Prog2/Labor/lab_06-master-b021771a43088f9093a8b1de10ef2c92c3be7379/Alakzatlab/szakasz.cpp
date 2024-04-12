/**
 *  \file szakasz.cpp
 *  Szakasz oszt�ly tagf�ggv�nyinek megval�s�t�sa
 */
#include "szakasz.h"

/// Szakaszt rajzol� rajzol fv.
void Szakasz::rajzol() {
    std::cout << "Rajzol: " << *this << std::endl;
}

/// Glob�lis << oper�tor
std::ostream& operator<<(std::ostream& os, const Szakasz& sz) {
    return os << "Szakasz " << (Alakzat&)sz << ",pv=" << sz.getpv();
}
