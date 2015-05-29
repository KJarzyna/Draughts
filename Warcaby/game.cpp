#include "game.h"

game::game()
{

}

game::~game()
{

}


//Switch places of field from (prev_row,prev_col) with field from (new_row,new_col)
void game::MovePionToField(size_t prev_row, size_t prev_col, size_t new_row, size_t new_col)
{
        pawn field_copy;
        field_copy = checkboard[new_row][new_col];

        checkboard[new_row][new_col] =  checkboard[prev_row][prev_col];
        checkboard[new_row][new_col].setPosition(new_row,new_col);
        checkboard[prev_row][prev_col] = field_copy;
        checkboard[prev_row][prev_col].setPosition(prev_row,prev_col);
}

//Set size of checkerboard
void game::setBoardSize(size_t size)
{
    board_size = size;
}

//Returns size of checkerboard
size_t game::getBoardSize()
{
    return board_size;
}

//Set number of pawns (per player)
void game::setPawnNumber(size_t pwn_nmb)
{
    num_of_pions = pwn_nmb;
}

//Initialize checkerboard (fill it with Empty Fields and Forbidden Fields)
void game::InitializeBoard()
{
    for(size_t i=0;i<board_size;i++)
    {
        checkboard.resize(board_size);
        checkboard[i].resize(board_size);
    }

    InitializeEmptyFields();
    InitializeForbiddenFields();
}

//Initialize Both Players on checkerboard
void game::InitializePionPositions()
{
    InitializeRedPlayer();
    InitializeBluePlayer();
    anypawnselected = false;
}

//Initialize Blue Player
void game::InitializeBluePlayer()
{
    size_t player_rows = num_of_pions/(board_size/2);
    size_t col=0;

    for(size_t row=board_size-1;row>=board_size-player_rows;row--)
       {
            for(col;col<board_size;col=col+2)
            {
                field.type = pawn::PAWN;
                field.setDamka(false);
                field.side = pawn::BLUE;
                field.pos_x = row;
                field.pos_y = col;
                field.setCanAttack(false);
                field.setSelected(false);
                checkboard[row][col] = field;
                 }
            if(row%2==0) col = 0;
            else col = 1;
        }
 }

//Initialize Red Player
void game::InitializeRedPlayer()
{
    size_t player_rows = num_of_pions/(board_size/2);
    size_t col=1;

    for(size_t row=0;row<player_rows;row++)
        {
            for(col;col<board_size;col=col+2)
            {
                field.type = pawn::PAWN;
                field.setDamka(false);
                field.side = pawn::RED;
                field.pos_x = row;
                field.pos_y = col;
                field.setCanAttack(false);
                field.setSelected(false);
                checkboard[row][col] = field;
             }
            if(row%2==0) col = 0;
            else col = 1;
        }


}

//Initialize Empty Fields (fields on which pawn can move)
void game::InitializeEmptyFields()
{
size_t col = 1;

for(size_t row=0;row<board_size;row++)
  {
        for(col;col<board_size;col=col+2)
        {
            field.setEmptyField();
            checkboard[row][col] = field;
        }
        if(row%2==0) col = 0;
        else col = 1;
    }
}

//Initialize Forbidden Fields (fields between empty fields, on which pawns can't move)
void game::InitializeForbiddenFields()
{
    size_t col = 0;

    for(size_t row=0;row<board_size;row++)
        {
            for(col;col<board_size;col=col+2)
            {
                field.type = pawn::FORBIDDEN;
                field.setDamka(false);
                field.setSelected(false);
                field.setCanAttack(false);
                checkboard[row][col] = field;
            }
            if(row%2==0) col = 1;
            else col = 0;
        }
}

//Select Pawn at (row,column) position
void game::selectPawn(size_t row, size_t column)
{
    if(checkboard[row][column].type == pawn::PAWN)
    {
        checkboard[row][column].setSelected(true);
        anypawnselected = true;
    }
    else checkboard[row][column].setSelected(false);
}

//Deselect pawn at (row, column) position
void game::deselectPawn(size_t row, size_t column)
{
    if(checkboard[row][column].type == pawn::PAWN)
    {
        checkboard[row][column].setSelected(false);
        anypawnselected = false;
    }
    else checkboard[row][column].setSelected(false);
}

//If any pawn is selected, return true. Else return false
bool game::isAnyPawnSelected()
{
    if(anypawnselected==true) return true;
    else return false;
}

//Return (x,y) position of selected pawn
game::xy_pos game::SelectedPawn()
{
    xy_pos field_coord;
    for(size_t i=0;i<checkboard.size();i++)
    {
        for(size_t j=0;j<checkboard.size();j++)
        {
            if(checkboard[i][j].isSelected() == true)
            {
                field_coord.x = i;
                field_coord.y = j;
            }
            else;
        }
    }
    return field_coord;
}

//if pawn have enemy diagonally and there is EMPTY FIELD behind it, returns true
bool game::doesPawnHaveAttackPossibilities(size_t row, size_t col)
{
    bool up_left, up_right, down_left, down_right;
    bool canAttack;
    up_left = 1;
    up_right = 1;
    down_left = 1;
    down_right = 1;
    canAttack = 0;

    if(row == 0 || row == 1)
    {
        up_left = 0;
        up_right = 0;
    }
    else if(row == checkboard.size()-1 || row == checkboard.size()-2)
    {
        down_left = 0;
        down_right = 0;
    }
    if(col == 0 || col == 1)
    {
        up_left = 0;
        down_left = 0;
    }
    else if(col == checkboard.size()-1 || col == checkboard.size()-2)
    {
        up_right = 0;
        down_right = 0;
    }

    if(checkboard[row][col].side == pawn::RED && !checkboard[row][col].isDamka())
    {
        if(up_left)
        {
            if(checkboard[row-1][col-1].side == pawn::BLUE && checkboard[row-2][col-2].type == pawn::EMPTY_FIELD) canAttack = 1;
        }
        if(up_right)
        {
            if(checkboard[row-1][col+1].side == pawn::BLUE && checkboard[row-2][col+2].type == pawn::EMPTY_FIELD) canAttack = 1;
        }
        if(down_left)
        {
            if(checkboard[row+1][col-1].side == pawn::BLUE && checkboard[row+2][col-2].type == pawn::EMPTY_FIELD) canAttack = 1;
        }
        if(down_right)
        {
            if(checkboard[row+1][col+1].side == pawn::BLUE && checkboard[row+2][col+2].type == pawn::EMPTY_FIELD) canAttack = 1;
        }
    }
    else if(checkboard[row][col].side == pawn::BLUE && !checkboard[row][col].isDamka())
    {
        if(up_left)
        {
            if(checkboard[row-1][col-1].side == pawn::RED && checkboard[row-2][col-2].type == pawn::EMPTY_FIELD) canAttack = 1;
        }
        if(up_right)
        {
            if(checkboard[row-1][col+1].side == pawn::RED && checkboard[row-2][col+2].type == pawn::EMPTY_FIELD) canAttack = 1;
        }
        if(down_left)
        {
            if(checkboard[row+1][col-1].side == pawn::RED && checkboard[row+2][col-2].type == pawn::EMPTY_FIELD) canAttack = 1;
        }
        if(down_right)
        {
            if(checkboard[row+1][col+1].side == pawn::RED && checkboard[row+2][col+2].type == pawn::EMPTY_FIELD) canAttack = 1;
        }
    }

    else if(checkboard[row][col].isDamka())
    {
        if(up_left)
        {
            for(size_t i=2;i<checkboard.size();i++)
            {
                if(row-i>=0 && col-i>=0)
                {
                    if(isEnemyPawnBetweenPositions(row,col,row-i,col-i) && checkboard[row-i][col-i].type == pawn::EMPTY_FIELD &&
                       isAllEmptyBetweenPositions(row,col,row-i+2,col-i+2)) canAttack = 1;
                }
            }

        }
        if(up_right)
        {
            for(size_t i=2;i<checkboard.size();i++)
            {
                if(col+i<checkboard.size() && row-i>=0)
                {
                    if(isEnemyPawnBetweenPositions(row,col,row-i,col+i) && checkboard[row-i][col+i].type == pawn::EMPTY_FIELD &&
                       isAllEmptyBetweenPositions(row,col,row-i+2,col+i-2)) canAttack = 1;
                }
            }
        }
        if(down_left)
        {
            for(size_t i=2;i<checkboard.size();i++)
            {
                if(row+i<checkboard.size() && col-i>=0)
                {
                    if(isEnemyPawnBetweenPositions(row,col,row+i,col-i) && checkboard[row+i][col-i].type == pawn::EMPTY_FIELD &&
                       isAllEmptyBetweenPositions(row,col,row+i-2,col-i+2)) canAttack = 1;
                }
            }
        }
        if(down_right)
        {
            for(size_t i=2;i<checkboard.size();i++)
            {
                if(row+i<checkboard.size() && col+i<checkboard.size())
                {
                    if(isEnemyPawnBetweenPositions(row,col,row+i,col+i) && checkboard[row+i][col+i].type == pawn::EMPTY_FIELD &&
                       isAllEmptyBetweenPositions(row,col,row+i-2,col+i-2)) canAttack = 1;
                }
            }
        }
    }


    else canAttack = 0;

    if(canAttack) return true;
    else return false;

}

//If there is a single, enemy pawn between (prev_row,prev_col) and (new_row,new_col), return true
bool game::isEnemyPawnBetweenPositions(size_t prev_row, size_t prev_col, size_t new_row, size_t new_col)
{
size_t distance = labs(new_row-prev_row);
size_t single = 0;

for(size_t i=1;i<distance;i++)
{
    if(new_row>prev_row && new_col>prev_col)
    {
        if(checkboard[prev_row+i][prev_col+i].type == pawn::PAWN && checkboard[prev_row+i][prev_col+i].side != checkboard[prev_row][prev_col].side
                && checkboard[prev_row+i][prev_col+i].side != pawn::NONE) single++;
    }
    else if(new_row<prev_row && new_col<prev_col)
    {
        if(checkboard[prev_row-i][prev_col-i].type == pawn::PAWN && checkboard[prev_row-i][prev_col-i].side != checkboard[prev_row][prev_col].side
                && checkboard[prev_row-i][prev_col-i].side != pawn::NONE) single++;
    }
    else if(new_row<prev_row && new_col>prev_col)
    {
        if(checkboard[prev_row-i][prev_col+i].type == pawn::PAWN && checkboard[prev_row-i][prev_col+i].side != checkboard[prev_row][prev_col].side
                && checkboard[prev_row-i][prev_col+i].side != pawn::NONE) single++;
    }
    else if(new_row>prev_row && new_col<prev_col)
    {
        if(checkboard[prev_row+i][prev_col-i].type == pawn::PAWN && checkboard[prev_row+i][prev_col-i].side != checkboard[prev_row][prev_col].side
                && checkboard[prev_row+i][prev_col-i].side != pawn::NONE) single++;
    }
    else return false;
}

if(single==1) return true;
else return false;
}

//If there isn't any pawn between position (prev_row,prev_col) and position (new_row, new_col) return true
bool game::isAllEmptyBetweenPositions(size_t prev_row, size_t prev_col, size_t new_row, size_t new_col)
{
    size_t distance = labs(new_row-prev_row);
    bool allempty = 1;

    for(size_t i=1;i<distance;i++)
    {
        if(new_row>prev_row && new_col>prev_col)
        {
            if(checkboard[prev_row+i][prev_col+i].type == pawn::PAWN) allempty = 0;
        }
        else if(new_row<prev_row && new_col<prev_col)
        {
            if(checkboard[prev_row-i][prev_col-i].type == pawn::PAWN) allempty = 0;
        }
        else if(new_row<prev_row && new_col>prev_col)
        {
            if(checkboard[prev_row-i][prev_col+i].type == pawn::PAWN) allempty = 0;
        }
        else if(new_row>prev_row && new_col<prev_col)
        {
            if(checkboard[prev_row+i][prev_col-i].type == pawn::PAWN) allempty = 0;
        }
        else return false;
    }

    if(allempty) return true;
    else return false;
}

//Destroy all pawns between position (prev_row,prev_col) and position (new_row,new_col), diagonally
void game::KillPawnsBetweenPositions(size_t prev_row, size_t prev_col, size_t new_row, size_t new_col)
{
    size_t distance = labs(new_row-prev_row);

    for(size_t i=1;i<distance;i++)
    {
        if(new_row>prev_row && new_col>prev_col)
        {
            if(checkboard[prev_row+i][prev_col+i].type == pawn::PAWN) checkboard[prev_row+i][prev_col+i].setEmptyField();
        }
        else if(new_row<prev_row && new_col<prev_col)
        {
            if(checkboard[prev_row-i][prev_col-i].type == pawn::PAWN) checkboard[prev_row-i][prev_col-i].setEmptyField();
        }
        else if(new_row<prev_row && new_col>prev_col)
        {
            if(checkboard[prev_row-i][prev_col+i].type == pawn::PAWN) checkboard[prev_row-i][prev_col+i].setEmptyField();
        }
        else if(new_row>prev_row && new_col<prev_col)
        {
            if(checkboard[prev_row+i][prev_col-i].type == pawn::PAWN) checkboard[prev_row+i][prev_col-i].setEmptyField();
        }
        else;
    }
}

//Select pawn at position (row,column) - function checks if any pawn is selected and if any pawn can attack (if so, it forbidds selection of "non-attacking" pawn)
void game::Select(size_t row, size_t column)
{
    if(!isAnyPawnCanAttack())
    {
        //when a pawn is selected and player clicks on diffrent pawn, select the new one (only if pawn isn't in the middle of attack spree)
        if(isAnyPawnSelected() && !mustattack)
        {
            xy_pos selectedPawnCoords;
            selectedPawnCoords = SelectedPawn();
            deselectPawn(selectedPawnCoords.x, selectedPawnCoords.y);
            selectPawn(row,column);
        }
        //if pawn isn't selected and player clicks on a pawn, select it
        else if(!isAnyPawnSelected() && !mustattack)
        {
            selectPawn(row,column);
        }
        else ;
    }
    else if(isAnyPawnCanAttack())
    {
        if(isAnyPawnSelected() && !mustattack && checkboard[row][column].isAttacker())
        {
            xy_pos selectedPawnCoords;
            selectedPawnCoords = SelectedPawn();
            deselectPawn(selectedPawnCoords.x, selectedPawnCoords.y);
            selectPawn(row,column);
        }
        //if pawn isn't selected and player clicks on a pawn, select it
        else if(!isAnyPawnSelected() && !mustattack && checkboard[row][column].isAttacker())
        {
            selectPawn(row,column);
        }
        else ;
    }
}

//Move pawn to field (row,column)
void game::Move(size_t row, size_t column)
{
            xy_pos selectedPawnCoords;
            selectedPawnCoords = SelectedPawn();
            deselectPawn(selectedPawnCoords.x,selectedPawnCoords.y);

            //simple move for no-Damka pawn
            if(!checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isDamka() && checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isMoveAllowed(row,column))
            {
                MovePionToField(selectedPawnCoords.x,selectedPawnCoords.y,row,column);
                NextTurn();
            }
            //simple move for Damka pawn
            else if(checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isDamka() && isAllEmptyBetweenPositions(selectedPawnCoords.x,selectedPawnCoords.y,row,column)
                    && checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isMoveAllowed(row,column))
            {
                MovePionToField(selectedPawnCoords.x,selectedPawnCoords.y,row,column);
                NextTurn();
            }

            else status = "This pawn can't perform this move";
}

//Move pawn to field (row, column) and destroy pawn between selected pawn's position and new position
void game::Attack(size_t row, size_t column)
{
            xy_pos selectedPawnCoords;
            selectedPawnCoords = SelectedPawn();

            //Attack for no-Damka pawn
            if(!checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isDamka() && checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isMoveAllowed(row,column) &&
                    isEnemyPawnBetweenPositions(selectedPawnCoords.x,selectedPawnCoords.y,row,column) && labs(selectedPawnCoords.x-row)<3)
            {
                MovePionToField(selectedPawnCoords.x,selectedPawnCoords.y,row,column);
                KillPawnsBetweenPositions(selectedPawnCoords.x,selectedPawnCoords.y,row,column);
                if(doesPawnHaveAttackPossibilities(row,column)) checkboard[row][column].setCanAttack(true);
                else checkboard[row][column].setCanAttack(false);
                if(checkboard[row][column].isAttacker())
                {
                    mustattack = 1;
                }
                else
                {
                    deselectPawn(row,column);
                    mustattack = 0;
                    NextTurn();
                }
            }
            //Attack for Damka pawn
            else if(checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isDamka() && checkboard[selectedPawnCoords.x][selectedPawnCoords.y].isMoveAllowed(row,column) &&
                    isEnemyPawnBetweenPositions(selectedPawnCoords.x,selectedPawnCoords.y,row,column))
            {
                MovePionToField(selectedPawnCoords.x,selectedPawnCoords.y,row,column);
                KillPawnsBetweenPositions(selectedPawnCoords.x,selectedPawnCoords.y,row,column);
                if(doesPawnHaveAttackPossibilities(row,column)) checkboard[row][column].setCanAttack(true);
                else checkboard[row][column].setCanAttack(false);
                if(checkboard[row][column].isAttacker())
                {
                    mustattack = 1;
                }
                else
                {
                    deselectPawn(row,column);
                    mustattack = 0;
                    NextTurn();
                }
            }

            else status =  "Move forbidden, must attack!";
}

//If selected pawn color matches with current player's turn, return true
bool game::isMyTurn(size_t row, size_t col)
{
    if(checkboard[row][col].side == pawn::RED && turn == game::PLAYER_RED) return true;
    else if(checkboard[row][col].side == pawn::BLUE && turn == game::PLAYER_BLUE) return true;
    else return false;
}

//Changes turns (and if any pawn finish it's movement on the opposite side of the checkerboard, chang it to "Damka").
//Also, check if any pawn can attack
void game::NextTurn()
{
    if(turn == game::PLAYER_RED) turn = game::PLAYER_BLUE;
    else if(turn == game::PLAYER_BLUE) turn = game::PLAYER_RED;
    else;

    for(size_t i=0;i<checkboard.size();i++)
    {
        if(checkboard[0][i].side == pawn::BLUE) checkboard[0][i].setDamka(true);
        else if(checkboard[checkboard.size()-1][i].side == pawn::RED) checkboard[checkboard.size()-1][i].setDamka(true);
    }

    for(size_t row=0;row<checkboard.size();row++)
    {
        for(size_t col=0;col<checkboard[row].size();col++)
        {
            if(doesPawnHaveAttackPossibilities(row,col)) checkboard[row][col].setCanAttack(true);
            else checkboard[row][col].setCanAttack(false);
        }
    }
    status = "";
}

//If any pawn have attack possibilities, return true. Else return false
bool game::isAnyPawnCanAttack()
{
    if(turn == game::PLAYER_RED)
    {
        for(size_t row=0;row<checkboard.size();row++)
        {
            for(size_t col=0;col<checkboard[row].size();col++)
            {
                if(checkboard[row][col].side == pawn::RED && checkboard[row][col].isAttacker())
                {
                    status = "Red player must attack";
                    return true;
                }
            }
        }
    }
    else if(turn == game::PLAYER_BLUE)
    {
        for(size_t row=0;row<checkboard.size();row++)
        {
            for(size_t col=0;col<checkboard[row].size();col++)
            {
                if(checkboard[row][col].side == pawn::BLUE && checkboard[row][col].isAttacker())
                {
                    status = "Blue player must attack";
                    return true;
                }
            }
        }
    }
    else return false;
    return false;
}

//If any player loose all his pawns, return true. Else return false
bool game::isEndGame()
{
    size_t reds,blues;
    reds = 0;
    blues = 0;

    for(size_t row=0;row<checkboard.size();row++)
    {
        for(size_t col=0;col<checkboard[row].size();col++)
        {
            if(checkboard[row][col].side == pawn::RED) reds++;
            else if(checkboard[row][col].side == pawn::BLUE) blues++;
        }
    }

    if(reds == 0)
    {
        status = "BLUE PLAYER WON!";
        return true;
    }
    else if(blues == 0)
    {
        status = "RED PLAYER WON!";
        return true;
    }
    else return false;
}

//Set New Game
void game::NewGame()
{
    InitializeBoard();
    InitializePionPositions();
    turn = game::PLAYER_BLUE;
}
