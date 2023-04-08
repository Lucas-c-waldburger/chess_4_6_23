//
// Created by Lucas on 4/6/2023.
//

#ifndef CHESS_4_6_23_TILE_H
#define CHESS_4_6_23_TILE_H
#include "Piece.h"
#include <memory>
#include <vector>
#include <map>

class Piece;

class Tile {
public:
    Tile() = default;
    Tile(int row, int column);

    std::unique_ptr<Piece> occupant = nullptr;

    std::pair<int, int> getLocation();

    void giveOccupantTo(Tile& recipientTile);
    void receiveOccupantFrom(Tile& donorTile);

private:
    std::pair<int, int> location;

};



#endif //CHESS_4_6_23_TILE_H
