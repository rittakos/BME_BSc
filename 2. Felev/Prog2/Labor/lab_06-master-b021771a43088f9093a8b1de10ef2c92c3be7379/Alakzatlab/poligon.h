#ifndef POLIGON_H_INCLUDED
#define POLIGON_H_INCLUDED

#include "alakzat.h"

class Poligon :public Alakzat
{
	int size;
	Pont* points
public:
	Poligon(const Pont& p0, Szin color, int n, Pont* otherPoints) :Alakzat(p0, color)
	{
		size = n;

		points = new Pont[n];
		points[0] = p0;
		for(int idx = 1; idx < n; ++idx)
		{
			points[idx] = otherPoints[idx - 1];
		}
	}

	Pont operator[](int idx)
	{
		return points[idx];
	}

	Pont operator[](int idx) const
	{
		return points[idx];
	}

    ~Poligon()
    {
        delete points;
    }

	void AddPoint(Pont p)
	{
        ++size;

	}

};

#endif // POLIGON_H_INCLUDED
