//
// Created by Lucas on 4/12/2023.
//

#ifndef CHESS_4_6_23_PLAYER_H
#define CHESS_4_6_23_PLAYER_H
#include "Piece.h"
#include "Board.h"


struct Player {
public:
    Player(int color);
    int color;
    std::vector<std::shared_ptr<Piece>> playerPieces;

    std::shared_ptr<Piece> findPiece(std::string name);
    std::shared_ptr<Piece> findPiece(std::pair<int, int> location);
};


#endif //CHESS_4_6_23_PLAYER_H
