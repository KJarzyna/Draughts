#include "QtVisualisationBoard.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>

szachownica::szachownica()
{

}

szachownica::~szachownica()
{

}

//Set size of checkerboard
void szachownica::setSize(int rc)
{
    size = rc;
}
//Return size of checkerboard
int szachownica::getSize()
{
    return size;
}

//Draw checkerboard (a TableWidget)
void szachownica::draw(QTableWidget* checkboard)
{
    checkboard->setColumnCount(size);
    checkboard->setRowCount(size);

    for(int i=0;i<checkboard->columnCount();i++)
    {
     checkboard->setRowHeight(i,50);
     checkboard->setColumnWidth(i,50);
    }
    checkboard->horizontalHeader()->hide();
    checkboard->verticalHeader()->hide();
    checkboard->verticalHeader()->hide();

    int row,col;
    row=0;
    col=1;
    for(row;row<size;row++)
    {
        for(col;col<size;col=col+2)
        {
            checkboard->setItem(row,col,new QTableWidgetItem);
            setCellColor(checkboard,row,col,Qt::black);
        }
        if(row%2==0) col = 0;
        else col = 1;
    }
    checkboard->setMaximumWidth(size*checkboard->columnWidth(0)+2);
    checkboard->setMaximumHeight(size*checkboard->rowHeight(1)+2);
    checkboard->setMinimumWidth(size*checkboard->columnWidth(0)+2);
    checkboard->setMinimumHeight(size*checkboard->rowHeight(1)+2);

}

//Set color of cell at position (row,column) in TableWidget
void szachownica::setCellColor(QTableWidget *parent, int row, int column, QColor color)
{
    parent->setItem(row,column,new QTableWidgetItem);
    parent->item(row,column)->setBackgroundColor(color);
}

//Draw pawns on checkerboard (color cells of TableWidget)
void szachownica::draw_pawns(QTableWidget *parent, std::vector<std::vector<pawn> > board)
{
    for(int row=0;row<size;row++)
    {
        for(int col=0;col<size;col++)
        {
            parent->setItem(row,col,new QTableWidgetItem);
            if(board[row][col].type == pawn::PAWN && board[row][col].isSelected()) setCellColor(parent,row,col,Qt::green);
            else if(board[row][col].type == pawn::PAWN && board[row][col].side == pawn::RED) setCellColor(parent,row,col,Qt::red);
            else if(board[row][col].type == pawn::PAWN && board[row][col].side == pawn::BLUE) setCellColor(parent,row,col,Qt::blue);
            else if(board[row][col].type == pawn::EMPTY_FIELD) setCellColor(parent,row,col,Qt::black);
            else if(board[row][col].type == pawn::FORBIDDEN) setCellColor(parent,row,col,Qt::gray);
            else;

            if(board[row][col].isDamka() && board[row][col].side == pawn::RED)
            {
                QColor orange;
                orange.setRgb(255,128,0,255);
                setCellColor(parent,row,col,orange);
            }
            else if(board[row][col].isDamka() && board[row][col].side == pawn::BLUE)
            {
                QColor cyan;
                cyan.setRgb(0,230,255,255);
                setCellColor(parent,row,col,cyan);
            }
        }

    }

}

//Highlight cell at position (row,col) in TableWidget
void szachownica::highlight_selected(QTableWidget *parent, int row, int col)
{
    setCellColor(parent, row, col, Qt::green);
}

//Show current turn in QLineEdit
void szachownica::ShowCurrentTurn(QLineEdit *parent, game::player turn)
{
    if(turn == game::PLAYER_RED) parent->setText("RED");
    else if(turn == game::PLAYER_BLUE) parent->setText("BLUE");
    else;
}

//Set current status in QLineEdit
void szachownica::setCurrentStatus(QLineEdit *parent, std::string status)
{
    QString Qstatus;
    parent->setText(Qstatus.fromStdString(status));
}

//If player choose to reset game, return true
bool szachownica::isReset()
{

    QMessageBox::information(0, "Koniec gry", "KONIEC GRY!","RESET");

    if(QMessageBox::Ok)
    {
        return true;
    }
    else return false;

}
