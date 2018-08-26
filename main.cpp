#include "mainwindow.h"
#include "mapgraphicsview.h"
#include <QApplication>
#include <QTimer>

void startGame();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    startGame();

    MapGraphicsView *gameView = new MapGraphicsView();
    MainWindow *mainwindow = new MainWindow(gameView);
    mainwindow->show();

    QTimer *timer = new QTimer();
    timer->setInterval(static_cast<int>(MapGraphicsView::MOVE_FORWARD_INTERVAL));
    QObject::connect(timer, &QTimer::timeout, gameView, &MapGraphicsView::snakeMoveForward);
    QObject::connect(gameView, &MapGraphicsView::snakeDead, timer, &QTimer::stop);
    QObject::connect(gameView, SIGNAL(gameRestart()), timer, SLOT(start()));
    QObject::connect(gameView, &MapGraphicsView::fruitEaten, mainwindow, &MainWindow::fruitEatenScored);
    QObject::connect(gameView, &MapGraphicsView::gameRestart, mainwindow, &MainWindow::resetScore);

    timer->start();

    return a.exec();
}

void startGame(){
    MapGraphicsView *view = new MapGraphicsView();
    view->show();

    QTimer *timer = new QTimer();
    timer->setInterval(static_cast<int>(MapGraphicsView::MOVE_FORWARD_INTERVAL));
    QObject::connect(timer, &QTimer::timeout, view, &MapGraphicsView::snakeMoveForward);
    QObject::connect(view, &MapGraphicsView::snakeDead, timer, &QTimer::stop);
    QObject::connect(view, SIGNAL(gameRestart()), timer, SLOT(start()));

    timer->start();
}
