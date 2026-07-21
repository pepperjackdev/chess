#pragma once

#include <stdint.h>

typedef uint8_t Piece;

typedef enum : Piece {
  PIECE_TYPE_NULL   = 0b00000000,
  PIECE_TYPE_KING   = 0b00000001,
  PIECE_TYPE_QUEEN  = 0b00000010,
  PIECE_TYPE_BISHOP = 0b00000011,
  PIECE_TYPE_KNIGHT = 0b00000100,
  PIECE_TYPE_ROOK   = 0b00000101,
  PIECE_TYPE_PAWN   = 0b00000110
} PieceType;

typedef enum : Piece { 
  PIECE_SIDE_WHITE = 0b00000000, 
  PIECE_SIDE_BLACK = 0b00001000 
} PieceSide;

typedef enum : Piece {
  PIECE_FLAG_MOVED = 0b00010000,
} PieceFlags;

#define NULL_PIECE 0x00

Piece piece_new(PieceType type, PieceSide side);
PieceType piece_get_type(Piece piece);
PieceSide piece_get_side(Piece piece);
