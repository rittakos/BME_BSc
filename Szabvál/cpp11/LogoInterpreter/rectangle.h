//
// Created by akosr on 05/05/2020.
//

#ifndef LOGO_INTERPRETER_RECTANGLE_H
#define LOGO_INTERPRETER_RECTANGLE_H

#include "drawable.h"
#include <iostream>

class Rectangle : public Drawable
{
public:
    Rectangle(int x, int y, int w, int h, SDL_Color color = {255, 255, 255, 255}) : x_{x}, y_{y}, w_{w}, h_{h}
    {
        color_ = color;
        rectangle.x = x;
        rectangle.y = y;
        rectangle.h = w;
        rectangle.w = h;
    }

    void Draw(SDL_Renderer* renderer) override
    {
        //std::cout << "rec";
        SDL_SetRenderDrawColor(renderer, color_.r, color_.g , color_.b, color_.a);

        SDL_RenderDrawRect(renderer, &rectangle);
        SDL_RenderFillRect(renderer, &rectangle);
    }

private:
    SDL_Rect rectangle;

    int x_;
    int y_;
    int w_;
    int h_;
    SDL_Color color_;
};

#endif //LOGO_INTERPRETER_RECTANGLE_H
