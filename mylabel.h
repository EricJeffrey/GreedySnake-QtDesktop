#ifndef MYLABEL_H
#define MYLABEL_H

#include <QKeyEvent>
#include <QLabel>



class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(QColor c = QColor(Qt::white), QWidget *parent=Q_NULLPTR, Qt::WindowFlags f=Qt::WindowFlags());
    void setBackgroundColor(QColor c);

signals:
    void clicked();

public slots:

protected:
    void mouseReleaseEvent(QMouseEvent *ev);

private:

};

#endif // MYLABEL_H
