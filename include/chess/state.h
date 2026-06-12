#pragma once

#include "chess/piece.h"

#include <stdint.h>
#include "utils/array.h"

typedef uint8_t Board[64];

typedef enum : uint8_t {
  CASTLING_BLACK_KING_SIDE  = 0b00000001,
  CASTLING_BLACK_QUEEN_SIDE = 0b00000010,
  CASTLING_WHITE_KING_SIDE  = 0b00000100,
  CASTLING_WHITE_QUEEN_SIDE = 0b00001000,
} CastlingRights;

typedef struct {
  Board placement;
  PieceSide active_side;
  CastlingRights castling_rights;
  int en_passant_index;
  int halfmove_clock;
  int fullmove_clock;
  Array legal_moves_cache;
} State;

void state_create(State *state, char *fen);
void state_delete(State *state);