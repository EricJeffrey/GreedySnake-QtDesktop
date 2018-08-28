#include "mapgraphicsview.h"
#include "settingwindow.h"
#include <QColorDialog>
#include <QDebug>
#include <QHBoxLayout>
#include <QPointer>
#include <QSpinBox>
#include <QSpinBox>

QString SettingWindow::SETTING_FONT_FAMILY("Lucida Calligraphy");
int SettingWindow::SETTING_FONT_SIZE = 17;
int SettingWindow::SPEED_VALUE_MAX = 320;
int SettingWindow::MYLABEL_HEIGHT = 25;

SettingWindow::SettingWindow(QWidget *parent) : QMainWindow(parent)
{
    // start and exit buttons
    startGameButton.setText("START");
    startGameButton.setFont(QFont(SETTING_FONT_FAMILY, SETTING_FONT_SIZE));
    startGameButton.setMinimumWidth(140);
    connect(&startGameButton, &QPushButton::clicked, this, &SettingWindow::startGame);
    exitButton.setText("EXIT");
    exitButton.setFont(QFont(SETTING_FONT_FAMILY, SETTING_FONT_SIZE));
    exitButton.setMinimumWidth(140);
    connect(&exitButton, &QPushButton::clicked, this, &SettingWindow::close);
    QPointer<QHBoxLayout> bottomLayout(new QHBoxLayout());
    bottomLayout->addWidget(&startGameButton);
    bottomLayout->addWidget(&exitButton);

    // speed setting
    speedLabel.setText("Speed :");
    speedLabel.setFont(QFont(SETTING_FONT_FAMILY, SETTING_FONT_SIZE));
    speedSlider.setValue(100 - static_cast<int>(MapGraphicsView::MOVE_FORWARD_INTERVAL / 3));
    speedSlider.setRange(0, 100);
    speedSlider.setOrientation(Qt::Horizontal);
    connect(&speedSlider, &QSlider::valueChanged, this, &SettingWindow::changeSnakeMoveSpeed);
    connect(&speedSlider, &QSlider::valueChanged, &speedSpin, &QSpinBox::setValue);
    speedSpin.setValue(100 - static_cast<int>(MapGraphicsView::MOVE_FORWARD_INTERVAL / 3));
    speedSpin.setRange(0, 100);
    connect(&speedSpin, SIGNAL(valueChanged(int)), &speedSlider, SLOT(setValue(int)));
    connect(&speedSpin, SIGNAL(valueChanged(int)), this, SLOT(changeSnakeMoveSpeed(int)));
    QPointer<QHBoxLayout> speedBox(new QHBoxLayout());
    speedBox->addWidget(&speedLabel);
    speedBox->addWidget(&speedSlider);
    speedBox->addWidget(&speedSpin);

    // snake head body and fruit color
    snakeHeadColorLabel.setText("snake head color :");
    snakeHeadColorLabel.setFont(QFont(SETTING_FONT_FAMILY, SETTING_FONT_SIZE));
    snakeHeadColorSeletor.setBackgroundColor(MapGraphicsView::SNAKE_HEAD_COLOR);
    snakeHeadColorSeletor.setFixedHeight(MYLABEL_HEIGHT);
    connect(&snakeHeadColorSeletor, &MyLabel::clicked, [this]()->void{
                QColor c = QColorDialog::getColor(Qt::white, this);
                if (c.isValid()){
                    this->snakeHeadColorSeletor.setBackgroundColor(c);
                    MapGraphicsView::SNAKE_HEAD_COLOR = c;
                }
    });
    QPointer<QHBoxLayout> headColorLayout(new QHBoxLayout());
    headColorLayout->addWidget(&snakeHeadColorLabel);
    headColorLayout->addWidget(&snakeHeadColorSeletor);

    // central widget
    QPointer<QVBoxLayout> outlayout(new QVBoxLayout());
    outlayout->addLayout(headColorLayout);
    outlayout->addLayout(speedBox);
    outlayout->addLayout(bottomLayout);
    QWidget *cenWidget = new QWidget(this);
    cenWidget->setAttribute(Qt::WA_DeleteOnClose);
    cenWidget->setLayout(outlayout);

    resize(250, 250);
    setWindowTitle("Setting");
    setCentralWidget(cenWidget);
}

void SettingWindow::startGame()
{
    hide();
    emit gameStart();
}

void SettingWindow::changeSnakeMoveSpeed(int value)
{
    if (value < 0 || value > 1000){
        qDebug() << Q_FUNC_INFO << "snake move speed wrong";
        return;
    }
    MapGraphicsView::MOVE_FORWARD_INTERVAL = static_cast<ulong>(SPEED_VALUE_MAX - value * 3);
}

QColor SettingWindow::showColor()
{
    QColor c = QColorDialog::getColor(Qt::white, this);
    return c.isValid()? c: Qt::white;
}

void SettingWindow::keyReleaseEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape){
        close();
        return;
    }
    QMainWindow::keyReleaseEvent(ev);
}

void SettingWindow::closeEvent(QCloseEvent *ev)
{
    QMainWindow::closeEvent(ev);
}





