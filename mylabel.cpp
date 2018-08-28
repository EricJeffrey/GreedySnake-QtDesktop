#include "mylabel.h"

MyLabel::MyLabel(QColor c, QWidget *parent, Qt::WindowFlags f) : QLabel(parent, f)
{
    setBackgroundColor(c);
}

void MyLabel::setBackgroundColor(QColor c)
{
    setStyleSheet(QString("background-color:rgb(%1, %2, %3);")
                  .arg(c.red())
                  .arg(c.green())
                  .arg(c.blue()));
}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::MouseButton::LeftButton){
        emit clicked();
    }
    QLabel::mouseReleaseEvent(ev);
}
