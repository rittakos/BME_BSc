#include "draw.h"

//itt vannak a draw.h ban definialt fuggvenyek kodjai valamint az azokhoz hasznalt segedfuggvenyek


void sdl_init(WindowData windowData, SDL_Window **pwindow, SDL_Renderer **prenderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(windowData.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowData.width, windowData.height, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

WindowData CreatWindow(int width, int height, int cellSize, char* title)
{
    WindowData windowData;
    windowData.cellSize = cellSize;
    windowData.title = title;
    windowData.height = height * cellSize;
    windowData.width = width * cellSize;
    return windowData;
}

//megrajzolja az alapveto palyata lehelyezett korongok nelkul, zold 8X8as negyzetracsos palya
//szegellyel ami a kovetkezo jatekos szinet mutatja
void SetBackground(SDL_Renderer *renderer, int size, WindowData windowData)
{
    Color green = {0, 255, 0, 255};
    Color black = {0, 0, 0, 255};
    Point leftUp = {windowData.cellSize / 2, windowData.cellSize / 2};
    Point rightDown;
    rightDown.x = windowData.width - windowData.cellSize/2;
    rightDown.y = windowData.height - windowData.cellSize/2;

    boxRGBA(renderer, leftUp.x, leftUp.y, rightDown.x, rightDown.y, green.R, green.G, green.B, green.A);
    for(int idx = windowData.cellSize / 2; idx < windowData.height; idx += windowData.cellSize)
    {
        lineRGBA(renderer, windowData.cellSize / 2, idx, windowData.height + windowData.cellSize / 2, idx, black.R, black.G, black.B, black.A);
        lineRGBA(renderer, idx, windowData.cellSize / 2, idx, windowData.height + windowData.cellSize / 2, black.R, black.G, black.B, black.A);
    }
}

//adott kozeppontu, sugaru es szinu kort rajzol
void DrawCircle(SDL_Renderer *renderer, Point O, int r, Color color)
{
    filledCircleRGBA(renderer, O.x, O.y, r, color.R, color.G, color.B, color.A);
}

//adott pomttol adott pontig rajzol egyenest adott vastagsaggal es szinnel
void DrawLine(SDL_Renderer *renderer, Point startPoint, Point endPoint, int thick, Color color)
{
    thickLineRGBA(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y, thick, color.R, color.G, color.B, color.A);
}

//megrajzolja a keretet a kovetkezo jatekos szinevel
void DrawBorder(SDL_Renderer *renderer, Player nextPlayer, WindowData windowData)
{
    Color black = {0, 0, 0, 255};
    Color white = {255, 255, 255, 255};
    Color red = {255, 0, 0, 255};

    Color lineColor;
    if(nextPlayer == 2)
        lineColor = black;
    else
        lineColor = white;

    int thick = windowData.cellSize;

    Point leftUp = {0, 0};
    Point leftDown = {windowData.height, 0};
    Point rightUp = {0, windowData.width};
    Point rightDown = {windowData.height, windowData.width};

    Point resetPoz = {0, windowData.cellSize/4};

    DrawLine(renderer, leftUp, rightUp, thick, lineColor);
    DrawLine(renderer, leftUp, leftDown, thick, lineColor);
    DrawLine(renderer, rightDown, rightUp, thick, lineColor);
    DrawLine(renderer, rightDown, leftDown, thick, lineColor);

    stringRGBA(renderer, resetPoz.x, resetPoz.y, "RESET", red.R, red.G, red.B, red.A);
}

void DrawBoard(SDL_Renderer *renderer, Game game, WindowData windowData)
{
    Color Black = {0, 0, 0, 255};
    Color White = {255, 255, 255, 255};
    Color circleColor;

    const int r = 20;

    SetBackground(renderer, game.size, windowData);
    DrawBorder(renderer, game.nextPlayer, windowData);

    Point O;
    Cell currentCell;

    //vegig megy a cellakon es kirajzol egy olyan szinu kort mint az a cella
    for(int idy = 0; idy < GetRow(&game); ++idy)
    {
        for(int idx = 0; idx < GetColumn(&game); ++idx)
        {
            currentCell = *GetCell(&game, idx, idy);
            O.x = windowData.cellSize  + idx * windowData.cellSize;
            O.y = windowData.cellSize  + idy * windowData.cellSize;

            if(GetOwner(currentCell) == white)
            {
                circleColor = White;
            }
            else if(GetOwner(currentCell) == black)
            {
                circleColor = Black;
            }
            if(GetOwner(currentCell) != none)
                DrawCircle(renderer, O, r, circleColor);
        }
    }
}


