#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <utility>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void setupConnections();

private slots:
    void btnBattlePhaseClicked();
    void btnMainPhase2Clicked();
    void btnEndPhaseClicked();

};




#endif // MAINWINDOW_H
