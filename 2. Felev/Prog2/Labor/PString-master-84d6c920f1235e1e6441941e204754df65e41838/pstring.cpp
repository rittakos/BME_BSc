#include "pstring.h"

void write(std::ostream& os)
{
    os << this->size() << std::endl();
    os << this->c_str() << std::endl();
}
void read(std::istream& is)
{
    size_t len = 0;
    char* str;
    is >> len;
    is >> str;
    *this =
}
