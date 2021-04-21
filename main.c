#include <stdio.h>
#include <stdbool.h>
#include "lib.h"

int main() {
    /*Variables needed by the functions*/
    struct data Data;
    char board[8][8] = {0};
    int move[2];
    bool valid = false;

    /*Setting up*/
    InitializeGameSettings(&Data, board);
    PrintBoard(board);

    /*PLaying the game*/
    do {
        Move(&Data, move);  //Getting user input for move

        if (IsEmpty(board, move) == true) { //Spot is empty
            printf("Valid move\n");
            valid = true;
        }
        else { //Spot isn't empty
            printf("Invalid move\n");
        }
    } while (valid == false);


    return 0;
}