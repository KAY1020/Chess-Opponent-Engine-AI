
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
//            
//        }
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

