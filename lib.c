//
// Created by loidt on 20/04/2021.
//

#include "lib.h"

struct data Data;

void InitializeGameSettings(void) {
    printf("\n---Welcome to Othello---\n\n");

    /*Name Initialization*/
    printf("Enter player 1 name: ");
    scanf("%s", Data.player1_name);
    printf("Enter player 2 name: ");
    scanf("%s", Data.player2_name);

    /*Board Initialization*/
    Data.board[3][3] = 'W';
    Data.board[3][4] = 'B';
    Data.board[4][3] = 'B';
    Data.board[4][4] = 'W';

    /*Score Initialization*/
    Data.player1_score = 2;
    Data.player2_score = 2;

    /*Random Disc Color Initialization*/
    strcpy(Data.current_color, "Black"); //Set starting color
    srand(time(NULL)); // Set random seed

    if ((rand() % 2) == 1) { //1 is rolled therefore player 1 is black
        strcpy(Data.player1_color, "Black");
        strcpy(Data.player2_color, "White");
    }
    else { //0 is rolled therefore player 2 is black
        strcpy(Data.player1_color, "White");
        strcpy(Data.player2_color, "Black");
    }

    printf("Random 50-50 assignment of colors has been completed, %s is %s and %s is %s.",
           Data.player1_name, Data.player1_color, Data.player2_name, Data.player2_color);

    /*For separating*/
    printf("\n\n------------------------------------------------------------------------------\n\n"
           "Example of move input: 3 d (row number + space + column letter)\n\n");
}

bool PossibleMoves(void) {
    bool possibleMoves = false;

    /*Check to see if there is any valid moves left*/
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Data.move[0] = i;
            Data.move[1] = j;
            if (IsEmptyMove() == true) {
                if (DirectionMove(false) == true) {
                    possibleMoves = true;
                    printf("%i %c\n", Data.move[0] + 1, Data.move[1] + 97);
                }
            }
        }
    }

    if (possibleMoves == true) {
        printf("The above are the moves you can make.\n\n");
    }

    return possibleMoves;
}

void GetMove(void) {
    char temp[2]; //to store Column move so that we can convert it to an integer

    /*Check which player's turn it is*/
    Data.player1_color[0] == Data.current_color[0]?
    printf("%s, enter your move: ", Data.player1_name): //Player 1's turn
    printf("%s, enter your move: ", Data.player2_name); //Player 2's turn

    /*Read in player's move and convert to index form*/
    fscanf(stdin, "%i %c", &Data.move[0], temp);
    Data.move[0]--; //Getting correct row index
    Data.move[1] = temp[0] - 97; //Getting correct column index using ascii code
}

bool IsEmptyMove(void) {
    //Checking to see if it has a 'W' or 'B' in it already by using ascii code for char comparison
    return Data.board[Data.move[0]][Data.move[1]] != 66 && Data.board[Data.move[0]][Data.move[1]] != 87;
}

bool DirectionMove(bool modify) {
    bool validDirections = false;

    /*We have to execute and check each one individually because 'or conditions' would cause a problem.
    Let's say 'North()' was true, because we use 'or conditions' the following functions wouldn't be executed
    because we only need one to be true i.e. it would not allow for multiple directions to be changed.*/
    if (North(modify) == true) {validDirections = true;}
    if (NorthEast(modify) == true) {validDirections = true;}
    if (East(modify) == true) {validDirections = true;}
    if (SouthEast(modify) == true) {validDirections = true;}
    if (South(modify) == true) {validDirections = true;}
    if (SouthWest(modify) == true) {validDirections = true;}
    if (West(modify) == true) {validDirections = true;}
    if (NorthWest(modify) == true) {validDirections = true;}
    if (validDirections == true && modify == true) {SpotCapture();} //Score calculator

    return validDirections;
}

void SpotCapture(void) {
    printf("eeee\n");
    (Data.player1_color[0] == Data.current_color[0])? //Check whose spot it is
    Data.player1_score++: //Player 1's spot
    Data.player2_score++; //Player 2's spot
}

void NonSpotCapture(void) {
    if (Data.player1_color[0] == Data.current_color[0]) { //Player 1 is capturing
        printf("Player 1 captured!\n");
        Data.player1_score++;
        Data.player2_score--;
    }
    else { //Player 2 is capturing
        printf("Player 1 captured!\n");
        Data.player2_score++;
        Data.player1_score--;
    }
}

bool North(bool modify) {
    int jumpCounter = -1; //Keeps track of the index of the last disc of the same color
    bool capture = false; //Change to 'true' if we capture at least one disc

    //Starting at index above spot, loop to check how far until the final same colored disc is found
    for (int row = Data.move[0] - 1; Data.board[row][Data.move[1]] != 0 && row > -1; --row) {
        if (Data.board[row][Data.move[1]] == Data.current_color[0]) { //Passes if same color is found
            jumpCounter = row;
        }
    }

    if (jumpCounter != -1) { //Passes if same color was found
        //Starting at index above spot, loop to check if it would result in at least 1 capture
        for (int row = Data.move[0] - 1; row >= jumpCounter; --row) {
            if (Data.board[row][Data.move[1]] != Data.current_color[0]) { //Passes if opposite color is found
                if (modify == true) {
                    NonSpotCapture(); //Score calculator
                }
                capture = true;
            }
        }

        if (capture == true && modify == true) { //Passes if above loop found at least one capture
            //Starting at spot, loop to replace every disc with 'current_color'
            for (int row = Data.move[0]; row >= jumpCounter; --row) {
                Data.board[row][Data.move[1]] = Data.current_color[0];
            }
        }
    }

    return capture;
}

bool NorthEast(bool modify) {
    int jumpCounter = -1; //Keeps track of the index of the last disc of the same color
    bool capture = false; //Change to 'true' if we capture at least one disc

    //Starting at index that is to the top-right of spot, loop to check how far until the final same colored disc is found
    int row = Data.move[0] - 1;
    int column = Data.move[1] + 1;
    while (Data.board[row][column] != 0 && row > -1 && column < 8) {
        if (Data.board[row][column] == Data.current_color[0]) { //Passes if same color is found
            jumpCounter = row;
        }
        --row;
        ++column;
    }

    if (jumpCounter != -1) { //Passes if same color was found
        //Starting at index that is to the top-right of spot, loop to check if it would result in at least 1 capture
        row = Data.move[0] - 1;
        column = Data.move[1] + 1;
        while (row >= jumpCounter) {
            if (Data.board[row][column] != Data.current_color[0]) { //Passes if opposite color is found
                if (modify == true) {
                    NonSpotCapture(); //Score calculator
                }
                capture = true;
            }
            --row;
            ++column;
        }

        if (capture == true && modify == true) { //Passes if above loop found at least one capture
            //Starting at spot, loop to replace every disc with 'current_color'
            row = Data.move[0];
            column = Data.move[1];
            while (row >= jumpCounter) {
                Data.board[row][column] = Data.current_color[0];
                --row;
                ++column;
            }
        }
    }

    return capture;
}

bool East(bool modify) {
    int jumpCounter = -1; //Keeps track of the index of the last disc of the same color
    bool capture = false; //Change to 'true' if we capture at least one disc

    //Starting at index that's to the right of spot, loop to check how far until the final same colored disc is found
    for (int column = Data.move[1] + 1; Data.board[Data.move[0]][column] != 0 && column < 8; ++column) {
        if (Data.board[Data.move[0]][column] == Data.current_color[0]) { //Passes if same color is found
            jumpCounter = column;
        }
    }

    if (jumpCounter != -1) { //Passes if same color was found
        //Starting at index that's to the right of spot, loop to check if it would result in at least 1 capture
        for (int column = Data.move[1] + 1; column <= jumpCounter; ++column) {
            if (Data.board[Data.move[0]][column] != Data.current_color[0]) { //Passes if opposite color is found
                if (modify == true) {
                    NonSpotCapture(); //Score calculator
                }
                capture = true;
            }
        }

        if (capture == true && modify == true) { //Passes if above loop found at least one capture
            //Starting at spot, loop to replace every disc with 'current_color'
            for (int column = Data.move[1]; column <= jumpCounter; ++column) {
                Data.board[Data.move[0]][column] = Data.current_color[0];
            }
        }
    }

    return capture;
}

bool SouthEast(bool modify) {
    int jumpCounter = -1; //Keeps track of the index of the last disc of the same color
    bool capture = false; //Change to 'true' if we capture at least one disc

    //Starting at index that is to the bottom-right of spot, loop to check how far until the final same colored disc is found
    int row = Data.move[0] + 1;
    int column = Data.move[1] + 1;
    while (Data.board[row][column] != 0 && row < 8 && column < 8) {
        if (Data.board[row][column] == Data.current_color[0]) { //Passes if same color is found
            jumpCounter = row;
        }
        ++row;
        ++column;
    }

    if (jumpCounter != -1) { //Passes if same color was found
        //Starting at index that is to the bottom-right of spot, loop to check if it would result in at least 1 capture
        row = Data.move[0] + 1;
        column = Data.move[1] + 1;
        while (row <= jumpCounter) {
            if (Data.board[row][column] != Data.current_color[0]) { //Passes if opposite color is found
                if (modify == true) {
                    NonSpotCapture(); //Score calculator
                }
                capture = true;
            }
            ++row;
            ++column;
        }

        if (capture == true && modify == true) { //Passes if above loop found at least one capture
            //Starting at spot, loop to replace every disc with 'current_color'
            row = Data.move[0];
            column = Data.move[1];
            while (row <= jumpCounter) {
                Data.board[row][column] = Data.current_color[0];
                ++row;
                ++column;
            }
        }
    }

    return capture;
}

bool South(bool modify) {
    int jumpCounter = -1; //Keeps track of the index of the last disc of the same color
    bool capture = false; //Change to 'true' if we capture at least one disc

    //Starting at index below spot, loop to check how far until the final same colored disc is found
    for (int row = Data.move[0] + 1; Data.board[row][Data.move[1]] != 0 && row < 8; ++row) {
        if (Data.board[row][Data.move[1]] == Data.current_color[0]) { //Passes if same color is found
            jumpCounter = row;
        }
    }

    if (jumpCounter != -1) { //Passes if same color was found
        //Starting at index below spot, loop to check if it would result in at least 1 capture
        for (int row = Data.move[0] + 1; row <= jumpCounter; ++row) {
            if (Data.board[row][Data.move[1]] != Data.current_color[0]) { //Passes if opposite color is found
                if (modify == true) {
                    NonSpotCapture(); //Score calculator
                }
                capture = true;
            }
        }

        if (capture == true && modify == true) { //Passes if above loop found at least one capture
            //Starting at spot, loop to replace every disc with 'current_color'
            for (int row = Data.move[0]; row <= jumpCounter; ++row) {
                Data.board[row][Data.move[1]] = Data.current_color[0];
            }
        }
    }

    return capture;
}

bool SouthWest(bool modify) {
    int jumpCounter = -1; //Keeps track of the index of the last disc of the same color
    bool capture = false; //Change to 'true' if we capture at least one disc

    //Starting at index that is to the bottom-left of spot, loop to check how far until the final same colored disc is found
    int row = Data.move[0] + 1;
    int column = Data.move[1] - 1;
    while (Data.board[row][column] != 0 && row < 8 && column > -1) {
        if (Data.board[row][column] == Data.current_color[0]) { //Passes if same color is found
            jumpCounter = row;
        }
        ++row;
        --column;
    }

    if (jumpCounter != -1) { //Passes if same color was found
        //Starting at index that is to the bottom-left of spot, loop to check if it would result in at least 1 capture
        row = Data.move[0] + 1;
        column = Data.move[1] - 1;
        while (row <= jumpCounter) {
            if (Data.board[row][column] != Data.current_color[0]) { //Passes if opposite color is found
                if (modify == true) {
                    NonSpotCapture(); //Score calculator
                }
                capture = true;
            }
            ++row;
            --column;
        }

        if (capture == true && modify == true) { //Passes if above loop found at least one capture
            //Starting at spot, loop to replace every disc with 'current_color'
            row = Data.move[0];
            column = Data.move[1];
            while (row <= jumpCounter) {
                Data.board[row][column] = Data.current_color[0];
                ++row;
                --column;
            }
        }
    }

    return capture;
}

bool West(bool modify) {
    int jumpCounter = -1; //Keeps track of the index of the last disc of the same color
    bool capture = false; //Change to 'true' if we capture at least one disc

    //Starting at index that's to the left of spot, loop to check how far until the final same colored disc is found
    for (int column = Data.move[1] - 1; Data.board[Data.move[0]][column] != 0 && column > -1; --column) {
        if (Data.board[Data.move[0]][column] == Data.current_color[0]) { //Passes if same color is found
            jumpCounter = column;
        }
    }

    if (jumpCounter != -1) { //Passes if same color was found
        //Starting at index that's to the left of spot, loop to check if it would result in at least 1 capture
        for (int column = Data.move[1] - 1; column >= jumpCounter; --column) {
            if (Data.board[Data.move[0]][column] != Data.current_color[0]) { //Passes if opposite color is found
                if (modify == true) {
                    NonSpotCapture(); //Score calculator
                }
                capture = true;
            }
        }

        if (capture == true && modify == true) { //Passes if above loop found at least one capture
            //Starting at spot, loop to replace every disc with 'current_color'
            for (int column = Data.move[1]; column >= jumpCounter; --column) {
                Data.board[Data.move[0]][column] = Data.current_color[0];
            }
        }
    }

    return capture;
}

bool NorthWest(bool modify) {
    int jumpCounter = -1; //Keeps track of the index of the last disc of the same color
    bool capture = false; //Change to 'true' if we capture at least one disc

    //Starting at index that is to the top-left of spot, loop to check how far until the final same colored disc is found
    int row = Data.move[0] - 1;
    int column = Data.move[1] - 1;
    while (Data.board[row][column] != 0 && row > -1 && column > -1) {
        if (Data.board[row][column] == Data.current_color[0]) { //Passes if same color is found
            jumpCounter = row;
        }
        --row;
        --column;
    }

    if (jumpCounter != -1) { //Passes if same color was found
        //Starting at index that is to the top-left of spot, loop to check if it would result in at least 1 capture
        row = Data.move[0] - 1;
        column = Data.move[1] - 1;
        while (row >= jumpCounter) {
            if (Data.board[row][column] != Data.current_color[0]) { //Passes if opposite color is found
                if (modify == true) {
                    NonSpotCapture(); //Score calculator
                }
                capture = true;
            }
            --row;
            --column;
        }

        if (capture == true && modify == true) { //Passes if above loop found at least one capture
            //Starting at spot, loop to replace every disc with 'current_color'
            row = Data.move[0];
            column = Data.move[1];
            while (row >= jumpCounter) {
                Data.board[row][column] = Data.current_color[0];
                --row;
                --column;
            }
        }
    }

    return capture;
}

int whosTurn(void) {
    if (Data.player1_color[0] == Data.current_color[0]) {
        return 1;
    }
    else {
        return 2;
    }
}

int displayTurn(void) {
    printf("\n"); //Separates move input line and board
    for (int i = 0; i < 9; ++i) { //Row Index
        /*Board*/
        printf("     ---------------------------------\n"); //Row Splitter
        (i != 8) ? (printf("  %i  ", i + 1)) : (printf("     ")); //In row 9, don't want to show '9'
        for (int j = 0; j < 8; ++j) { //Column Index
            //In row 9, don't want to show '|' before each letter
            (i != 8) ? (printf("| %c ", Data.board[i][j])) : (printf("  %c ", 97 + j));
        }
        (i != 8) ? (printf("|")) : (printf(" ")); //In row 9, don't want to show '|' at the end of the letters

        /*Scoreboard*/
        switch (i) {
            case 2:
                printf("      __________________________________\n");
                break;
            case 3:
                printf("      -%10s (%s): %i           -\n", Data.player1_name, Data.player1_color, Data.player1_score);
                break;
            case 4:
                printf("      -%10s (%s): %i           -\n", Data.player2_name, Data.player2_color, Data.player2_score);
                break;
            case 5:
                printf("      __________________________________\n");
                break;
            default:
                printf("\n");
                break;
        }
    }
    printf("\n\n------------------------------------------------------------------------------\n\n"); //Separates turns

    return (Data.player1_score + Data.player2_score);
}

void switchTurn(void) {
    strcmp(Data.current_color, "Black") == 0 ?
    strcpy(Data.current_color, "White") : //End black's turn
    strcpy(Data.current_color, "Black"); //End white's turn
}