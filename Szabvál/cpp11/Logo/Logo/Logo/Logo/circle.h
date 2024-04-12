
#ifndef SDL_DEMO_COMMAND_H
#define SDL_DEMO_COMMAND_H

#include "drawable.h"
#include "point.h"
#include <iostream>

class Circle : public Drawable
{
public:
    Circle(Point center, int radius, SDL_Color color = { 0, 255, 0, 255 }) : O_{ center }, r_{ radius }, color_{color}
	{

	}

	void Draw(SDL_Renderer* renderer) override
	{
        SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
        for (int x = O_.X() - r_; x < O_.X() + r_; ++x)
        {
            for (int y = O_.Y() - r_; y < O_.Y() + r_; ++y)
            {
                Point P(x, y);

                if (P.distance(O_) <= r_)
                    P.Draw(renderer);
            }
        }
	}

private:
	Point O_;
	int r_;
    SDL_Color color_;
};

#endif