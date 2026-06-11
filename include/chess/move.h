#pragma once

#include "chess/state.h"

#include <stdint.h>

typedef struct {
  int source;
  int target;
} PieceMove;

enum MoveType {
  PIECE_MOVE,
};

union Move {
  PieceMove piece_move;
};

bool compare_piece_moves(PieceMove m1, PieceMove m2);

typedef struct {
  enum MoveType move_type;
  union Move move_data;
} Move;

void submit_piece_move(PieceMove move, State *state);
void submit_move(Move move, State *state);