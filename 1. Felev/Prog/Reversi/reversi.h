#ifndef REVERSI_H_INCLUDED
#define REVERSI_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//#define DEBUG
#ifdef DEBUG
#define LOG(msg) printf("%s\n", msg)
#else
#define LOG(msg)
#endif // DEBUG

typedef enum Player
{
    none,
    black,
    white
}Player;

typedef struct Cell
{
    Player owner;

}Cell;

typedef struct Game
{
    int size;
    int x;
    int y;
    Cell **board; //0nal ures a mezo, 1nel fekete, -1nel feher
    Player nextPlayer;
}Game;


void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
void DrawCircle(SDL_Renderer *renderer, int x, int y, int r);
void DrawBoard(SDL_Renderer *renderer, Game game);
void Reset(Game *game);
void Load(Game *game, FILE *save);
void Malloc(Game *game);
void Free(Game *game);
void Save(Game *game, FILE *save);
void Step(Game *game, Cell cell);

#endif // REVERSI_H_INCLUDED
