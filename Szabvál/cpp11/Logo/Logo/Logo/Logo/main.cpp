#include "window.h"


//Parancsok:
//
//t1 forward parameter : eloremegy a parameterul kapott pixelnyit
//t1 back parameter : hatramegy a parameterul kapott pixelnyit
//t1 left parameter : balra fordul a parameterul kapott szognyit
//t1 right parameter : jobbra fordul a parameterul kapott szognyit
//
//t1 penup : nem rajzol csak mozog
//t2 pendown : rajzol amikor mozog
//
//clear: torli a kirajzolt dolgokat
//


int main(int argc, char** argv)
{
    std::cout
        << "Parancsok:                                                       " << std::endl
        << "t1 forward parameter : eloremegy a parameterul kapott pixelnyit  " << std::endl
        << "t1 back parameter : hatramegy a parameterul kapott pixelnyit     " << std::endl
        << "t1 left parameter : balra fordul a parameterul kapott szognyit   " << std::endl
        << "t1 right parameter : jobbra fordul a parameterul kapott szognyit " << std::endl
        << "                                                                 " << std::endl
        << "t1 penup : nem rajzol csak mozog                                 " << std::endl
        << "t2 pendown : rajzol amikor mozog                                 " << std::endl
        << "                                                                 " << std::endl
        << "clear: torli a kirajzolt dolgokat                                " << std::endl
        << "-----------------------------------------------------------------" << std::endl
        << std::endl;

    Window window;


    return 0;
}


