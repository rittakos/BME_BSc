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
    
    Page(std::string name, int width, int height) : name_{name}
    {
        width_ = width - 2 * tab;
        height_ = height - 2 * tab;
        center_ = Point(width / 2, height / 2);

        turtles.push_back(std::make_shared<Turtle>(Turtle("t1", center_)));
    }


    void Draw(SDL_Renderer* renderer)
    {
        Rectangle rectangle(Point(tab, tab), width_, height_);
        rectangle.Draw(renderer);

        for(std::shared_ptr<Drawable> item : picture)
            item->Draw(renderer);

        for(std::shared_ptr<Turtle> item : turtles)
            item->Draw(renderer);

    }

    void Add(std::shared_ptr<Drawable> item)
    {
        if(item == nullptr)
            return;
        picture.push_back(item);
    }

    void Clear()
    {
        for (std::shared_ptr<Turtle> t : turtles)
            t->Reset();
        picture.clear();
    }

    std::shared_ptr<Turtle> GetTurtle(std::string name) const
    {
        for(size_t idx = 0; idx < turtles.size(); ++idx)
        {
            if (turtles[idx]->Name() == name)
            {
                return turtles[idx];
            }
        }

        throw InvalidTurtleExeption();
    }
private:
    int width_;
    int height_;
    Point center_;

    std::string name_;

    const int tab = 50;

    std::vector<std::shared_ptr <Turtle>> turtles;
    std::vector<std::shared_ptr<Drawable>> picture;

};


#endif
