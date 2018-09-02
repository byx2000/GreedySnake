#ifndef HINTPAGE_H
#define HINTPAGE_H

#include <QWidget>

namespace Ui {
class HintPage;
}

class HintPage : public QWidget
{
    Q_OBJECT

public:
    explicit HintPage(QWidget *parent = 0);
    ~HintPage();

private slots:
    void on_BackButton_clicked();

private:
    Ui::HintPage *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // HINTPAGE_H
