#pragma once

#include <iostream>
#include <bitset>
#include "Constants.h"

typedef std::bitset<BOARD_BIT_SIZE> Chessboard;

struct Move {
    uint8_t fromX;
    uint8_t fromY;
    uint8_t toX;
    uint8_t toY;
    
    Move() : fromX(0), fromY(0), toX(0), toY(0) {};
    
    Move (uint8_t _fromX, uint8_t _fromY) {
        fromX = _fromX;
        fromY = _fromY;
        toX = _fromX;
        toY = _fromY;
    }
    
    Move (uint8_t _fromX, uint8_t _fromY, uint8_t _toX, uint8_t _toY) {
        fromX = _fromX;
        fromY = _fromY;
        toX = _toX;
        toY = _toY;
    }
    
    Move(const Move& other) {
        fromX = other.fromX;
        fromY = other.fromY;
        toX = other.toX;
        toY = other.toY;
    }
    
};

void setDefault(Chessboard& board);
uint8_t getPosition(Chessboard board, uint8_t x, uint8_t y);
void setPosition(Chessboard& board, uint8_t position, uint8_t x, uint8_t y);
bool getColor(uint8_t position);

bool validateMove(Chessboard board, Move p, bool color);
void move(Chessboard& board, Move m);

bool validateKing(Chessboard board, uint8_t dest, Move p);
bool validateQueen(Chessboard board, uint8_t dest, Move p);
bool validateRook(Chessboard board, uint8_t dest, Move p);
bool validateKnight(Chessboard board, uint8_t dest, Move p);
bool validateBishop(Chessboard board, uint8_t dest, Move p);
bool validatePawn(Chessboard board, uint8_t dest, Move p, bool color);
bool hasCheck(Chessboard board, bool color);

void displayBinary(Chessboard board);
void displayBoard(Chessboard board);