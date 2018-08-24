#include "mainwindow.h"
#include "mapgraphicsview.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapGraphicsView *view = new MapGraphicsView();
    view->show();

    QTimer *timer = new QTimer();
    timer->setInterval(static_cast<int>(MapGraphicsView::MOVE_FORWARD_INTERVAL));
    QObject::connect(timer, &QTimer::timeout, view, &MapGraphicsView::snakeMoveForward);
    QObject::connect(view, &MapGraphicsView::snakeDead, timer, &QTimer::stop);
    QObject::connect(view, SIGNAL(gameRestart()), timer, SLOT(start()));

    timer->start();

    return a.exec();
}
