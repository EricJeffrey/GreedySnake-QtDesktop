#include <QDebug>
#include "fruit.h"

int Fruit::FRUIT_HEIGHT = 10;
int Fruit::FRUIT_WIDTH = 10;

Fruit::Fruit(QObject *parent) : QObject(parent) {}

Fruit::~Fruit()
{
}

void Fruit::generate(QPoint p)
{
    pos = QPoint(p);
}

QPoint Fruit::getPos() const
{
    return pos;
}
