//
// Created by akosr on 04/05/2020.
//

#ifndef LOGO_INTERPRETER_WINDOW_H
#define LOGO_INTERPRETER_WINDOW_H

#include <vector>
#include <memory>
#include <cstdio>
#include <SDL.h>
#include <SDL_ttf.h>

#include "page.h"
#include "commandBox.h"

class Window
{
public:
    void start();
    void run();
    void exit() ;

    void onQuit();
    void onKeyDown( SDL_Event* event );

    void draw();
    void write(std::string c, Point pos = Point(5, 0));
    void update();


    Window(int width = 1000, int height = 600)
        : running{ false }, window{ nullptr }, renderer{ nullptr }, width_{ width }, height_{height}
    {
        currentPage_ = std::make_shared<Page>(Page("p1", width_, height_));
        pages.push_back(currentPage_);
        this->start();
    }

    ~Window()
    {
        this->exit();
    }
private:
    std::vector<std::shared_ptr<Page>> pages;
    std::shared_ptr<Page> currentPage_;

    std::string input = "";
    std::shared_ptr<CommandBox> commandBox;

    int width_;
    int height_;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Surface* text;
    SDL_Texture* textTexture;

    bool running;

    bool shift = false;
    bool inputIsException = false;
};


#endif
