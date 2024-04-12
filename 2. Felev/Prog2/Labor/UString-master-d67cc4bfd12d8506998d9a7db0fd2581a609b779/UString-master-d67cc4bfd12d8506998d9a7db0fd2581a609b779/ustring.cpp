#include "ustring.h"

    void UString::UCase(bool u)
    {
        this->upper = u;
    }

    bool UString::UCase()
    {
        return this->upper;
    }

    std::ostream& UString::operator<<(std::ostream& os)
    {
        if(this->UCase())
            os << std::uppercase << this->c_str();
        else
            os << this->c_str();
        return os;
    }

    UString::operator String()
    {
        String str (this->c_str());
        return str;
    }

    UString::UString(UString& other)
    {
        this = other;
        this->upper = other.upper;
    }

    UString::UString& operator= (UString& other)
    {
        if (this != &other)
        {
            this = other;
            this->upper = other.upper;
        }
        return *this;
    }

    UString& UString::operator+(char ch) const
    {

    }

    UString& UString::operator+(UString str) const
    {
        UString temp;
        temp =

        return temp;
    }
