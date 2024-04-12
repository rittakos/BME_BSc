//
// Created by akosr on 05/05/2020.
//

#ifndef SDL_DEMO_COMMAND_H
#define SDL_DEMO_COMMAND_H

#include <string>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "line.h"
#include "turtle.h"


class Command
{
public:
    Command()
    {

    }

    virtual Drawable* execute(SDL_Renderer* renderer, SDL_Window* window) = 0;
    virtual ~Command() = default;


    std::string Name(){ return  name; }
protected:
    std::string name;
private:

};


class ForwardCommand final : public Command
{
public:
    ForwardCommand(Turtle& turtle, int parameter) : turtle_{turtle}, parameter_{parameter}
    {

        name = "forward";
        begin = turtle.Position();

        turtle.Position() = Point(begin.X() + cos(turtle_.Direction()) * parameter_,
                                  begin.Y() + sin(turtle_.Direction()) * parameter_);
    }
    Drawable* execute(SDL_Renderer* renderer, SDL_Window* window) override
    {
        Line* l = nullptr;
        if(!turtle_.PenDown())
            l = new Line(begin.X(), begin.Y(), turtle_.Direction(), parameter_);
        return l;
    }
private:
    Point begin;

    int parameter_;
    Turtle turtle_;
};

class BackCommand final : public Command
{
public:
    BackCommand(Turtle& turtle, int parameter) : turtle_{turtle}, parameter_{parameter}
    {
        name = "back";

        begin = turtle.Position();

        turtle.Position() = Point(begin.X() - cos(turtle_.Direction()) * parameter_,
                                  begin.Y() - sin(turtle_.Direction()) * parameter_);

    }
    Drawable* execute(SDL_Renderer* renderer, SDL_Window* window) override
    {
        Line* l = nullptr;
        if(!turtle_.PenDown())
            l = new Line(begin.X(), begin.Y(), turtle_.Direction() + M_PI, parameter_);
        return l;
    }
private:
    Point begin;

    Turtle turtle_;
    int parameter_;
};


class RigthCommand final : public Command
{
public:
    RigthCommand(Turtle& turtle, int parameter)
    {
        name = "back";
        float convertedParameter = parameter * (M_PI / (double)180);

        turtle.Direction() += convertedParameter;

        float d = turtle.Direction();
        turtle.Direction() -= floor(d / 2*M_PI) * 2 * M_PI;
    }
    Drawable* execute(SDL_Renderer* renderer, SDL_Window* window) override
    {
        return nullptr;
    }
};

class LeftCommand final : public Command
{
public:
    LeftCommand(Turtle& turtle, int parameter)
    {
        name = "back";
        float convertedParameter = parameter * (M_PI / (double)180);

        turtle.Direction() -= convertedParameter;

        float d = turtle.Direction();
        turtle.Direction() -= floor(d / 2*M_PI) * 2 * M_PI;
    }
    Drawable* execute(SDL_Renderer* renderer, SDL_Window* window) override
    {
        return nullptr;
    }
};



class PenDownCommand final : public  Command
{
public:
    PenDownCommand(Turtle& turtle)
    {
        name = "pendown";
        turtle.PenDown() = true;
    }

    Drawable* execute(SDL_Renderer* renderer, SDL_Window* window) override {
        return nullptr;
    }
};

class PenUpCommand final : public  Command
{
public:
    PenUpCommand(Turtle& turtle)
    {
        name = "penup";
        turtle.PenDown() = false;
    }

    Drawable* execute(SDL_Renderer* renderer, SDL_Window* window) override {
        return nullptr;
    }
};

#endif //SDL_DEMO_COMMAND_H
