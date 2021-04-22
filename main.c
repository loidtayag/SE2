#include <stdio.h>
#include <stdbool.h>
#include "lib.h"

int main() {
    /*Variables needed by the functions*/
    struct data Data;
    char board[8][8] = {0};
    int move[2];
    bool valid = false;
    bool gameOver = false;

    /*Setting up*/
    InitializeGameSettings(&Data, board);
    PrintBoard(board);

    while (gameOver == false) {
        /*Checking if spot is empty*/
        printf("Example of move input: 3 a (row goes first SEPARATED by a space for the column)\n\n");
        do {
            /*User Input for move*/
            GetMove(&Data, move);

            if (IsEmptyMove(board, move) == true) { //Spot is empty
                valid = true;
            } else { //Spot isn't empty
                printf("Invalid move\n");
            }
        } while (valid == false);

        /*Checking all directions*/


        /*Switching turns*/
        EndTurn(&Data);
        PrintBoard(board);
    }

    return 0;
}