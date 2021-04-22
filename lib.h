//
// Created by loidt on 20/04/2021.
//

#ifndef SE2_LIB_H
#define SE2_LIB_H

struct data {
    char player1_name[16];
    int player1_score;
    char player1_color[6];
    char player2_name[16];
    int player2_score;
    char player2_color[6];
    char current_color[6];
    int move[2];
};

void InitializeGameSettings(char board[8][8]);
void PrintBoard(char board[8][8]);
void GetMove(void);
int IsEmptyMove(char board[8][8]);
void EndTurn(void);

#endif //SE2_LIB_H
