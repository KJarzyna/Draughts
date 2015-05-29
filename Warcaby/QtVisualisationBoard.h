#ifndef SZACHOWNICA_H
#define SZACHOWNICA_H
#include <QTableWidget>
#include <QLineEdit>
#include <QMainWindow>
#include "game.h"


class szachownica
{
public:
    szachownica();
    ~szachownica();

    void setSize(int);
    void draw(QTableWidget *checkboard);
    void draw_pawns(QTableWidget *parent, std::vector<std::vector<pawn>> board);
    void ShowCurrentTurn(QLineEdit *parent, game::player turn);
    void setCurrentStatus(QLineEdit *parent, std::string status);

    bool isReset();

    int getSize();

private:
    int size;
    void setCellColor(QTableWidget *parent, int row, int column,QColor color);
    void highlight_selected(QTableWidget *parent, int row, int col);

};

#endif // SZACHOWNICA_H
