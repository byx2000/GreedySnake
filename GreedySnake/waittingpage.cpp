#include "waittingpage.h"
#include "ui_waittingpage.h"
#include "hintpage.h"
#include "global.h"
#include <QMessageBox>

WaittingPage::WaittingPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaittingPage)
{
    ui->setupUi(this);

    this->setFixedSize( this->width(),this->height());

    //Global::lastPage = this;
}

WaittingPage::~WaittingPage()
{
    delete ui;
}

void WaittingPage::on_StartButton_clicked()
{
    //start game
    Global::game->initGame();
    Global::game->start();
    Global::gamePage->show();
    this->close();

}

void WaittingPage::on_HintButton_clicked()
{
    Global::hintPage->show();
    this->close();
}

void WaittingPage::on_AboutButton_clicked()
{
    Global::aboutPage->show();
    this->close();
}

void WaittingPage::on_ExitButton_clicked()
{
    this->close();
}

void WaittingPage::showEvent(QShowEvent* event)
{
    Global::lastPage = this;
}

void WaittingPage::on_RecordButton_clicked()
{
    QMessageBox::information(this, tr("记录"), tr("最大长度：") + QString::number(Global::maxLength), QMessageBox::Ok);
}
