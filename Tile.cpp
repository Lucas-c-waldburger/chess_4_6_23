//
// Created by Lucas on 4/6/2023.
//

#include "Tile.h"


Tile::Tile(int row, int column) {
    location = std::make_pair(row, column);
}

std::pair<int, int> Tile::getLocation() {
    return location;
}

void Tile::giveOccupantTo(Tile &recipientTile) {
    recipientTile.occupant = std::move(this->occupant);
}

void Tile::receiveOccupantFrom(Tile &donorTile) {
    this->occupant = std::move(donorTile.occupant);
}

