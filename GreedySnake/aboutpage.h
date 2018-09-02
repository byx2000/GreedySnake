#ifndef ABOUTPAGE_H
#define ABOUTPAGE_H

#include <QWidget>

namespace Ui {
class AboutPage;
}

class AboutPage : public QWidget
{
    Q_OBJECT

public:
    explicit AboutPage(QWidget *parent = 0);
    ~AboutPage();

private slots:
    void on_BackButton_clicked();

private:
    Ui::AboutPage *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // ABOUTPAGE_H
