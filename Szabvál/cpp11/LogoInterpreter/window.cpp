//
// Created by akosr on 04/05/2020.
//

#include <iostream>
#include <memory>
#include "window.h"

enum {
    UPDATE_INTERVAL = 1000/60
    , HERO_SPEED = 2
};

void Window::start()
{
    int flags = SDL_WINDOW_SHOWN ;

    if (SDL_Init(SDL_INIT_EVERYTHING))
        return ;
    if (SDL_CreateWindowAndRenderer(width, height, flags, &window, &renderer ) )
        return;

    this->running = 1 ;
    run();
}

void Window::draw()
{

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);


    currentPage->Draw(renderer);

    SDL_RenderPresent(renderer);
}

void Window::exit()
{
    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit() ;
}




void Window::onQuit()
{
    running = 0 ;
}

void Window::run()
{
    int start = SDL_GetTicks();
    int time = start;
    SDL_Event event ;
    while ( running )
    {
        if(first)
        {

            first = false;
            for(std::string i : inputs)
            {
                std::cout << i;
                try
                {
                    currentPage->Add(commandBox->newInput(i, currentPage));
                }catch (InvalidCommandExeption e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT: onQuit();
                    break;
                case SDL_KEYDOWN: onKeyDown( &event );
                    break ;
            }
        }

        time = SDL_GetTicks() - start ;
        if ( time >= UPDATE_INTERVAL  )
        {
            update();
            draw();
        }

    }
}

void Window::update()
{
    draw();
}

void Window::onKeyDown( SDL_Event* event )
{
    commandBox = new CommandBox(renderer, window);
    char ch = (char)event->key.keysym.sym;
    if(event->key.keysym.sym == 13)
    {
        std::cout << std::endl;
        try
        {
            currentPage->Add(commandBox->newInput(input, currentPage));
        }catch (InvalidCommandExeption e)
        {
            input = "";
            std::cout << e.what() << std::endl;
        }


        input = "";
    }
    else
    {
        input += ch;
        std::cout << ch;
    }
}
