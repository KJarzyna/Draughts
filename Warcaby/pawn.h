#ifndef PAWN_H
#define PAWN_H

class pawn
{
public:
    pawn();
    ~pawn();

    size_t pos_x;
    size_t pos_y;

    enum color{RED=3,BLUE=4,NONE=5};
    enum element{EMPTY_FIELD=0,PAWN=1,FORBIDDEN=2};
    color side;
    element type;

    void setPosition(size_t x, size_t y);
    void setDamka(bool bl);
    void setCanAttack(bool bl);
    void setSelected(bool bl);
    void setEmptyField();

    bool isDamka();
    bool isSelected();
    bool isAttacker();
    bool isMoveAllowed(size_t x, size_t y);
private:

    bool damka;
    bool canAttack;
    bool selected;




};

#endif // PAWN_H
