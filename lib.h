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

struct end {
    bool player1_passed;
    bool player2_passed;
    int combined_score;
};

void InitializeGameSettings(void);
bool PossibleMoves(void);
void GetMove(void);
bool IsEmptyMove(void);
bool DirectionMove(bool modify);
void SpotCapture(void);
void NonSpotCapture(void);
bool North(bool modify);
bool NorthEast(bool modify);
bool East(bool modify);
bool SouthEast(bool modify);
bool South(bool modify);
bool SouthWest(bool modify);
bool West(bool modify);
bool NorthWest(bool modify);
int whosTurn(void);
int displayTurn(void);
void switchTurn(void);
void endGame(void);

#endif //SE2_LIB_H
