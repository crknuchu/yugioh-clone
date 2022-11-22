#include "headers/mainwindow.h"
#include "headers/ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect objects, signals that they emit and slots that handle them:
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupConnections() {
    connect(ui->btnBattlePhase, &QPushButton::clicked, this, &MainWindow::btnBattlePhaseClicked);
}



// connect(toolButton, &QPushButton::clicked, this, &YourClassName::nameOfYourSlot);
// Slot implementation:
void MainWindow::btnBattlePhaseClicked()
{
    std::cout << "Battle phase button clicked" << std::endl;
}

void MainWindow::btnMainPhase2Clicked()
{
    std::cout << "Main phase 2 button clicked" << std::endl;
}

void MainWindow::btnEndPhaseClicked()
{
    std::cout << "End phase button clicked" << std::endl;
}
