//
// Created by akosr on 04/05/2020.
//

#ifndef LOGO_INTERPRETER_PAGE_H
#define LOGO_INTERPRETER_PAGE_H

#include <vector>
#include "turtle.h"
#include "rectangle.h"
#include "line.h"
#include "exception.h"

class Page final : public Drawable
{
public:
    Page(int width = 900, int height = 500) : width_{width}, height_{height}
    {
        Turtle* firstTurtle = new Turtle("t1");
        //turtles.clear();
        firstTurtle->Position() = Point((width + 2 * tab) / 2, (height +2 *  tab) / 2);
        //firstTurtle->Direction() = -M_PI / 2;
        turtles.push_back(firstTurtle);
    }

    void Draw(SDL_Renderer* renderer)
    {
        Rectangle rectangle(tab, tab, height_, width_);
        rectangle.Draw(renderer);

        for(Drawable* item : picture)
            item->Draw(renderer);

        for(Turtle* item : turtles)
            item->Draw(renderer);

    }

    void Add(Drawable* item)
    {
        if(item == nullptr)
            return;
        picture.push_back(item);
    }

    ~Page()
    {
        for(Drawable* item : picture)
            delete item;

        for(Turtle* item : turtles)
            delete item;
    }

    Turtle& GetTurtle(std::string name)
    {
        for(int idx = 0; idx < turtles.size(); ++idx)
        {
            if (turtles[idx]->Name() == name)
            {
                return *turtles[idx];
            }
        }

        throw InvalidTurtleExeption();
    }
private:
    int width_;
    int height_;

    int tab = 50;

    std::vector<Turtle*> turtles;
    std::vector<Drawable*> picture;

};


#endif
