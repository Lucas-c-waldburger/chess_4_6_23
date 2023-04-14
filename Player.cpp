//
// Created by Lucas on 4/12/2023.
//

#include "Player.h"

Player::Player(int color) : color{color} {}

std::shared_ptr<Piece> Player::findPiece(std::string name) {
    while (true) {
        for (auto &piece: playerPieces) {
            if (name == piece->name) { return piece; }
        }
        std::string pieceColor;
        if (color == black) {pieceColor = "black";}
        else {pieceColor = "white";}

        std::cout << "Piece not found in " << pieceColor << " pieces. Enter another name: ";
        std::cin >> name;
    }
}

std::shared_ptr<Piece> Player::findPiece(std::pair<int, int> location) {
    while (true) {
        for (auto &piece: playerPieces) {
            if (location == piece->currentLocation) { return piece; }
        }
        std::string pieceColor;
        if (color == black) {pieceColor = "black";}
        else {pieceColor = "white";}

        std::cout << "Piece not found in " << pieceColor << " pieces. Enter another location: ";
        std::cin >> location.first >> location.second;
    }
}