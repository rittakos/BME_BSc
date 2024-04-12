/*
 * \file point.h
 *
 */


#ifndef POINT_H
#define POINT_H

/// Point osztály
/// Szándékosan egyszerû (buta)
class Point {
    int x;
    int y;
public:
    Point(int x = 0, int  y = 0) :x(x), y(y) { }
    int getX() const { return x; }
    int getY() const { return y; }

    bool operator==(const Point& other) const
    {
        if(this->x == other.x && this->y == other.y)
            return true;
        return false;
    }
};

#endif // POINT_H
