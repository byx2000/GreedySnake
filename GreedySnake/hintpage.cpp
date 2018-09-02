#include "hintpage.h"
#include "ui_hintpage.h"
#include "global.h"

HintPage::HintPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HintPage)
{
    ui->setupUi(this);

    this->setFixedSize( this->width(),this->height());
}

HintPage::~HintPage()
{
    delete ui;
}

void HintPage::on_BackButton_clicked()
{
    Global::lastPage->show();
    this->close();
}

void HintPage::closeEvent(QCloseEvent *event)
{
    on_BackButton_clicked();
}
