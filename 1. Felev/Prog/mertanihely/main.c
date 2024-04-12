#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>

typedef struct Point
{
    int x;
    int y;
}Point;

typedef struct Color
{
    int r;
    int g;
    int b;
    int a;
}Color;

double distance(Point O, Point P)
{
    return sqrt(pow(O.x - P.x, 2) + pow(O.y - P.y, 2));
}

void Circle(Point O, int r, int height, int width, int epsilon, SDL_Renderer *renderer)
{
    Color red = {255, 0, 0, 255};
    for(int y = 0; y <= height; ++y)
    {
        for(int x = 0; x <= width; ++x)
        {
            Point P = {x, y};
            if(fabs(distance(O, P) - r) < epsilon)
                pixelRGBA(renderer, P.x, P.y, red.r, red.g, red.b, red.a);
        }
    }
    stringRGBA(renderer, O.x, O.y, "Kor", red.r, red.g, red.b, red.a);
}

void Ellipse(Point O1, Point O2, int r, int height, int width, int epsilon, SDL_Renderer *renderer)
{
    Color green = {0, 255, 0, 255};
    for(int y = 0; y <= height; ++y)
    {
        for(int x = 0; x <= width; ++x)
        {
            Point P = {x, y};
            if(fabs(distance(O1, P) + distance(O2, P) - r) < epsilon)
                pixelRGBA(renderer, P.x, P.y, green.r, green.g, green.b, green.a);
        }
    }
    stringRGBA(renderer, O1.x, O1.y, "Elipszis", green.r, green.g, green.b, green.a);
}

void Hyperbola(Point O1, Point O2, int r, int height, int width, int epsilon, SDL_Renderer *renderer)
{
    Color blue = {0, 0, 255, 255};
    for(int y = 0; y <= height; ++y)
    {
        for(int x = 0; x <= width; ++x)
        {
            Point P = {x, y};
            if(fabs(fabs(distance(O1, P) - distance(O2, P)) - r) < epsilon)
                pixelRGBA(renderer, P.x, P.y, blue.r, blue.g, blue.b, blue.a);
        }
    }
    stringRGBA(renderer, O1.x, O1.y, "hiperbola", blue.r, blue.g, blue.b, blue.a);
}

void Parabola(Point O, int linex, int height, int width, int epsilon, SDL_Renderer *renderer)
{
    Color white = {255, 255, 255, 255};
    for(int y = 0; y <= height; ++y)
    {
        for(int x = 0; x <= width; ++x)
        {
            Point P = {x, y};
            if(fabs(fabs(distance(O, P) - fabs(linex - P.x))) < epsilon)
                pixelRGBA(renderer, P.x, P.y, white.r, white.g, white.b, white.a);
        }
    }
    stringRGBA(renderer, O.x, O.y-20, "parabola", white.r, white.g, white.b, white.a);
}

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
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


int main(int argc, char *argv[])
{

    const int height = 480;
    const int width = 640;
    const int epsilon = 1;

    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("SDL peldaprogram", width, height, &window, &renderer);

    Point O = {320, 240};
    //Circle(O, 200, height, width, epsilon, renderer);
    Point O1 = {240, 200};
    Point O2 = {400, 280};
    //Ellipse(O1, O2, 250, height, width, epsilon, renderer);
    Point O3 = {240, 240};
    Point O4 = {400, 240};
    //Hyperbola(O3, O4, 100, height, width, epsilon, renderer);
    Point O5 = {320, 240};
    //Parabola(O5, 400, height, width, epsilon, renderer);



    Color red = {255, 0, 0, 255};
    Color green = {0, 255, 0, 255};
    Color blue = {0, 0, 255, 255};
    Color white = {255, 255, 255, 255};
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            Point P = {x, y};
            if(fabs(distance(O, P) - 200) < epsilon)
                pixelRGBA(renderer, P.x, P.y, red.r, red.g, red.b, red.a);
            if(fabs(distance(O1, P) + distance(O2, P) - 250) < epsilon)
                pixelRGBA(renderer, P.x, P.y, green.r, green.g, green.b, green.a);
            if(fabs(fabs(distance(O3, P) - distance(O4, P)) - 100) < epsilon)
                pixelRGBA(renderer, P.x, P.y, blue.r, blue.g, blue.b, blue.a);
            if(fabs(fabs(distance(O5, P) - fabs(400 - P.x))) < epsilon)
                pixelRGBA(renderer, P.x, P.y, white.r, white.g, white.b, white.a);
        }
    }
    stringRGBA(renderer, O.x, O.y, "Kor", red.r, red.g, red.b, red.a);
    stringRGBA(renderer, O1.x, O1.y, "Elipszis", green.r, green.g, green.b, green.a);
    stringRGBA(renderer, O3.x, O3.y, "hiperbola", blue.r, blue.g, blue.b, blue.a);
    stringRGBA(renderer, O5.x, O5.y-20, "parabola", white.r, white.g, white.b, white.a);




    SDL_RenderPresent(renderer);

    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT);

    SDL_Quit();

    return 0;
}
