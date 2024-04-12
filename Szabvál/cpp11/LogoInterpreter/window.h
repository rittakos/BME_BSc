//
// Created by akosr on 04/05/2020.
//

#ifndef LOGO_INTERPRETER_WINDOW_H
#define LOGO_INTERPRETER_WINDOW_H

#include <SDL2/SDL.h>
#include <vector>
#include <fstream>
#include <memory>
#include "page.h"
#include "commandBox.h"
#include <cstdio>
#include <map>
#include "SDL2/SDL_ttf.h"


class Window
{
public:
    void start();
    void exit() ;
    void draw();

    void onQuit();
    void onKeyDown( SDL_Event* event );
    void run();
    void update();

    Window(): running(0), window(nullptr), renderer(nullptr)
    {
        Page* firstPage = new Page();
        currentPage = firstPage;
        pages.push_back(firstPage);
        this->start();
    }

    ~Window()
    {
        this->exit();
    }
private:
    void Read(std::string fileName)
    {
        std::string line;
        std::ifstream myfile(fileName);
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                inputs.push_back(line);
            }
            myfile.close();
        }
        else
            std::cout << "Unsuccesfull reading." << std::endl;
    }

    std::vector<Page*> pages;
    Page* currentPage;
    std::string input = "";
    CommandBox* commandBox;

    std::vector<std::string> inputs;

    int width = 1000;
    int height = 600;

    SDL_Window* window;
    SDL_Renderer* renderer;

    int running ;
    bool first = true;


};


#endif
