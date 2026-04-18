#pragma once

#include <stdint.h>

enum Type {
  TYPE_PAWN   = 0b00000001,
  TYPE_ROOK   = 0b00000010,
  TYPE_KNIGHT = 0b00000011,
  TYPE_BISHOP = 0b00000100,
  TYPE_QUEEN  = 0b00000101,
  TYPE_KING   = 0b00000111
};

enum Side {
  SIDE_WHITE = 0b00000000,
  SIDE_BLACK = 0b00001000
};

typedef uint8_t PieceType;
typedef uint8_t PieceSide;
typedef uint8_t Piece;

typedef uint8_t Board[64];

Piece piece_of(PieceType type, PieceSide side) {
  return type | side;
}

PieceType type_of_piece(Piece piece) {
  return piece & 0b00000111;
}

PieceSide side_of_piece(Piece piece) {
  return piece & 0b00001000;
}
