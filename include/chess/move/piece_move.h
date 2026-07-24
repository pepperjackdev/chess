#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "chess/state.h"

typedef enum : uint8_t {
  PIECE_MOVE_IS_REVERSIBLE            = 0b1 << 0,
  PIECE_MOVE_IS_NOT_REVERSIBLE        = 0b1 << 1,
  PIECE_MOVE_ENABLES_ENPASSANT        = 0b1 << 2,
  PIECE_MOVE_DISABLES_CASTLING_KING   = 0b1 << 3,
  PIECE_MOVE_DISABLES_CASTLING_QUEEN  = 0b1 << 4,
  PIECE_MOVE_IMPLIES_PROMOTION        = 0b1 << 5
} PieceMoveFlag;

typedef struct {
  size_t from;
  size_t to;
  PieceMoveFlag flags;
} PieceMove;

void submit_piece_move(PieceSide actor, PieceMove move, State *state);
