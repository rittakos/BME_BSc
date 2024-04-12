/**
 *  \file szakasz.h
 *  Szakasz osztály deklarációja
 */
#ifndef SZAKASZ_H
#define SZAKASZ_H

#include "alakzat.h"

/// szakasz
class Szakasz : public Alakzat {
    Pont pv;    /// szakasz végpontja a P0-hoz képest
public:
    /// konstruktor 2 pontból
    /// @param p0 - kezdőpont
    /// @param pv - végpont
    /// @param sz - szín és átlátszóság
    Szakasz(const Pont& p0, const Pont& pv, Szin sz)
                     : Alakzat(p0, sz), pv(pv-p0) { }

    /// konstruktor 1 pontból és 2 hosszból
    /// @param p0 - kezdõpont
    /// @param xl - x irányú hossz
    /// @param yl - y irányú hossz
    /// @param sz - szín és átlátszóság
    Szakasz(const Pont& p0, int xl, int yl, Szin sz)
                     : Alakzat(p0, sz), pv(getp0()+Pont(xl, yl)) { }

    /// Szakasz végpontjénak lekérdezése
    /// @return szakasz végpontjaa
    Pont getpv() const { return getp0()+pv; }

    /// szakaszt rajzol
    void rajzol();	    // átdefiniáljuk a virt. fv-t.
};

/// Globális << operátor
/// @param os - ostream
/// @param sz - szakasz
/// @return os - ostream
std::ostream& operator<<(std::ostream& os, const Szakasz& sz);

#endif // SZAKASZ_H
