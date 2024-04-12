//
// Created by akosr on 15/05/2020.
//

#ifndef LOGO_INTERPRETER_LINE_H
#define LOGO_INTERPRETER_LINE_H

#include <SDL_render.h>
#include "drawable.h"
#include "point.h"

class Line : public Drawable
{
public:
    Line(Point begin, double dir, int len) : begin_{begin}
    {
        color = { 0, 0, 0, 255 };
        end_ = Point(begin_.X() + (int)(cos(dir) * len),
                     begin_.Y() + (int)(sin(dir) * len));
    }

    Line(Point begin, Point end) : begin_{ begin }, end_{end}
    {
        color = { 0, 0, 0, 255 };
    }

    void Draw(SDL_Renderer* renderer) override
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g , color.b, color.a);

        SDL_RenderDrawLine(renderer, begin_.X(), begin_.Y(), end_.X(), end_.Y());
    }

private:

    Point begin_;
    Point end_;

    SDL_Color color;
};

#endif
