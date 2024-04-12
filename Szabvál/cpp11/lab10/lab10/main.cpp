#include <iostream>
#include <ctype.h>

struct CharTraits 
{
    using Type = char;

    static bool equal(Type c1, Type c2) { return c1 == c2; }
};

struct CharTraits2
{
    using Type = char;

    static bool equal(char c1, char c2) { return tolower(c1) == tolower(c2); }
};



template<typename charTraits>
class String 
{
private:
    CharTraits::Type data[100];

public:
    String() {
        data[0] = 0;
    }

    String(char const* init) 
    {
        for (int idx = 0; idx < strlen(init); ++idx)
        {
            data[idx] = init[idx];
        }
        data[strlen(init)] = 0;
    }

    bool operator==(String const& rhs) {
        String const& lhs = *this;
        size_t i;
        for (i = 0; lhs.data[i] != 0 && rhs.data[i] != 0; ++i)
            if (!charTraits::equal(lhs.data[i], rhs.data[i]))
                return false;
        return charTraits::equal(lhs.data[i], '\0') && charTraits::equal(rhs.data[i], '\0');
    }
};



struct Nothing
{
    template<typename T>
    static int index(T* v, int size, int idx) { return idx; }
};

struct Exception
{
    template<typename T>
    static int index(T* v, int size, int idx)
    { 
        throw std::runtime_error("IndexOutOfRange"); 
    }
};

struct Repeat
{
    template<typename T>
    static int index(T* v, int size, int idx)
    {
        return idx - size;
    }
};

struct Reallocate
{
    template<typename T>
    static int index(T* v, int size, int idx)
    {
        T* newData = new T[idx + 1];
        for (int i = 0; i < size; ++i)
            newData[i] = v[i];
        delete[] v;
        v = newData;
    }
};

template <typename T, class IndexStrategy = Nothing>
class Vector 
{
private:
    size_t size;
    T* data;

public:
    explicit Vector(size_t size)
        : size{ size }
        , data{ new T[size] } {
    }
    Vector(Vector const&) = delete; /* lusta */
    Vector& operator=(Vector const&) = delete; /* lusta */
    ~Vector() {
        delete[] data;
    }

    T& operator[](size_t idx) 
    {
        if (idx >= size)
            idx = IndexStrategy::index(*this, size, idx);
        return data[idx];
    }
};




class Base 
{

};


class Derived : public Base 
{

};



template<typename BASE, typename DERIVED>
struct IsDerived
{
    static constexpr bool value = false;
};

template<typename BASE>
struct IsDerived<BASE, void*>
{
    static constexpr bool value = false;
};



template <typename BASE>
struct IsDerived<BASE, BASE*>
{
    static constexpr bool value = true;
};

int main() {
    String<CharTraits2> s1 = "hello";
    String<CharTraits2> s2 = "HeLLo";
    std::cout << (s1 == s2) << std::endl;

    Vector<int> v1(10);

    std::cout << IsDerived<Base, Derived>::value << std::endl;    /* 1 */
    std::cout << IsDerived<Base, std::ostream>::value << std::endl;    /* 0 */
}