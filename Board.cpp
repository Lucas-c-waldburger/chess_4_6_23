//
// Created by Lucas on 4/6/2023.
//

#include "Board.h"



Board::Board() {
    tileGrid();
    assignPieces();
}

void Board::tileGrid() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            grid[i][j] = Tile(i, j);
        }
    }
};

void Board::assignPieces() {
    int rowIndexes[4] = {0, 1, 6, 7};
    for (int row : rowIndexes) {
        for (int col = 0; col < 8; col++) {

            int color = (row < 2) ? black : white;

            if (row == 1 || row == 6) {
                grid[row][col].occupant = std::make_unique<Pawn>(color, grid[row][col].getLocation());
            }

            else {
                if (col == 0 || col == 7) {
                    grid[row][col].occupant = std::make_unique<Rook>(color, grid[row][col].getLocation());
                }
                if (col == 1 || col == 6) {
                    grid[row][col].occupant = std::make_unique<Knight>(color, grid[row][col].getLocation());
                }
                if (col == 2 || col == 5) {
                    grid[row][col].occupant = std::make_unique<Bishop>(color, grid[row][col].getLocation());
                }
                if (col == 3) {
                    grid[row][col].occupant = std::make_unique<King>(color, grid[row][col].getLocation());
                }
                if (col == 4) {
                    grid[row][col].occupant = std::make_unique<Queen>(color, grid[row][col].getLocation());
                }
            }
        }
    }
}

void Board::movePiece(Tile& currentTile, Tile& destinationTile) {
    std::map<std::string, std::vector<std::pair<int, int>>> possibleMoves = currentTile.occupant->findMoves();
    std::cout << "Found Moves: ";
    for (auto& pair : possibleMoves) {
        std::cout << pair.first << " - ";
        for (auto& move : pair.second) {
            std::cout << '(' << move.first << ", " << move.second << "), ";
        }
        std::cout << '\n';
    }


//    std::cout << currentTile.occupant->currentLocation.first << "\n, " << currentTile.occupant->currentLocation.second << '\n';
    for (auto& pair : possibleMoves) {
        // for each movement direction, set pathBlocked to false
        bool pathBlocked = false;

        for (auto &move: pair.second) {
            // if we haven't reached the destination tile yet but found another piece, mark pathBlocked true
            if ((grid[move.first][move.second].occupant != nullptr) &&
                (destinationTile.getLocation().first != move.first || destinationTile.getLocation().second != move.second)) {

                pathBlocked = true;
                std::cout << "Path is Blocked at: (" << move.first << ", " << move.second << ")\n";
            }
            if ((destinationTile.getLocation().first == move.first) &&
                (destinationTile.getLocation().second == move.second)) {
                std::cout << "tile location matched with move vector\n";
                // if destination tile is eventually found in this movement direction, check if pathBlocked and
                // that the piece is not a knight
                if (pathBlocked && currentTile.occupant->name != "Knight") {
                    throw std::invalid_argument("Path to destination is blocked by a piece");
                }

                // at this point, our destination tile was found this movement direction and it's not blocked by
                // any pieces leading up to it
                if (destinationTile.occupant != nullptr) {
                    std::cout << "determined destination occupant wasn't null\n";

                    // destination tile is occupied, so now we check to see if it's our own piece or the opponents piece
                    if (destinationTile.occupant->color == currentTile.occupant->color) {
                        throw std::invalid_argument("Can't move on top of your own piece");
                    } else {
                        // we capture it if it's the opponents piece
                        captureNew(destinationTile);
                        std::cout << "piece captured\n";
                    }
                }
                else { std::cout << "found to be null\n"; }

                // now, the only things that could have happened are a.) the destination tile's piece was captured,
                // b.) the destination tile didn't have a piece on it,
                // so now in both instances we have to transfer the piece to the destination tile and update the piece's location
                currentTile.giveOccupantTo(destinationTile);
                destinationTile.occupant->updateLocation(destinationTile.getLocation());
                std::cout << destinationTile.occupant->currentLocation.first << ", "
                          << destinationTile.occupant->currentLocation.second << '\n';
                return;
            }
        }
    }
    throw std::invalid_argument("requested destination is either out of range or not in the piece's moveset\n");
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
