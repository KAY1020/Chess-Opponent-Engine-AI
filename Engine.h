#pragma once

#include <unordered_set>
#include "Chessboard.h"
#include "Constants.h"

static const int8_t PIECE_SCORE[] = 
    {0, 80, 9, 5, 3, 3, 1, 0, 0, -80, -9, -5, -3, -3, -1, 0};

struct MeasuredBoard {
    Chessboard board;
    int8_t score; // your piece score - opponent piece score
};

using namespace std;

class Engine {
    
    public:
        // Constructor
        Engine();
        virtual ~Engine();
        
        Move getBestMove(Chessboard board, bool color, int depth);
        MeasuredBoard getInitialMeasure(Chessboard board) const; // make private later
        
        unordered_set<MeasuredBoard> getValidMoves(MeasuredBoard b, bool color);
        unordered_set<MeasuredBoard> getMovesKnight(MeasuredBoard b, bool color, uint8_t x, uint8_t y);
        
        
    private:
        
        
        
        

};


