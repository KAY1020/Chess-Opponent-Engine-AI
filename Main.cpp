
#include <cstdlib>
#include <iostream>
#include "Chessboard.h"
#include "Engine.h"

using namespace std;

Move moveWrapper(Chessboard& board, string input) {
    Move m;
    m.fromX = input[0] - 'a';
    m.fromY = input[1] - '1';
    m.toX = input[2] - 'a';
    m.toY = input[3] - '1';
    return m;
}


int main(int argc, char** argv) {
    Chessboard board(DEFAULT_BOARD);
    bool turn = WHITE;
    string input;
//    Engine engine;
//    MeasuredBoard measuredBoard; 
    
    displayBoard(board);   
    
    while (input != "quit") {
        cin >> input;
        Move m = moveWrapper(board, input);
        if (validateMove(board, m, turn)) {
            move(board, m);
            turn = !turn;
        }
        
        displayBoard(board);
//        measuredBoard = engine.getMeasuredBoard(board);
//        cout << "Board score = " << (int)measuredBoard.score << endl; 
    }
    
    return 0;
}


