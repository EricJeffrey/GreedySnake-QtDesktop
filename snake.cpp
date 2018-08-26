#include <QDebug>
#include "snake.h"

const int Snake::LEFT = 0;
const int Snake::RIGHT = 1;
const int Snake::UP = 2;
const int Snake::DOWN = 3;
int Snake::GROW_UP_SIZE = 1;
int Snake::START_UP_DIRECTION = Snake::RIGHT;
int Snake::ONE_PART_WIDTH = 10;


Snake::Snake(QObject *parent) : QObject(parent)
{
    curDirection = START_UP_DIRECTION;
    body.push_back(QPoint(0, 0));
}

Snake::~Snake()
{
}

void Snake::growUp()
{
    if (body.size() == 0) {
        qDebug() << Q_FUNC_INFO << "body size zero";
    }
    else if (body.size() == 1){
        QPoint p(body.first());

        switch (curDirection) {
        case LEFT:
            p.setX(p.x() + ONE_PART_WIDTH);
            break;
        case RIGHT:
            p.setX(p.x() - ONE_PART_WIDTH);
            break;
        case UP:
            p.setY(p.y() + ONE_PART_WIDTH);
            break;
        case DOWN:
            p.setY(p.y() - ONE_PART_WIDTH);
            break;
        }
        body.push_back(p);
    }
    else {
        QPoint tailp = body.last(), tailforwardp = *(body.end() - 2);
        QPoint np(tailp);
        if (tailp.x() - tailforwardp.x() == 0){
            int z = tailp.y() - tailforwardp.y();
            if (z > 0)
                np.setY(np.y() + ONE_PART_WIDTH);
            else
                np.setY(np.y() - ONE_PART_WIDTH);
        }
        else {
            int z = tailp.x() - tailforwardp.x();
            if (z > 0)
                np.setX(np.x() + ONE_PART_WIDTH);
            else
                np.setX(np.x() - ONE_PART_WIDTH);
        }
        body.push_back(np);
    }
}

void Snake::moveForward()
{
    QPoint p(body.first());
    switch (curDirection) {
    case LEFT:
        p.setX(p.x() - ONE_PART_WIDTH);
        break;
    case RIGHT:
        p.setX(p.x() + ONE_PART_WIDTH);
        break;
    case UP:
        p.setY(p.y() - ONE_PART_WIDTH);
        break;
    case DOWN:
        p.setY(p.y() + ONE_PART_WIDTH);
        break;
    }
    body.pop_back();
    body.push_front(p);
}

void Snake::changeDirection(int targetDirection)
{
    if ((targetDirection ^ curDirection) == 0 || (targetDirection ^ curDirection) == 1)
        return;
    curDirection = targetDirection;
}

void Snake::reset()
{
    body.clear();
    body.push_back(QPoint(0, 0));
    curDirection = RIGHT;
}

QPoint Snake::headPosition()
{
    return body.first();
}

QVector<QPoint> Snake::getBody() const
{
    return body;
}
