#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "settings.h"

//#define DEBUG
#ifdef DEBUG
#define LOG(msg) printf("%s\n", msg)
#else
#define LOG(msg)
#endif // DEBUG

//eltarolja az ablak parametereit, meret, fejlecszoveg, cellanagysag
typedef struct WindowData
{
     char *title;
     int height, width;
     int cellSize;
}WindowData;

//egy szint tarol el RGBA formatumban
typedef struct Color
{
    int R;
    int G;
    int B;
    int A;
}Color;

//egy pontot tarol el x, y koordinatak alapajan
typedef struct Point
{
    int x;
    int y;
}Point;

//visszater egy WindowData tipussal amiben benne vannak a bemenetkent megadott parameterek
WindowData CreatWindow(int width, int height, int cellSize, char* title);

//letrehozza az ablakot a megadott parameterei alapjan
void sdl_init(WindowData windowData, SDL_Window **pwindow, SDL_Renderer **prenderer);

//megrajzolja az aktualis palyat
void DrawBoard(SDL_Renderer *renderer, Game game, WindowData windowData);

#endif // DRAW_H_INCLUDED
