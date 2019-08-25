
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
    Engine engine;
    bool turn = WHITE;
    string input;
    
    MeasuredBoard measuredBoard; 
    
    displayBoard(board);   
    
    while (input != "quit") {
        cin >> input;
        Move m = moveWrapper(board, input);
        if (validateMove(board, m, turn)) {
            move(board, m);
            cout << "White's turn:" << endl;
//            board = engine.getBestMove(board, WHITE, 2);
            displayBoard(board);
            cout << "Black's turn:" << endl;
            board = engine.getBestMove(board, BLACK, 4);
        }
        
    displayBoard(board);
    cout << "Score: " << (int)engine.getInitialMeasure(board).score << endl;
    
//    measuredBoard = engine.getInitialMeasure(board);
//    engine.getValidMoves(measuredBoard, BLACK);

    }
    
    return 0;
}


