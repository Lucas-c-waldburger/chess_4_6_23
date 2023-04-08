//
// Created by Lucas on 4/6/2023.
// GET RID OF ALL THOSE DAMN UNUSED MOVEMENT VECTORS!!!

#include "Piece.h"



Piece::Piece(int color, const std::pair<int, int> currentLocation) {
    this->color = color;
    this->currentLocation = currentLocation;
//    this->movement = {
//        {"up", std::vector<std::pair<int,int>>()},
//        {"down", std::vector<std::pair<int,int>>()},
//        {"left", std::vector<std::pair<int,int>>()},
//        {"right", std::vector<std::pair<int,int>>()},
//        {"upLeft", std::vector<std::pair<int,int>>()},
//        {"upRight", std::vector<std::pair<int,int>>()},
//        {"downLeft", std::vector<std::pair<int,int>>()},
//        {"downRight", std::vector<std::pair<int,int>>()},
//    };
//    std::cout << "Piece Created" << std::endl;
}

Piece::~Piece() {
//    std::cout << "Piece Destroyed" << std::endl;
}

void Piece::updateLocation(std::pair<int, int> newLocation) {
    this->currentLocation = newLocation;
}

//std::vector<std::pair<int, int>> Piece::findMoves() {
//    std::vector<std::pair<int, int>> possibleMoves;
//    for (auto& pair : movement) {
//        for (auto& coord : pair.second) {
//
//            int rowDestination = coord.first + currentLocation.first;
//            int colDestination = coord.second + currentLocation.second;
//
//            if ((rowDestination >= 0 && rowDestination <= 7) && (colDestination >= 0 && colDestination <= 7)) {
//                possibleMoves.emplace_back(rowDestination, colDestination);
//            }
//        }
//    }
//    return possibleMoves;
//}

std::map<std::string, std::vector<std::pair<int, int>>> Piece::findMoves() {
    std::map<std::string, std::vector<std::pair<int, int>>> possibleMoves;
    for (auto& pair : movement) {
        for (auto& coord : pair.second) {

            int rowDestination = coord.first + currentLocation.first;
            int colDestination = coord.second + currentLocation.second;

            if ((rowDestination >= 0 && rowDestination <= 7) && (colDestination >= 0 && colDestination <= 7)) {
                possibleMoves[pair.first].emplace_back(rowDestination, colDestination);
            }
        }
    }
    return possibleMoves;
}



Pawn::Pawn(int color, std::pair<int, int> currentLocation) : Piece(color, currentLocation) {
    this->name = "Pawn";
    this->movement["up"] = {
            std::make_pair<int, int>(-1, 0),
            std::make_pair<int, int>(-2, 0)
    };
    this->movement["upLeft"] = {
            std::make_pair<int, int>(-1, -1)
    };
    this->movement["upRight"] = {
            std::make_pair<int, int>(-1, 1)
    };
}


Rook::Rook(int color, std::pair<int, int> currentLocation) : Piece(color, currentLocation) {
    this->name = "Rook";
    for (int i = 1; i <= 7; i++) {
        this->movement["up"].emplace_back(std::make_pair(i * -1, 0));
        this->movement["down"].emplace_back(std::make_pair(i, 0));
        this->movement["left"].emplace_back(std::make_pair(0, i * -1));
        this->movement["right"].emplace_back(std::make_pair(0, i));
    }
}

Knight::Knight(int color, std::pair<int, int> currentLocation) : Piece(color, currentLocation) {
    this->name = "Knight";
    this->movement["upLeft"] = {
            std::make_pair<int, int>(-1, -2),
            std::make_pair<int, int>(-2, -1),
    };
    this->movement["upRight"] = {
            std::make_pair<int, int>(-1, 2),
            std::make_pair<int, int>(-2, 1),
    };
    this->movement["downLeft"] = {
            std::make_pair<int, int>(1, -2),
            std::make_pair<int, int>(2, -1),
    };
    this->movement["upRight"] = {
            std::make_pair<int, int>(1, 2),
            std::make_pair<int, int>(2, 1),
    };
}

Bishop::Bishop(int color, std::pair<int, int> currentLocation) : Piece(color, currentLocation) {
    this->name = "Bishop";
    for (int i = 1; i <= 7; i++) {
        this->movement["upLeft"].emplace_back(std::make_pair(i * -1, i * -1));
        this->movement["upRight"].emplace_back(std::make_pair(i * -1, i));
        this->movement["downLeft"].emplace_back(std::make_pair(i, i * -1));
        this->movement["downRight"].emplace_back(std::make_pair(i, i));
    }
}

King::King(int color, std::pair<int, int> currentLocation) : Piece(color, currentLocation) {
    this->name = "King";
    this->movement["up"] = {
            std::make_pair<int, int>(-1, 0),
    };
    this->movement["down"] = {
            std::make_pair<int, int>(1, 0),
    };
    this->movement["left"] = {
            std::make_pair<int, int>(0, -1),
    };
    this->movement["right"] = {
            std::make_pair<int, int>(0, 1),
    };
    this->movement["upLeft"] = {
            std::make_pair<int, int>(-1, -1)
    };
    this->movement["upRight"] = {
            std::make_pair<int, int>(-1, 1)
    };
    this->movement["downLeft"] = {
            std::make_pair<int, int>(1, -1)
    };
    this->movement["downRight"] = {
            std::make_pair<int, int>(1, 1)
    };
}

Queen::Queen(int color, std::pair<int, int> currentLocation) : Piece(color, currentLocation) {
    this->name = "Queen";
    for (int i = 1; i <= 7; i++) {
        this->movement["up"].emplace_back(std::make_pair(i * -1, 0));
        this->movement["down"].emplace_back(std::make_pair(i, 0));
        this->movement["left"].emplace_back(std::make_pair(0, i * -1));
        this->movement["right"].emplace_back(std::make_pair(0, i));
        this->movement["upLeft"].emplace_back(std::make_pair(i * -1, i * -1));
        this->movement["upRight"].emplace_back(std::make_pair(i * -1, i));
        this->movement["downLeft"].emplace_back(std::make_pair(i, i * -1));
        this->movement["downRight"].emplace_back(std::make_pair(i, i));
    }
}
