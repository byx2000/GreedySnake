#include "toastwindow.h"
#include "ui_toastwindow.h"
#include "global.h"
#include <QPropertyAnimation>

ToastWindow::ToastWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToastWindow)
{
    ui->setupUi(this);

    //connect(Global::gamePage, SIGNAL(launchCompleted()), this, SLOT(show()));

    //去掉标题栏
    setWindowFlags(Qt::FramelessWindowHint);

    //设置窗口始终在最前
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    //设置窗口不获取焦点
    setAttribute(Qt::WA_ShowWithoutActivating,true);

    //设置窗口大小
    resize(Global::gamePage->width(), Global::gamePage->height());

    //调整窗口位置
    //QPoint p = Global::gamePage->mapToGlobal(QPoint(0, 0));
    //move(Global::gamePage->geometry().x(), Global::gamePage->geometry().y());
}

ToastWindow::~ToastWindow()
{
    delete ui;
}

void ToastWindow::showEvent(QShowEvent *event)
{
    //qDebug() << "show";

    //Global::father->setFocus();

    moveWindow();

    //设置透明度
    //setWindowOpacity(0.5);
    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(0.5);
    //Sleep(1000);
    animation->start();


    //设置背景色
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);

    //设置字体颜色
    pal.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(pal);

    //启动计时器
    id = startTimer(2500);
}

void ToastWindow::timerEvent(QTimerEvent *event)
{
    killTimer(id);
    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0.5);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
    //close();
}

void ToastWindow::moveWindow()
{
    //调整窗口位置
    move(Global::gamePage->geometry().x(), Global::gamePage->geometry().y());
}
