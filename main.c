#include "lib.h"
bool BothPassed(struct end End);

int main() {
    struct end End;
    End.player1_passed = false;
    End.player2_passed = false;
    End.combined_score = 4;

    /*Initialization*/
    InitializeGameSettings();
    EndTurn();

    /*Turn Simulation*/
    while (End.combined_score < 65 || BothPassed(End) == false) {
        /*Move Input*/
        if (PossibleMoves() == true) { //Passes if there is an available move
            bool validMove = false;
            do { //Ensuring validity of move
                GetMove();
                if (IsEmptyMove() == true) { //Spot is empty
                    if (DirectionMove(true) == true) { //Spot had at least one direction that would result in at least one capture
                        whosTurn() == 1 ? (End.player1_passed = true): (End.player2_passed = true);
                        validMove = true; //It has passed every test thus making it a valid move, ends loop
                    }
                    else { //Spot had no direction that would result in at least one capture
                        printf("Invalid move because no direction captured at least one disc!\n\n");
                    }
                }
                else { //Spot isn't empty
                    printf("Invalid move because it's not empty!\n\n");
                }
            } while (validMove == false);
        }
        else { //Fails if no available moves, hence end turn
            printf("Unfortunately, you have no available moves left therefore your turn must be skipped!\n");
            whosTurn() == 1 ? (End.player1_passed = true): (End.player2_passed = true);
        }

        /*End of turn*/
        End.combined_score = EndTurn();
        SwitchTurn();
    }

    if (End.combined_score > 64) {
        printf("The board has been filled, game ending...");
    }
    else {
        printf("Neither players have any available moves, game ending");
    }

    return 0;
}

bool BothPassed(struct end End) {
    return End.player1_passed == true && End.player2_passed == true;
}