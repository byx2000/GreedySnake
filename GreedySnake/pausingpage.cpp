#include "pausingpage.h"
#include "ui_pausingpage.h"
#include "global.h"
#include <QMessageBox>

PausingPage::PausingPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PausingPage)
{
    ui->setupUi(this);

    this->setFixedSize( this->width(),this->height());

    setWindowFlags(Qt::WindowMinimizeButtonHint);
}

PausingPage::~PausingPage()
{
    delete ui;
}

void PausingPage::on_ContinueButton_clicked()
{
    Global::game->start();
    Global::gamePage->show();
    this->close();
}

void PausingPage::on_HintButton_clicked()
{
    Global::hintPage->show();
    this->close();
}

void PausingPage::on_HomeButton_clicked()
{
    int ret = QMessageBox::question(this, tr("返回主界面"), tr("是否退出游戏？"), QMessageBox::Yes, QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        Global::game->exit();
        Global::waittingPage->show();
        this->close();
    }
}

void PausingPage::showEvent(QShowEvent *event)
{
    Global::lastPage = this;
}
