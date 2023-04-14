//
// Created by Lucas on 4/6/2023.
//

#include "Tile.h"


Tile::Tile(int row, int column) {
    location = std::make_pair(row, column);
}

std::pair<int, int> Tile::getLocation() const {
    return location;
}

void Tile::giveOccupantTo(Tile &recipientTile) {
    recipientTile.occupant = std::move(this->occupant);
}

void Tile::receiveOccupantFrom(Tile &donorTile) {
    this->occupant = std::move(donorTile.occupant);
}

bool Tile::operator==(std::pair<int, int> &move) const {
    if ((this->getLocation().first == move.first) &&
        (this->getLocation().second == move.second)) {
        std::cout << "tile location matched with move vector\n";
        return true;
    }
    return false;
}

bool Tile::operator!=(std::pair<int, int> &move) const {
    if ((this->getLocation().first == move.first) &&
        (this->getLocation().second == move.second)) {
        std::cout << "tile location matched with move vector\n";
        return false;
    }
    return true;
}

