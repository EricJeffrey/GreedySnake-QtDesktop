#ifndef STARTSETTINGWINDOW_H
#define STARTSETTINGWINDOW_H

#include "mylabel.h"

#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QTimer>

class SettingWindow : public QMainWindow
{
    Q_OBJECT
public:
    static QString SETTING_FONT_FAMILY;
    static int SETTING_FONT_SIZE;

    explicit SettingWindow(QWidget *parent = nullptr);

signals:
    void gameStart();

public slots:
    void startGame();
    void changeSnakeMoveSpeed(int value);
    QColor showColor();

protected:
    void keyReleaseEvent(QKeyEvent *ev);

private:
    static int SPEED_VALUE_MAX;
    static int MYLABEL_HEIGHT;

    QPushButton startGameButton;
    QPushButton exitButton;

    QLabel speedLabel;
    QSpinBox speedSpin;
    QSlider speedSlider;
    QLabel snakeHeadColorLabel;
    MyLabel snakeHeadColorSeletor;

    void closeEvent(QCloseEvent *ev) override;
};

#endif // STARTSETTINGWINDOW_H
