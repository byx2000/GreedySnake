#ifndef PAUSINGPAGE_H
#define PAUSINGPAGE_H

#include <QWidget>

namespace Ui {
class PausingPage;
}

class PausingPage : public QWidget
{
    Q_OBJECT

public:
    explicit PausingPage(QWidget *parent = 0);
    ~PausingPage();

private slots:
    void on_ContinueButton_clicked();

    void on_HintButton_clicked();

    void on_HomeButton_clicked();

private:
    Ui::PausingPage *ui;
    void showEvent(QShowEvent* event);
};

#endif // PAUSINGPAGE_H
