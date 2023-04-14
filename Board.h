//
// Created by Lucas on 4/6/2023.
//

#ifndef CHESS_4_6_23_BOARD_H
#define CHESS_4_6_23_BOARD_H
#include <vector>
#include <map>
#include "Tile.h"
#include "Piece.h"
#include "Player.h"


class Tile;
class Player;

class Board {
public:
    Board(Player& player1, Player& player2);
    Tile grid[8][8];
    char gridVisual[8][8];


    std::vector<std::unique_ptr<Tile>> captureTiles;
    void captureNew(Tile& donorTile);
    bool inCheck(Player& currentPlayer, Player& enemyPlayer);
    bool inCheck(Player& currentPlayer, Player& enemyPlayer, Tile& currentTile);

    bool isBlocked(std::pair<int, int>& move, Tile& currentTile, Tile& destinationTile);
    bool isBlocked(std::pair<int, int>& move, Tile& tileBeingAssessed, std::pair<int, int>& currentPlayersKingLocation);

    bool pawnMoveDiagonal(Tile& currentTile, std::pair<int, int>& move);
    bool opponentWillCapture(std::pair<int, int>& move, Tile& opponentTileBeingAssessed);
    void movePiece(Player& currentPlayer, Player& opponentPlayer, Tile& currentTile, Tile& destinationTile);

    int getPieceCount(int color);
    std::vector<std::string> getPieceNames(int color);
    void reportPieces();
    void reportPieces(int color);

    void refreshGridVisual();
    void printGridVisual();



private:

    void tileGrid();
    void assignPieces(Player& player1, Player& player2);


};



#endif //CHESS_4_6_23_BOARD_H
