//
// Created by akosr on 04/05/2020.
//

#ifndef LOGO_INTERPRETER_COMMANDBOX_H
#define LOGO_INTERPRETER_COMMANDBOX_H

#include <SDL.h>
#include <memory>
#include <vector>

#include "command.h"
#include "page.h"
#include "exception.h"

class CommandBox
{
public:
    CommandBox(SDL_Renderer* renderer, SDL_Window* window) : renderer_{renderer}, window_{window}
    {
        currentCommand_ = nullptr;
    }


    std::shared_ptr<Drawable> newInput(std::string input, std::shared_ptr<Page> currentPage)
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

   

private:
    void evaluate(std::string input)
    {
        std::vector<std::string> parts = split(input);


        try
        {
            currentCommand_ = NewCommand(parts);

        }
        catch (InvalidTurtleExeption e)
        {
            std::cout << e.what() << " <-- ";
            throw InvalidCommandExeption();
        }
    }

    std::shared_ptr<Command> NewCommand(std::vector<std::string> args)
    {
        
        if (args.size() == 1)
        {
            if (args[0] == "clear")
            {
                return std::make_shared<ClearCommand>(ClearCommand(currentPage_));
            }
            else
                throw InvalidCommandExeption();

        }

        std::string turtleName = args[0];
        std::shared_ptr<Turtle> turtle = currentPage_->GetTurtle(turtleName);

        std::string commandName = args[1];

        if(args.size() == 3)
        {
            int parameter = stoi(args[2]);

            if(commandName ==  "forward")
                return std::make_shared<ForwardCommand>(ForwardCommand(turtle, parameter));
            else if(commandName ==  "back")
                return std::make_shared<BackCommand>(BackCommand(turtle, parameter));
            else if(commandName ==  "left")
                return std::make_shared<LeftCommand>(LeftCommand(turtle, parameter));
            else if(commandName ==  "right")
                return std::make_shared<RigthCommand>(RigthCommand(turtle, parameter));
        }else
        {
            if(commandName ==  "penup")
                return std::make_shared<PenUpCommand>(PenUpCommand(turtle));
            else if(commandName ==  "pendown")
                return std::make_shared<PenDownCommand>(PenDownCommand(turtle));
        }


        throw InvalidCommandExeption();
    }

    std::vector<std::string> commands;
    const int numOfPreviousCommands_ = 100;

    std::shared_ptr<Page> currentPage_;
    std::shared_ptr<Command> currentCommand_;

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
