//
// Created by loidt on 20/04/2021.
//

#include "lib.h"

static struct data Data;

void InitializeGameSettings(void) {
    printf("\n---Welcome to Othello---\n\n");

    /*Name Initialization*/
    printf("Enter player 1 name: ");
    scanf("%s", Data.player1_name);
    printf("Enter player 2 name: ");
    scanf("%s", Data.player2_name);

    /*Score Initialization*/
    Data.player1_score = 2;
    Data.player2_score = 2;

    /*Board Initialization*/
    //Without 'strtok' you'd be assigning a char array of size 2 e.g. "W" + "\0"
    Data.board[3][3] = 'W';
    Data.board[3][4] = 'B';
    Data.board[4][3] = 'B';
    Data.board[4][4] = 'W';

    /*Random Disc Color Initialization*/
    strcpy(Data.current_color, "Black"); //Set starting color
    srand(time(NULL)); // Set random seed

    if ((rand() % 2) == 1) { //1 is rolled
        strcpy(Data.player1_color, "Black");
        strcpy(Data.player2_color, "White");
    }
    else { //0 is rolled
        strcpy(Data.player1_color, "White");
        strcpy(Data.player2_color, "Black");
    }
    printf("Random 50-50 assignment of colors has been completed, %s is %s and %s is %s\n\n",
           Data.player1_name, Data.player1_color, Data.player2_name, Data.player2_color);
}

void GetMove(void) {
    char temp[2]; //to store Column move so that we can convert it to an integer

    /*Check which player's turn it is*/
    (strcmp(Data.current_color, Data.player1_color) == 0)?
    (printf("%s, enter your move: ", Data.player1_name)): //Player 1's turn
    (printf("%s, enter your move: ", Data.player2_name)); //Player 2's turn

    /*Read in player's move and convert to index form*/
    fscanf(stdin, "%i %c", &Data.move[0], temp);
    Data.move[0]--; //Getting correct row index
    Data.move[1] = temp[0] - 97; //Getting correct column index using ascii code

//    printf("Move inputted in index: %i %i\n\n", move[0], move[1]);
}

int IsEmptyMove(void) {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //We can't use 'strcmp()' because 'board[move[0]][move[1]]' as a string might be 'BBB','WB' and so on because we  //
    //had to take away the null terminator in InitializingGameSettings(). Thus, strcmp would keep reading until a 0 is//
    //found e.g. move 4 d, strcmp would read it as 'WB'.                                                              //
    //As a result strcmp would only work if there was no letters at the right of the move e.g. move 4 e.              //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char *ptr = &Data.board[Data.move[0]][Data.move[1]];

    //Checking to see if it has a 'W' or 'B' in it already
    return *ptr != 66 && *ptr != 87; //Using ascii code for char comparison
}

int DirectionMove(void) {
    int jumpCounter = -1; //Initialize to -1 to allow us to check validity of move

    return (North(jumpCounter) != -1 ||
            NorthEast(jumpCounter) != -1 ||
            East(jumpCounter) != -1 ||
            SouthEast(jumpCounter) != -1 ||
            South(jumpCounter) != -1  ||
            SouthWest(jumpCounter) != -1  ||
            West(jumpCounter) != -1  ||
            NorthWest(jumpCounter) != -1);
}

int North(int jumpCounter) {
    int row = Data.move[0] - 1; //Starting at index above spot

    while (Data.board[row][Data.move[1]] != 0) { //Loop until end of direction is found
        if (Data.board[row][Data.move[1]] == Data.current_color[0]) { //Found same color => valid direction
            jumpCounter = row; //Keeps track of the index of the last disc of the same color
        }

        --row;
    }

    row = Data.move[0]; //Starting at spot

    if (jumpCounter != -1) { //Valid direction because we found same color
        while (row >= jumpCounter) { //Loop until final disc of same color is found
            Data.board[row][Data.move[1]] = Data.current_color[0]; //Replace every disc with 'current_color'

            --row;
        }
    }

    return jumpCounter;
}

int NorthEast(int jumpCounter) {
    int row = Data.move[0] - 1; //Starting at index that is top-right to spot
    int column = Data.move[1] + 1;

    while (Data.board[row][column] != 0) { //Loop until end of direction is found
        if (Data.board[row][column] == Data.current_color[0]) { //Found same color => valid direction
            jumpCounter = row; //Keeps track of the index of the last disc of the same color
        }

        --row;
        ++column;
    }

    row = Data.move[0]; //Starting at spot
    column = Data.move[1];

    if (jumpCounter != -1) { //Valid direction because we found same color
        while (row >= jumpCounter) { //Loop until final disc of same color is found
            Data.board[row][column] = Data.current_color[0]; //Replace every disc with 'current_color'

            --row;
            ++column;
        }
    }

    return jumpCounter;
}

int East(int jumpCounter) {
    int column = Data.move[1] + 1; //Starting at index that is to the right of spot

    while (Data.board[Data.move[0]][column] != 0) { //Loop until end of direction is found
        if (Data.board[Data.move[0]][column] == Data.current_color[0]) { //Found same color => valid direction
            jumpCounter = column; //Keeps track of the index of the last disc of the same color
        }

        ++column;
    }

    column = Data.move[1]; //Starting at spot

    if (jumpCounter != -1) { //Valid direction because we found same color
        while (column <= jumpCounter) { //Loop until final disc of same color is found
            Data.board[Data.move[0]][column] = Data.current_color[0]; //Replace every disc with 'current_color'

            ++column;
        }
    }

    return jumpCounter;
}

int SouthEast(int jumpCounter) {
    int row = Data.move[0] + 1; //Starting at index that is bottom-right to spot
    int column = Data.move[1] + 1;

    while (Data.board[row][column] != 0) { //Loop until end of direction is found
        if (Data.board[row][column] == Data.current_color[0]) { //Found same color => valid direction
            jumpCounter = row; //Keeps track of the index of the last disc of the same color
        }

        ++row;
        ++column;
    }

    row = Data.move[0]; //Starting at spot
    column = Data.move[1];

    if (jumpCounter != -1) { //Valid direction because we found same color
        while (row <= jumpCounter) { //Loop until final disc of same color is found
            Data.board[row][column] = Data.current_color[0]; //Replace every disc with 'current_color'

            ++row;
            ++column;
        }
    }

    return jumpCounter != -1;
}

int South(int jumpCounter) {
    int row = Data.move[0] + 1; //Starting at index below spot

    while (Data.board[row][Data.move[1]] != 0) { //Loop until end of direction is found
        if (Data.board[row][Data.move[1]] == Data.current_color[0]) { //Found same color => valid direction
            jumpCounter = row; //Keeps track of the index of the last disc of the same color
        }

        ++row;
    }

    row = Data.move[0]; //Starting at spot

    if (jumpCounter != -1) {
        while (row <= jumpCounter) { //Loop until final disc of same color is found
            Data.board[row][Data.move[1]] = Data.current_color[0]; //Replace every disc with 'current_color'

            ++row;
        }
    }

    return jumpCounter;
}

int SouthWest(int jumpCounter) {
    int row = Data.move[0] + 1; //Loop 'idk' starting from index 'idk' spot
    int column = Data.move[1] - 1; //Loop 'idk' starting from index 'idk' spot

    while (Data.board[row][column] != 0) { //Stop if 0 is found i.e. end of direction
        if (Data.board[row][column] == Data.current_color[0]) { //Found same color => valid direction
            jumpCounter++; //Keeps track of how many discs we had to check before finding 0 i.e. end of direction
        }
        else { //Found opposite color
            jumpCounter++;
        }
        ++row;
        --column;
    }

    row = Data.move[0];
    column = Data.move[1];

    if (jumpCounter != -1) { //Decides if it should replace the disc colors in the direction
        do {
            Data.board[row][column] = Data.current_color[0]; //Replace every disc with 'current_color'
            --jumpCounter;
            ++row;
            --column;
        } while (Data.board[row][column] != 0);
    }

    return jumpCounter;
}

int West(int jumpCounter) {
    for (int i = Data.move[1] -  1; i > -1; --i) { //Loop left-wards starting from index that's to the left of spot
        if (Data.board[Data.move[0]][i] == Data.current_color[0]) { //Found same color => valid direction
        }
        else if (Data.board[Data.move[0]][i] == 0) { //Found 0 i.e. end of direction => end loop
            break;
        }
        jumpCounter++; //Keeps track of how many discs we had to check before finding 0 i.e. end of direction
    }

    if (jumpCounter != -1) { //Decides if it should replace the disc colors in the direction
        for (int i = Data.move[1]; jumpCounter > 0; --i) { //Loop left-wards starting from spot
            Data.board[Data.move[0]][i] = Data.current_color[0]; //Replace every disc with 'current_color'
            --jumpCounter;
        }
    }

    return jumpCounter;
}

int NorthWest(int jumpCounter) {
    int row = Data.move[0] - 1; //Loop top-left-wards starting from index that's to the top-left of spot
    int column = Data.move[1] - 1;

    while (Data.board[row][column] != 0) { //Stop if 0 is found i.e. end of direction
        if (Data.board[row][column] == Data.current_color[0]) { //Found same color => valid direction
            jumpCounter++; //Keeps track of how many discs we had to check before finding 0 i.e. end of direction
        }
        else { //Found opposite color
            jumpCounter++;
        }
        --row;
        --column;
    }

    row = Data.move[0];
    column = Data.move[1];

    if (jumpCounter != -1) { //Decides if it should replace the disc colors in the direction
        do {
            Data.board[row][column] = Data.current_color[0]; //Replace every disc with 'current_color'
            --jumpCounter;
            --row;
            --column;
        } while (Data.board[row][column] != 0);
    }

    return jumpCounter;
}

void PrintBoard(void) {
    for (int i = 0; i < 9; ++i) { //Row Index
        printf("     ---------------------------------\n"); //Row Splitter
        (i != 8) ? (printf("  %i  ", i + 1)) : (printf("     ")); //In row 9, don't want to show '9'
        for (int j = 0; j < 8; ++j) { //Column Index
            //In row 9, don't want to show '|' before each letter in row 9 and to show letter value not numerical value
            (i != 8) ? (printf("| %c ", Data.board[i][j])) : (printf("  %c ", 97 + j));
        }
        (i != 8) ? (printf("|\n")) : (printf("\n")); //In row 9, don't want to show '|' at the end of the letters
    }

    /*After each play you want it to separate the plays clearly*/
    printf("\n\n-------------------------------------------------------------------------\n\n");
}

void PrintScore(void) {

}

void EndTurn(void) {
    /*Change 'Data->current_color' to the opposite*/
    (strcmp(Data.current_color, "Black") == 0)?
    (strcpy(Data.current_color, "White")): //End black's turn
    (strcpy(Data.current_color, "Black")); //End whites' turn
}