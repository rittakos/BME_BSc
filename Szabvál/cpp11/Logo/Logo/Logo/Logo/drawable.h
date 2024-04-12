//
// Created by akosr on 04/05/2020.
//

#ifndef LOGO_INTERPRETER_DRAWABLE_H
#define LOGO_INTERPRETER_DRAWABLE_H

#include <SDL.h>

class Drawable
{
public:
    Drawable()
    {

    }

    virtual void Draw(SDL_Renderer* renderer) = 0;

    virtual ~Drawable() = default;
};


#endif
