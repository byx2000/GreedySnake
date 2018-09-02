#include "gamepage.h"
#include "ui_gamepage.h"
#include "global.h"
#include "toastwindow.h"
#include "bufferwindow.h"
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QFile>

GamePage::GamePage(GreedySnakeGame* game, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GamePage)
{
    ui->setupUi(this);
    this->game = game;

    buffer = NULL;

    //根据显示屏尺寸调节游戏窗口大小
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    unit = screenHeight / 30;
    this->setFixedSize(unit * game->spaceWidth, unit * game->spaceHeight);

    //加载食物图片
    foodPics.push_back(QPixmap(":/image/images/food1.png"));
    foodPics.push_back(QPixmap(":/image/images/food2.png"));
    foodPics.push_back(QPixmap(":/image/images/food3.png"));
    foodPics.push_back(QPixmap(":/image/images/food4.png"));
}

GamePage::~GamePage()
{
    delete ui;
    if (toast != NULL)
    {
        delete toast;
        toast = NULL;
    }
    //delete buffer;
    //delete toast;
}

void GamePage::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        game->pause();
        killTimer(timerId);
        Global::pausingPage->show();
        //Global::game->pause();
        if (buffer != NULL)
        {
            delete buffer;
            buffer = NULL;
        }

        this->close();
        break;
    case Qt::Key_Up:
        //qDebug() << "UP";
        game->changeDirection(Snake::UP);
        break;
    case Qt::Key_Down:
        //qDebug() << "DOWN";
        game->changeDirection(Snake::DOWN);
        break;
    case Qt::Key_Left:
        //qDebug() << "LEFT";
        game->changeDirection(Snake::LEFT);
        break;
    case Qt::Key_Right:
        //qDebug() << "RIGHT";
        game->changeDirection(Snake::RIGHT);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void GamePage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    int x, y;

    //draw snake
    for (int i = 0; i < game->snake->getLength(); ++i)
    {
        brush.setColor(snakeColor[i]);
        pen.setColor(snakeColor[i]);
        painter.setBrush(brush);
        painter.setPen(pen);
        x = game->snake->getSnakeNode(i).getX();
        y = game->snake->getSnakeNode(i).getY();
        painter.drawEllipse(QPoint((2 * x + 1) * unit / 2, (2 * y + 1) * unit / 2), unit / 2, unit / 2);
    }

    QColor color(255 - snakeColor[0].red(), 255 - snakeColor[0].green(), 255 - snakeColor[0].blue());
    brush.setColor(color);
    pen.setColor(color);
    painter.setBrush(brush);
    painter.setPen(pen);
    x = game->snake->getSnakeNode(0).getX();
    y = game->snake->getSnakeNode(0).getY();
    painter.drawEllipse(QPoint((2 * x + 1) * unit / 2, (2 * y + 1) * unit / 2), unit / 8, unit / 8);

    //draw food
    if (game->hasFood)
    {
        x = game->xFood;
        y = game->yFood;
        /*brush.setColor(QColor(255, 255, 255));
        pen.setColor(QColor(0, 0, 0));
        painter.setBrush(brush);
        painter.setPen(pen);
        painter.drawRect(QRect(x * unit, y * unit, unit, unit));*/
        //QPixmap pix;
        //pix.load(":/image/images/food.png");
        //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        //foodIndex = qrand() % foodPics.size();
        painter.drawPixmap(x * unit, y * unit, unit, unit, foodPics[foodIndex]);

        //this->setWindowTitle(tr("游戏进行中 长度：") + QString::number(game->snake->getLength()) + tr(" 速度：") + QString::number(160 - game->speed));
    }



}

void GamePage::update(int msg)
{
    if (msg == GamePage::STARTING)
    {
        //init timer
        if (!Global::needToShowBuffer)
            timerId = startTimer(game->speed);
        initSnakeColor();
        updateFoodIndex();

        /*if (!Global::hasPopToast)
        {
            ToastWindow* toast = new ToastWindow;
            //connect(this, SIGNAL())
            //emit launchCompleted();
            //toast->show();
            Global::hasPopToast = true;
        }*/
    }
    else if (msg == GamePage::RUNNING)
    {
        //update frame
        QWidget::update();
    }
    else if (msg == GamePage::WAITTING)
    {
        //end game, return to main frame
        game->exit();
        Global::waittingPage->show();
        this->close();
    }
    else if (msg == GamePage::PAUSING)
    {
        //pause game, show pause frame
        //game->pause();
    }
    else if (msg == GamePage::SPEEDCHANGED)
    {
        killTimer(timerId);
        timerId = startTimer(game->speed);

        updateTitle();
    }
    else if (msg == GamePage::GAMEOVER)
    {
        game->exit();

        if (game->snake->getLength() <= Global::maxLength)
        {
            QMessageBox::information(this, tr("游戏结束"), tr("Game over!\n长度:") + QString::number(game->snake->getLength()), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(this, tr("游戏结束"), tr("Game over!\n恭喜您创造了新纪录！\n长度:") + QString::number(game->snake->getLength()) + tr("\n旧纪录:") + QString::number(Global::maxLength), QMessageBox::Ok);
            QFile gameRecord("record.dat");
            gameRecord.open(QIODevice::ReadWrite);
            gameRecord.write(to_string(game->snake->getLength()).c_str());
            gameRecord.close();
            Global::maxLength = game->snake->getLength();
        }

        killTimer(timerId);

        Global::waittingPage->show();
        this->close();
    }
    else if (msg == GamePage::LONGER)
    {
        updateTitle();
        addColor();
        updateFoodIndex();
    }
    else if (msg == GamePage::CONTINUE)
    {
        Global::needToShowBuffer = true;
    }
}

void GamePage::timerEvent(QTimerEvent *event)
{
    static int i = 0;
    if (event->timerId() == timerId)
    {
        //qDebug() << "gamepage:" << i++;
        //qDebug() << "timer";
        //step game
        game->step();
    }
}

void GamePage::updateTitle()
{
    this->setWindowTitle(tr("游戏进行中 长度:") + QString::number(game->snake->getLength()) + tr(" 速度:") + QString::number(160 - game->speed));
}

void GamePage::showEvent(QShowEvent *event)
{
    updateTitle();
    if (!Global::hasPopToast)
    {
        Global::hasPopToast = true;
        toast = new ToastWindow;
        toast->show();
        connect(this, SIGNAL(moving()), toast, SLOT(moveWindow()));
        connect(this, SIGNAL(closing()), toast, SLOT(close()));
    }
    else if (Global::needToShowBuffer)
    {
        //killTimer(timerId);
        Global::needToShowBuffer = false;
        buffer = new BufferWindow;
        buffer->show();

        connect(buffer, SIGNAL(bufferComplete()), this, SLOT(launchTimer()));
        connect(this, SIGNAL(moving()), buffer, SLOT(moveWindow()));
        connect(this, SIGNAL(closing()), buffer, SLOT(close()));
    }
}

void GamePage::initSnakeColor()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    snakeColor.clear();
    for (int i = 0; i < game->snake->getLength(); ++i)
    {
        snakeColor.push_back(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
    }
}

void GamePage::addColor()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    snakeColor.push_back(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
}

void GamePage::updateFoodIndex()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    foodIndex = qrand() % foodPics.size();
}

void GamePage::launchTimer()
{
    //qDebug() << "launch timer";
    timerId = startTimer(game->speed);
    if (buffer != NULL)
    {
        delete buffer;
        buffer = NULL;
    }
}

void GamePage::moveEvent(QMoveEvent *event)
{
    //qDebug() << "move";
    emit moving();
}

void GamePage::closeEvent(QCloseEvent *event)
{
    //killTimer(timerId);
    emit closing();

}
