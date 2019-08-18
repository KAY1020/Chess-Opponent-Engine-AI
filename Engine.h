
#pragma once

#include "Chessboard.h"
#include "Constants.h"

static const int8_t PIECE_SCORE[] = 
    {0, 80, 9, 5, 3, 3, 1, 0, 0, -80, -9, -5, -3, -3, -1, 0};

struct MeasuredBoard {
    Chessboard board;
    int8_t score; // your piece score - opponent piece score
};

class Engine {
    
    public:
        // Constructor
        Engine();
        virtual ~Engine();
        
        Move getBestMove(Chessboard board, bool color, int depth);
        MeasuredBoard getInitialMeasure(Chessboard board) const; // make private later
        
        
    private:
        
        
        
        

};


