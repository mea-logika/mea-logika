#include "TXLib.h"
#include <cmath>

//! @file       BolotoLib.cpp
//! @brief      Библиотека для заселения болота. Выполнена в рамках КПК
//! @note       Разрешена к распространению на некоммерческой основе :)
//! @warning    Автор не несет ответственности за ошибки и с благодарностью примет рекомендации по усовершенствованию,
//!             но не гарантирует исправление.
//! @defgroup   Образы
//! @defgroup   Примеры движения
//!
//!             Рисование примитивного фона,
//!             два прямоугольника - вода и небо. Размер заполнения - все окно.
void DrawBack ( void );

//!             Рисование перепончатой лапы
//! @param      int x0, int y0 - точка привязки лапы к телу
//! @param      int Bedro, int ub длина плеча бедра и угол направления бедра
//! @param      int Golen, int ugGolen  длина плеча голени и угол направления голени
//! @param      int r, int R размерные характеристики перепонок
//!                 r - минимальное, R - самое большое, среднее растояние высчитывается как среднее арифметическое
//! @param      int uL - Направление "середины лыпы"
//! @param      int duL - угол "разброса" лапы
//! @param      COLORREF Col - Цвет закрашивания лапы,
//!             цвет границы лапы, цвет линий бедра и голени
void DrawLapa (int x0, int y0, int Bedro, int ub, int Golen, int ugGolen, int r, int R, int uL, int duL, COLORREF Col);

//!             Рисует птаху отдаленно напоминающую утку.
//! @param      int x0, int y0 - координата "пятки"
//! @param      int Wlapa, int HLapa ширина и высота лапы.
//!             Лапа сделана на основе лапы лягушки, поэтому WLapa передать значение 0
//! @param      int WBody, int HBody - ширина и высота размера тушки.
//! @param      int WHead, int HHead - ширина и высота размера головы.
//! @param      int dxHead смещение головы относительно тушки может принимать отрицательное и положительное значение
//!                        если абсолютная величина превысит половину ширины тела, голова будет "оторвана" от тушки
//! @param      COLORREF ColBird Цвет птахи. Лапы и клюв красные.
void DrawBird (int x0, int y0, int Wlapa, int HLapa, int WBody, int HBody, int WHead, int HHead, int dxHead, COLORREF ColBird);

//!              Рисует улитку
//! @param       int x0, int y0 - Центр нижней точки тела улитки.
//! @param       int dx, int dy Высота и ширина тела улиточки
//! @param       COLORREF ColBody, COLORREF ColHead Цвет тела и цвет головы улитки
void DrawUlit (int x0, int y0, int dx, int dy, COLORREF ColBody, COLORREF ColHead);

//! @param       int x0, int y0 - нижняя точка лягушки
//! @param       int WBody, int HBody ширина и высота тушки лягушки
//! @param       int WHead, int HHead ширина и высота головы лягушки
//! @param       int Reye размер глаз
//! @param       COLORREF Col цвет лягушки
void DrawFrog (int x0, int y0, int WBody, int HBody, int WHead, int HHead, int Reye, COLORREF Col);

//!              Пример движения лягушки синхронно с лапами.
//! @param       int x0, int y0 стартовое положение лягушки
//! @param       int dx, int dy вектор движдения лягушки
void MovingFrog (int x0, int y0, int dx, int dy);

//!              Пример движения улиток - как семь слоников.
//! @param       int x0, int y0 стартовое положение первой улитки
//! @param       int dx, int dy вектор движдения улиток
void MovingUlits (int x0, int y0, int dx, int dy);

//!                Вспомогательная процедура корректировки цвета.
//! @param       COLORREF Col - цвет в модели RGB
//! @param       double dCol - коэффициент изменения каждой составляющей. Если <1 - темнее,
//!                            если >1 может стать светлее, но может и "свалиться" в черный.
COLORREF Darks (COLORREF Col, double dCol);


//----------------------------------------------------------------------------------

void MovingFrog (int x0, int y0, int dx, int dy)
    {
    int x = x0;
    int y = y0;
    int t = 0;
    while ( t <= 50 )
        {
        txBegin();
        DrawBack();
        DrawFrog (x, y, 50, 80, 100, 30, 10, TX_GREEN);
        DrawLapa ( x+5, y-5,   50, 90-45-t%12*10, 50,  270-45+t%12*5, 50, 70, 0-t%12*9, 30, TX_GREEN);
        DrawLapa ( x-5, y-5,   50, 90+45+t%12*10, 50,  270+45-t%12*5, 50, 70, 180+t%12*9, 30, TX_GREEN);
        DrawLapa ( x+20, y-50, 40,     (t+4)%5*15, 40,  90+t%5*10, 20, 30,  90+t%10*4, t%4*12, TX_GREEN);
        DrawLapa ( x-20, y-50, 40, 180-(t+4)%5*15, 40,  90-t%5*10, 20, 30,  90-t%10*4, t%4*12, TX_GREEN);
        txSleep (300);
        x += dx;
        y += dy;
        t++;
        txEnd();
        }
    }
void MovingUlits (int x0, int y0, int dx, int dy)
    {
    int x;
    int y;
    int xFirst = x0;
    int yFirst = y0;
    int t = 0;
    double WBody;
    double HBody;
    COLORREF ColBody;
    COLORREF ColHead;
    int znak;
    if (dx<0) znak = -1; else znak=1;
    double posHead = 0.9;
   // txSetColor (RGB(red * 0.5, green * 0.5, blue * 0.5),2);

    while ( t <= 100 )
        {
        txBegin();
        ColBody=RGB(180, 200, 100);
        ColHead=RGB(200, 200, 10);
        WBody=50*znak;
        HBody=60;
        DrawBack();
        x=xFirst;
        y=yFirst;

        int tF=50;
        int xF=tF*5+100;
        int yF=tF*(-1) +400;
        for (int i=0; i<=6; i++)
            {
            DrawFrog (xF, yF, 50, 80, 100, 30, 10, TX_GREEN);
            DrawLapa ( xF+5, yF-5,   50, 90-45-tF%12*10, 50,  270-45+tF%12*5, 50, 70, 0-tF%12*9, 30, TX_GREEN);
            DrawLapa ( xF-5, yF-5,   50, 90+45+tF%12*10, 50,  270+45-tF%12*5, 50, 70, 180+(t+tF)%6*9, 30, TX_GREEN);
            DrawLapa ( xF+20, yF-50, 40,     (tF+4)%5*15, 40,  90+tF%5*10, 20, 30,  85+abs(5-(tF+t)%10)*10, 50, TX_GREEN);
            DrawLapa ( xF-20, yF-50, 40, 180-(tF+4)%5*15, 40,  90-tF%5*10, 20, 30,  90-tF%10*4, 50, TX_GREEN);

            DrawUlit (x, y, WBody, HBody, ColBody, ColHead);
            x -= abs(WBody)*2.5;
            WBody *= 0.9;
            HBody *= 0.9;
            ColBody = Darks(ColBody, 1.05);
            ColHead = Darks(ColHead, 0.8);
            }

        txSleep (300);
        xFirst += dx;
        yFirst += dy;
        t++;
        txEnd();
        }
    }
//--------------------------------------------------------------------
void DrawBack (void)
    {
    txSetFillColor (RGB(0, 0, 255));
    txRectangle(0, 0, txGetExtentX(), txGetExtentY() / 4);
    txSetFillColor (RGB(0, 200, 200));
    txRectangle ( 0, txGetExtentY() / 4, txGetExtentX(), txGetExtentY() );
    DrawOblako (100, 20, 5);
    }

void DrawUlit (int x0, int y0, int dx, int dy, COLORREF ColBody, COLORREF ColHead)

    {
    txSetColor (ColBody);
    txSetFillColor (ColBody);
    txPie (x0-dx, y0-dy, x0+dx, y0+dy, 0, 180);
    txSetColor (ColHead);
    txSetFillColor (ColHead);
    txArc (x0+dx/2, y0-dy, x0+dx*3/2, y0, 180, 180);
    txArc (x0+dx/2, y0-dy/2+dy/5, x0+dx*3/2,y0-dy/2-dy/5 , 180, 180);
    txFloodFill(x0+dx+dx/10, y0-dy/4);
    txFloodFill(x0+dx-dx/10, y0-dy/4);
    txPie (x0+dx/2-dx/10, y0-dy/2-dx/10, x0+dx/2+dx/10, y0-dy/2+dx/10, 0, 360);
    txPie (x0+dx*3/2-dx/10, y0-dy/2-dx/10, x0+dx*3/2+dx/10, y0-dy/2+dx/10, 0, 360);
    }

void DrawBird (int x0, int y0, int WLapa, int HLapa, int WBody, int HBody, int WHead, int HHead, int dxHead, COLORREF ColBird)
    {
    int znak = 1;
    double posHead = 0.75;
    if (dxHead<0)
        {
        znak = -1;
        }

    DrawLapa (x0, y0-HLapa, HLapa, 270, 0, 0, HBody/4, WBody/4, 90-znak*90, 50, RGB(255,0,0));

    txSetColor (Darks(ColBird, 0.5),1);
    txSetFillColor (ColBird);

    txEllipse (x0-WBody / 2, y0-HLapa , x0+WBody / 2, y0-HLapa-HBody);
    txEllipse (x0+dxHead+WHead/2, y0-HLapa-HBody*posHead, x0+dxHead-WHead/2, y0-HLapa-HBody*posHead-HHead);
    txSetColor (RGB(0, 0, 0), 2);
    txSetFillColor (RGB(255,255,255));
    txEllipse ( x0+dxHead+znak*(0.1*WHead), y0-HLapa-HBody*posHead-HHead*0.5, x0+dxHead+znak*(0.25*WHead), y0-HLapa-HBody*posHead-0.7*HHead );
    txSetColor (RGB(255,0,0), 2);
    txSetFillColor (RGB(255, 0,0));
    POINT Nose[4] = {{x0+dxHead+znak*WHead/2, y0-HLapa-HBody*posHead-HHead*0.5},
                     {x0+dxHead+znak*(WHead/2+WHead*0.1), y0-HLapa-HBody*posHead-HHead*0.5-HHead/5},
                     {x0+dxHead+znak*(WHead/2-WHead*0.2), y0-HLapa-HBody*posHead-HHead*0.5},
                     {x0+dxHead+znak*(WHead/2+WHead*0.1), y0-HLapa-HBody*posHead-HHead*0.5+HHead/5}
                     };
    txPolygon (Nose, 4);

    }
void DrawLapa (int x0, int y0,
               int Bedro, int ub,
               int Golen, int ugGolen,
               int r, int R,
               int uL, int duL,
               COLORREF Col)


{
    #define PiGr 3.14159265/180

    double AngleFin = uL + duL/2;
    double AngleStart = uL - duL/2;
    double al = duL /4;

    int red = txExtractColor (Col, TX_RED);
    int green = txExtractColor (Col, TX_GREEN);
    int blue = txExtractColor (Col, TX_BLUE);

    txSetColor (RGB(red * 0.5, green * 0.5, blue * 0.5),3);
    txSetFillColor (Col);

    int xk = x0 + Bedro*cos(ub*PiGr);
    int yk = y0 - Bedro*sin(ub*PiGr);
    txLine(x0, y0, xk, yk);
    int xs = xk + Golen*cos(ugGolen*PiGr);
    int ys = yk - Golen*sin(ugGolen*PiGr);
    txLine(xk, yk, xs, ys);

    txSetColor (RGB(red * 0.5, green * 0.5, blue * 0.5),1);

    POINT Lap[6];
    Lap[0].x = xs;
    Lap[0].y = ys;
    Lap[1].x = xs + (R+r)/2*cos(AngleStart * PiGr);
    Lap[1].y = ys - (R+r)/2*sin(AngleStart * PiGr);
    Lap[2].x = xs + r*cos((AngleStart+al) * PiGr);
    Lap[2].y = ys - r*sin((AngleStart+al) * PiGr);
    Lap[3].x = xs + R*cos((AngleStart+2*al) * PiGr);
    Lap[3].y = ys - R*sin((AngleStart+2*al) * PiGr);
    Lap[4].x = xs + r*cos((AngleStart+al*3) * PiGr);
    Lap[4].y = ys - r*sin((AngleStart+al*3) * PiGr);
    Lap[5].x = xs + (R+r)/2*cos(AngleFin * PiGr);
    Lap[5].y = ys - (R+r)/2*sin(AngleFin * PiGr);
    txPolygon (Lap, 6);

    }

void DrawFrog (int x0, int y0, int WBody, int HBody, int WHead, int HHead, int Reye, COLORREF Col)
    {

    double posHead = 0.9;
    txSetColor (Darks(Col, 0.5),2);
    txSetFillColor (Col);

    txEllipse(x0-WBody/2, y0, x0+WBody/2, y0-HBody);
    txEllipse(x0-WHead/2, y0-HBody*posHead, x0+WHead/2, y0-HBody*posHead-HHead);

    txEllipse(x0-WHead*0.4, y0-HBody*posHead-HHead*0.7, x0-WHead*0.1, y0-HBody*posHead-HHead*0.7-WHead*0.2);
    txEllipse(x0+WHead*0.4, y0-HBody*posHead-HHead*0.7, x0+WHead*0.1, y0-HBody*posHead-HHead*0.7-WHead*0.2);

    }

COLORREF Darks(COLORREF Col, double dCol)
    {
    int red = txExtractColor (Col, TX_RED);
    int green = txExtractColor (Col, TX_GREEN);
    int blue = txExtractColor (Col, TX_BLUE);
    return RGB(red*dCol, green*dCol, blue*dCol);

    }

