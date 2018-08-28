#ifndef MAPGRAPHICSVIEW_H
#define MAPGRAPHICSVIEW_H

#include "fruit.h"
#include "snake.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QKeyEvent>



class MapGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    static ulong MOVE_FORWARD_INTERVAL;
    static int SCORE_PER_FRUIT;
    static QColor SNAKE_HEAD_COLOR;
    static QColor SNAKE_BODY_COLOR;
    static QColor FRUIT_COLOR;
    static QColor WALL_COLOR;

    MapGraphicsView();
    ~MapGraphicsView();
    void restartGame();

signals:
    void snakeDead();
    void gameRestart();
    void gameEnd();
    void fruitEaten();

public slots:
    void snakeMoveForward();

protected:
    void keyReleaseEvent(QKeyEvent *ev);

private:
    void drawWall();
    void drawSnakeAndFruit();
    QPoint generateFruitPos();
    bool isSnakeDead();
    bool isFruitEaten();

    static QString WINDOW_TITLE;
    static int MAP_WIDTH, MAP_HEIGHT, WALL_WIDTH;

    Snake snake;
    Fruit f;
    ulong laReleaseTime;
};

#endif // MAPGRAPHICSVIEW_H
