#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//#define DEBUG
#ifdef DEBUG
#define LOG(msg) printf("%s\n", msg)
#else
#define LOG(msg)
#endif // DEBUG
#include "settings.h"


//trueval ter vissza, hogyha a kovetkezo jatekos tud rakni falseal ha nem
bool AvailableNextStep(Game game);

//visszaallitja a tablat a kezdeti allapotra es beallitja a kovetkezo jatekost whitera
void Reset(Game *game);

//beolvassa a kovetkezo jatekost es a jatek modjat egy filebol, aztan az osszes cella tulajdonosat
//ezeket mond belerakja a megadott Game pointerbe
void Load(Game *game);

//lefoglalja a ketdimenzios Cell tombot ami sizeXsize nagysagu
void CreateGame(Game *game);

//felszabaditja az elobbiekben lefoglalt matrixot
void Free(Game *game);

//kimenti a jatek kovetkezo jatekosat es modjat valamint az osszes cella tartalmat egy fileba
void Save(Game *game);

//egy lepest halyt vegre, a bemeneti logikai valtozo azt modndja meg, hogy halytsa is vegre a
//valtoztatasokat vagy csak nezze meg, holgy lehetseges es terjen vissza azzal
bool Step(Game *game, Cell cell, bool turn);

//visszater azzal a cellaval aminek a forgatasaval a legnagyob nyereseg erheto el
Cell BestTurn(Game *game);

//Vizsgalja, hogy vege van-e a jateknak a szabalyok alapjan majd visszater, hogy igen vagy nem
bool End(Game game);

//megnezi es visszater a nyertessel
Player Winner(Game *game);

#endif // GAME_H_INCLUDED
