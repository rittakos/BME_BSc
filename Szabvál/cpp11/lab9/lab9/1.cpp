#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std::placeholders;

double heron(double x) 
{
    auto good_enough = [x](double guess) {return abs(guess * guess - x) < 0.001; };

    auto improve = [x](double guess) {return (guess + x / guess) / 2.0; };

    double guess = 1.0;
    while (!good_enough(guess))
        guess = improve(guess);
    return guess;
}

double doubler(double d)
{
    return 2 * d;
}

void Feladat1()
{
    std::vector<double> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    double m = 0;
    std::cin >> m;

    //auto multiple = std::bind(std::multiplies<double>{}, _1, 2.0);
    auto multiple = std::bind(std::multiplies<double>{}, _1, m);

    //std::transform(v.begin(), v.end(), v.begin(), 
     //   [&](double d) { return m * d; });

    std::transform(v.begin(), v.end(), v.begin(), multiple);

    for (auto i : v)
        std::cout << i << std::endl;
}


class Page {
public:
    Page(int w, int h) {
        w_ = w;
        h_ = h;
        page_ = new char* [h_];
        for (int y = 0; y < h_; ++y)
            page_[y] = new char[w_];
        clear();
    }

    /* destruktor, másoló konstruktor, op= helye */

    void clear() {
        for (int y = 0; y < h_; ++y)
            for (int x = 0; x < w_; ++x)
                page_[y][x] = ' ';
    }

    void print() const {
        for (int y = 0; y < h_; ++y) {
            for (int x = 0; x < w_; ++x)
                putchar(page_[y][x]);
            putchar('\n');
        }
    }

    void setchar(int x, int y, char c) {
        if (x >= 0 && x < w_ && y >= 0 && y < h_)
            page_[y][x] = c;
    }

    int get_width() const {
        return w_;
    }
    int get_height() const {
        return h_;
    }

private:
    int w_, h_;
    char** page_;
};



//void plot(Page& page, char c, double (*f)(double)) 

//template<class F>
//void plot(Page& page, char c, F f)

void plot(Page& page, char c, std::function<double(double)> f)
{
    for (int x = 0; x < page.get_width(); ++x) {
        double fx = (x - page.get_width() / 2) / 4.0;
        double fy = f(fx);
        int y = (fy * 4.0) * -1 + page.get_height() / 2;
        page.setchar(x, y, c);
    }
}

void Feladat3()
{
    Page p(40, 10);
    plot(p, '.', [](double x) {return sin(x); });
    p.print();
}

int main1()
{
    //Feladat1();
    //std::cout << heron(2) << std::endl;
    //Feladat3();

    return 0;
}