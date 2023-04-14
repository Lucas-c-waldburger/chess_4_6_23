//
// Created by Lucas on 4/6/2023.
//

#ifndef CHESS_4_6_23_TILE_H
#define CHESS_4_6_23_TILE_H
#include "Piece.h"
#include <memory>
#include <vector>
#include <map>
#include <iostream>

class Piece;

class Tile {
public:
    Tile() = default;
    Tile(int row, int column);

    std::shared_ptr<Piece> occupant = nullptr;

    std::pair<int, int> getLocation() const;

    void giveOccupantTo(Tile& recipientTile);
    void receiveOccupantFrom(Tile& donorTile);


    bool operator==(std::pair<int, int>& move) const;
    bool operator!=(std::pair<int, int>& move) const;

private:
    std::pair<int, int> location;

};



#endif //CHESS_4_6_23_TILE_H
