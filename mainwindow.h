#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mapgraphicsview.h"

#include <QLabel>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(MapGraphicsView *gv, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void fruitEatenScored();
    void resetScore();

private:
    Ui::MainWindow *ui;
    QLabel *scoreTextLabel;
    QLabel *scoreLabel;
    int currentScore;

};

#endif // MAINWINDOW_H
