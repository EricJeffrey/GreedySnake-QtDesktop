#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QPoint>
#include <QVector>

class Snake : public QObject
{
    Q_OBJECT
public:
    const static int LEFT, RIGHT, UP, DOWN;
    static int ONE_PART_WIDTH;

    explicit Snake(QObject *parent = nullptr);
    ~Snake();
    void growUp();
    void moveForward();
    void changeDirection(int targetDirection);
    void reset();
    QPoint headPosition();

    QVector<QPoint> getBody() const;

signals:

public slots:

private:
    static int GROW_UP_SIZE;
    static int START_UP_DIRECTION;

    QVector<QPoint> body;
    int curDirection;

};

#endif // SNAKE_H
