#include "GamePainter.h"
#include "global.h"
#include <QApplication>
#include <QPainter>

GamePainter::GamePainter(const GreedySnakeGame* game) : game(game){}
GamePainter::GamePainter(){}
/*void GamePainter::update(int msg)
{
    //QPainter painter(Global::gamePage);
    switch (msg)
    {
    case WAITTING_FRAME:
        //Global::waittingPage->show();
        break;
    case RUNNING_FRAME:
        //QApplication::beep();
        //painter.drawLine(QPoint(0, 0), QPoint(100, 100));
        break;
    case PAUSING_FRAME:

        break;
    }
}*/
