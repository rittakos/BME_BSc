//
// Created by akosr on 10/05/2020.
//

#ifndef LOGO_INTERPRETER_RENDERER_H
#define LOGO_INTERPRETER_RENDERER_H

#include "SDL2/SDL.h"

class Renderer
{
public:
    Renderer(SDL_Renderer * renderer): renderer_{renderer}{}
private:
    SDL_Renderer * renderer_;
};

#endif //LOGO_INTERPRETER_RENDERER_H
