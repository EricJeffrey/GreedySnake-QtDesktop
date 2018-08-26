#include "mainwindow.h"
#include "mapgraphicsview.h"
#include "settingwindow.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SettingWindow *launchWindow = new SettingWindow();
    QObject::connect(launchWindow, static_cast<void (SettingWindow:: *)()>(&SettingWindow::gameStart), [launchWindow]() {

        MainWindow *mainwindow = new MainWindow();
        QObject::connect(mainwindow, &MainWindow::gameWindowClosed, launchWindow, &SettingWindow::show);
        mainwindow->setAttribute(Qt::WA_DeleteOnClose);
        mainwindow->startGame();

    });
    launchWindow->setAttribute(Qt::WA_DeleteOnClose);
    launchWindow->show();

    return a.exec();
}

