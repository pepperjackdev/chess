#pragma once

#include <stdint.h>

typedef uint8_t Piece;

typedef enum : uint8_t {
  TYPE_KING   = 0b00000001,
  TYPE_QUEEN  = 0b00000010,
  TYPE_BISHOP = 0b00000011,
  TYPE_KNIGHT = 0b00000100,
  TYPE_ROOK   = 0b00000101,
  TYPE_PAWN   = 0b00000110
} PieceType;

typedef enum : uint8_t { 
  SIDE_WHITE = 0b00000000, 
  SIDE_BLACK = 0b00001000 
} PieceSide;

typedef enum : uint8_t {
  FLAG_MOVED = 0b00010000,
} PieceFlags;

static Piece NULL_PIECE = 0;

Piece piece_of(PieceType type, PieceSide side);
PieceType type_of(Piece piece);
PieceSide side_of(Piece piece);