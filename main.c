#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct data {
    char player1_name[16];
    char player2_name[16];
    char player1_color[6];
    char player2_color[6];
    char current_color[6];
    int player1_score;
    int player2_score;
};

void InitializeGameSettings(struct data * data, char board[8][8]);
void PrintBoard(char board[8][8]);

int main() {
    struct data Data;
    char board[8][8] = {0};

    InitializeGameSettings(&Data, board);
    PrintBoard(board);

    return 0;
}

void InitializeGameSettings(struct data * Data, char board[8][8]) {
    printf("\n---Welcome to Othello---\n\n");

    /*Name Initialization*/
    printf("Enter player 1 name: ");
    scanf("%s", Data->player1_name);
    printf("Enter player 2 name: ");
    scanf("%s", Data->player2_name);

    /*Score Initialization*/
    Data->player1_score = 0;
    Data->player2_score = 0;

    /*Board Initialization*/
    //Without 'strtok' you'd be assigning a char array of size 2 e.g. "W" + "\0"
    board[4][4] = *strtok("W", "\0");
    board[4][5] = *strtok("B", "\0");
    board[5][4] = *strtok("B", "\0");
    board[5][5] = *strtok("W", "\0");

    /*Random Disc Color Initialization*/
    srand(time(NULL)); // Set random seed

    if ((rand() % 2) == 1) { //1 is rolled
        strcpy(Data->player1_color, "black");
        strcpy(Data->player2_color, "white");
    }
    else { //0 is rolled
        strcpy(Data->player1_color, "white");
        strcpy(Data->player2_color, "black");
    }

    printf("Random 50-50 assignment of colors has been completed, %s is %s and %s is %s\n\n", Data->player1_name, Data->player1_color, Data->player2_name, Data->player2_color);
}

void PrintBoard(char board[8][8]) {
    for (int i = 0; i < 9; ++i) { //Row Index
        printf("     ---------------------------------\n"); //Row Splitter
        (i != 8) ? (printf("  %i  ", i + 1)) : (printf("     ")); //Don't want to show '9' in row 9
        for (int j = 0; j < 8; ++j) { //Column Index
            (i != 8) ? (printf("| %i ", board[i][j])) : (printf("  %c ", 97 + j)); //Don't want to show '|' before each letter in row 9
        }
        (i != 8) ? (printf("|\n")) : (printf("\n")); //Don't want to show '|' at the end of the letters in row 9
    }
}

