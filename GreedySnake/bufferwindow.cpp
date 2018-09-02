#include "bufferwindow.h"
#include "ui_bufferwindow.h"
#include "global.h"
#include <QPropertyAnimation>
#include <QDebug>
#include <QCloseEvent>

BufferWindow::BufferWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BufferWindow)
{
    ui->setupUi(this);

    //去掉标题栏
    setWindowFlags(Qt::FramelessWindowHint);

    //设置窗口始终在最前
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    //设置窗口不获取焦点
    setAttribute(Qt::WA_ShowWithoutActivating,true);

    //设置窗口大小
    resize(Global::gamePage->width(), Global::gamePage->height());
}

BufferWindow::~BufferWindow()
{
    delete ui;
}

void BufferWindow::showEvent(QShowEvent *event)
{
    moveWindow();

    //设置透明度
    setWindowOpacity(0.3);

    //设置背景色
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);

    //设置字体颜色
    pal.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(pal);

    //启动计时器
    id = startTimer(1000);
    cnt = 1;

}

void BufferWindow::timerEvent(QTimerEvent *event)
{
    static int i = 0;
    //qDebug() << "buffer:" << i++;
    if (cnt != 3)
    {
        ui->label->setText(QString::number(3 - cnt));
        cnt++;
    }
    else
    {
        killTimer(id);
        ui->label->setText(QString::number(0));
        QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(1000);
        //animation->setStartValue(0.5);
        animation->setEndValue(0);
        animation->start();
        connect(animation, SIGNAL(finished()), this, SLOT(close()));
    }
}

void BufferWindow::closeEvent(QCloseEvent *event)
{
    //qDebug() << "close";
    //killTimer(id);
    if (Global::gamePage->isVisible())
    emit bufferComplete();

    //event->accept();
}

void BufferWindow::moveWindow()
{
    //调整窗口位置
    move(Global::gamePage->geometry().x(), Global::gamePage->geometry().y());
}
