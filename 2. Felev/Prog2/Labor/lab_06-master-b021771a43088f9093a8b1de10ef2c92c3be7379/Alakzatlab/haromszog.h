#ifndef HAROMSZOG_H_INCLUDED
#define HAROMSZOG_H_INCLUDED

#include "alakzat.h"

class Haromszog : public Alakzat
{
    Pont p1;
    Pont p2;
public:
    Haromszog(const Pont& p0, Pont P1, Pont P2, Szin sz) :Alakzat(p0, sz)
    {

    }

    void rajzol();
};

#endif // HAROMSZOG_H_INCLUDED
