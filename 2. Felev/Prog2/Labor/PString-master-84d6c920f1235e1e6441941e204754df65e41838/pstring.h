#ifndef PSTRING_H_INCLUDED
#define PSTRING_H_INCLUDED

#include "string5.h"

class PString :public String
{
public:
    PString():String(""){}
    PString(char ch):String(ch) {}
    PString(const char *p):String(p){}

    void write(std::ostream& os);
    void read(std::istream& is);
};


#endif // PSTRING_H_INCLUDED
