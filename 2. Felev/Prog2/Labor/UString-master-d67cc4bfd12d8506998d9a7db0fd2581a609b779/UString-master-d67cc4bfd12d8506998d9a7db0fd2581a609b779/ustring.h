#ifndef USTRING_H
#define USTRING_H

#include "string5.h"

class UString : public String
{
    bool upper;
public:

    UString() :String(""){}
    UString(char a) :String(a){}
    UString(const char* str) :String(str){}

    UString(UString& other);
    UString& operator= (UString& other);

    UString& operator+(char ch) const;
    UString& operator+(UString ustr) const;

    void UCase(bool u);
    bool UCase();

    std::ostream& operator<<(std::ostream& os);

    operator String();



};

#endif // USTRING_H
