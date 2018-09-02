#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include "waittingpage.h"
#include "hintpage.h"
#include "aboutpage.h"
#include "gamepage.h"
#include "pausingpage.h"
#include "global.h"
#include "game/GreedySnakeGame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QFileInfo inf("record.dat");
    if (inf.exists()) //文件存在
    {
        //qDebug() << QObject::tr("文件存在");
        QFile gameRecord("record.dat");
        gameRecord.open(QIODevice::ReadWrite);
        QTextStream in(&gameRecord);
        if (!in.atEnd())
        {
            QString line = in.readLine();
            Global::maxLength = line.toInt();
            //qDebug() << Global::maxLength;
        }
        else
        {
            Global::maxLength = 5;
            //qDebug() << QObject::tr("文件为空");
            //Global::maxLength = 5;
            gameRecord.write("5");
        }
        gameRecord.close();
    }
    else //文件不存在
    {
        //qDebug() << QObject::tr("文件不存在");
        QFile gameRecord("record.dat");
        gameRecord.open(QIODevice::ReadWrite);
        gameRecord.write("5");
        Global::maxLength = 0;
        gameRecord.close();
    }

    Global::hasPopToast = false;
    Global::needToShowBuffer = false;

    //init game data
    Global::game = new GreedySnakeGame(20, 20, 5);
    Global::game->setCurrentState(Global::game->getWaittingForStartStatus());

    //init all windows
    Global::waittingPage = new WaittingPage;
    Global::hintPage = new HintPage;
    Global::aboutPage = new AboutPage;
    Global::gamePage = new GamePage(Global::game);
    Global::pausingPage = new PausingPage;

    Global::game->registerGamePage(Global::gamePage);

    Global::waittingPage->show();

    //game.start();

    return a.exec();
}
