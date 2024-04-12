#include <iostream>
#include <iomanip>
#include <cmath>

class Heron
{
    double x_;
    double guess_ = 1.0;

    double good_enough()
    {
        return abs(guess_ * guess_ - x_) < 0.001;
    }

    double improve()
    {
        return (guess_ + x_ / guess_) / 2.0;
    }

public:

    double get(double x)
    {
        x_ = x;
        while (!good_enough())
        {
            guess_ = improve();
        }
        return guess_;
    }
};

template <class T>
class Derival
{
    double dx = 0.001;
    //double (*f_) (double);
    T f_;
    
    double derivalt(double x) 
    {
        return (f_(x + dx) - f_(x)) / dx;
    }
public:
    Derival( const T& fu)
    {
        f_ = fu;
    }

    double operator()(double x)
    {
        return derivalt(x);
    }
};

class Parabola
{
    double a_;
    double b_;
    double c_;

    double value(double x)
    {
        return a_ * x * x + b_ * x + c_;
    }
public:
    Parabola(double a = 0, double b = 0, double c = 0) : a_{ a }, b_{ b }, c_{ c }
    {

    }

    double operator()(double x)
    {
        return value(x);
    }
};

void main1()
{
    Heron h;
    std::cout << h.get(2.0);
}

void main2()
{
    Derival<double (*) (double)> my_cos = Derival<double (*) (double)>{ sin };
    for (double f = 0; f < 3.1415; f += 0.1)
        std::cout << std::setw(20) << my_cos(f) - cos(f) << std::endl;

    Parabola p1{ 0.5, 2.3, -5 };  /* 0.5x^2 + 2.3x - 5 */
    Derival<Parabola> p1_der = Derival<Parabola>{ p1 };

    Parabola p2{ 0, 1, 2.3 };     /* x + 2.3, p1 deriváltja */
    for (double f = 0; f < 3.0; f += 0.1)
        std::cout << std::setw(20) << p1_der(f) - p2(f) << std::endl;
}
