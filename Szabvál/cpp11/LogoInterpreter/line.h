//
// Created by akosr on 15/05/2020.
//

#ifndef LOGO_INTERPRETER_LINE_H
#define LOGO_INTERPRETER_LINE_H

#include <SDL2/SDL_render.h>
#include "drawable.h"
#include <math.h>

class Line : public Drawable
{
public:
    Line(int x, int y, float dir, int len) : x_{x}, y_{y}, d_{dir}, l_{len}
    {
        color = {0, 0, 0, 255};
    }

    void Draw(SDL_Renderer* renderer) override
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g , color.b, color.a);

        int endx = x_ + cos(d_) * l_;
        int endy = y_ + sin(d_) * l_;

        SDL_RenderDrawLine(renderer, x_, y_ , endx, endy);
    }

private:

    int x_;
    int y_;
    float d_;
    int l_;
    SDL_Color color;
};

#endif //LOGO_INTERPRETER_LINE_H
