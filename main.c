#include <stdio.h>
#include <stdbool.h>
#include "lib.h"

int main() {
    bool valid = false;
    bool gameOver = false;

    /*Setting up*/
    InitializeGameSettings();
    PrintBoard();

    while (gameOver == false) {
        /*Checking if spot is empty*/
        printf("Example of move input: 3 a (row goes first SEPARATED by a space for the column)\n\n");
        do {
            /*User Input for move*/
            GetMove();

            /*Checking if it's empty*/
            if (IsEmptyMove() == true) { //Spot is empty
                valid = true;
            } else { //Spot isn't empty
                printf("Invalid move because it's not empty!\n");
            }

            /*Checking all directions*/
            if (DirectionMove() == false) { //No direction had any discs with the same color
                valid = false;
                printf("Invalid move because no direction has the same color!\n");
            }
        } while (valid == false);

        /*Switching turns*/
        EndTurn();
        PrintBoard();

        /*Resetting variables*/
        valid = false;
    }

    return 0;
}