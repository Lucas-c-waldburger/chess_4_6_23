#include <iostream>
#include "Board.h"



// 8x8 matrix holding tile objects
// tile objects hold shared pointers to pieces
// piece as a base class
// MEMBER VARIABLES
// type
// x y location
//
// MEMBER FUNCTIONS
// move(Tile& tile)
// if (!tile.occupant = nullPtr) {
// tile.occupant = this



/*
 * g++ -c main.cpp Board.cpp Tile.cpp Piece.cpp Player.cpp
 * g++ -o main.exe main.o Board.o Tile.o Piece.o Player.o
 * main.exe
*/

bool validLetterEntry(char letterEntry) {
        bool letterValid = false;
        char validLetterEntries[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
        for (char letter : validLetterEntries) {
            if (letterEntry == letter) {letterValid = true;}
        }
        return letterValid;
};

bool validNumberEntry(char numberEntry) {
    bool numberValid = false;
    if (int(numberEntry) >= 49 && int(numberEntry) <= 56) {numberValid = true;}
    return numberValid;
};

void moveInputExceptionTest(std::string& rawInput) {
    if (std::islower(rawInput[0])) {rawInput[0] = std::toupper(rawInput[0]);}

    if (rawInput.length() < 2) {
        throw std::length_error("Your tile entry was too short\n");
    }
    if (rawInput.length() > 2) {
        throw std::length_error("Your tile entry was too long\n");
    }
    if (!validLetterEntry(rawInput[0])) {
        throw std::invalid_argument("Only enter letters from A - H\n");
    }
    if (!validNumberEntry(rawInput[1])) {
        throw std::invalid_argument("Only enter numbers from 1 - 8\n");
    }
}


std::pair<int, int> convertMoveInput(std::string playerMoveInput) {
    std::pair<int, int> convertedMove;

    int row = int(playerMoveInput[1] - '0');
    int col = int(playerMoveInput[0] - 65);

    convertedMove.first = abs(row - 8);
    convertedMove.second = col;
    std::cout << convertedMove.first << ", " << convertedMove.second << '\n';
    return convertedMove;
}

std::pair<std::pair<int, int>, std::pair<int, int>> getPlayerMove() {
    std::pair<std::pair<int, int>, std::pair<int, int>> playerMove;
    std::string currentLocationInput;
    std::string destinationLocationInput;

    bool validEntry = false;

    while (!validEntry) {
        validEntry = true;

        std::cout << "Move piece from: ";
        std::cin >> currentLocationInput;
        try {
            moveInputExceptionTest(currentLocationInput);
        }
        catch (std::exception& ex) {
            validEntry = false;
            std::cout << ex.what();
            continue;
        }
        playerMove.first = convertMoveInput(currentLocationInput);

        std::cout << "\nTo: ";

        std::cin >> destinationLocationInput;
        try {
            moveInputExceptionTest(destinationLocationInput);
        }
        catch (std::exception& ex) {
            validEntry = false;
            std::cout << ex.what();
            continue;
        }
        playerMove.second = convertMoveInput(destinationLocationInput);
        std::cout << "\n\n";
    }
    return playerMove;
}


int main() {
    std::shared_ptr<Player> p1 = std::make_unique<Player>(white);
    std::shared_ptr<Player> p2 = std::make_unique<Player>(black);

    Board board(*p1, *p2);

    int turn = 1;
    bool gameOver = false;
    std::shared_ptr<Player> activePlayer = p1;
    std::shared_ptr<Player> defendingPlayer = p2;

    while (!gameOver) {
        system("cls");
        board.printGridVisual(); std::cout << '\n';
        std::pair<std::pair<int, int>, std::pair<int, int>> playerMove;

        bool illegalMove = true;

        std::cout << "\t  Turn: " << turn << '\n';

        if (turn % 2 != 0) {
            std::cout << "-------PLAYER 1 TURN-------\n";
            activePlayer = p1;
            defendingPlayer = p2;
        }
        else {
            std::cout << "-------PLAYER 2 TURN-------\n";
            activePlayer = p2;
            defendingPlayer = p1;
        }

        while (illegalMove) {
            illegalMove = false;
            playerMove = getPlayerMove();

            try {
                board.movePiece(*activePlayer, *defendingPlayer, board.grid[playerMove.first.first][playerMove.first.second],
                                board.grid[playerMove.second.first][playerMove.second.second]);
            }
            catch (std::invalid_argument &ex) {
                std::cout << "ILLEGAL MOVE - " << ex.what() << "\nTry again!\n\n";
                illegalMove = true;
            }
        }
        turn += 1;
    }







//    std::shared_ptr<Piece> foundPiece = player1.findPiece(std::make_pair<int, int>(3, 0));
//    std::cout << foundPiece->name;

//    board.reportPieces(black);
//
//    std::cout << board.getPieceCount(white) << '\n';

//    std::cout << board.captureTiles.size();

//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board.grid[i][j].occupant != nullptr) {
//                std::cout << board.grid[i][j].occupant->currentLocation.first << ", "
//                          << board.grid[i][j].occupant->currentLocation.second << " - " << board.grid[i][j].occupant->movement.size() << std::endl;
//            }
//        }
//    }

    return 0;
}
