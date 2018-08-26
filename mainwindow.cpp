#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(MapGraphicsView *gv, QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentScore = 0;
    setContentsMargins(0, 0, 0, 0);

    scoreTextLabel = new QLabel("SCORE: ");
    scoreTextLabel->setFont(QFont("castellar", 17));
    scoreTextLabel->setFixedHeight(30);

    scoreLabel = new QLabel("0");
    scoreLabel->setFont(QFont("castellar", 17));
    scoreLabel->setFixedHeight(30);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->setContentsMargins(5, 0, 5, 5);
    bottomLayout->addWidget(scoreTextLabel);
    bottomLayout->addWidget(scoreLabel);

    QVBoxLayout *outlayout = new QVBoxLayout();
    outlayout->setContentsMargins(5, 5, 5, 0);
    outlayout->addWidget(gv);
    outlayout->addLayout(bottomLayout);

    QWidget *cenWidget = new QWidget(this);
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
    scoreLabel->setText(QString::fromStdString(std::to_string(currentScore)));
}

void MainWindow::resetScore()
{
    currentScore = 0;
    scoreLabel->setText("0");
}

