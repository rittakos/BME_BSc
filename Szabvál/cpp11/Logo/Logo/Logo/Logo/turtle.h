//
// Created by akosr on 04/05/2020.
//

#ifndef LOGO_INTERPRETER_TURTLE_H
#define LOGO_INTERPRETER_TURTLE_H

#include <string>
#include "drawable.h"
#include "point.h"
#include "circle.h"


class Turtle final : public Drawable
{
public:

    explicit Turtle(std::string name, Point position)
    {
        name_ = name;
        position_ = position;
        defaultPosition_ = position;
        direction_ = -M_PI / 2;
        penDown_ = true;
    }

    std::string Name() const
    {
        return name_;
    }
    double& Direction(){ return direction_; }
    Point& Position(){ return  position_; }
    bool& PenDown() { return penDown_;}

    void Reset()
    {
        position_ = defaultPosition_;
        direction_ = -M_PI / 2;
    }

    void Draw(SDL_Renderer* renderer) override
    {
        Circle c1(position_, a, { 100, 200, 150, 255 });
        Circle c2(Point(
                        position_.X() + (int)(cos(direction_) * 1.4 * a), 
                        position_.Y() + (int)(sin(direction_) * 1.4 * a)), 
                        a / 2);
 
        c1.Draw(renderer);
        c2.Draw(renderer);
    }
private:
    Point position_;
    double direction_;
    std::string name_;
    bool penDown_;

    Point defaultPosition_;
    const int a = 10;
};


#endif
