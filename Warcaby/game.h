#ifndef GAME_H
#define GAME_H
#include <string>
#include "pawn.h"
#include <vector>

class game
{
public:
    game();
    ~game();

    struct xy_pos
    {
        size_t x;
        size_t y;
    };

    enum player{PLAYER_RED,PLAYER_BLUE};

    void setBoardSize(size_t size);
    void setPawnNumber(size_t pwn_nmb);
    void NewGame();

    void Select(size_t row, size_t column);
    void Move(size_t row, size_t column);
    void Attack(size_t row, size_t column);
    void NextTurn();

    size_t getBoardSize();

    bool isAnyPawnSelected();
    bool isAnyPawnCanAttack();
    bool isMyTurn(size_t row, size_t col);
    bool isEndGame();

    std::string status;

    std::vector<std::vector<pawn>> checkboard;
    xy_pos SelectedPawn();
    player turn;

private:

    size_t board_size;
    size_t num_of_pions;

    pawn field;

    bool isEnemyPawnBetweenPositions(size_t prev_row, size_t prev_col, size_t new_row, size_t new_col);
    bool isAllEmptyBetweenPositions(size_t prev_row, size_t prev_col, size_t new_row, size_t new_col);

    bool doesPawnHaveAttackPossibilities(size_t row, size_t col);
    bool anypawnselected;
    bool mustattack;

    void InitializeBoard();
    void InitializePionPositions();
    void InitializeRedPlayer();
    void InitializeBluePlayer();
    void InitializeEmptyFields();
    void InitializeForbiddenFields();

    void selectPawn(size_t row, size_t column);
    void deselectPawn(size_t row, size_t column);

    void MovePionToField(size_t prev_row, size_t prev_col, size_t new_row, size_t new_col);
    void KillPawnsBetweenPositions(size_t prev_row, size_t prev_col, size_t new_row, size_t new_col);


};

#endif // GAME_H
