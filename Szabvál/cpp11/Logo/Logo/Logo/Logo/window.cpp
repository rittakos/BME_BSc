//
// Created by akosr on 04/05/2020.
//
#include "window.h"

void Window::start()
{
    std::cout << "--program started" << std::endl;

    try
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_CreateWindowAndRenderer(width_, height_, SDL_WINDOW_SHOWN, &window, &renderer);
        TTF_Init();
    }
    catch (...)
    {
        exit();
    }

    this->running = true;
    run();
}

void Window::run()
{
    int start = SDL_GetTicks();
    int time = start;
    SDL_Event event ;
    while ( running )
    {
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
        if ( time >= 1000 / 60  )
        {
            update();
        }

    }
}


void Window::draw()
{
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    currentPage_->Draw(renderer);

    SDL_RenderPresent(renderer);
}

void Window::write(std::string string, Point pos)
{
    if (string == "")
        return;

    SDL_Color black = {0, 0, 0, 255};

    TTF_Font *font = TTF_OpenFont("arial.ttf", 32);
    if (!font) 
        return;

    
    SDL_Rect rect = { 0, 0, 0, 0 };

    
    text = TTF_RenderUTF8_Solid(font, string.c_str(), black);
    textTexture = SDL_CreateTextureFromSurface(renderer, text);

    rect.x = pos.X();
    rect.y = pos.Y();
    rect.w = text->w;
    rect.h = text->h;
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);
    

    SDL_RenderPresent(renderer);
    for (int i = 0; i < 25000000; ++i);
    
    TTF_CloseFont(font);

}


void Window::update()
{
    draw();
    write(input);
}


void Window::onKeyDown( SDL_Event* event )
{
    commandBox = std::make_shared<CommandBox>(CommandBox(renderer, window));
    char ch = (char)event->key.keysym.sym;
    if(event->key.keysym.sym == 13)
    {
        try
        {
            currentPage_->Add(commandBox->newInput(input, currentPage_));
        }catch (InvalidCommandExeption e)
        {
            inputIsException = true;
            input = e.what();
            std::cout << input << std::endl;
        }
        if(!inputIsException)
            input = "";
    }
    else if (event->key.keysym.sym == 8)
    {
        if(input.size() > 0 && !inputIsException)
            input.pop_back();
    }
    else if (event->key.keysym.sym == 1073742053)
    {
        shift = true;
    }
    else
    {
        if (inputIsException)
        {
            input = "";
            inputIsException = false;
        }

        if (shift)
        {
            ch = toupper(ch);
            shift = false;
        }

        input += ch;
    }
}

void Window::onQuit()
{
    running = false;
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
    if (text != nullptr)
    {
        SDL_FreeSurface(text);
        text = nullptr;
    }
    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }

    std::cout << "--program closed" << std::endl;


    TTF_Quit();
    SDL_Quit() ;
}