#include <stdio.h>
#include <math.h>

#include "SDL.h"
#include "SDL_shape.h"
#include "SDL_render.h"
#include "SDL_pixels.h"
#include "SDL_main.h"  
#include "SDL2_gfxPrimitives.h"



int main(int argc, char *argv[]) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
		exit(1);
	}
	SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
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
 
	for (int x = 0; x <= 640; ++x)
	{
		for (int y = 0; y <= 480; ++y);
			//pixelColor(renderer, x, y, 123);
	}
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
	/* az elvegzett rajzolasok a kepernyore */
	SDL_RenderPresent(renderer);
 
	/* varunk a kilepesre */
	SDL_Event ev;
	while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
	}

	int x, y, r;
	r = 50;

	/* karika */
	x = 100;
	y = 100;
	circleRGBA(renderer, x, y, r, 255, 0, 0, 255);
	circleRGBA(renderer, x + r, y, r, 0, 255, 0, 255);
	circleRGBA(renderer, x + r * cos(3.1415 / 3), y - r * sin(3.1415 / 3), r, 0, 0, 255, 255);
 
	/* ablak bezarasa */
	SDL_Quit();
 
	return 0;
}
