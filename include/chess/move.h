#pragma once

#include "chess/state.h"
#include "chess/move/piece_move.h"

#include <stdint.h>

enum MoveType {
  PIECE_MOVE,
};

union Move {
  PieceMove piece_move;
};

typedef struct {
  enum MoveType move_type;
  union Move move_data;
} Move;

void submit_move(Move move, State *state);
