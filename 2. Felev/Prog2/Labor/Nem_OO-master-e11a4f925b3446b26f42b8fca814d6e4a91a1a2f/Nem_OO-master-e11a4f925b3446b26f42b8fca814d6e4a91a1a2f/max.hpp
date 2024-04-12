#ifndef _MAX_HPP
#define _MAX_HPP
/**
 * file max.hpp
 * (UTF-8 kodolasu fajl. Allitsa at a megjenetes kodolasat,
 *  ha a tovabbi kommentek nem olvashatok helyesen!)
 *
 *
 * A C++ nem OO bõvítéseinek gyakorlásához.
 *
 *
 * FELADATOK:
 *  2. Valósítson meg EBBEN a fájlban, a Sajat névtéren belül egy olyan sablont, ami
 *     alaptípusok esetén a paraméterként kapott érték közül a nagyobbat adja.
 *  3. Specializálja a sablont a nem_oo.h állományban deklarált Komplex típusra
 *     úgy hogy a nagyobb abszolút értékû Komplex számot adja vissza!
 *
 * Ügyeljen a helyes névtér használatra!
 *   Tipp: Használja a scope operátort, vagy nyisson névteret!
 */

 namespace sajat
{
template<typename T>
    T max(T a, T b)
    {
        return a > b ? a : b;
    }
    inline sajat::Komplex max(sajat::Komplex a, sajat::Komplex b)
    {
        return sajat::absKomplex(a) > sajat::absKomplex(b) ? a : b;
    }
}


#include "nem_oo.h"





#endif // _MAX_HPP

