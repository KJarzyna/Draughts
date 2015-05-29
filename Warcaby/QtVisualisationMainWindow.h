#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "QtVisualisationBoard.h"
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void StartNewGame();
    void UpdateVis();

private slots:

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_actionNew_Game_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    szachownica Checkboard;
    game wrcby;
};

#endif // MAINWINDOW_H
