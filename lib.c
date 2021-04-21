//
// Created by loidt on 20/04/2021.
//

#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void InitializeGameSettings(struct data * Data, char board[8][8]) {
    printf("\n---Welcome to Othello---\n\n");

    /*Name Initialization*/
    printf("Enter player 1 name: ");
    scanf("%s", Data->player1_name);
    printf("Enter player 2 name: ");
    scanf("%s", Data->player2_name);

    /*Score Initialization*/
    Data->player1_score = 2;
    Data->player2_score = 2;

    /*Board Initialization*/
    //Without 'strtok' you'd be assigning a char array of size 2 e.g. "W" + "\0"
    board[3][3] = *strtok("W", "\0");
    board[3][4] = *strtok("B", "\0");
    board[4][3] = *strtok("B", "\0");
    board[4][4] = *strtok("W", "\0");

    /*Random Disc Color Initialization*/
    strcpy(Data->current_color, "black"); //Set starting color
    srand(time(NULL)); // Set random seed

    if ((rand() % 2) == 1) { //1 is rolled
        strcpy(Data->player1_color, "black");
        strcpy(Data->player2_color, "white");
    }
    else { //0 is rolled
        strcpy(Data->player1_color, "white");
        strcpy(Data->player2_color, "black");
    }
    printf("Random 50-50 assignment of colors has been completed, %s is %s and %s is %s\n\n",
           Data->player1_name, Data->player1_color, Data->player2_name, Data->player2_color);
}

void PrintBoard(char board[8][8]) {
    for (int i = 0; i < 9; ++i) { //Row Index
        printf("     ---------------------------------\n"); //Row Splitter
        (i != 8) ? (printf("  %i  ", i + 1)) : (printf("     ")); //In row 9, don't want to show '9'
        for (int j = 0; j < 8; ++j) { //Column Index
            //In row 9, don't want to show '|' before each letter in row 9 and to show letter value not numerical value
            (i != 8) ? (printf("| %c ", board[i][j])) : (printf("  %c ", 97 + j));
        }
        (i != 8) ? (printf("|\n")) : (printf("\n")); //In row 9, don't want to show '|' at the end of the letters
    }

    /*After each play you want it to separate the plays clearly*/
    printf("\n\n-------------------------------------------------------------------------\n\n");
}

void Move(struct data * Data, int move[2]) {
    char temp[2]; //to store Column move so that we can convert it to an integer
    printf("Example of move input: 3 a (row goes first SEPARATED by a space for the column)\n\n");

    /*Check which player's turn it is*/
    (strcmp(Data->current_color, Data->player1_color) == 0)?
    (printf("%s, enter your move: ", Data->player1_name)): //Player 1's turn
    (printf("%s, enter your move: ", Data->player2_name)); //Player 2's turn

    /*Read in player's move and convert to index form*/
    fscanf(stdin, "%i %c", &move[0], temp);
    move[0]--; //Getting correct row index
    move[1] = temp[0] - 97; //Getting correct column index

//    printf("Move inputted in index: %i %i\n\n", move[0], move[1]);
}

int IsEmpty(char board[8][8], int move[2]) {
    //Checking to see if it has a 'W' or 'B' in it already
    return (strcmp(&board[move[0]][move[1]], "B") != 0 && strcmp(&board[move[0]][move[1]], "W") != 0);
}