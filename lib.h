//
// Created by loidt on 20/04/2021.
//

#ifndef SE2_LIB_H
#define SE2_LIB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct data {
    char player1_name[16];
    int player1_score;
    char player1_color[6];
    char player2_name[16];
    int player2_score;
    char player2_color[6];
    char current_color[6];
    int move[2];
    char board[8][8];
};

void InitializeGameSettings(void);
bool PossibleMoves(void);
void GetMove(void);
bool IsEmptyMove(void);
bool DirectionMove(bool modifyBoard);
void SpotCapture(void);
void NonSpotCapture(void);
bool North(bool modifyBoard);
bool NorthEast(bool modifyBoard);
bool East(bool modifyBoard);
bool SouthEast(bool modifyBoard);
bool South(bool modifyBoard);
bool SouthWest(bool modifyBoard);
bool West(bool modifyBoard);
bool NorthWest(bool modifyBoard);
void PrintTurn(void);
void SwitchTurn(void);

#endif //SE2_LIB_H
