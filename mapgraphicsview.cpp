#include <QDebug>
#include <QMessageBox>
#include "mapgraphicsview.h"

int MapGraphicsView::MAP_WIDTH = 500;
int MapGraphicsView::MAP_HEIGHT = 500;
int MapGraphicsView::WALL_WIDTH = 2;
int MapGraphicsView::SCORE_PER_FRUIT = 10;
ulong MapGraphicsView::MOVE_FORWARD_INTERVAL = 150;

QColor MapGraphicsView::SNAKE_HEAD_COLOR = QColor(200, 200, 200);
QColor MapGraphicsView::SNAKE_BODY_COLOR = QColor(130, 130, 130);
QColor MapGraphicsView::FRUIT_COLOR = QColor(255, 0, 0);
QColor MapGraphicsView::WALL_COLOR = QColor(60, 60, 60);

QString MapGraphicsView::WINDOW_TITLE = QString("Greedy Snake");

MapGraphicsView::MapGraphicsView()
{
    setContentsMargins(0, 0, 0, 0);
    setStyleSheet("padding:0px;border:0px");

    resize(MAP_WIDTH + (WALL_WIDTH << 1) + 3, MAP_HEIGHT + (WALL_WIDTH << 1) + 3);
    setWindowTitle(WINDOW_TITLE);

    setScene(new QGraphicsScene());
    drawWall();

    f.generate(generateFruitPos());
    laReleaseTime = 0;
}

MapGraphicsView::~MapGraphicsView()
{
}

void MapGraphicsView::restartGame()
{

    scene()->clear();
    drawWall();
    snake.reset();
    f.generate(generateFruitPos());
    drawSnakeAndFruit();
}


void MapGraphicsView::snakeMoveForward()
{
    snake.moveForward();
    QGraphicsScene *sc = scene();
    if (sc == nullptr){
        qDebug() << Q_FUNC_INFO << "scene of view is nullptr";
        return;
    }
    if (isSnakeDead()){
        emit snakeDead();
    }
    else {
        sc->clear();
        drawWall();
        if (isFruitEaten()){
            snake.growUp();
            f.generate(generateFruitPos());
            emit fruitEaten();
        }
        drawSnakeAndFruit();
        update();
    }
}

void MapGraphicsView::keyReleaseEvent(QKeyEvent *ev)
{
    int key = ev->key();
    if (key >= Qt::Key_Left && key <= Qt::Key_Down){
        int targetDirection = Snake::DOWN;
        switch (key) {
        case Qt::Key_Left:
            targetDirection = Snake::LEFT;
            break;
        case Qt::Key_Right:
            targetDirection = Snake::RIGHT;
            break;
        case Qt::Key_Up:
            targetDirection = Snake::UP;
            break;
        case Qt::Key_Down:
            targetDirection = Snake::DOWN;
            break;
        }
        if (ev->timestamp() - laReleaseTime <= MOVE_FORWARD_INTERVAL){
            snake.moveForward();
        }
        snake.changeDirection(targetDirection);
        laReleaseTime = ev->timestamp();
    }
    QGraphicsView::keyReleaseEvent(ev);
}

void MapGraphicsView::drawWall()
{
    QGraphicsScene *sc = scene();
    if (sc != nullptr){
        for (int i = 1; i <= WALL_WIDTH; i++){
            sc->addRect(-(MAP_WIDTH >> 1) - i, -(MAP_HEIGHT >> 1) - i, \
                        MAP_WIDTH + (i << 1), MAP_HEIGHT + (i << 1), QPen(WALL_COLOR));
        }
    }
}

void MapGraphicsView::drawSnakeAndFruit()
{
    QGraphicsScene *sc = scene();
    if (sc == nullptr){
        qDebug() << Q_FUNC_INFO << "scene of view null";
        return;
    }
    QVector<QPoint> snakeBody = snake.getBody();
    if (snakeBody.size() == 0) {
        qDebug() << Q_FUNC_INFO << "snake size 0";
        return;
    }
    int opw = Snake::ONE_PART_WIDTH;
    QPen pg = QPen(Qt::gray);
    for (int i = 0; i < snakeBody.size(); i++){
        QPoint p = snakeBody[i];
        if (i == 0)
            sc->addRect(p.x(), p.y(), opw, opw, QPen(SNAKE_HEAD_COLOR), QBrush(SNAKE_HEAD_COLOR));
        else
            sc->addRect(p.x(), p.y(), opw, opw, QPen(SNAKE_BODY_COLOR), QBrush(SNAKE_BODY_COLOR));
    }
    QPoint fpos = f.getPos();
    sc->addEllipse(fpos.x(), fpos.y(), \
                               Fruit::FRUIT_WIDTH, Fruit::FRUIT_HEIGHT, QPen(FRUIT_COLOR), QBrush(FRUIT_COLOR));
}

QPoint MapGraphicsView::generateFruitPos()
{
    qsrand(static_cast<uint>(time(nullptr)));
    int x, y;
    while(true){
        int mw = MAP_WIDTH - 20, mh = MAP_HEIGHT - 20;
        x = qrand() % mw;
        y = qrand() % mh;
        x /= 10; x *= 10; y /= 10; y *= 10;
        if (x > (mw >> 1))
            x -= mw;
        if (y > (mh >> 1))
            y -= mh;
        bool onBody = false;
        for (QPoint tmp : snake.getBody()){
            if (tmp.x() == x && tmp.y() == y){
                onBody = true;
                break;
            }
        }
        if (!onBody)
            break;
    }
    return QPoint(x, y);
}


bool MapGraphicsView::isSnakeDead()
{
    int x = snake.headPosition().x(), y = snake.headPosition().y();
    if (x < -((MAP_WIDTH + 10) >> 1) || x > ((MAP_WIDTH - 10) >> 1))
        return true;
    if (y < -((MAP_HEIGHT + 10) >> 1) || y > ((MAP_HEIGHT - 10) >> 1))
        return true;
    QVector<QPoint> body = snake.getBody();
    for (int i = 1; i < body.size(); i++){
        if (body[i] == snake.headPosition())
            return true;
    }
    return false;
}

bool MapGraphicsView::isFruitEaten()
{
    if (snake.headPosition() == f.getPos())
        return true;
    return false;
}
