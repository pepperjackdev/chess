#pragma once

#include <stdint.h>

enum Type {
  TYPE_KING   = 0b00000001,
  TYPE_QUEEN  = 0b00000010,
  TYPE_BISHOP = 0b00000011,
  TYPE_KNIGHT = 0b00000100,
  TYPE_ROOK   = 0b00000101,
  TYPE_PAWN   = 0b00000110
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

PieceType type_of(Piece piece) {
  return piece & 0b00000111;
}

PieceSide side_of(Piece piece) {
  return piece & 0b00001000;
}

// FIXME: tmp. implementation 
void load_fen_into_board(char *fen, Board *board) {
  // Clearing board
  for (int i = 0; i < 65; i++) (*board)[i] = 0;
  // Loading FEN content into board
  for (int i = 0, bi = 0; fen[i] != '\0'; i++) {
    char symbol = fen[i];
    if (symbol == '/') bi += 8;
  }
}
