#include "TXLib.h"

void createSys(struct CoordSys);
void drawLine(double xscale, double yscale, double xvalues[10], double yvalues[10], CoordSys Coord);
double scale(CoordSys Coord, double yvalues[10], double xvalues[10]);
double xscale(CoordSys Coord, double xvalues[10]);
double yscale(CoordSys Coord, double yvalues[10]);
bool comp(double a, double b);

bool comp(double a, double b)
{
    return (a > b);
}

struct CoordSys
{
    int x0, y0;
    int x1, y1;
    double scalex;
};

int main()
{
    txCreateWindow(1000,600);
    txSetColor(TX_LIGHTGREEN);
    CoordSys Sys1;
    CoordSys Sys2;

    Sys1.x0 = 50;
    Sys1.y0 = 50;
    Sys1.x1 = 450;
    Sys1.y1 = 550;

    Sys2.x0 = 550;
    Sys2.y0 = 50;
    Sys2.x1 = 950;
    Sys2.y1 = 550;

    double xbblch[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    double xsltch[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    double ybblch[10] = {19.6, 93.4, 207.7, 388.2, 588.2, 889.4, 1214.8, 1517, 1975.6, 2413};
    double ysltch[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    double xbblcmp[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    double xsltcmp[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    double ybblcmp[10] = {42, 177.6, 402.5, 764.6, 1198.4, 1730.6, 2393.8, 3133.4, 3924.8, 4854.6};
    double ysltcmp[10] = {59.6, 212.1, 456.2, 811.4, 1256, 1802.4, 2459.4, 3202.2, 4048, 4979.6};

    createSys(Sys1);
    createSys(Sys2);

   // scale(Sys1,xbblch,ybblch);
    txSetColor(TX_WHITE);
    txRectangle(475, 50, 525, 550);
    RECT area = {475, 50, 525, 550};

    txSetColor(TX_LIGHTBLUE);
    drawLine(std::max(xscale(Sys1, xbblch), xscale(Sys1, xsltch), comp), std::max(yscale(Sys1, ybblch), yscale(Sys1, ysltch), comp), xbblch, ybblch, Sys1);
    drawLine(std::max(xscale(Sys2, xbblcmp), xscale(Sys2, xsltcmp), comp), std::max(yscale(Sys2, ybblcmp), yscale(Sys2, ysltcmp), comp), xbblcmp, ybblcmp, Sys2);

    txSetColor(TX_LIGHTGREEN);
    txTextOut (10, 10, "нажатие белой кнопки приведет к появлению графиков сравнения выбором");
    txTextOut (10, 20, "для завершения работы нажмите пкм");
    txTextOut (50, 50, "график обменов");
    txTextOut (550, 50, "график сравнений");

    while (txMouseButtons() != 2)     //наверное можно в отдельную функцию(?)
    {
        while ((txMouseButtons() & 1)&&(In (txMousePos(), area)))
        {
            txSetColor(TX_PINK);
            drawLine(std::max(xscale(Sys1, xbblch), xscale(Sys1, xsltch), comp), std::max(yscale(Sys1, ybblch), yscale(Sys1, ysltch), comp), xsltch, ysltch, Sys1);
            drawLine(std::max(xscale(Sys2, xbblcmp), xscale(Sys2, xsltcmp), comp), std::max(yscale(Sys2, ybblcmp), yscale(Sys2, ysltcmp), comp), xsltcmp, ysltcmp, Sys2);

            txSleep();

            txSetColor(TX_BLACK);
            drawLine(std::max(xscale(Sys1, xbblch), xscale(Sys1, xsltch), comp), std::max(yscale(Sys1, ybblch), yscale(Sys1, ysltch), comp), xsltch, ysltch, Sys1);
            drawLine(std::max(xscale(Sys2, xbblcmp), xscale(Sys2, xsltcmp), comp), std::max(yscale(Sys2, ybblcmp), yscale(Sys2, ysltcmp), comp), xsltcmp, ysltcmp, Sys2);
        }
    }
}

void createSys(CoordSys Coord)
{
    txLine(Coord.x0, Coord.y0, Coord.x0, Coord.y1);
    txLine(Coord.x0, Coord.y1, Coord.x1, Coord.y1);
}

double xscale(CoordSys Coord, double xvalues[10])
{
    return (Coord.x1 - Coord.x0)/xvalues[9];
}

double yscale(CoordSys Coord, double yvalues[10])
{
    return (Coord.y1 - Coord.y0)/yvalues[9];
}

/*double scale(CoordSys Coord, double yvalues[10], double xvalues[10])
{
    return std::max(xscale(Coord, xvalues), yscale(Coord, yvalues), comp);
} */

void drawLine(double xscale, double yscale, double xvalues[10], double yvalues[10], CoordSys Coord)
{
    int i = 0;

    for (i = 0; i < 9; i++)
    {
        txLine(xscale * xvalues[i] + Coord.x0, -yscale * yvalues[i] + Coord.y1, xscale * xvalues[i + 1] + Coord.x0, -yscale * yvalues[i + 1] + Coord.y1);
    }
}
