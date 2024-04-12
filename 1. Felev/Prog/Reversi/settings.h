#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

//#define DEBUG
#ifdef DEBUG
#define LOG(msg) printf("%s\n", msg)
#else
#define LOG(msg)
#endif // DEBUG


//A az adatszerkezetek vannak benne es az azok hasznalatat egyszerusito fuggvenyek


//a kovetkezo jatekos es a cella tulajdonosanak jelolesere hasznalt
typedef enum Player
{
    none,
    white,
    black
}Player;


//A jatek modjat, gep ellen vagy ember ellen, tarolja
typedef enum Mode
{
    person,
    computer
}Mode;


//egy cellanak az adatai vannak benne, tulajdonos, koordinatak
typedef struct Cell
{
    Player owner;
    int x, y;

}Cell;


//a jatek tulajdonsagait, mod, kovetkezo jateko, meret valamint a jatektabla ketdimenzios Cell tomb
//van benne
typedef struct Game
{
    int size;
    Cell **board; //0nal ures a mezo, 1nel fekete, -1nel feher
    Player nextPlayer;
    Mode mode;
}Game;


//a jatek egy adott koordinataju cella pointerevel
Cell *GetCell(Game *game, int x, int y);

//visszater a kovetkezo jatekossal
Player NextPlayer(Game *game);

//visszater a jatek modjaval
Player GetMode(Game *game);

//Visszater egy adott cella tulajdonosaval
Player GetOwner(Cell cell);

//visszater az oszlopok szamaval
int GetColumn(Game *game);

//visszater a sorok szamaval
int GetRow(Game *game);

//megmondja, hogy egy cella benne van-e a jatekmezoben
bool InMatrix(Game *game, Cell cell);

//varakozik megadott masodpercet
void Delay(int sec);



#endif // SETTINGS_H_INCLUDED
