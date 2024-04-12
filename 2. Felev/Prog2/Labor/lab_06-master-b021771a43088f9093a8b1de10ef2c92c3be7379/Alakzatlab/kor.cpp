/**
 *  \file kor.cpp
 *  Kor oszt�ly tagf�ggv�nyinek megval�s�t�sa
 */
#include "kor.h"

/// K�rt rajzol� rajzol fv.
void Kor::rajzol() {
    std::cout << "Rajzol: " << *this << std::endl;
}

/// Glob�lis << oper�tor
std::ostream& operator<<(std::ostream& os, const Kor& k) {
    return os << "Kor " << (Alakzat&)k << ",r=" << k.getr();
}
