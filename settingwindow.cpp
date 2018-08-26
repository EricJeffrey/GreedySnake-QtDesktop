#include "settingwindow.h"

#include <QHBoxLayout>
#include <QPointer>

SettingWindow::SettingWindow(QWidget *parent) : QMainWindow(parent)
{

    startGameButton.setText("START");
    connect(&startGameButton, &QPushButton::clicked, this, &SettingWindow::startGame);

    exitButton.setText("EXIT");
    connect(&exitButton, &QPushButton::clicked, this, &SettingWindow::close);

    QPointer<QHBoxLayout> layout(new QHBoxLayout());
    layout->addWidget(&startGameButton);
    layout->addWidget(&exitButton);

    QWidget *cenWidget = new QWidget(this);
    cenWidget->setAttribute(Qt::WA_DeleteOnClose);
    cenWidget->setLayout(layout);

    setCentralWidget(cenWidget);
}

void SettingWindow::startGame()
{
    hide();
    emit gameStart();
}

void SettingWindow::closeEvent(QCloseEvent *ev)
{
    QMainWindow::closeEvent(ev);
}



