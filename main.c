#include "lib.h"

int main() {
    struct data Data;
    char board[8][8] = {0};

    InitializeGameSettings(&Data, board);
    PrintBoard(board);

    return 0;
}