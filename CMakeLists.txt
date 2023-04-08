cmake_minimum_required(VERSION 3.24)
project(chess_4_6_23)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess_4_6_23 main.cpp Tile.h Piece.h Piece.cpp Tile.cpp Board.h Board.cpp)
