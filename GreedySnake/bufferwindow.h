#ifndef BUFFERWINDOW_H
#define BUFFERWINDOW_H

#include <QWidget>

namespace Ui {
class BufferWindow;
}

class BufferWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BufferWindow(QWidget *parent = 0);
    ~BufferWindow();

private:
    Ui::BufferWindow *ui;
    int cnt;
    int id;
    void showEvent(QShowEvent* event);
    void timerEvent(QTimerEvent* event);
    void closeEvent(QCloseEvent* event);

signals:
    void bufferComplete();

private slots:
    void moveWindow();
};

#endif // BUFFERWINDOW_H
