#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct Point
{
    double x;
    double y;
}Point;
typedef struct Circle
{

}Circle;
void MakeSvgDatas(FILE* file, double version, double height, double width, char* xmlns, char* color)
{
    fprintf(file, "<svg width=\"%f\" height=\"%f\" xmlns=\"%s\" version=\"%f\" style=\"background: %s\">\n", width, height, xmlns, version, color);
    //fprint(file, "sfd");
}
void DrawCircle(FILE* file, Point poz, double r)
{
    fprintf(file, "<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke-width=\"%d\" stroke=\"%s\" fill=\"%s\"/>\n", poz.x, poz.y, r, 5, "black", "black");
}
void DrawLine()
{

}
void DrawRecktangle()
{

}
void DrawPig()
{

}
void DrawBird()
{

}
int main()
{
    const double pi = 3.14159265359;
    const double g = 9.81;

    FILE* file;
    const double version = 1.1;
    const double height = 600;
    const double width = 600    ;
    char* xmlns = "http://www.w3.org/2000/svg";
    char* backgroundColor = "#00ffff";

    Point poz = {100, 100};
    file = fopen("csirke.svg", "w");
    MakeSvgDatas(file, version, height, width, xmlns, backgroundColor);
    //DrawCircle(file, poz, 50);
    fprintf(file, "</svg>");

    fclose(file);


    return 0;
}
