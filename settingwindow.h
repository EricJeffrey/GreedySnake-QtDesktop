#ifndef STARTSETTINGWINDOW_H
#define STARTSETTINGWINDOW_H

#include "mapgraphicsview.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

class SettingWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingWindow(QWidget *parent = nullptr);

signals:
    void gameStart();

public slots:
    void startGame();

private:
    QPushButton startGameButton;
    QPushButton exitButton;

    void closeEvent(QCloseEvent *ev);
};

#endif // STARTSETTINGWINDOW_H
