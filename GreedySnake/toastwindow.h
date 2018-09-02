#ifndef TOASTWINDOW_H
#define TOASTWINDOW_H

#include <QWidget>

namespace Ui {
class ToastWindow;
}

class ToastWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ToastWindow(QWidget *parent = 0);
    ~ToastWindow();

private:
    Ui::ToastWindow *ui;
    int id;
    void showEvent(QShowEvent* event);
    void timerEvent(QTimerEvent* event);
    //void closeEvent(QCloseEvent* event);
private slots:
    void moveWindow();
};

#endif // TOASTWINDOW_H
