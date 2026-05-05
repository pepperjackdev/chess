#pragma once

#include <stdint.h>

enum PieceType {
  TYPE_NULL   = 0b00000000,
  TYPE_KING   = 0b00000001,
  TYPE_QUEEN  = 0b00000010,
  TYPE_BISHOP = 0b00000011,
  TYPE_KNIGHT = 0b00000100,
  TYPE_ROOK   = 0b00000101,
  TYPE_PAWN   = 0b00000110
};

enum PieceSide { 
  SIDE_WHITE = 0b00000000, 
  SIDE_BLACK = 0b00001000 
};

typedef uint8_t PieceType;
typedef uint8_t PieceSide;
typedef uint8_t Piece;

typedef uint8_t Board[64];

enum CastlingRights {
  CASTLING_BLACK_KING_SIDE  = 0b00000001,
  CASTLING_BLACK_QUEEN_SIDE = 0b00000010,
  CASTLING_WHITE_KING_SIDE  = 0b00000100,
  CASTLING_WHITE_QUEEN_SIDE = 0b00001000,
};

typedef uint8_t CastlingRights;

typedef struct {
  Board piece_placement_data;
  PieceSide active_color;
  CastlingRights castling_availability;
  int en_passant_target_square;
  int halfmove_clock;
  int fullmove_clock;
} State;

Piece piece_of(PieceType type, PieceSide side);
PieceType type_of(Piece piece);
PieceSide side_of(Piece piece);