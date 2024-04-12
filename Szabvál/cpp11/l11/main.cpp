#include <iostream>

int fib(int n)
{
	if (n < 2)
		return n;

	return fib(n - 1) + fib(n - 2);
}


template<int n>
class Fibonacci
{
public:
    static constexpr int value = Fibonacci<n-1>::value + Fibonacci<n-2>::value;
};

template<>
class Fibonacci<0>
{
public:
    static constexpr int value = 0;
};

template <>
class Fibonacci<1>
{
public:
    static constexpr int value = 1;
};


template <int n>
void write()
{
    write<n - 1>();
    std::cout << Fibonacci<n>::value << std::endl;
}

template<>
void write<0>()
{
    std::cout << Fibonacci<0>::value << std::endl;
}

void Feladat1()
{
    //Azert lassul mert ahhoz, hogy megmondjunk egy elemet meg kell hatarozni az elobbi kettot, ez nagy szamnal
    //mar nagyon sok. A 40. elemhez 40-szer kell megmondani az elsot. Ugy gyorsithato hogy a mar kiszamoltakat eltaroljuk
    //for (int idx = 0; idx < 40; ++idx)
        //std::cout << fib(idx) << std::endl;

    //std::cout << Fibonacci<40>::value << std::endl;
    //std::cout << Fibonacci<50>::value << std::endl;
    write<5>();
}


int powint(int base, unsigned exp, int acc)
{
    if(exp == 0)
        return acc;
    else
        return  powint(base, exp-1, acc * base);
}

int powint(int base, unsigned exp)
{
    return powint(base, exp, 1);
}


template <int base, int exp>
class PowInt
{
public:
    static constexpr int value = PowInt<base, exp - 1>::value * base;
};

template <int base>
class PowInt<base, 0>
{
public:
    static constexpr int value = 1;
};



int gcd(int a, int b)
{
    if(b == 0)
        return  a;
    else
        return gcd(b, a % b);
}


template <int a, int b>
class Gcd
{
public:
    //static constexpr int value = Gcd<b, a % b>::value;
};

template <int a>
class Gcd<a, 1>
{
public:
    static constexpr int value = 1;
};

void Feladat2()
{
    std::cout << powint(2, 3) << std::endl;
    std::cout << PowInt<2, 10>::value << std::endl;
    std::cout << gcd(32, 20) << std::endl;
    //std::cout << Gcd<32, 20>::value << std::endl;
}


int greatest(int arr[], int first, int size)
{
    if(first == size - 1)
        return arr[first];
    int max = arr[first];
    int g = greatest(arr, first + 1, size);
    if (g > max)
        max = g;
    return  max;
}

int greatest(int arr[], int size)
{
    return greatest(arr, 0, size);
}


template<int FIRST, int... TAIL>
 class Greatest
{
 public:
    static constexpr int value = FIRST > Greatest<TAIL...>::value ? FIRST : Greatest<TAIL...>::value;
};

template<int LAST>
class Greatest<LAST>
{
public:
    static constexpr int value = LAST;
};

void Feladat3()
{
    int a[] = { 4, 87, 2, 65, 89, 1 };
    std::cout << greatest(a, 6) << std::endl;
    std::cout << Greatest<3, 9, 8, 5>::value << std::endl;
}
int main()
{
	//Feladat1();
	//Feladat2();
	Feladat3();
    return 0;
}