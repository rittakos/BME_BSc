//
// Created by akosr on 04/05/2020.
//

#ifndef LOGO_INTERPRETER_POINT_H
#define LOGO_INTERPRETER_POINT_H

class Point
{
public:
    Point(int x = 0, int y = 0): x_{x}, y_{y} {}

    int X() const{return x_;}
    int Y() const{return y_;}
private:
    int x_;
    int y_;
};
#endif //SDL_DEMO_POINT_H
