#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mapgraphicsview.h"

#include <QLabel>
#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void gameWindowClosed();

public slots:
    void fruitEatenScored();
    void resetScore();
    void startGame();

protected:
    void keyReleaseEvent(QKeyEvent *ev);

private:
    Ui::MainWindow *ui;
    QLabel scoreTextLabel;
    QLabel scoreLabel;
    MapGraphicsView gameView;
    QTimer timer;
    int currentScore;


protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
