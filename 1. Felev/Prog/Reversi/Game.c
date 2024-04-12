#include "game.h"

//itt vannak a game.h ban definialt fuggvenyek kodjai valamint az azokhoz hasznalt segedfuggvenyek


void CreateGame(Game *game)
{
    game->board = (Cell**)malloc(game->size * sizeof(Cell*));

    for (int idx = 0; idx < game->size; ++idx)
    {
        game->board[idx] = (Cell*)malloc(game->size * sizeof(Cell));
    }
}

void FreeGame(Game *game)
{

    for (int idx = 0; idx < (*game).size; ++idx)
    {
        free(game->board[idx]);
    }

    free(game->board);
}

void Load(Game *game)
{
    FILE *save = fopen("save.txt", "rt");
    if (save == NULL)
    {
        perror("Fájl megnyitása sikertelen");
        return;
    }

    fscanf(save, "%d %d", &(game->nextPlayer), &(game->mode));


    for(int row = 0; row < GetRow(game); ++row)
    {
        for(int column = 0; column < GetColumn(game); ++column)
        {

            fscanf(save, "%d", &(*game).board[column][row].owner);
            game->board[column][row].x = column;
            game->board[column][row].y = row;
        }
    }
    fclose(save);
}

void Reset(Game *game)
{
    game->nextPlayer = white;
    for(int idy = 0; idy < GetRow(game); ++idy)
    {
        for(int idx = 0; idx < GetColumn(game); ++idx)
        {

            GetCell(game, idx, idy)->owner = none;
            GetCell(game, idx, idy)->x = idx;
            GetCell(game, idx, idy)->y = idy;
        }
    }
    GetCell(game, GetColumn(game)/2 - 1, GetRow(game)/2 - 1)->owner = white;
    GetCell(game, GetColumn(game)/2, GetRow(game)/2 - 1)->owner = black;
    GetCell(game, GetColumn(game)/2 - 1, GetRow(game)/2)->owner = black;
    GetCell(game, GetColumn(game)/2, GetRow(game)/2)->owner = white;
}

void Save(Game *game)
{
    FILE *save = fopen("save.txt", "wt");
    if (save == NULL)
    {
        perror("Fájl megnyitása sikertelen");
        return;
    }
    fprintf(save, "%d %d\n", game->nextPlayer, game->mode);


    game->nextPlayer = white;
    for(int row = 0; row < GetRow(game); ++row)
    {
        for(int column = 0; column < GetColumn(game); ++column)
        {
            fprintf(save, "%d ", game->board[column][row]);
        }
       fprintf(save, "\n");
    }
    fclose(save);
}

Player Winner(Game *game)
{
    int whiteNum = 0;
    int blackNum = 0;
    int noneNum = 0;
    for(int idx = 0; idx < GetColumn(game); ++idx)
    {
        for(int idy = 0; idy < GetRow(game); ++idy)
        {
            if(GetCell(game, idx, idy)->owner == none)
                ++noneNum;
            else if(GetCell(game, idx, idy)->owner == black)
                ++blackNum;
            else
                ++whiteNum;
        }
    }
    if(whiteNum > blackNum)
        return white;
    else if(whiteNum < blackNum)
        return black;
    else
        return none;
}

//visszater, hogy a megadott cella az adott esetben kielegiti e szukseges felteteleit annak, hogy
//atforgathato legyen
bool EnableCell(Game *game, Cell cell, int xDir, int yDir)
{
    if(cell.y == 0 && yDir == -1)
        return false;
    if(cell.x == 0 && xDir == -1)
        return false;
    if(cell.y == GetRow(game) - 1 && yDir == 1)
        return false;
    if(cell.x == GetColumn(game) - 1 && xDir == 1)
        return false;

    if(game->board[cell.x + xDir][cell.y + yDir].owner == game->nextPlayer)
       return false;

    if(game->board[cell.x + xDir][cell.y + yDir].owner == none)
       return false;

    return true;
}

//a fargatasert felel, visszater az atforgathato korongok szamaval, ha a turn false akkor nem
//forgatja at, ha true akkor atforgatja
int Turn(Game *game, Cell cell, int xDir, int yDir, bool turn)
{
    //printf("START Turn - %d %d %d\n", cell.x, cell.y, cell.owner);
    int changed = 0;


    int x = cell.x;
    int y = cell.y;

    Cell currentCell = *GetCell(game, x, y);
    //printf("Current Cell: %d %d %d \n", game->board[cell.x][cell.y], currentCell.y, currentCell.owner);

    if(!EnableCell(game, cell, xDir, yDir))
    {
        //printf("END Turn\n");
        return 0;
    }

    bool outOfBoard = false;

    //printf("START WHILE\n");
    y += yDir;
    x += xDir;
    currentCell = *GetCell(game, x, y);
    //printf("currentCell - %d %d %d\n", currentCell.x, currentCell.y, currentCell.owner);
    while(currentCell.owner != NextPlayer(game) && currentCell.owner != none)
    {
        y += yDir;
        x += xDir;

        if(x >= 0 && y >= 0 && x < GetColumn(game) && y < GetRow(game))
            currentCell = *GetCell(game, x, y);
        else
        {
            y -= yDir;
            x -= xDir;
            outOfBoard = true;
            break;
        }

        //printf("currentCell - %d %d %d\n", currentCell.x, currentCell.y, currentCell.owner);

    }
    //printf("END WHILE \n");

    if(GetCell(game, x, y)->owner != none && !outOfBoard)
    {
        //printf("START DO\n");
        while(!(x == cell.x && y == cell.y))
        {
            //printf("%d %d\n", x, y);
            ++changed;
            if (turn)
                GetCell(game, x, y)->owner = NextPlayer(game);
            y -= yDir;
            x -= xDir;
        }
        //printf("END DO\n");
        if(turn)
            GetCell(game, cell.x, cell.y)->owner = NextPlayer(game);
    }
    //printf("END Turn - %d\n", changed);
    return changed;
}

//Az osszes iranyon vegigmenve megnezi az osszes forgatasi lehetoseget egy cellanak
//ha a turn true akkor vegre is halytja, ha false akkor csak visszater az atfordithatok szamaval
int AllTurns(Game *game, Cell cell, bool turn)
{
    int numOfChanged = 0;

    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            if(x != 0 || y != 0)
            {
                numOfChanged += Turn(game, cell, x, y, turn);
            }
        }
    }

    /*int sum = 0;
    for(int id = -1; id <= 1; ++id)
    {
        if(id != 0)
        {
            sum += Turn(game, cell, 0, id, turn);
            sum += Turn(game, cell, id, 0, turn);
        }
    }
    return sum;*/
//    printf("%d\n", numOfChanged);
    return numOfChanged;
}

//trueval ter vissza ha lehetseges kovetkezo lepes falsesal ha nem
bool AvailableNextStep(Game game)
{

    if(game.nextPlayer == white)
        game.nextPlayer = black;
    else
        game.nextPlayer = white;

    for(int idy = 0; idy < GetRow(&game); ++idy)
    {
        for(int idx = 0; idx < GetColumn(&game); ++idx)
        {
            Cell cell = *GetCell(&game, idx, idy);
            //printf("%d ", AllTurns(&game, cell, false));
            if(cell.owner == none)
                if(AllTurns(&game, cell, false) > 0)
                    return true;
        }
    }
    return false;
}

//megmndja, hogy egy adott cella valasztasa mellett mi a kovetkezo lgjobb valasztas
int NextBestTurn(Game *game, Cell prevCell)
{
    int bestTurnCount = 0;
    int currentTurnCount = 0;
    Cell currentCell;

    if((*game).nextPlayer == white)
    {
        (*game).nextPlayer = black;
        for(int row = 0; row < GetRow(game); ++row)
        {
            for(int column = 0; column < GetColumn(game); ++column)
            {
                currentCell = (*game).board[column][row];
                if(!(currentCell.x == prevCell.x && currentCell.y == prevCell.y))
                {
                    currentTurnCount = AllTurns(game, currentCell, false);
                    if(currentTurnCount > bestTurnCount)
                    {
                        bestTurnCount = currentTurnCount;
                    }
                }
            }
        }
        (*game).nextPlayer = white;
    }else
    {
        (*game).nextPlayer = white;
        for(int row = 0; row < GetRow(game); ++row)
        {
            for(int column = 0; column < GetColumn(game); ++column)
            {
                currentTurnCount = AllTurns(game, (*game).board[column][row], false);
                if(currentTurnCount > bestTurnCount)
                {
                    bestTurnCount = currentTurnCount;
                }
            }
        }
        (*game).nextPlayer = black;
    }
    return bestTurnCount;
}

Cell BestTurn(Game *game)
{
    const int maxTurned = 8*8;
    int bestTurn = -maxTurned;
    int currentTurn = 0;
    Cell bestCell;
    Cell currentCell;


    for(int row = 0; row < GetRow(game); ++row)
    {
        for(int column = 0; column < GetColumn(game); ++column)
        {
            currentCell = game->board[column][row];
            int allTurns = AllTurns(game, currentCell, false);
            //kivonja egymasbol az aktualis forgathato es kovetkezoleg forgathato cellak szamat
            currentTurn = allTurns - NextBestTurn(game, currentCell);
            //ezek maximuma a legjobb valasztas lepesre
            if(currentCell.owner != none)
                currentTurn = -maxTurned;
            //printf("%d ", currentTurn);
            if(currentTurn > bestTurn)
            {
                bestTurn = currentTurn;
                bestCell = game->board[column][row];
            }
        }
    }
    return bestCell;
}

bool End (Game game)
{
    int whiteNum = 0;
    int blackNum = 0;
    int noneNum = 0;
    int putWhite = 0;
    int putBlack = 0;

    for(int idy = 0; idy < GetRow(&game); ++idy)
    {
        for(int idx = 0; idx < GetColumn(&game); ++idx)
        {
            if(game.board[idy][idx].owner == none)
                ++noneNum;
            else if(game.board[idy][idx].owner == black)
                ++blackNum;
            else
                ++whiteNum;
            game.nextPlayer = white;
            putWhite += AllTurns(&game, *GetCell(&game, idx, idy), false);
            game.nextPlayer = black;
            putBlack += AllTurns(&game, *GetCell(&game, idx, idy), false);

        }
    }

    //printf("%d %d %d", noneNum, blackNum, whiteNum);
    if(putBlack == 0 && putWhite == 0)
        return false;
    if(noneNum == 0)
        return true;
    else if(whiteNum == 0)
        return true;
    else if(blackNum == 0)
        return true;
    return false;
}

//visszater a forgathato cellak szamaval ha vannak, hogyha a mezo valaszthato kovetkezo lepesnek
//ha turn true akkor vegre is halytja forgatasokat
int PossibleStep(Game *game, Cell cell, bool turn)
{
    if(cell.owner == none && !End(*game))
    {
        return AllTurns(game, cell, turn);
    }
    return 0;
}

//hibakereseshez vegigmegy a cellakon es kiirja azok bizonyos adatait
void Write2(Game game)
{
    printf("next: %d\n", game.nextPlayer);
        for(int idy = 0; idy < game.size; ++idy)
        {
            for(int idx = 0; idx < game.size; ++idx)
            {
                //printf("%d ", GetCell(&game, idx, idy)->owner);
                printf("%d ", AllTurns(&game, *GetCell(&game, idx, idy), false));
                //printf("(%d %d) ", GetCell(&game, idx, idy)->x, GetCell(&game, idx, idy)->y);
            }
            printf("\n");
        }
}

bool Step(Game *game, Cell cell, bool turn)
{
    if(PossibleStep(game, cell, turn) != 0 && turn)
    {
        if(AvailableNextStep(*game))
        {
            cell.owner = game->nextPlayer;
            if(game->nextPlayer == black)
            {
                game->nextPlayer = white;
            }

            else
            {
                game->nextPlayer = black;
            }
            //AllTurns(game, cell);
            return true;
        }
    }
    return false;
}

