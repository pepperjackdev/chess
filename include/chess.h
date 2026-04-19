#pragma once

#include <stdint.h>

enum Type {
  TYPE_KING = 0b00000001,
  TYPE_QUEEN = 0b00000010,
  TYPE_BISHOP = 0b00000011,
  TYPE_KNIGHT = 0b00000100,
  TYPE_ROOK = 0b00000101,
  TYPE_PAWN = 0b00000110
};

enum Side { 
  SIDE_WHITE = 0b00000000, 
  SIDE_BLACK = 0b00001000 
};

typedef uint8_t PieceType;
typedef uint8_t PieceSide;
typedef uint8_t Piece;

typedef uint8_t Board[64];

Piece piece_of(PieceType type, PieceSide side);
PieceType type_of(Piece piece);
PieceSide side_of(Piece piece);

void load_fen_into_board(char *fen, Board *board);
