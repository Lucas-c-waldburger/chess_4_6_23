#include <iostream>
#include "Tile.h"
#include "Piece.h"
#include "Board.h"


// 8x8 matrix holding tile objects
// tile objects hold unique pointers to pieces
// piece as a base class
// MEMBER VARIABLES
// type
// x y location
//
// MEMBER FUNCTIONS
// move(Tile& tile)
// if (!tile.occupant = nullPtr) {
// tile.occupant = this



/* when tile accepts a piece, the piece's location gets updated, either
 * a - holds a ptr to the tile object
 * b - the tile object holds a pointer to the piece
 * c - both
*/




int main() {

    Board board;


    board.movePiece(board.grid[0][0], board.grid[1][4]);

//    board.reportPieces(black);
//
//    std::cout << board.getPieceCount(white) << '\n';

//    std::cout << board.captureTiles.size();

//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board.grid[i][j].occupant != nullptr) {
//                std::cout << board.grid[i][j].occupant->currentLocation.first << ", "
//                          << board.grid[i][j].occupant->currentLocation.second << " - " << board.grid[i][j].occupant->movement.size() << std::endl;
//            }
//        }
//    }

    return 0;
}
