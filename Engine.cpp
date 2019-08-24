
#include "Engine.h"

Engine::Engine() {
}

Engine::~Engine() {
}

Chessboard Engine::getBestMove(Chessboard board, bool color, int depth) {
    MeasuredBoard mb = getInitialMeasure(board);
    unordered_set<MeasuredBoard> possibleBoards = getValidMoves(mb, color);
    //for (getEngineScore())
    
    MeasuredBoard bestBoard(board, 100);
    for (const MeasuredBoard b : possibleBoards) {
        cout << "Found move score " << (int)b.score << endl;
        if (b.score < bestBoard.score) {
            bestBoard = b;
        }
    }
    return bestBoard.board;
    
    
    /*
     *  MeasuredBoard b = getMeasuredBoard(board);
     *  possibleMoves[] = getPossibleMoves(board, color);
     *  
     *  Chessboard currentBoard;
     *  Move bestMove;
     *  int8_t bestScore, currentScore;
     * 
     *  for (m in possibleMoves) {
     *      currentBoard = board;
     *      move(board, m);
     *      currentScore = getEngineScore(m, depth, MAXIMIZE);
     *      if (color == WHITE && currentScore > bestScore) {
     *          bestMove = m;
     *      }
     *      else if (color == BLACK && currentScore < bestScore) {
     *          bestMove = m;
     *      }
     *  }
     *  return bestMove;
     *  
     *
     */
}
//
//MeasuredBoard Engine::getEngineScore(MeasuredBoard root, uint8_t depth, bool maximize) {
//    vector<MeasuredBoard> possibleMoves = getPossibleMoves(root);
//    MeasuredBoard best;
//    
//    for (b in possibleBoards) {
//        if (depth > 0) {
//            MeasuredBoard result = findBestRecursive(root, depth - 1, !maximize);
//        }
//        
//        if (maximize && b.score > best.score) {
//            best = b;
//        }
//        else if (!maximize && b.score < best.score) {
//            best = b;
//        }
//    }
//    root.score = best.score;
//    return root;
//}

MeasuredBoard Engine::getInitialMeasure(Chessboard board) const {
    MeasuredBoard out;
    for (uint8_t y = 0; y < DEFAULT_SIZE; y++) {
        for (uint8_t x = 0; x < DEFAULT_SIZE; x++) {
            out.score += PIECE_SCORE[getPosition(board, x, y)];
        }        
    }
    out.board = board;
    return out;
}

//vector<Move> Engine::getPossibleMoves(MeasuredBoard b, bool color) {
//    uint8_t userMask, opponentMask, position;
//    Move currentMove;
//    
//    userMask = color == WHITE ? WHITE_MASK : BLACK_MASK;
//    opponentMask = color == WHITE? BLACK_MASK : WHITE_MASK;
//    
//    for (uint8_t y = 0; y < DEFAULT_SIZE; y++) {
//        for (uint8_t x = 0; x < DEFAULT_SIZE; x++) {
//            position = getPosition(b.board, x, y);
//             v
//    }
//    
//}
        
//vector<MeasuredBoard> Engine::getPossibleBoards(MeasuredBoard b, bool color) {
//    uint8_t position;
//    MeasuredBoard currentboard;
//    
//    for (uint8_t y = 0; y < DEFAULT_SIZE; y++) {
//        for (uint8_t x = 0; x < DEFAULT_SIZE; x++) {
//            position = getPosition(b.board, x, y);
//            if ((position & MASKS[color]) == MASKS[color]) {
//                
//            }
//            
//        }
//    }
//    
//}
//
//vector<MeasuredBoard> Engine::getMovesPawn(MeasuredBoard b, bool color) {
//    
//}

unordered_set<MeasuredBoard> Engine::getValidMoves(MeasuredBoard b, bool color) {
    unordered_set<MeasuredBoard> moves, current;
    uint8_t position;
    
    for (uint8_t y = 0; y < DEFAULT_SIZE; y++) {
        for (uint8_t x = 0; x < DEFAULT_SIZE; x++) {
            position = getPosition(b.board, x, y);
            if (position != EMPTY && getColor(position) == color) {
                
                switch (position & PIECE_MASK) {
                    case KING:
                        current = getMovesKing(b, color, x, y);
                        break;
                        
                    case QUEEN:
                        current = getMovesQueen(b, color, x, y);
                        break;
                        
                    case ROOK:
                        current = getMovesRook(b, color, x, y);
                        break;
                        
                    case KNIGHT:
                        current = getMovesKnight(b, color, x, y);
                        break;
                        
                    case BISHOP:
                        current = getMovesBishop(b, color, x, y);
                        break;
                        
                    case PAWN:
                        current = getMovesPawn(b, color, x, y);
                        break;
                        
                    default:
                        cout << "Engine: Error - invalid piece" << endl;
                        return moves;
                }
                
                for (const MeasuredBoard& b : current) {
                    moves.insert(b);
                }
            }
        }
    }
    //cout << "Engine: Found " << moves.size() << " valid moves" << endl; 
    return moves;
}

unordered_set<MeasuredBoard> Engine::getMovesKnight(MeasuredBoard b, bool color, uint8_t x, uint8_t y) {
    unordered_set<MeasuredBoard> movesFound;
    Move currentMove;
    currentMove.fromX = x;
    currentMove.fromY = y;
    
    for (uint8_t toX = x - 2; toX <= x + 2; toX+=4) {
        if (toX >= DEFAULT_SIZE) continue;
        for (uint8_t toY = y - 1; toY <= y + 1; toY+=2) {
            if (toY >= DEFAULT_SIZE) continue;
            uint8_t position = getPosition(b.board, toX, toY);
            if (position != EMPTY && getColor(position) != color) {
                MeasuredBoard found(b);
                currentMove.toX = toX;
                currentMove.toY = toY;
                move(found.board, currentMove);
                if (!hasCheck(found.board, color)) {
                    found.score -= PIECE_SCORE[position];
                    movesFound.insert(found);
                }
            }
        }    
    }
    
    for (uint8_t toX = x - 1; toX <= x + 1; toX+=2) {
        if (toX >= DEFAULT_SIZE) continue;
        for (uint8_t toY = y - 2; toY <= y + 2; toY+=4) {
            if (toY >= DEFAULT_SIZE) continue;
            uint8_t position = getPosition(b.board, toX, toY);
            if (position != EMPTY && getColor(position) != color) {
                MeasuredBoard found(b);
                currentMove.toX = toX;
                currentMove.toY = toY;
                move(found.board, currentMove);
                if (!hasCheck(found.board, color)) {
                    found.score -= PIECE_SCORE[position];
                    movesFound.insert(found);
                }
            }
        }    
    }
    
    return movesFound;
}

unordered_set<MeasuredBoard> Engine::getMovesPawn(MeasuredBoard b, bool color, uint8_t x, uint8_t y) {
    unordered_set<MeasuredBoard> movesFound;
    MeasuredBoard currentBoard;
    Move currentMove(x, y, 0, 0);
    
    int8_t playerOffset = color == WHITE ? 1 : -1;
    uint8_t toY = y + playerOffset;  
    
    if (toY >= DEFAULT_SIZE) {
        return movesFound;
    }
    
    // Check front movement
    if (getPosition(b.board, x, toY) == EMPTY) {
        currentBoard = MeasuredBoard(b);
        currentMove.toX = x;
        currentMove.toY = toY;
        move(currentBoard.board, currentMove);
        if (!hasCheck(currentBoard.board, color)) {
            movesFound.insert(currentBoard);
        }
        
        // Check start double movement 
        toY += playerOffset;
        if (y == PAWN_START_Y[color] && getPosition(b.board, x, toY) == EMPTY) {
            currentBoard = MeasuredBoard(b);
            currentMove.toX = x;
            currentMove.toY = toY;
            move(currentBoard.board, currentMove);
            if (!hasCheck(currentBoard.board, color)) {
                movesFound.insert(currentBoard);
            }
        }
    }
    
    // Check attack movements
    currentMove.toY = y + playerOffset;
    for (int8_t offsetX = -1; offsetX <= 1; offsetX += 2) {
        currentMove.toX = x + offsetX;
        uint8_t dest = getPosition(b.board, currentMove.toX, currentMove.toY);
        if (dest != EMPTY && getColor(dest) != color) {
            currentBoard = MeasuredBoard(b);
            move(currentBoard.board, currentMove);
            if (!hasCheck(currentBoard.board, color)) {
                currentBoard.score -= PIECE_SCORE[dest];
                movesFound.insert(currentBoard);
            }
        }
    }
    
    return movesFound;
}

unordered_set<MeasuredBoard> Engine::getMovesRook(MeasuredBoard b, bool color, uint8_t x, uint8_t y) {
    unordered_set<MeasuredBoard> movesFound;
    MeasuredBoard currentBoard;
    Move currentMove(x, y);
    bool blocked;
    
    for (int8_t dir = -1; dir <= 1; dir += 2) {    
        blocked = false;
        
        for (uint8_t toX = x + dir; toX < DEFAULT_SIZE; toX += dir) {
            uint8_t position = getPosition(b.board, toX, y);
            if (position != EMPTY) { 
                if (getColor(position) != color)
                    blocked = true;
                else break;
            }
            currentBoard = MeasuredBoard(b);
            currentMove.toX = toX;
            currentMove.toY = y;
            move(currentBoard.board, currentMove);
            if (!hasCheck(currentBoard.board, color)) {
                currentBoard.score -= PIECE_SCORE[position];
                movesFound.insert(currentBoard);
            }
            if (blocked) break;
        }
        
        for (uint8_t toY = y + dir; toY < DEFAULT_SIZE; toY += dir) {
            uint8_t position = getPosition(b.board, x, toY);
            if (position != EMPTY) { 
                if (getColor(position) != color)
                    blocked = true;
                else break;
            }
            currentBoard = MeasuredBoard(b);
            currentMove.toX = x;
            currentMove.toY = toY;
            move(currentBoard.board, currentMove);
            if (!hasCheck(currentBoard.board, color)) {
                currentBoard.score -= PIECE_SCORE[position];
                movesFound.insert(currentBoard);
            }
            if (blocked) break;
        }
    }
    return movesFound;
}


unordered_set<MeasuredBoard> Engine::getMovesBishop(MeasuredBoard b, bool color, uint8_t x, uint8_t y) {
    unordered_set<MeasuredBoard> movesFound;
    MeasuredBoard currentBoard;
    Move currentMove(x, y);
    
    for (int8_t dirX = -1; dirX <= 1; dirX += 2) {
        for (int8_t dirY = -1; dirY <= 1; dirY += 2) {
            currentMove.toX = x + dirX;
            currentMove.toY = y + dirY;
            
            while (currentMove.toX < DEFAULT_SIZE && currentMove.toY < DEFAULT_SIZE) {
                uint8_t position = getPosition(b.board, currentMove.toX, currentMove.toY);

                if (position != EMPTY) {
                    if (getColor(position) != color) {
                        currentBoard = MeasuredBoard(b);
                        move(currentBoard.board, currentMove);
                        if (!hasCheck(currentBoard.board, color)) {
                            currentBoard.score -= PIECE_SCORE[position];
                            movesFound.insert(currentBoard);
                        }
                    }
                    break;
                }
                
                currentBoard = MeasuredBoard(b);
                move(currentBoard.board, currentMove);
                if (!hasCheck(currentBoard.board, color)) {
                    currentBoard.score -= PIECE_SCORE[position];
                    movesFound.insert(currentBoard);
                }
                currentMove.toX += dirX;
                currentMove.toY += dirY;
            }
                
        }
    }
    return movesFound;
}

unordered_set<MeasuredBoard> Engine::getMovesQueen(MeasuredBoard b, bool color, uint8_t x, uint8_t y) {
    unordered_set<MeasuredBoard> movesFound, temp;
    movesFound = getMovesRook(b, color, x, y);
    temp = getMovesBishop(b, color, x, y);
    for (const MeasuredBoard found : temp) {
        movesFound.insert(found);
    }
    return movesFound;
}

unordered_set<MeasuredBoard> Engine::getMovesKing(MeasuredBoard b, bool color, uint8_t x, uint8_t y) {
    unordered_set<MeasuredBoard> movesFound;
    MeasuredBoard currentBoard;
    Move currentMove(x, y);
    
    for (int8_t dirX = -1; dirX <= 1; dirX++) {
        currentMove.toX = x + dirX;
        if (currentMove.toX >= DEFAULT_SIZE) {
            continue;
        }
        for (int8_t dirY = -1; dirY <= 1; dirY++) {
            currentMove.toY = y + dirY;
            if (currentMove.toY >= DEFAULT_SIZE) {
                continue;
            }
            
            if (currentMove.toX == currentMove.fromX && 
                    currentMove.toY == currentMove.fromY) {
                continue;
            }
            
            uint8_t position = getPosition(b.board, currentMove.toX, currentMove.toY);
            if (position != EMPTY && getColor(position) == color) {
                continue;
            }
            
            currentBoard = MeasuredBoard(b);
            move(currentBoard.board, currentMove);
            if (!hasCheck(currentBoard.board, color)) {
                currentBoard.score -= PIECE_SCORE[position];
                movesFound.insert(currentBoard);
            }
        }
    }
    return movesFound;
}