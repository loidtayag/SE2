#include "lib.h"

int main() {
    bool gameOver = false;
    bool validMove = false;

    /*Initialization*/
    InitializeGameSettings();
    PrintTurn();

    while (gameOver == false) {
        if (PossibleMoves() == true) { //Passes if there is an available move
            do { //Ensuring validity of move input
                GetMove();
                if (IsEmptyMove() == true) { //Passes if spot is empty
                    if (DirectionMove(true) == true) { //Passes if spot had at least one direction that would result in at least one capture
                        validMove = true; //It has passed every test thus making it a valid move, ends loop
                    }
                    else { //Fails if spot had no direction that would result in at least one disc capture
                        printf("Invalid move because no direction captured at least one disc!\n\n");
                    }
                }
                else { //Fails if spot isn't empty
                    printf("Invalid move because it's not empty!\n\n");
                }
            } while (validMove == false);
        }
        else { //Fails if no available moves, hence end turn
            printf("Unfortunately, you have no available moves left therefore your turn must be skipped!\n");
            validMove = true;
        }


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