//
// Created by akosr on 05/05/2020.
//

#ifndef LOGO_INTERPRETER_COMMAND_H
#define LOGO_INTERPRETER_COMMAND_H


#include "line.h"
#include "turtle.h"
#include "page.h"


class Command
{
public:
    Command()
    {

    }

    virtual std::shared_ptr<Drawable> execute (SDL_Renderer* renderer, SDL_Window* window) = 0;
    virtual ~Command() = default;


    std::string Name() const { return  name_; }
protected:
    std::string name_;
private:

};


class ForwardCommand final : public Command
{
public:
    ForwardCommand(std::shared_ptr<Turtle> turtle, int parameter) : turtle_{turtle}, parameter_{parameter}
    {
        name_ = "forward";
    }

    std::shared_ptr<Drawable> execute(SDL_Renderer* renderer, SDL_Window* window) override
    {
        Point begin = turtle_->Position();

        turtle_->Position() = Point(begin.X() + (int)(cos(turtle_->Direction()) * parameter_),
            begin.Y() + (int)(sin(turtle_->Direction()) * parameter_));

        if(turtle_->PenDown())
            return std::make_shared<Line>(Line(begin, turtle_->Direction(), parameter_));
        return nullptr;
    }
private:
    int parameter_;
    std::shared_ptr<Turtle> turtle_;
};

class BackCommand final : public Command
{
public:
    BackCommand(std::shared_ptr<Turtle> turtle, int parameter) : turtle_{turtle}, parameter_{parameter}
    {
        name_ = "back";
    }

    std::shared_ptr<Drawable> execute(SDL_Renderer* renderer, SDL_Window* window) override
    {
        Point begin = turtle_->Position();

        turtle_->Position() = Point(begin.X() - (int)(cos(turtle_->Direction()) * parameter_),
            begin.Y() - (int)(sin(turtle_->Direction()) * parameter_));

        if(turtle_->PenDown())
            return std::make_shared<Line>(Line(begin, turtle_->Direction() + M_PI, parameter_));
        return nullptr;
    }
private:
    Point begin;

    std::shared_ptr<Turtle> turtle_;
    int parameter_;
};


class RigthCommand final : public Command
{
public:
    RigthCommand(std::shared_ptr<Turtle> turtle, int parameter) : turtle_{ turtle }, parameter_{ parameter }
    {
        name_ = "back";
    }

    std::shared_ptr<Drawable> execute(SDL_Renderer* renderer, SDL_Window* window) override
    {
        double convertedParameter = parameter_ * (M_PI / (double)180);

        turtle_->Direction() += convertedParameter;

        double d = turtle_->Direction();
        turtle_->Direction() -= floor(d / 2 * M_PI) * 2 * M_PI;

        return nullptr;
    }
private:
    std::shared_ptr<Turtle> turtle_;
    int parameter_;
};

class LeftCommand final : public Command
{
public:
    LeftCommand(std::shared_ptr<Turtle> turtle, int parameter) : turtle_{ turtle }, parameter_{ parameter }
    {
        name_ = "back";
    }

    std::shared_ptr<Drawable> execute(SDL_Renderer* renderer, SDL_Window* window) override
    {
        double convertedParameter = parameter_ * (M_PI / (double)180);

        turtle_->Direction() -= convertedParameter;

        double d = turtle_->Direction();
        turtle_->Direction() -= floor(d / 2 * M_PI) * 2 * M_PI;

        return nullptr;
    }
private:
    std::shared_ptr<Turtle> turtle_;
    int parameter_;
};


class PenDownCommand final : public  Command
{
public:
    PenDownCommand(std::shared_ptr<Turtle> turtle) : turtle_{turtle}
    {
        name_ = "pendown";
    }

    std::shared_ptr<Drawable> execute(SDL_Renderer* renderer, SDL_Window* window) override 
    {
        turtle_->PenDown() = true;
        return nullptr;
    }
private:
    std::shared_ptr<Turtle> turtle_;
};

class PenUpCommand final : public  Command
{
public:
    PenUpCommand(std::shared_ptr<Turtle> turtle) : turtle_{turtle}
    {
        name_ = "penup";
    }

    std::shared_ptr<Drawable> execute(SDL_Renderer* renderer, SDL_Window* window) override 
    {
        turtle_->PenDown() = false;
        return nullptr;
    }
private:
    std::shared_ptr<Turtle> turtle_;
};


class ClearCommand final : public  Command
{
public:
    ClearCommand(std::shared_ptr<Page> page) : page_{ page }
    {
        name_ = "clear";
    }

    std::shared_ptr<Drawable> execute(SDL_Renderer* renderer, SDL_Window* window) override
    {
        page_->Clear();
        return nullptr;
    }
private:
    std::shared_ptr<Page> page_;
};

#endif
