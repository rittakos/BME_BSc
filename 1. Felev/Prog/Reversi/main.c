#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include "draw.h"
#include "game.h"
#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

/*void Help()
{
    WindowData windowData;
    windowData.title = "Help";
    windowData.height = 300;
    windowData.width = 300;

    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(windowData, &window, &renderer);

    String string;
    String currentLetter;

    //string->nextletter = currentLetter;

    FILE *help = fopen("help.txt", "rt");
    if (help == NULL)
    {
        perror("Fájl megnyitása sikertelen");
        return;
    }

    printf("\n");
    char currentChar;
    while ((currentChar = getc(help)) != EOF)
    {
        currentLetter.letter = currentChar;
        //currentLetter->

    }
    fclose(help);

    stringRGBA(renderer, 10, 10, "Kilepeshez: piros x az ablakon", 255, 255, 255, 255);

    SDL_RenderPresent(renderer);

    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
    }

    SDL_Quit();

}*/

/*Beolvassa a jatek parametereit a standard inputrol*/
void Read(Game *game)
{
    char loadOrReset;
    char computerOrPerson;

    printf("Add meg, hogy uj jatekot szeretnel kezdeni vagy folytatni szeretned a regit(r/l): ");
    do
    {
        scanf("%c", &loadOrReset);
    }while(loadOrReset != 'r' && loadOrReset != 'l');

    if(loadOrReset == 'r')
        Reset(game);
    else
        Load(game);

    if(loadOrReset == 'r')
    {

        printf("\nGep vagy ember ellen szeretnel jatszani (c/p):");
        do
        {
            scanf("%c", &computerOrPerson);
        }while(computerOrPerson != 'c' && computerOrPerson != 'p');

        if(computerOrPerson == 'c')
            game->mode = computer;
        else
            game->mode = person;

        /*printf("\nHa nem ismered a szabajokat akkor h betut, ha ismered n betut adj meg: " );
        do
        {
            scanf("%c", &helpOrNext);
        }while(helpOrNext != 'h' && helpOrNext != 'n');

        if(helpOrNext == 'h')
            Help();*/
    }

}

/*A karakteres jatekhoz es hibakereseshez kiirja a tablat*/
void Write(Game game)
{
    printf("next: %d\n", NextPlayer(&game));
        for(int idy = 0; idy < game.size; ++idy)
        {
            for(int idx = 0; idx < game.size; ++idx)
            {
                printf("%d ", GetCell(&game, idx, idy)->owner);
                //printf("(%d %d) ", game.board[idx][idy].x, game.board[idx][idy].y);
            }
            printf("\n");
        }
}

/*A karakteres jatek ketemberes modjaert fele*/
void PlayPerson(Game *game)
{
    int x, y;
    Cell cell;
    while(!End(*game))
    {
        Write(*game);
        scanf("%d %d", &x, &y);
        cell = *GetCell(game, x, y);
        if(InMatrix(game, cell))
        {
            Step(game, cell, true);
        }

        printf("\n");

    }

}

/*a karakteres jatek gep elleni modjaert felel*/
void PlayComputer(Game *game)
{
    int x,y;
    Cell cell;
    while(!End(*game))
    {
        Write(*game);
        scanf("%d %d", &x, &y);
        cell = *GetCell(game, x, y);

        if(InMatrix(game, cell))
        {
            Step(game, cell, true);
            Write(*game);

            cell = BestTurn(game);
            //printf("%d %d", cell.x, cell.y);

            Step(game, cell, true);
        }
        printf("\n");

    }
}

/*A grafikus jatek mukodeseert felel*/
void Play(Game *game, WindowData windowData, SDL_Renderer *renderer)
{
    bool quit = false;
    bool succesStep = false;
    int step = 0;

    while (!quit && !End(*game))
    {
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                {
                    if(event.button.y < windowData.cellSize / 2 && event.button.x < windowData.cellSize)
                    {
                        Reset(game);
                        DrawBoard(renderer, *game, windowData);
                    }else if(event.button.y < windowData.cellSize / 2 || event.button.x < windowData.cellSize / 2 || event.button.y > windowData.height - windowData.cellSize / 2 || event.button.x > windowData.width - windowData.cellSize / 2)
                    {
                    }
                    else
                    {
                        int x = (event.button.x - windowData.cellSize / 2) / (windowData.width / (game->size + 1));
                        int y = (event.button.y - windowData.cellSize / 2) / (windowData.height / (game->size + 1));
                        Cell currentCell = *GetCell(game, x, y);

                        //printf("%d %d\n", currentCell.x, currentCell.y);

                        LOG("Step");
                        if(Step(game, currentCell, true))
                        {
                            //printf("%d", NextPlayer(game));
                            succesStep = true;
                            ++step;
                        }

                        DrawBoard(renderer, *game, windowData);
                        SDL_RenderPresent(renderer);

                        if(succesStep && GetMode(game) == computer)
                        {
                            Delay(1);
                            Cell best = BestTurn(game);
                            Step(game, best, true);
                            //printf("%d", NextPlayer(game));
                            ++step;
                            //printf("%d %d\n", best.x, best.y);
                            LOG("ComputerStep");

                            DrawBoard(renderer, *game, windowData);
                            succesStep = false;
                        }
                    }
                    SDL_RenderPresent(renderer);
                    break;
                }
            case SDL_QUIT:
                quit = true;
                break;
        }
        SDL_RenderPresent(renderer);
    }

    //printf("\n%d\n", step);
    SDL_RenderPresent(renderer);
}

//A jatek vegen meghivodo fuggveny, kijelzi a nyertees szinet
void EndGame(Game *game, SDL_Renderer *renderer, WindowData windowData)
{
    if(End(*game))
    {
        Color White = {255, 255, 255, 255};
        Color Black = {0, 0, 0, 255};

        int width = windowData.width * windowData.cellSize;
        int height = windowData.height * windowData.cellSize;

        Point leftUp = {0, 0};
        Point rightDown = {width, height};
        Point middleUp = {width / 2, 0};
        Point middleDown = {width / 2, height};


        Player winner = Winner(game);
        if(winner == white)
        {
            boxRGBA(renderer, leftUp.x, leftUp.y, rightDown.x, rightDown.y, White.R, White.G, White.B, White.A);
        }else if(winner == black)
        {
            boxRGBA(renderer, leftUp.x, leftUp.y, rightDown.x, rightDown.y, Black.R, Black.G, Black.B, Black.A);
        }else
        {
            boxRGBA(renderer, leftUp.x, leftUp.y, middleDown.x, middleDown.y, White.R, White.G, White.B, White.A);
            boxRGBA(renderer, middleUp.x, middleUp.y, rightDown.x, rightDown.y, Black.R, Black.G, Black.B, Black.A);
        }
        SDL_RenderPresent(renderer);
        Delay(5);
    }

}

int main(int argc, char *argv[])
{
    LOG ("START");
    Game game;
    game.size = 8;

    CreateGame(&game);


    Read(&game);



    /*ablak adatainak megadasa, minden cellanak legyen hely plusz legyen egy felcellanyi
    sav a szeleken aminek a szine jeloli a kovetkezo jatekost*/
    WindowData windowData = CreatWindow(game.size + 1, game.size + 1, 50, "Reversi");
    SDL_Window *window;
    SDL_Renderer *renderer;

    /*ablak letrehozasa*/
    sdl_init(windowData, &window, &renderer);

    /*kezdo palya kiralyzolasa, mindig a feher jatekos kezd*/
    DrawBoard(renderer, game, windowData);

    /*A jatek*/
    Play(&game, windowData, renderer);

    /*A kiralyzolasok megjelenitese*/
    SDL_RenderPresent(renderer);

    /*A jatek vege*/
    EndGame(&game, renderer, windowData);

    /* ablak bezarasa */
    SDL_Quit();

    if(End(game))
        Reset(&game);

    /*Jatek mentese*/
    Save(&game);


    /*memoria felszabaditasa*/
    FreeGame(&game);

    LOG("END");
    return 0;
}
