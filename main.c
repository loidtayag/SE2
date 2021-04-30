#include "lib.h"

int main() {
    bool gameOver = false;
    bool validMove = false;

    /*Initialization*/
    InitializeGameSettings();
    PrintTurn();

    while (gameOver == false) {
        /*Ensuring validity of move*/
        do {
            /*User Input for move*/
            GetMove();

            /*Tests for validity of move*/
            if (IsEmptyMove() == true) { //Spot is empty
                if (DirectionMove() == true) { //At least one direction had at least one disc to be captured
                    validMove = true; //It has passed every test thus making it a valid move, ends loop
                }
                else { //No direction had at least one disc to be captured
                    printf("Invalid move because no direction captured at least one disc!\n");
                }
            }
            else { //Spot isn't empty
                printf("Invalid move because it's not empty!\n");
            }
        } while (validMove == false);

        /*Results of the move*/
        PrintTurn();

        /*Checking if game should end or move on to next player's turn*/
        if (NULL) { //Ending game
            gameOver = true;
        }
        else { //Resetting variables for next player's turn
            SwitchTurn();
            validMove = false;
        }
    }

    return 0;
}