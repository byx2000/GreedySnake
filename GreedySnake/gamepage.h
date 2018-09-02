#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include "game/GreedySnakeGame.h"
#include "game/ObserverMode.h"
#include "bufferwindow.h"
#include "toastwindow.h"

class GreedySnakeGame;

namespace Ui {
class GamePage;
}

class GamePage : public QWidget, public Listener
{

    Q_OBJECT
public:
    friend class GreedySnakeGame;

    enum {STARTING, RUNNING, WAITTING, PAUSING, SPEEDCHANGED, GAMEOVER, LONGER, CONTINUE};
    explicit GamePage(GreedySnakeGame* game, QWidget *parent = 0);
    ~GamePage();
    void update(int msg);

private:
    Ui::GamePage *ui;
    BufferWindow* buffer;
    ToastWindow* toast;
    GreedySnakeGame* game;
    vector<QColor> snakeColor;
    vector<QPixmap> foodPics;
    int foodIndex;
    int timerId;
    int unit;
    void updateTitle();
    void initSnakeColor();
    void addColor();
    void updateFoodIndex();
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);
    void showEvent(QShowEvent* event);
    void moveEvent(QMoveEvent* event);
    void closeEvent(QCloseEvent *event);

private slots:
    void launchTimer();

signals:
    void moving();
    void closing();
};

#endif // GAMEPAGE_H
