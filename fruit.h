#ifndef FRUIT_H
#define FRUIT_H

#include <QObject>
#include <QPoint>

class Fruit : public QObject
{
    Q_OBJECT
public:
    static int FRUIT_WIDTH;
    static int FRUIT_HEIGHT;

    explicit Fruit(QObject *parent = nullptr);

    void generate(QPoint p);
    QPoint getPos() const;

signals:

public slots:

private:
    QPoint pos;
};

#endif // FRUIT_H
