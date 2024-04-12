//
// Created by akosr on 04/05/2020.
//

#ifndef LOGO_INTERPRETER_TURTLE_H
#define LOGO_INTERPRETER_TURTLE_H

//#include "page.h"
#include "drawable.h"
#include "rectangle.h"
#include "point.h"


class Turtle final : public Drawable
{
public:

    Turtle()
    {
        //SetPosition();
        //SetDirection();
        direction_ = -M_PI / 2;
        penDown_ = true;
    }

    Turtle(std::string name)
    {
        name_ = name;
        direction_ = -M_PI / 2;
        penDown_ = true;
    }

    Turtle(const Turtle& other)
    {
        position_ = other.position_;
        direction_ = other.direction_;
    }

    Turtle& operator=(const Turtle& other)
    {
        position_ = other.position_;
        direction_ = other.direction_;
        return *this;
    }

    std::string Name()
    {
        return name_;
    }
    float& Direction(){ return direction_; }
    Point& Position(){ return  position_; }
    bool& PenDown() { return penDown_;}

    ~Turtle()
    {

    }

    void Draw(SDL_Renderer* renderer) override
    {
        Rectangle r(position_.X() - a/2, position_.Y() - a/2, a, a, {0, 255, 0, 255});
        r.Draw(renderer);
    }
private:
    Point position_;
    float direction_;
    std::string name_;
    bool penDown_;

    const int a = 20;
    //Page page;
    //Page* pageRef;
};


#endif
