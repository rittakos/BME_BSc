//
// Created by akosr on 05/05/2020.
//

#ifndef LOGO_INTERPRETER_EXCEPTION_H
#define LOGO_INTERPRETER_EXCEPTION_H

#include <exception>

class InvalidCommandExeption : public std::exception
{
public:
    virtual const char* what() const noexcept
    {
        return "Invalid command;";
    }
};

class InvalidTurtleExeption : public std::exception
{
public:
    virtual const char* what() const noexcept
    {
        return "Invalid turtle;";
    }
};
#endif //LOGO_INTERPRETER_EXCEPTION_H
