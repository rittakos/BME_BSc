//
// Created by akosr on 04/05/2020.
//

#ifndef LOGO_INTERPRETER_POINT_H
#define LOGO_INTERPRETER_POINT_H

#include <SDL.h>

class Point : public Drawable
{
public:
    Point(int x = 0, int y = 0): x_{x}, y_{y} {}

    void Draw(SDL_Renderer* renderer) override
    {
        SDL_RenderDrawPoint(renderer, x_, y_);
    }

    double distance(const Point& otherPoint)
    {
        double dx = (double)(x_ - otherPoint.X());
        double dy = (double)(y_ - otherPoint.Y());

        return sqrt(dx * dx + dy * dy);
    }

    int X() const{return x_;}
    int Y() const{return y_;}
private:
    int x_;
    int y_;
};
#endif
