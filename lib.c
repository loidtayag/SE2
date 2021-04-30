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
    Data.board[3][3] = 'W'; //Without 'strtok' you'd be assigning a char array of size 2 i.e. "W" + "\0"
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

void GetMove(void) {
    char temp[2]; //to store Column move so that we can convert it to an integer

    /*Check which player's turn it is*/
    Data.player1_color[0] == Data.current_color[0]?
    printf("%s, enter your move: ", Data.player1_name): //Player 1's turn
    printf("%s, enter your move: ", Data.player2_name); //Player 2's turn

    /*Read in player's move and convert to index form*/
    fscanf(stdin, "%i %c", &Data.move[0], temp);
    printf("\n"); //Separates move input line and board
    Data.move[0]--; //Getting correct row index
    Data.move[1] = temp[0] - 97; //Getting correct column index using ascii code
}

int IsEmptyMove(void) {
    //Checking to see if it has a 'W' or 'B' in it already
    return Data.board[Data.move[0]][Data.move[1]] != 66 && Data.board[Data.move[0]][Data.move[1]] != 87; //Using ascii code for char comparison
}

int DirectionMove(void) {
    int valid = 0;
    //We have to execute and check each one individually because 'or conditions' would cause a problem.
    //Let's say 'North()' was true, because we use 'or conditions' the following functions wouldn't be executed
    //because we only need one to be true i.e. it would not allow for multiple directions to be changed.
    //Also only 'North()' is the only one well commented because the other directions just copy the comments from it
    if (North() == true) {valid = 1;}
    if (NorthEast() != 0) {valid = 1;}
    if (East() != 0) {valid = 1;}
    if (SouthEast() != 0) {valid = 1;}
    if (South() != 0) {valid = 1;}
    if (SouthWest() != 0) {valid = 1;}
    if (West() != 0) {valid = 1;}
    if (NorthWest() != 0) {valid = 1;}

    return valid;
}

bool North(void) {
    int jumpCounter = -1; //Keeps track of the index of the last disc of the same color
    bool capture = false;

    //Starting at index above spot, loop to check how far until the final same colored disc is found
    for (int row = Data.move[0] - 1; Data.board[row][Data.move[1]] != 0; --row) {
        if (Data.board[row][Data.move[1]] == Data.current_color[0]) { //Passes if same color is found
            jumpCounter = row;
        }
    }

    if (jumpCounter != -1) { //Passes if same color was found
        //Starting at spot, loop to check if any disc would result in at least 1 capture
        for (int row = Data.move[0] - 1; row >= jumpCounter; --row) {
            if (Data.board[row][Data.move[1]] != Data.current_color[0]) { //Passes if opposite color is found
                capture = true;
            }
        }

        if (capture == true) { //Passes if opposite color was found
            //Starting at spot, loop to replace every disc with 'current_color'
            for (int row = Data.move[0]; row >= jumpCounter; --row) {
                Data.board[row][Data.move[1]] = Data.current_color[0];
            }
        }
    }

    return capture;
}

int NorthEast(void) {
    int jumpCounter = -1;

    int row = Data.move[0] - 1; //Starting at index that is top-right to spot
    int column = Data.move[1] + 1;
    while (Data.board[row][column] != 0) {
        if (Data.board[row][column] == Data.current_color[0]) {
            jumpCounter = row;
        }

        --row;
        ++column;
    }

    row = Data.move[0]; //Starting at spot
    column = Data.move[1];
    if (jumpCounter != -1 && jumpCounter != Data.move[0] - 1) {
        while (row >= jumpCounter) {
            Data.board[row][column] = Data.current_color[0];

            --row;
            ++column;
        }
    }

    return jumpCounter != -1 && jumpCounter != Data.move[0] - 1;
}

int East(void) {
    int jumpCounter = -1;

    int column = Data.move[1] + 1; //Starting at index that is to the right of spot
    while (Data.board[Data.move[0]][column] != 0) {
        if (Data.board[Data.move[0]][column] == Data.current_color[0]) {
            jumpCounter = column;
        }

        ++column;
    }

    column = Data.move[1]; //Starting at spot
    if (jumpCounter != -1 && jumpCounter != Data.move[1] + 1) {
        while (column <= jumpCounter) {
            Data.board[Data.move[0]][column] = Data.current_color[0];

            ++column;
        }
    }

    return jumpCounter != -1 && jumpCounter != Data.move[1] + 1;
}

int SouthEast(void) {
    int jumpCounter = -1;

    int row = Data.move[0] + 1; //Starting at index that is bottom-right to spot
    int column = Data.move[1] + 1;
    while (Data.board[row][column] != 0) {
        if (Data.board[row][column] == Data.current_color[0]) {
            jumpCounter = row;
        }

        ++row;
        ++column;
    }

    row = Data.move[0]; //Starting at spot
    column = Data.move[1];
    if (jumpCounter != -1 && jumpCounter != Data.move[0] + 1) {
        while (row <= jumpCounter) {
            Data.board[row][column] = Data.current_color[0];

            ++row;
            ++column;
        }
    }

    return jumpCounter != -1 && jumpCounter != Data.move[0] + 1;
}

int South(void) {
    int jumpCounter = -1;

    int row = Data.move[0] + 1; //Starting at index below spot
    while (Data.board[row][Data.move[1]] != 0) {
        if (Data.board[row][Data.move[1]] == Data.current_color[0]) {
            jumpCounter = row;
        }

        ++row;
    }

    row = Data.move[0]; //Starting at spot

    if (jumpCounter != -1 && jumpCounter != Data.move[0] + 1) {
        while (row <= jumpCounter) {
            Data.board[row][Data.move[1]] = Data.current_color[0];

            ++row;
        }
    }

    return jumpCounter != -1 && jumpCounter != Data.move[0] + 1;
}

int SouthWest(void) {
    int jumpCounter = -1;

    int row = Data.move[0] + 1; //Starting at index that is bottom-left to spot
    int column = Data.move[1] - 1;
    while (Data.board[row][column] != 0) {
        if (Data.board[row][column] == Data.current_color[0]) {
            jumpCounter = row;
        }

        ++row;
        --column;
    }

    row = Data.move[0]; //Starting at spot
    column = Data.move[1];
    if (jumpCounter != -1 && jumpCounter != Data.move[0] + 1) {
        while (row <= jumpCounter) {
            Data.board[row][column] = Data.current_color[0];

            ++row;
            --column;
        }
    }

    return jumpCounter != -1 && jumpCounter != Data.move[0] + 1;
}

int West(void) {
    int jumpCounter = -1;

    int column = Data.move[1] - 1; //Starting at index that is to the right of spot
    while (Data.board[Data.move[0]][column] != 0) {
        if (Data.board[Data.move[0]][column] == Data.current_color[0]) {
            jumpCounter = column;
        }

        --column;
    }

    column = Data.move[1]; //Starting at spot

    if (jumpCounter != -1 && jumpCounter != Data.move[1] - 1) {
        while (column <= jumpCounter) {
            Data.board[Data.move[0]][column] = Data.current_color[0];

            --column;
        }
    }

    return jumpCounter != -1 && jumpCounter != Data.move[1] - 1;
}

int NorthWest(void) {
    int jumpCounter = -1;

    int row = Data.move[0] - 1; //Starting at index that is bottom-left to spot
    int column = Data.move[1] - 1;
    while (Data.board[row][column] != 0) {
        if (Data.board[row][column] == Data.current_color[0]) {
            jumpCounter = row;
        }

        --row;
        --column;
    }

    row = Data.move[0]; //Starting at spot
    column = Data.move[1];
    if (jumpCounter != -1 && jumpCounter != Data.move[0] - 1) {
        while (row <= jumpCounter) {
            Data.board[row][column] = Data.current_color[0];

            --row;
            --column;
        }
    }

    return jumpCounter != -1 && jumpCounter != Data.move[0] - 1;
}

void PrintTurn(void) {
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
                printf("      -%10s (black): %i           -\n", Data.player1_name, Data.player1_score);
                break;
            case 4:
                printf("      -%10s (white): %i           -\n", Data.player2_name, Data.player2_score);
                break;
            case 5:
                printf("      __________________________________\n");
                break;
            default:
                printf("\n");
                break;
        }
    }

    /*Turn separator*/
    printf("\n\n------------------------------------------------------------------------------\n\n");
}

void SwitchTurn(void) {
    /*Change 'Data->current_color' to the opposite*/
    strcmp(Data.current_color, "Black") == 0 ?
    strcpy(Data.current_color, "White") : //End black's turn
    strcpy(Data.current_color, "Black"); //End white's turn
}