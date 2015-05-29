#include "QtVisualisationMainWindow.h"
#include "ui_QtVisualisationMainWindow.h"
#include <QDebug>
#include <QWidgetItem>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    StartNewGame();

}

MainWindow::~MainWindow()
{
    delete ui;
}



//Run when cell double clicked
void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
        //when player click on pawn, select it
        if(wrcby.checkboard[row][column].type == pawn::PAWN && wrcby.isMyTurn(row,column))
        {
            wrcby.Select(row,column);
        }
        //when player click on an empty field, move selected pawn on this field
        else if(wrcby.checkboard[row][column].type == pawn::EMPTY_FIELD)
        {
            if(wrcby.isAnyPawnSelected())
                {
                    game::xy_pos selectedPawnCoords;
                    selectedPawnCoords = wrcby.SelectedPawn();

                    //Check if move is an attack
                    if(wrcby.checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isAttacker())
                    {
                        wrcby.Attack(row,column);
                    }
                    else
                    {
                        wrcby.Move(row,column);
                    }
                }

        }
        else;

        //Update visualistaion checkerboard
        UpdateVis();

        //Check if End Game
        if(wrcby.isEndGame())
        {
            if(Checkboard.isReset()) StartNewGame();
        }
}


//Start New Game
void MainWindow::StartNewGame()
{
    wrcby.setBoardSize(8);
    wrcby.setPawnNumber(12);
    wrcby.NewGame();

    Checkboard.setSize(wrcby.getBoardSize());
    Checkboard.draw(ui->tableWidget);
    Checkboard.draw_pawns(ui->tableWidget,wrcby.checkboard);
    Checkboard.ShowCurrentTurn(ui->lineEdit,wrcby.turn);
}

//Update visualisation
void MainWindow::UpdateVis()
{
    Checkboard.draw_pawns(ui->tableWidget,wrcby.checkboard);
    Checkboard.ShowCurrentTurn(ui->lineEdit,wrcby.turn);
    Checkboard.setCurrentStatus(ui->lineEdit_2,wrcby.status);
}

void MainWindow::on_actionNew_Game_triggered()
{
    StartNewGame();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::NoIcon);
        msgbox.setWindowTitle("About draughts");
        msgbox.setText("<center><font size=14><b>Draughts (2 players)</b></font><br> by Krzysztof Jarzyna<br><br>"
                       "</center>");

        msgbox.exec();
}
