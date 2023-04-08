//
// Created by Lucas on 4/6/2023.
//

#ifndef CHESS_4_6_23_BOARD_H
#define CHESS_4_6_23_BOARD_H
#include "Tile.h"
#include "Piece.h"
#include <vector>
#include <map>

class Tile;

class Board {
public:
    Board();
    Tile grid[8][8];

    std::vector<std::unique_ptr<Tile>> captureTiles;
    void captureNew(Tile& donorTile);

    void movePiece(Tile& currentTile, Tile& destinationTile);

    int getPieceCount(int color);
    std::vector<std::string> getPieceNames(int color);
    void reportPieces();
    void reportPieces(int color);

private:

    void tileGrid();
    void assignPieces();


};



#endif //CHESS_4_6_23_BOARD_H
