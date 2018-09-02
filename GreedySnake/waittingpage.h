#ifndef WAITTINGPAGE_H
#define WAITTINGPAGE_H

#include <QWidget>

namespace Ui {
class WaittingPage;
}

class WaittingPage : public QWidget
{
    Q_OBJECT

public:
    explicit WaittingPage(QWidget *parent = 0);
    ~WaittingPage();

private slots:
    void on_StartButton_clicked();

    void on_HintButton_clicked();

    void on_AboutButton_clicked();

    void on_ExitButton_clicked();

    void on_RecordButton_clicked();

private:
    Ui::WaittingPage *ui;
    void showEvent(QShowEvent* event);
};

#endif // WAITTINGPAGE_H
