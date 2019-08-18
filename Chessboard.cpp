
#include "Chessboard.h"
#include "Constants.h"

using namespace std;

void setDefault(Chessboard& board) {
    board = Chessboard(DEFAULT_BOARD);
}

uint8_t getPosition(Chessboard board, uint8_t x, uint8_t y) {
    size_t index = POSITION_BIT_SIZE * (y * DEFAULT_SIZE + x);
    uint8_t position = 0;
    for (int i = POSITION_BIT_SIZE - 1; i >= 0; i--) 
        position = (position << 1) + board[index + i];
    return position;
}

void setPosition(Chessboard& board, uint8_t position, uint8_t x, uint8_t y) {
    size_t index = POSITION_BIT_SIZE * (y * DEFAULT_SIZE + x);
    //cout << "Writing: " << bitset<8>(position) << endl;
    for (int i = 0; i < POSITION_BIT_SIZE; i++) { 
        board[index + i] = position & 0b0001;
        position >>= 1;
    }
    //cout << "Result: " << bitset<8>(getPosition(board, x, y)) << endl;
}

bool getColor(uint8_t position) {
    return !((position & BLACK_MASK) == BLACK_MASK);
}

void displayBinary(Chessboard board) {
    for (int y = DEFAULT_SIZE - 1; y >= 0; y--) {
        for (int x = 0; x < DEFAULT_SIZE; x++) {
            int position = POSITION_BIT_SIZE * (y * DEFAULT_SIZE + x);
            for (int i = 0; i < POSITION_BIT_SIZE; i++) {
                cout << board[position + (POSITION_BIT_SIZE - i - 1)];
            }
            cout << " ";
        }
        cout << endl;
    }
}

void displayHexadecimal(Chessboard board) {
    for (int y = DEFAULT_SIZE - 1; y >= 0; y--) {
        for (int x = 0; x < DEFAULT_SIZE; x++) {
            cout << hex << (int)getPosition(board, x, y) << " ";
        }
        cout << endl;
        
    }
}

void displayBoard(Chessboard board) {    
    const char CHAR_DISPLAY[] = {' ', 'K', 'Q', 'R', 'N', 'B', 'P', 'X'};
    cout << "  +---+---+---+---+---+---+---+---+" << endl;
    for (int y = DEFAULT_SIZE - 1; y >= 0; y--) {
        cout << (y + 1) << " |";
        for (int x = 0; x < DEFAULT_SIZE; x++) {
            uint8_t position = getPosition(board, x, y);
            char display = CHAR_DISPLAY[position % DEFAULT_SIZE];
            if (getColor(position) == BLACK)
                display = tolower(display);
            cout << " " << display << " |";
        }
        cout << endl << "  +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << " ";
    for (int x = 0; x < DEFAULT_SIZE; x++) 
        cout << "   " << (char)('a' + x);
    cout << endl;
}

bool move(Chessboard& board, Move p) {
    cout << endl << "Movement (" << (int)p.fromX << "," << (int)p.fromY
         << ") to (" << (int)p.toX << "," << (int)p.toY << ")" << endl;
    
    if (p.fromX == p.toX && p.fromY == p.toY) {
        cout << "-- Can't move to same tile" << endl;
        return false;
    }
    
    if (p.fromX >= DEFAULT_SIZE || p.fromY >= DEFAULT_SIZE || 
        p.toX >= DEFAULT_SIZE || p.toY >= DEFAULT_SIZE) {
        cout << "-- Position out of bounds" << endl;
        return false;
    }
    
    uint8_t position = getPosition(board, p.fromX, p.fromY);
    cout << "Moving piece " << bitset<4>(position) << endl;
    
    if (position == EMPTY) {
        cout << "-- Can't move empty tile" << position << endl;
        return false;
    }
    
    uint8_t destination = getPosition(board, p.toX, p.toY);
    cout << "Destination piece " << bitset<4>(destination) << endl;
    
    if ((destination != EMPTY) && ((position ^ destination) < 0b1000)) {
        cout << "-- Destination is occupied" << endl;
        return false;
    }
    
    switch (position & PIECE_MASK) {
        case KING:
            if (!validateKing(board, destination, p))
                return false;
            break;
            
        case QUEEN:
            if (!validateQueen(board, destination, p))
                return false;
            break;
            
        case ROOK:
            if (!validateRook(board, destination, p))
                return false;
            break;
            
            
        case KNIGHT:
            if (!validateKnight(board, destination, p))
                return false;
            break;
            
        case BISHOP:
            if (!validateBishop(board, destination, p))
                return false;
            break;
        
        case PAWN:
            if (!validatePawn(board, destination, p))
                return false;
            break;
        
        default:
            cout << "Unknown piece " << bitset<4>(position) << endl;
            return false;
    }
    
    Chessboard output(board);
    setPosition(output, position, p.toX, p.toY);
    setPosition(output, EMPTY, p.fromX, p.fromY);
    
    if (hasCheck(output, getColor(position))) {
        cout << "-- King in check" << endl;
        return false;       
    }
    
    board = output;
    cout << "-- Movement accepted" << endl;
    
    return true;
}

bool validateKing(Chessboard board, uint8_t dest, Move p) {
    if (abs(p.fromX - p.toX) <= 1 && abs(p.fromY - p.toY) <= 1)
        return true;
    cout << "-- Invalid king movement" << endl;
    return false;
}

bool validateQueen(Chessboard board, uint8_t dest, Move p) {
    return validateBishop(board, dest, p) || validateRook(board, dest, p);
}

bool validateRook(Chessboard board, uint8_t dest, Move p) {
    int i, increment;
    if (p.fromX == p.toX) {
        increment = p.toY > p.fromY ? 1 : -1;
        i = p.fromY + increment;
        while (i != p.toY) {
            if (getPosition(board, p.fromX, i) != EMPTY) {
                cout << "-- Path obstructed" << endl;
                return false;
            }
            i += increment;
        }
        return true;
    }
    if (p.fromY == p.toY) {
        increment = p.toX > p.fromX ? 1 : -1;
        i = p.fromX + increment;
        while (i != p.toX) {
            if (getPosition(board, i, p.fromY) != EMPTY) {
                cout << "-- Path obstructed" << endl;
                return false;
            }
            i += increment;
        }
        return true;
    }            
    cout << "-- Invalid rook movement" << endl;
    return false;
}

bool validateKnight(Chessboard board, uint8_t dest, Move p) {
    if (abs(p.toX - p.fromX) == 2 && abs(p.toY - p.fromY) == 1)
        return true;
    if (abs(p.toX - p.fromX) == 1 && abs(p.toY - p.fromY) == 2)
        return true;
    cout << "-- Invalid knight movement" << endl;
    return false;
}

bool validateBishop(Chessboard board, uint8_t dest, Move p) {
    int x, y, incrementX, incrementY;
    if (abs(p.toX - p.fromX) == abs(p.toY - p.fromY)) {
        incrementX = p.toX > p.fromX ? 1 : -1;
        incrementY = p.toY > p.fromY ? 1 : -1;
        x = p.fromX + incrementX;
        y = p.fromY + incrementY;
        while (x != p.toX) {
            if (getPosition(board, x, y) != EMPTY) {
                cout << "-- Path obstructed" << endl;
                return false;
            }
            x += incrementX;
            y += incrementY;
        }
        return true;
    }
    cout << "-- Invalid bishop movement" << endl;
    return false; 
}

bool validatePawn(Chessboard board, uint8_t dest, Move p) {
    if (dest == EMPTY && p.fromX == p.toX) {
        if (p.fromY + 1 == p.toY)
            return true;
        if (p.fromY + 2 == p.toY && p.fromY == 1)
            return true;
    }
    if (dest != EMPTY && abs(p.fromX - p.toX) == 1 && p.fromY + 1 == p.toY) {
        return true; 
    }
    cout << "-- Invalid pawn movement" << endl;
    return false;
}

bool hasCheck(Chessboard board, bool color) {
    if (color == BLACK) {
        return true;
    }
    uint8_t maskUser, maskOpponent;
    if (color == WHITE) {
        maskUser = WHITE_MASK;
        maskOpponent = BLACK_MASK;
    }
    else {
        maskUser = BLACK_MASK;
        maskOpponent = WHITE_MASK;
    }
    
    uint8_t kingX, kingY;
    uint8_t kingPiece = KING | maskUser;
    uint8_t targetPiece;
    for (kingY = 0; kingY < DEFAULT_SIZE; kingY++) {
        for (kingX = 0; kingX < DEFAULT_SIZE; kingX++) {
            if (getPosition(board, kingX, kingY) == kingPiece) {
                goto found;
            }
        }
    }
    
    found:
    cout << "King at " << (int)kingX << (int)kingY << endl;
    
    // Check if knight is attacking
    targetPiece = KNIGHT | maskOpponent;
    for (uint8_t x = kingX - 2; x <= kingX + 2; x+=4) {
        if (x >= DEFAULT_SIZE) continue;
        for (uint8_t y = kingY - 1; y <= kingY + 1; y+=2) {
            if (y >= DEFAULT_SIZE) continue;
            if (getPosition(board, x, y) == targetPiece)
                return true;
        }    
    }
    
    for (uint8_t x = kingX - 1; x <= kingX + 1; x+=2) {
        if (x >= DEFAULT_SIZE) continue;
        for (uint8_t y = kingY - 2; y <= kingY + 2; y+=4) {
            if (y >= DEFAULT_SIZE) continue;
            if (getPosition(board, x, y) == targetPiece)
                return true;
        }    
    }
    
    // Check if king is attacking
    targetPiece = KING | maskOpponent;
    for (uint8_t x = kingX - 1; x <= kingX + 1; x++) {
        if (x >= DEFAULT_SIZE) continue;
        for (uint8_t y = kingY - 1; y <= kingY + 1; y++) {
            if (y >= DEFAULT_SIZE) continue;
            if (x == kingX && y == kingY) continue;
                if (getPosition(board, x, y) == targetPiece)
                    return true;
        }
    }
    
    // Check if pawn is attacking
    targetPiece = PAWN | maskOpponent;
    uint8_t offset = color == WHITE ? 1 : -1;
    uint8_t kingPawnOffset = kingY + offset;
    if (kingPawnOffset < DEFAULT_SIZE) {
        for (uint8_t x = kingX - 1; x <= kingX + 1; x+=2) {
            if (x >= DEFAULT_SIZE) continue;
            if (getPosition(board, x, kingPawnOffset) == targetPiece) 
                return true;
        }
    }
    
    uint8_t x, y, currentTile;
    uint8_t rookOpponent = ROOK | maskOpponent;
    uint8_t bishopOpponent = BISHOP | maskOpponent;
    uint8_t queenOpponent = QUEEN | maskOpponent;
    
    // Check if diagonal piece is attacking
    for (int incrementY = -1; incrementY <= 1; incrementY+=2) {
        for (int incrementX = -1; incrementX <= 1; incrementX+=2) {
            x = kingX + incrementX;
            y = kingY + incrementY;
            while (x <= DEFAULT_SIZE && y <= DEFAULT_SIZE) {
                currentTile = getPosition(board, x, y);
                if (currentTile == EMPTY){
                    x += incrementX;
                    y += incrementY;
                    continue;
                }
                if (currentTile == bishopOpponent || currentTile == queenOpponent) {
                    return true;
                }
                break; 
            }
        }
    }
    
    // Check if vertical piece is attacking
    for (int incrementX = -1; incrementX <= 1; incrementX+=2) {
        x = kingX + incrementX;
        y = kingY;
        while (x <= DEFAULT_SIZE) {
            currentTile = getPosition(board, x, y);
            if (currentTile == EMPTY){
                x += incrementX;
                continue;
            }
            if (currentTile == rookOpponent || currentTile == queenOpponent) {
                return true;
            }
            break; 
        }
    }
    
    for (int incrementY = -1; incrementY <= 1; incrementY+=2) {
        x = kingX;
        y = kingY + incrementY;
        while (y <= DEFAULT_SIZE) {
            currentTile = getPosition(board, x, y);
            if (currentTile == EMPTY){
                y += incrementY;
                continue;
            }
            if (currentTile == rookOpponent || currentTile == queenOpponent) {
                return true;
            }
            break; 
        }
    }
    
    return false;
}