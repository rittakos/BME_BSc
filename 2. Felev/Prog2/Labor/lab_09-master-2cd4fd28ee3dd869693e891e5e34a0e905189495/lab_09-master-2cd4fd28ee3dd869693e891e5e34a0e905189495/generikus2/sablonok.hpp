#ifndef SABLONOK_HPP_INCLUDED
#define SABLONOK_HPP_INCLUDED

#define ELKESZULT 7

#include <string>
#include <iostream>

template<typename Iter>
std::ostream& printEach(Iter first, Iter last, std::ostream& os = std::cout, std::string gap = ", ")
{
    if(first != 0)
        os << *first;
    else
        throw "Empty";
    ++first;

    while(first != last)
    {
        os << gap << *first;
        ++first;
    }
    os << std::endl;
    return os;
}

template <typename Iter>
int szamol_ha_negativ(Iter first, Iter last)
{
    int count = 0;
    while(first != last)
    {
        if(*first < 0)
            ++count;
        ++first;
    }
    return count;
}

template<typename T>
class nagyobb_mint
{
    T data;
public:
    nagyobb_mint(T t) :data(t){}
    bool operator()(T other)
    {
        if(other > this->data)
            return true;
        return false;
    }
};

template<typename Iter, typename P>
int szamol_ha(Iter first, Iter last, P p)
{
    int count = 0;
    while(first != last)
    {
        if(p(*first))
            ++count;
        ++first;
    }
    return count;
}
#endif // SABLONOK_HPP_INCLUDED
