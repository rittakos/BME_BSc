#ifndef MYSET_HPP_INCLUDED
#define MYSET_HPP_INCLUDED

#include "point.h"

#define ELKESZULT 4

    template <typename Type>
    bool equal(const Type& t1, const Type& t2)
    {
        if(t1 == t2)
            return true;
        return false;
    }

    bool equal(const Point& p1, const Point& p2)
    {
        if(p1.getX() == p2.getX())
            return true;
        return false;
    }


template <typename T, std::size_t siz = 10>
class Set
{
    T *data;
    std::size_t count;
public:
    Set()
    {
        data = new T[siz];
        count = 0;
    }

    ~Set()
    {
        delete[] data;
    }

    std::size_t size()
    {
        return count;
    }


    bool isElement(T x)
    {
        for(std::size_t idx = 0; idx < count; ++idx)
            if(equal(data[idx], x))
                return true;
        return false;
    }

    void insert(T x)
    {
        if(isElement(x))
            return;
        if(count == siz)
            throw "Full";
        data[count] = x;
        ++count;
    }

};

#endif // MYSET_HPP_INCLUDED
