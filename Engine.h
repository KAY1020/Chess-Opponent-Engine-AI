#pragma once

#include <unordered_set>
#include "Chessboard.h"
#include "Constants.h"

static const int8_t PIECE_SCORE[] = 
    {0, 80, 9, 5, 3, 3, 1, 0, 0, -80, -9, -5, -3, -3, -1, 0};

struct MeasuredBoard {
    
    Chessboard board;
    int8_t score; // your piece score - opponent piece score
    
    MeasuredBoard() : board(0), score(0) {};
    MeasuredBoard(const Chessboard b, const int8_t s) : board(b), score(s) {};
    MeasuredBoard(const MeasuredBoard& other) {
        board = other.board;
        score = other.score;
    }
    
    MeasuredBoard& operator=(const MeasuredBoard other) {
        board = other.board;
        score = other.score;
        return *this;
    }
    
    bool operator==(const MeasuredBoard other) const {
        return board == other.board;
    }
    
    bool operator<(const MeasuredBoard other) const {
        for (int i = BOARD_BIT_SIZE - 1; i >= 0; i--) {
            if (board[i] ^ other.board[i]) 
                return other.board[i];
        }
        return false;
    }
        
};

namespace std {
    template<> struct hash<MeasuredBoard> {
        size_t operator()(const MeasuredBoard& b) const noexcept {
            hash<Chessboard> hasher;
            return hasher(b.board);
        }
    };
}


using namespace std;

class Engine {
    
    public:
        // Constructor
        Engine();
        virtual ~Engine();
        
        Chessboard getBestMove(Chessboard board, bool color, int depth);
        MeasuredBoard getInitialMeasure(Chessboard board) const; // make private later
        MeasuredBoard getEngineScore(MeasuredBoard root, uint8_t depth, bool player); // Check
        
        unordered_set<MeasuredBoard> getValidMoves(MeasuredBoard b, bool color);
        unordered_set<MeasuredBoard> getMovesKnight(MeasuredBoard b, bool color, uint8_t x, uint8_t y);
        unordered_set<MeasuredBoard> getMovesPawn(MeasuredBoard b, bool color, uint8_t x, uint8_t y);
        unordered_set<MeasuredBoard> getMovesRook(MeasuredBoard b, bool color, uint8_t x, uint8_t y);
        unordered_set<MeasuredBoard> getMovesBishop(MeasuredBoard b, bool color, uint8_t x, uint8_t y);
        unordered_set<MeasuredBoard> getMovesQueen(MeasuredBoard b, bool color, uint8_t x, uint8_t y);
        unordered_set<MeasuredBoard> getMovesKing(MeasuredBoard b, bool color, uint8_t x, uint8_t y);
        
        
    private:
        
        
        
        

};


