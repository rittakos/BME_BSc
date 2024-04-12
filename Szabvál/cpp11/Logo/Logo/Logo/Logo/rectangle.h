//
// Created by akosr on 05/05/2020.
//

#ifndef LOGO_INTERPRETER_RECTANGLE_H
#define LOGO_INTERPRETER_RECTANGLE_H

#include <iostream>
#include "drawable.h"
#include "point.h"

class Rectangle : public Drawable
{
public:
    Rectangle(Point leftUpCorner, int width, int height, SDL_Color color = {255, 255, 255, 255}) : leftUpCorner_{leftUpCorner}, w_{width}, h_{height}
    {
        color_ = color;
    }


    void Draw(SDL_Renderer* renderer) override
    {
        SDL_Rect rect;
        rect.x = leftUpCorner_.X();
        rect.y = leftUpCorner_.Y();
        rect.w = w_;
        rect.h = h_;

        SDL_SetRenderDrawColor(renderer, color_.r, color_.g , color_.b, color_.a);

        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

private:
    Point leftUpCorner_;
    int w_;
    int h_;

    SDL_Color color_;
};

#endif
