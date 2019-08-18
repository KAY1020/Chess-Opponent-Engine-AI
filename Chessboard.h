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