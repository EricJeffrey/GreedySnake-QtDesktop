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
int SettingWindow::MYLABEL_WIDTH = 40;

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

    // fruit color
    fruitColorLabel.setText("fruit color :");
    fruitColorLabel.setFont(QFont(SETTING_FONT_FAMILY, SETTING_FONT_SIZE));
    fruitColorSelector.setFixedSize(MYLABEL_WIDTH, MYLABEL_HEIGHT);
    fruitColorSelector.setBackgroundColor(MapGraphicsView::FRUIT_COLOR);
    connect(&fruitColorSelector, &MyLabel::clicked, [this]() -> void{
                QColor c = QColorDialog::getColor(Qt::white, this);
                if (c.isValid()){
                    this->fruitColorSelector.setBackgroundColor(c);
                    MapGraphicsView::FRUIT_COLOR = c;
                }
            });
    QPointer<QHBoxLayout> fruitColorLayout(new QHBoxLayout());
    fruitColorLayout->addWidget(&fruitColorLabel);
    fruitColorLayout->addWidget(&fruitColorSelector);

    // snake head color
    snakeHeadColorLabel.setText("snake head color :");
    snakeHeadColorLabel.setFont(QFont(SETTING_FONT_FAMILY, SETTING_FONT_SIZE));
    snakeHeadColorSelector.setBackgroundColor(MapGraphicsView::SNAKE_HEAD_COLOR);
    snakeHeadColorSelector.setFixedSize(MYLABEL_WIDTH, MYLABEL_HEIGHT);
    connect(&snakeHeadColorSelector, &MyLabel::clicked, [this]()->void{
                QColor c = QColorDialog::getColor(Qt::white, this);
                if (c.isValid()){
                    this->snakeHeadColorSelector.setBackgroundColor(c);
                    MapGraphicsView::SNAKE_HEAD_COLOR = c;
                }
    });
    QPointer<QHBoxLayout> headColorLayout(new QHBoxLayout());
    headColorLayout->addWidget(&snakeHeadColorLabel);
    headColorLayout->addWidget(&snakeHeadColorSelector);

    // snake body color
    snakeBodyColorLabel.setText("snake body color :");
    snakeBodyColorLabel.setFont(QFont(SETTING_FONT_FAMILY, SETTING_FONT_SIZE));
    snakeBodyColorSelector.setBackgroundColor(MapGraphicsView::SNAKE_BODY_COLOR);
    snakeBodyColorSelector.setFixedSize(MYLABEL_WIDTH, MYLABEL_HEIGHT);
    connect(&snakeBodyColorSelector, &MyLabel::clicked, [this]()->void{
                QColor c = QColorDialog::getColor(Qt::white, this);
                if (c.isValid()){
                    this->snakeBodyColorSelector.setBackgroundColor(c);
                    MapGraphicsView::SNAKE_BODY_COLOR = c;
                }
    });
    QPointer<QHBoxLayout> bodyColorLayout(new QHBoxLayout());
    bodyColorLayout->addWidget(&snakeBodyColorLabel);
    bodyColorLayout->addWidget(&snakeBodyColorSelector);

    // map wall color
    wallColorLabel.setText("wall color :");
    wallColorLabel.setFont(QFont(SETTING_FONT_FAMILY, SETTING_FONT_SIZE));
    wallColorSelector.setBackgroundColor(MapGraphicsView::WALL_COLOR);
    wallColorSelector.setFixedSize(MYLABEL_WIDTH, MYLABEL_HEIGHT);
    connect(&wallColorSelector, &MyLabel::clicked, [this]()->void{
                QColor c = QColorDialog::getColor(Qt::white, this);
                if (c.isValid()){
                    this->wallColorSelector.setBackgroundColor(c);
                    MapGraphicsView::WALL_COLOR = c;
                }
    });
    QPointer<QHBoxLayout> wallColorLayout(new QHBoxLayout());
    wallColorLayout->addWidget(&wallColorLabel);
    wallColorLayout->addWidget(&wallColorSelector);

    // map background color
    mapBackgroundColorLabel.setText("map background color :");
    mapBackgroundColorLabel.setFont(QFont(SETTING_FONT_FAMILY, SETTING_FONT_SIZE));
    mapBackgroundSelector.setBackgroundColor(MapGraphicsView::BACKGROUND_COLOR);
    mapBackgroundSelector.setFixedSize(MYLABEL_WIDTH, MYLABEL_HEIGHT);
    connect(&mapBackgroundSelector, &MyLabel::clicked, [this]()->void{
                QColor c = QColorDialog::getColor(Qt::white, this);
                if (c.isValid()){
                    this->mapBackgroundSelector.setBackgroundColor(c);
                    MapGraphicsView::BACKGROUND_COLOR = c;
                }
    });
    QPointer<QHBoxLayout> mapBackgroundLayout(new QHBoxLayout());
    mapBackgroundLayout->addWidget(&mapBackgroundColorLabel);
    mapBackgroundLayout->addWidget(&mapBackgroundSelector);

    // central widget
    QPointer<QVBoxLayout> outlayout(new QVBoxLayout());
    outlayout->addLayout(headColorLayout);
    outlayout->addLayout(bodyColorLayout);
    outlayout->addLayout(fruitColorLayout);
    outlayout->addLayout(wallColorLayout);
    outlayout->addLayout(mapBackgroundLayout);
    outlayout->addLayout(speedBox);
    outlayout->addLayout(bottomLayout);
    QWidget *cenWidget = new QWidget(this);
    cenWidget->setAttribute(Qt::WA_DeleteOnClose);
    cenWidget->setLayout(outlayout);

    resize(400, 420);
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





