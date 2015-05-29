#include "pawn.h"

pawn::pawn()
{

}

pawn::~pawn()
{

}

//If pawn is Damka, return true. Else return false.
bool pawn::isDamka()
{
    return damka;
}

//Set if pawn is damka or not
void pawn::setDamka(bool bl)
{
    damka = bl;
}

//Set if pawn can attack or not
void pawn::setCanAttack(bool bl)
{
    canAttack = bl;
}

//Set position (x,y) of pawn. x = row, y = column
void pawn::setPosition(size_t x, size_t y)
{
    pos_x = x;
    pos_y = y;
}

//If pawn can attack, return true. Else return false.
bool pawn::isAttacker()
{
    return canAttack;
}

//If pawn is selected, return true. Else return false.
bool pawn::isSelected()
{
    return selected;
}

//Sets if pawn is selected
void pawn::setSelected(bool bl)
{
    selected = bl;
}

//checks if field at (x,y) is in pawn's allowed moves (for example, a simple pawn can move only diagonaly and forward)
bool pawn::isMoveAllowed(size_t x, size_t y)
{
    if(isDamka())
    {
            for(size_t i=0;i<10;i++)
            {
                if(x==pos_x+i && y==pos_y+i) return true;
                else if(x==pos_x+i && y==pos_y-i) return true;
                else if(x==pos_x-i && y==pos_y+i) return true;
                else if(x==pos_x-i && y==pos_y-i) return true;
            }
            return false;

    }
    else if(!canAttack && !isDamka())
    {
        if(side==pawn::RED)
        {
            if(x==pos_x+1 && y==pos_y+1 ||
               x==pos_x+1 && y==pos_y-1) return true;
            else return false;
        }
        else if(side==pawn::BLUE)
        {
            if(x==pos_x-1 && y==pos_y+1 ||
               x==pos_x-1 && y==pos_y-1) return true;
            else return false;
        }
        else return false;
    }
    else if(canAttack && !isDamka())
    {
        if(type == pawn::PAWN)
        {
            if(x==pos_x+2 && y==pos_y+2 ||
               x==pos_x+2 && y==pos_y-2 ||
               x==pos_x-2 && y==pos_y+2 ||
               x==pos_x-2 && y==pos_y-2) return true;
            else return false;
        }
        else return false;
    }
    else return false;

}

//Set pawn as Empty Field
void pawn::setEmptyField()
{
    setSelected(false);
    setDamka(false);
    setCanAttack(false);
    type = pawn::EMPTY_FIELD;
    side = pawn::NONE;
}


