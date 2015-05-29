#include "ai.h"
#include <ctime>
#include <QDebug>

ai::ai()
{

}

ai::~ai()
{

}

void ai::MakeMuve(game checkers)
{
    game::xy_pos pawn_Att;
    game::xy_pos pawn_Mov;

    QVector<game::xy_pos> possible_pawns;
    QVector<game::xy_pos> possible_attackers;
    QVector<game::xy_pos> possible_moves;
    QVector<game::xy_pos> possible_attacks;

    board.clear();
    pawn_list.clear();

    srand(time(NULL));

    if(!checkers.isAnyPawnCanAttack())
    {

    for(int row=0;row<checkers.getBoardSize();row++)
    {
        for(int col=0;col<checkers.getBoardSize();col++)
        {
            if(checkers.checkboard[row][col].side == pawn::RED && doesPawnCanMove(checkers,row,col))
            {
                pawn_Mov.x = row;
                pawn_Mov.y = col;
                possible_pawns.append(pawn_Mov);
                pawn_list.clear();
            }
        }
    }




    int random;
    random = rand()%possible_pawns.size();
    int rw,cl;
    rw = possible_pawns[random].x;
    cl = possible_pawns[random].y;

    qDebug() << "Pawn: " << rw << " " << cl;

    checkers.Select(rw,cl);

    doesPawnCanMove(checkers,rw,cl);
    possible_moves.resize(pawn_list.size());
    possible_moves = pawn_list;

    random = rand()%possible_moves.size();
    int rw2,cl2;
    rw2 = possible_moves[random].x;
    cl2 = possible_moves[random].y;

    qDebug() << "Move: " << rw2 << " " << cl2;

    if(!checkers.isAnyPawnCanAttack()) checkers.Move(rw2,cl2);

    pawn_list.clear();



}
   else if(checkers.isAnyPawnCanAttack())
   {

        for(int row=0;row<checkers.getBoardSize();row++)
        {
            for(int col=0;col<checkers.getBoardSize();col++)
            {
                if(checkers.checkboard[row][col].side == pawn::RED && checkers.checkboard[row][col].isAttacker())
                {
                    pawn_Att.x = row;
                    pawn_Att.y = col;
                    possible_attackers.append(pawn_Att);
                }
            }
        }

    int random = rand()%possible_attackers.size();

    int rw = possible_attackers[random].x;
    int cl = possible_attackers[random].y;

    checkers.Select(rw,cl);


    possibleAttacks(checkers, rw, cl);
    possible_attacks.resize(pawn_list.size());
    possible_attacks = pawn_list;

    random = rand()%possible_attacks.size();

    int rw2 = possible_attacks[random].x;
    int cl2 = possible_attacks[random].y;

    checkers.Attack(rw2,cl2);

    while(checkers.mustattack)
    {
        checkers.Select(rw2,cl2);
        pawn_list.clear();
        possibleAttacks(checkers, rw2, cl2);
        possible_attacks.resize(pawn_list.size());
        possible_attacks = pawn_list;

        random = rand()%possible_attacks.size();

        rw2 = possible_attacks[random].x;
        cl2 = possible_attacks[random].y;

        checkers.Attack(rw2,cl2);
    }

   }

    board = checkers.checkboard;
    temp_turn = checkers.turn;



}

bool ai::doesPawnCanMove(game checkers, int row, int col)
{
    bool up_left, up_right, down_left, down_right;
    bool canMove;
    up_left = 0;
    up_right = 0;
    down_left = 1;
    down_right = 1;
    canMove = 0;

    game::xy_pos pawn_Moves;

    if(row == 0)
    {
        up_left = 0;
        up_right = 0;
    }
    else if(row == checkers.checkboard.size()-1)
    {
        down_left = 0;
        down_right = 0;
    }
    if(col == 0)
    {
        up_left = 0;
        down_left = 0;
    }
    else if(col == checkers.checkboard.size()-1)
    {
        up_right = 0;
        down_right = 0;
    }

    if(checkers.checkboard[row][col].side == pawn::RED && !checkers.checkboard[row][col].isDamka())
    {
        if(up_left)
        {
            if(checkers.checkboard[row-1][col-1].type == pawn::EMPTY_FIELD)
            {
                canMove = 1;
                pawn_Moves.x = row-1;
                pawn_Moves.y = col-1;
                pawn_list.append(pawn_Moves);
            }
        }
        if(up_right)
        {
            if(checkers.checkboard[row-1][col+1].type == pawn::EMPTY_FIELD)
            {
                canMove = 1;
                pawn_Moves.x = row-1;
                pawn_Moves.y = col+1;
                pawn_list.append(pawn_Moves);
            }
        }
        if(down_left)
        {
            if(checkers.checkboard[row+1][col-1].type == pawn::EMPTY_FIELD)
            {
                canMove = 1;
                pawn_Moves.x = row+1;
                pawn_Moves.y = col-1;
                pawn_list.append(pawn_Moves);
            }
        }
        if(down_right)
        {
            if(checkers.checkboard[row+1][col+1].type == pawn::EMPTY_FIELD)
            {
                canMove = 1;
                pawn_Moves.x = row+1;
                pawn_Moves.y = col+1;
                pawn_list.append(pawn_Moves);
            }
        }
    }

    else canMove = 0;

    if(canMove) return true;
    else return false;
}

bool ai::possibleAttacks(game checkers, int row, int col)
{

    bool up_left, up_right, down_left, down_right;
    bool canAttack;
    up_left = 1;
    up_right = 1;
    down_left = 1;
    down_right = 1;
    canAttack = 0;

    game::xy_pos pawn_attacks;

    if(row == 0 || row == 1)
    {
        up_left = 0;
        up_right = 0;
    }
    else if(row == checkers.checkboard.size()-1 || row == checkers.checkboard.size()-2)
    {
        down_left = 0;
        down_right = 0;
    }
    if(col == 0 || col == 1)
    {
        up_left = 0;
        down_left = 0;
    }
    else if(col == checkers.checkboard.size()-1 || col == checkers.checkboard.size()-2)
    {
        up_right = 0;
        down_right = 0;
    }

    if(checkers.checkboard[row][col].side == pawn::RED && !checkers.checkboard[row][col].isDamka())
    {
        if(up_left)
        {
            if(checkers.checkboard[row-1][col-1].side == pawn::BLUE && checkers.checkboard[row-2][col-2].type == pawn::EMPTY_FIELD)
            {
                pawn_attacks.x = row-2;
                pawn_attacks.y = col-2;
                pawn_list.append(pawn_attacks);
                canAttack = 1;
            }
        }
        if(up_right)
        {
            if(checkers.checkboard[row-1][col+1].side == pawn::BLUE && checkers.checkboard[row-2][col+2].type == pawn::EMPTY_FIELD)
            {
                pawn_attacks.x = row-2;
                pawn_attacks.y = col+2;
                pawn_list.append(pawn_attacks);
                canAttack = 1;
            }
        }
        if(down_left)
        {
            if(checkers.checkboard[row+1][col-1].side == pawn::BLUE && checkers.checkboard[row+2][col-2].type == pawn::EMPTY_FIELD)
            {
                pawn_attacks.x = row+2;
                pawn_attacks.y = col-2;
                pawn_list.append(pawn_attacks);
                canAttack = 1;
            }
        }
        if(down_right)
        {
            if(checkers.checkboard[row+1][col+1].side == pawn::BLUE && checkers.checkboard[row+2][col+2].type == pawn::EMPTY_FIELD)
            {
                pawn_attacks.x = row+2;
                pawn_attacks.y = col+2;
                pawn_list.append(pawn_attacks);
                canAttack = 1;
            }
        }
    }
    else canAttack = 0;

    if(canAttack) return true;
    else return false;





//    game::xy_pos selectedPawnCoords;
//    selectedPawnCoords = checkers.SelectedPawn();

//    //Attack for no-Damka pawn
//    for(int row=0;row<checkers.getBoardSize();row++)
//    {
//        for(int col=0;col<checkers.getBoardSize();col++)
//        {

//    if(!checkers.checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isDamka()  && checkers.checkboard[selectedPawnCoords.x][selectedPawnCoords.y].side == pawn::RED && checkers.checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isMoveAllowed(row,column) &&
//            checkers.isEnemyPawnBetweenPositions(selectedPawnCoords.x,selectedPawnCoords.y,row,column) && abs(selectedPawnCoords.x-row)<3)
//    {
//        checkers.MovePionToField(selectedPawnCoords.x,selectedPawnCoords.y,row,column);
//        checkers.KillPawnsBetweenPositions(selectedPawnCoords.x,selectedPawnCoords.y,row,column);
//        if(checkers.doesPawnHaveAttackPossibilities(row,column)) checkers.checkboard[row][column].setCanAttack(true);
//        else checkers.checkboard[row][column].setCanAttack(false);
//        if(checkers.checkboard[row][column].isAttacker())
//        {
//            checkers.mustattack = 1;
//        }
//        else
//        {
//            checkers.deselectPawn(row,column);
//            checkers.mustattack = 0;
//            checkers.NextTurn();
//        }
//    }
//        }
//}
}
