#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <logger.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void rxData(QString head, QString value);
private:
    Ui::MainWindow *ui;
    logger* log;
};

#endif // MAINWINDOW_H
