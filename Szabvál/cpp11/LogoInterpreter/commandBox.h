//
// Created by akosr on 04/05/2020.
//

#ifndef LOGO_INTERPRETER_COMMANDBOX_H
#define LOGO_INTERPRETER_COMMANDBOX_H

#include "command.h"
#include "page.h"
#include "exception.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>
#include <iostream>

class CommandBox
{
public:
    CommandBox(SDL_Renderer* renderer, SDL_Window* window) : renderer_{renderer}, window_{window}
    {
        currentCommand_ = nullptr;
    }


    Drawable* newInput(std::string input, Page* currentPage)
    {
        currentPage_ = currentPage;

        commands.push_back(input);

        try
        {
            evaluate(input);
        }catch(InvalidCommandExeption e)
        {
            throw;
        }
        return currentCommand_->execute(renderer_, window_);
    }

    void evaluate(std::string input)
    {
        if(currentCommand_ != nullptr)
            delete currentCommand_;

        std::vector<std::string> parts = split(input);
        if(parts.size() > 3 || parts.size() < 2)
            throw InvalidCommandExeption();


        try
        {
            currentCommand_ = NewCommand(parts);

        }catch(InvalidTurtleExeption e)
        {
            std::cout << e.what() << std::endl;
            throw InvalidCommandExeption();
        }


    }

    ~CommandBox()
    {
        delete currentCommand_;
    }

    void write(SDL_Renderer* renderer, char ch)const
    {
        //TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);

        //SDL_Color White = {255, 255, 255};

        //SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White);

        //SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        //SDL_Rect Message_rect;
        //Message_rect.x = 0;
        //Message_rect.y = 0;
        //Message_rect.w = 100;
        //Message_rect.h = 100;




        //SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    }
private:
    Command* NewCommand(std::vector<std::string> args)
    {
        std::string turtleName = args[0];
        Turtle& turtle = currentPage_->GetTurtle(turtleName);

        std::string commandName = args[1];

        if(args.size() == 3)
        {
            int parameter = stoi(args[2]);

            if(commandName ==  "forward")
                return new ForwardCommand(turtle, parameter);
            else if(commandName ==  "back")
                return new BackCommand(turtle, parameter);
            else if(commandName ==  "left")
                return new LeftCommand(turtle, parameter);
            else if(commandName ==  "right")
                return new RigthCommand(turtle, parameter);
        }else
        {
            if(commandName ==  "penup")
                return new PenUpCommand(turtle);
            else if(commandName ==  "pendown")
                return new PenDownCommand(turtle);
        }


        throw InvalidCommandExeption();
    }

    std::vector<std::string> commands;
    const int numOfPreviousCommands_ = 100;

    Page* currentPage_;
    Command* currentCommand_;

    SDL_Renderer* renderer_;
    SDL_Window* window_;


    std::vector<std::string> split (std::string input, std::string gap = " ")
    {
        std::vector<std::string> parts;
        std::string part;
        int end;
        int start = 0;
        while ((end = input.find (" ", start)) != std::string::npos)
        {
            part = input.substr (start, end - start);
            start = end + 1;
            parts.push_back (part);
        }

        parts.push_back (input.substr (start));

        return parts;
    }
};


#endif
