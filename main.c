#include "lib.h"

int main() {
    bool gameOver = false;

    /**Initialization**/
    InitializeGameSettings();
    PrintBoard();

    while (gameOver == false) {
        printf("Example of move input: 3 a (row goes first SEPARATED by a space for the column)\n\n");

        /**Ensuring validity of move**/
        bool valid = false;

        do {
            /*User Input for move*/
            GetMove();

            /*Tests for validity of move*/
            if (IsEmptyMove() == true) { //Spot is empty
                if (DirectionMove() == true) { //At least one direction had a disc with the same color
                    /*Results of the move*/
                    PrintScore();
                    PrintBoard();
                    EndTurn();
                    valid = true; //It has passed every test thus making it a valid move, ends loop
                }
                else {
                    printf("Invalid move because no direction has the same color!\n");
                }
            }
            else { //Spot isn't empty
                printf("Invalid move because it's not empty!\n");
            }

        } while (valid == false);

        /**Checking if game should end or move on to next player's turn**/
        if (NULL) {

            gameOver =true;
        }
        else { //Resetting variables for next player's turn
            valid = false;
        }
    }

    return 0;
}