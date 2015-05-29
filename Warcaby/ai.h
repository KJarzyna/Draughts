#ifndef AI_H
#define AI_H
#include "game.h"
#include <QVector>

class ai
{
public:
    ai();
    ~ai();

    QVector<game::xy_pos> pawn_list;

  void MakeMuve(game checkers);

  QVector<QVector<pawn>> board;
  game::player temp_turn;

private:
  bool isAnyCanMove();
  bool doesPawnCanMove(game checkers, int row, int col);
  bool possibleAttacks(game checkers, int row, int col);
};

#endif // AI_H
