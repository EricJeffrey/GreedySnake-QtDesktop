#include <QDebug>
#include "mainwindow.h"
#include "settingwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPointer>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentScore = 0;
    setWindowTitle("GreedySnake");
    setContentsMargins(0, 0, 0, 0);

    scoreTextLabel.setText("SCORE :");
    scoreTextLabel.setFont(QFont(SettingWindow::SETTING_FONT_FAMILY, SettingWindow::SETTING_FONT_SIZE));
    scoreTextLabel.setFixedHeight(30);

    scoreLabel.setText("0");
    scoreLabel.setFont(QFont(SettingWindow::SETTING_FONT_FAMILY, SettingWindow::SETTING_FONT_SIZE));
    scoreLabel.setFixedHeight(30);

    QPointer<QHBoxLayout> bottomLayout(new QHBoxLayout());
    bottomLayout->setContentsMargins(5, 0, 5, 5);
    bottomLayout->addWidget(&scoreTextLabel);
    bottomLayout->addWidget(&scoreLabel);

    QPointer<QVBoxLayout> outlayout(new QVBoxLayout());
    outlayout->setContentsMargins(5, 5, 5, 0);
    outlayout->addWidget(&gameView);
    outlayout->addLayout(bottomLayout);

    QPointer<QWidget> cenWidget(new QWidget(this));
    cenWidget->setAttribute(Qt::WA_DeleteOnClose);
    cenWidget->setLayout(outlayout);

    setCentralWidget(cenWidget);
    setFixedSize(507 + 10, 507 + 30 + 6 + 10);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fruitEatenScored()
{
    currentScore += MapGraphicsView::SCORE_PER_FRUIT;
    scoreLabel.setText(QString::fromStdString(std::to_string(currentScore)));
}

void MainWindow::resetScore()
{
    currentScore = 0;
    scoreLabel.setText("0");
}

void MainWindow::startGame()
{
    timer.setInterval(static_cast<int>(MapGraphicsView::MOVE_FORWARD_INTERVAL));
    QObject::connect(&timer, &QTimer::timeout, &gameView, &MapGraphicsView::snakeMoveForward);
    QObject::connect(&gameView, &MapGraphicsView::snakeDead, &timer, &QTimer::stop);
    QObject::connect(&gameView, SIGNAL(gameRestart()), &timer, SLOT(start()));
    QObject::connect(&gameView, &MapGraphicsView::fruitEaten, this, &MainWindow::fruitEatenScored);
    QObject::connect(&gameView, &MapGraphicsView::gameRestart, this, &MainWindow::resetScore);
    QObject::connect(&gameView, &MapGraphicsView::gameEnd, this, &MainWindow::close);

    timer.start();
    show();
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape){
        close();
        return;
    }
    QMainWindow::keyReleaseEvent(ev);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit gameWindowClosed();
    QMainWindow::closeEvent(event);
}

