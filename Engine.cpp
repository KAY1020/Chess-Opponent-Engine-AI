
#include "Engine.h"

Engine::Engine() {
}

Engine::~Engine() {
}

Move Engine::getBestMove(Chessboard board, bool color, int depth) {
    
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
    
    
    Move m;
    return m;
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
    MeasuredBoard out = {};
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
            if ((position & MASKS[color]) == MASKS[color]) {
                
                switch (position & PIECE_MASK) {
                    case KING:
                    case QUEEN:
                    case ROOK:
                    case KNIGHT:
                        current = getMovesKnight(b, color, x, y);
                    case BISHOP:
                    case PAWN:
                    default:
                        
                }
                moves.insert(current);
            }
        }
    }
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
            uint8_t target = getPosition(b, toX, toY);
            if (target == EMPTY || target & MASKS[color] != MASKS[color]) {
                MeasuredBoard found(b);
                currentMove.toX = toX;
                currentMove.toY = toY;
                b.score -= PIECE_SCORE[target];
                move(found.board, currentMove);
                if (!hasCheck(found.board)) {
                    movesFound.insert(found);
                }
            }
        }    
    }
    
    for (uint8_t toX = x - 1; toX <= x + 1; toX+=2) {
        if (toX >= DEFAULT_SIZE) continue;
        for (uint8_t toY = y - 2; toY <= y + 2; toY+=4) {
            if (toY >= DEFAULT_SIZE) continue;
            uint8_t target = getPosition(b, toX, toY);
            if (target == EMPTY || target & MASKS[color] != MASKS[color]) {
                MeasuredBoard found(b);
                currentMove.toX = toX;
                currentMove.toY = toY;
                b.score -= PIECE_SCORE[target];
                move(found.board, currentMove);
                if (!hasCheck(found.board)) {
                    movesFound.insert(found);
                }
            }
        }    
    }
    
    return movesFound;
}