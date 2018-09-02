#include "aboutpage.h"
#include "ui_aboutpage.h"
#include "global.h"

AboutPage::AboutPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutPage)
{
    ui->setupUi(this);

    this->setFixedSize( this->width(),this->height());
}

AboutPage::~AboutPage()
{
    delete ui;
}

void AboutPage::on_BackButton_clicked()
{
    Global::lastPage->show();
    this->close();
}

void AboutPage::closeEvent(QCloseEvent *event)
{
    on_BackButton_clicked();
}
