#include "settings.h"

//egy az egyben a settings.h-ban definialt fuggvenyek kodja van benne

int GetColumn(Game *game)
{
    return (*game).size;
}

int GetRow(Game *game)
{
    return (*game).size;
}

Cell *GetCell(Game *game, int x, int y)
{
    return &(game->board[x][y]);
}

Player NextPlayer(Game *game)
{
    return game->nextPlayer;
}

Player GetMode(Game *game)
{
    return game->mode;
}

Player GetOwner(Cell cell)
{
    return cell.owner;
}

bool InMatrix(Game *game, Cell cell)
{
    if(cell.x < 0 || cell.x >= GetColumn(game))
        return false;
    if(cell.y < 0 || cell.y >= GetRow(game))
        return false;
    return true;
}

void Delay(int sec)
{
    clock_t startTime = clock();

    while (clock() < startTime + sec * 1000);
}
