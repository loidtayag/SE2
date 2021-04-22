#include <stdio.h>
#include <stdbool.h>
#include "lib.h"

int main() {
    /*Variables needed by the functions*/
    char board[8][8] = {0};
    bool valid = false;
    bool gameOver = false;

    /*Setting up*/
    InitializeGameSettings(board);
    PrintBoard(board);

    while (gameOver == false) {
        /*Checking if spot is empty*/
        printf("Example of move input: 3 a (row goes first SEPARATED by a space for the column)\n\n");
        do {
            /*User Input for move*/
            GetMove();

            if (IsEmptyMove(board) == true) { //Spot is empty
                valid = true;
            } else { //Spot isn't empty
                printf("Invalid move\n");
            }
        } while (valid == false);

        /*Checking all directions*/


        /*Switching turns*/
        EndTurn();
        PrintBoard(board);

        /*Restting variables*/
        valid = false;
    }

    return 0;
}