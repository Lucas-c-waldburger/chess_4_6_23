//
// Created by Lucas on 4/6/2023.
//
#ifndef CHESS_4_6_23_PIECE_H
#define CHESS_4_6_23_PIECE_H
#include "Tile.h"
#include <iostream>
#include <map>
#include <vector>

class Tile;

enum Color {black = 0, white = 1};

class Piece {
public:
    Piece(int color, std::pair<int, int> currentLocation);
    ~Piece();

    int color;
    std::string name;
    char boardSymbol;
    std::pair<int, int> currentLocation;
    std::map<std::string, std::vector<std::pair<int, int>>> movement;


    void determineSymbol();
    void updateLocation(std::pair<int, int> newLocation);

    virtual std::map<std::string, std::vector<std::pair<int, int>>> findMoves();


private:


};

// Make way to iterate through all grid locations along the Piece's movement path to stop it from passing through other pieces!! //
// between current tile and destination tile {
    // iterate through piece to destination, break early if finds blocking piece
// }
// should do this inside getMoves() or movePiece()??

class Pawn : public Piece {
public:
    Pawn(int color, std::pair<int, int> currentLocation);
    std::map<std::string, std::vector<std::pair<int, int>>> findMoves() override;

};

class Rook : public Piece {
public:
    Rook(int color, std::pair<int, int> currentLocation);

};

class Knight : public Piece {
public:
    Knight(int color, std::pair<int, int> currentLocation);

};

class Bishop : public Piece {
public:
    Bishop(int color, std::pair<int, int> currentLocation);

};

class King : public Piece {
public:
    King(int color, std::pair<int, int> currentLocation);

};

class Queen : public Piece {
public:
    Queen(int color, std::pair<int, int> currentLocation);

};
#endif //CHESS_4_6_23_PIECE_H
