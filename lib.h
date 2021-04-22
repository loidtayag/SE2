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
};

void InitializeGameSettings(struct data * Data, char board[8][8]);
void PrintBoard(char board[8][8]);
void GetMove(struct data * Data, int move[2]);
int IsEmptyMove(char board[8][8], const int move[2]);
void EndTurn(struct data * Data);

#endif //SE2_LIB_H
