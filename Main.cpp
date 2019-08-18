
#include <cstdlib>
#include <iostream>
#include "Chessboard.h"

using namespace std;

void moveWrapper(Chessboard& board, string input) {
    Move p;
    p.fromX = input[0] - 'a';
    p.fromY = input[1] - '1';
    p.toX = input[2] - 'a';
    p.toY = input[3] - '1';
    move(board, p);
}


int main(int argc, char** argv) {
    Chessboard board(DEFAULT_BOARD);
    displayBoard(board);
    string input;
    
    while (input != "quit") {
        cin >> input;
        moveWrapper(board, input);
        displayBoard(board);
    }
    
    return 0;
}


