//
// Created by Lucas on 4/6/2023.
//

#include "Board.h"
#include "color-console-master/include/color.hpp"



Board::Board(Player& player1, Player& player2) {
    tileGrid();
    assignPieces(player1, player2);
}

void Board::tileGrid() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            grid[i][j] = Tile(i, j);
        }
    }
};

void Board::assignPieces(Player& player1, Player& player2) {
    int rowIndexes[4] = {0, 1, 6, 7};
    for (int row : rowIndexes) {
        for (int col = 0; col < 8; col++) {

            int color = (row < 2) ? black : white;

            if (row == 1 || row == 6) {
                grid[row][col].occupant = std::make_shared<Pawn>(color, grid[row][col].getLocation());
            }

            else {
                if (col == 0 || col == 7) {
                    grid[row][col].occupant = std::make_shared<Rook>(color, grid[row][col].getLocation());
                }
                if (col == 1 || col == 6) {
                    grid[row][col].occupant = std::make_shared<Knight>(color, grid[row][col].getLocation());
                }
                if (col == 2 || col == 5) {
                    grid[row][col].occupant = std::make_shared<Bishop>(color, grid[row][col].getLocation());
                }
                if (col == 3) {
                    grid[row][col].occupant = std::make_shared<King>(color, grid[row][col].getLocation());
                }
                if (col == 4) {
                    grid[row][col].occupant = std::make_shared<Queen>(color, grid[row][col].getLocation());
                }
            }

            std::shared_ptr<Piece> playerPiece = grid[row][col].occupant;
            if (color == black) {player1.playerPieces.push_back(playerPiece);}
            else {player2.playerPieces.push_back(playerPiece);}


        }
    }
}

void Board::movePiece(Player& currentPlayer, Player& enemyPlayer, Tile& currentTile, Tile& destinationTile) {
    if (currentTile.occupant == nullptr) {
        throw std::invalid_argument("The selected tile has no piece on it");
    }
    if (currentTile.occupant->color != currentPlayer.color) {
        throw std::invalid_argument("You cannot move an opponent's piece");
    }

    std::map<std::string, std::vector<std::pair<int, int>>> possibleMoves = currentTile.occupant->findMoves();
    std::cout << "Found Moves: ";
    for (auto& pair : possibleMoves) {
        std::cout << pair.first << " - ";
        for (auto& move : pair.second) {
            std::cout << '(' << move.first << ", " << move.second << "), ";
        }
        std::cout << '\n';
    }

    for (auto& pair : possibleMoves) {
        // for each movement direction, set pathBlocked to false
        bool pathBlocked = false;

        for (auto &move: pair.second) {
            // if we haven't reached the destination tile yet but found another piece, mark pathBlocked true
            if (isBlocked(move, currentTile, destinationTile)) {
                pathBlocked = true;
            }

            if ((destinationTile == move)) {
                // if destination tile is eventually found in this movement direction, check if pathBlocked
                // (pathBlocked also determines that the piece is not a knight)
                if (pathBlocked) {
                    throw std::invalid_argument("Path to destination is blocked by another piece");
                }

                // at this point, our destination tile was found this movement direction and it's not blocked by
                // any pieces leading up to it

                // temp bool willCapture to mark if we need to capture an enemy piece on the destination tile
                bool willCapture = false;
                if (destinationTile.occupant != nullptr) {
                    std::cout << "determined destination occupant wasn't null\n";

                    // destination tile is occupied, so now we check to see if it's our own piece or the opponents piece
                    if (destinationTile.occupant->color == currentTile.occupant->color) {
                        throw std::invalid_argument("Can't move on top of your own piece");
                    }
                    else {
                        // we mark that the piece needs to be captured if it's the opponents piece after checking
                        // first we negate the pawn's ability to capture if the current attempted move is not a diagonal move
                        if (!pawnMoveDiagonal(currentTile, move)) {
                            willCapture = false;
                        }

                        else {
                            willCapture = true;
                            std::cout << "piece marked to be captured\n";
                        }
                    }
                }
                else {
                    std::cout << "found to be null\n";
                }

                // now, the only things that could have happened are a.) the destination tile's piece was captured,
                // b.) the destination tile didn't have a piece on it,

                // first make sure we arent putting outselves in check
                if (inCheck(currentPlayer, enemyPlayer, currentTile)) {
                    throw std::invalid_argument("Can't put yourself in check");
                }
                // if marked to be captured, move the enemy piece on the destination tile over to a new capture tile
                // representing the piece "graveyard"
                if (willCapture) {
                    captureNew(destinationTile);
                }
                // now in both instances we have to transfer the piece to the destination tile and update the piece's location
                currentTile.giveOccupantTo(destinationTile);
                destinationTile.occupant->updateLocation(destinationTile.getLocation());
                std::cout << destinationTile.occupant->currentLocation.first << ", "
                          << destinationTile.occupant->currentLocation.second << '\n';

                return;
            }
        }
    }
    throw std::invalid_argument("Requested destination is either out of range or not in the selected piece's moveset\n");
}


bool Board::inCheck(Player& currentPlayer, Player& enemyPlayer) {
    std::shared_ptr<Piece> currentPlayersKing = currentPlayer.findPiece("King");

    for (auto& enemyPiece : enemyPlayer.playerPieces) {
        // run findMoves for all opponents pieces

        std::map<std::string, std::vector<std::pair<int, int>>> possibleMoves = enemyPiece->findMoves();

        for (auto& pair : possibleMoves) {
            bool pathBlocked = false;

            for (auto &move: pair.second) {
                if (isBlocked(move,grid[enemyPiece->currentLocation.first][enemyPiece->currentLocation.second],
                            currentPlayersKing->currentLocation)) {
                    pathBlocked = true;
                }
                std::cout << enemyPiece->name << '\n' << "--------------------\n";
                std::cout << "Path is blocked: " << std::boolalpha << pathBlocked << " - (" << move.first << ", " << move.second << ')' << '\n';
                std::cout << "at the king's location: " << std::boolalpha << (move == currentPlayersKing->currentLocation) << "\n\n";
                if ((!pathBlocked) && (move == currentPlayersKing->currentLocation)) {
                    std::cout << "returning true!!";
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::inCheck(Player& currentPlayer, Player& enemyPlayer, Tile& currentTile) {
    std::shared_ptr<Piece> currentPlayersKing = currentPlayer.findPiece("King");

    for (auto& enemyPiece : enemyPlayer.playerPieces) {
        // run findMoves for all opponents pieces

        std::map<std::string, std::vector<std::pair<int, int>>> possibleMoves = enemyPiece->findMoves();

        for (auto& pair : possibleMoves) {
            bool pathBlocked = false;

            for (auto &move: pair.second) {
                if (move != currentTile.getLocation()) {
                    if (isBlocked(move, grid[enemyPiece->currentLocation.first][enemyPiece->currentLocation.second],
                                  currentPlayersKing->currentLocation)) {
                        pathBlocked = true;
                    }
                }
                std::cout << enemyPiece->name << '\n' << "--------------------\n";
                std::cout << "Path is blocked: " << std::boolalpha << pathBlocked << " - (" << move.first << ", " << move.second << ')' << '\n';
                std::cout << "at the king's location: " << std::boolalpha << (move == currentPlayersKing->currentLocation) << "\n\n";
                if ((!pathBlocked) && (move == currentPlayersKing->currentLocation)) {
                    std::cout << "returning true!!";
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isBlocked(std::pair<int, int>& move, Tile& currentTile, Tile& destinationTile) {
    if (currentTile.occupant->name != "Knight") {
        if ((grid[move.first][move.second].occupant != nullptr) &&
            (destinationTile.getLocation().first != move.first ||
             destinationTile.getLocation().second != move.second)) {

            std::cout << "Path is Blocked at: (" << move.first << ", " << move.second << ")\n";
            return true;
        }
    }
    return false;
}

bool Board::isBlocked(std::pair<int, int>& move, Tile& tileBeingAssessed, std::pair<int, int>& currentPlayersKingLocation) {
    if (tileBeingAssessed.occupant->name != "Knight") {
        if ((grid[move.first][move.second].occupant != nullptr) &&
            (grid[move.first][move.second] != currentPlayersKingLocation)) {

//            std::cout << "Path to King Blocked at: (" << move.first << ", " << move.second << ")\n";
            return true;
        }
    }
    return false;
}

bool Board::pawnMoveDiagonal(Tile& currentTile, std::pair<int, int>& move) {
    if ((currentTile.occupant->name == "Pawn") && (move.second != currentTile.occupant->currentLocation.second)) {
        return true;
    }
    return false;
}


void Board::captureNew(Tile &donorTile) {
    captureTiles.push_back(std::make_unique<Tile>());
    donorTile.giveOccupantTo(*captureTiles.back());
}

int Board::getPieceCount(int color) {
    int pieceCount = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j].occupant != nullptr && grid[i][j].occupant->color == color) {
                pieceCount += 1;
            }
        }
    }
    return pieceCount;
}

std::vector<std::string> Board::getPieceNames(int color) {
    std::vector<std::string> pieceNames;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j].occupant != nullptr && grid[i][j].occupant->color == color) {
                pieceNames.push_back(grid[i][j].occupant->name);
            }
        }
    }
    return pieceNames;
}

void Board::reportPieces() {
    for (int i = 0; i < 8; i++) {
        if (i == 0) {std::cout << "------Black Pieces------\n";}
        if (i == 6) {std::cout << "------White Pieces------\n";}
        for (int j = 0; j < 8; j++) {
            if (grid[i][j].occupant != nullptr) {
                std::cout << grid[i][j].occupant->name << " - (" << grid[i][j].occupant->currentLocation.first << ", " << grid[i][j].occupant->currentLocation.second << ")\n";
            }
        }
    }
}

void Board::reportPieces(int color) {
    if (color == black) {std::cout << "------Black Pieces------\n";}
    else {std::cout << "------White Pieces------\n";}
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j].occupant != nullptr && grid[i][j].occupant->color == color) {
                std::cout << grid[i][j].occupant->name << " - (" << grid[i][j].occupant->currentLocation.first << ", " << grid[i][j].occupant->currentLocation.second << ")\n";
            }
        }
    }
}

void Board::refreshGridVisual() {
    for (int i = 0; i < 8; i++) {
        int colorAlternate = 1;
        for (int j = 0; j < 8; j++) {
            colorAlternate += 1;
            if (j == 0) {colorAlternate += i;}

            gridVisual[i][j].color = (colorAlternate % 2 == 0) ? white : black;

            if (grid[i][j].occupant != nullptr) {
                gridVisual[i][j].tileChar = grid[i][j].occupant->boardSymbol;
            }
            else {
                gridVisual[i][j].tileChar = ' ';
            }
        }
    }
}


void Board::printGridVisual() {
    refreshGridVisual();

    std::cout << '\n';
    for (int row = 0; row < 8; row++) {
        int colorAlternate = 1;
        for (int col = 0; col < 8; col++) {
            if (col == 0) {
                if (row == 0)
                    std::cout << "8  ";
                if (row == 1)
                    std::cout << "7  ";
                if (row == 2)
                    std::cout << "6  ";
                if (row == 3)
                    std::cout << "5  ";
                if (row == 4)
                    std::cout << "4  ";
                if (row == 5)
                    std::cout << "3  ";
                if (row == 6)
                    std::cout << "2  ";
                if (row == 7)
                    std::cout << "1  ";
            }
            colorAlternate += 1;
            if (col == 0) {colorAlternate += row;}

            if (gridVisual[row][col].color == white) {
                if (grid[row][col].occupant != nullptr) {
                    if (grid[row][col].occupant->color == black) {
                        std::cout << dye::purple_on_bright_white(" ")
                                  << dye::purple_on_bright_white(gridVisual[row][col].tileChar)
                                  << dye::purple_on_bright_white(" ");
                    }
                    else {
                        std::cout << dye::yellow_on_bright_white(" ")
                                  << dye::yellow_on_bright_white(gridVisual[row][col].tileChar)
                                  << dye::yellow_on_bright_white(" ");

                    }
                }
                else {
                    std::cout << dye::purple_on_bright_white("   ");
                }
            }
            else {
                if (grid[row][col].occupant != nullptr) {
                    if (grid[row][col].occupant->color == black) {
                        std::cout << dye::purple_on_grey(" ")
                                  << dye::purple_on_grey(gridVisual[row][col].tileChar)
                                  << dye::purple_on_grey(" ");
                    }
                    else {
                        std::cout << dye::yellow_on_grey(" ")
                                  << dye::yellow_on_grey(gridVisual[row][col].tileChar)
                                  << dye::yellow_on_grey(" ");
                    }
                }
                else {
                    std::cout << dye::purple_on_grey("   ");
                }
            }

            if (col == 7) {
                std::cout << '\n';
            }
        }
    }
    std::cout << "   -A--B--C--D--E--F--G--H-" << '\n';
}

