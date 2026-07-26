#pragma once

#include <stdint.h>

#include "chess/state.h"
#include "chess/utils/tuple.h"

typedef enum : uint8_t {
  PIECE_MOVE_IS_REVERSIBLE            = 0b1 << 0,
  PIECE_MOVE_IS_NOT_REVERSIBLE        = 0b1 << 1,
  PIECE_MOVE_ENABLES_EN_PASSANT       = 0b1 << 2,
  PIECE_MOVE_IS_EN_PASSANT            = 0b1 << 3,
  PIECE_MOVE_DISABLES_CASTLING_KING   = 0b1 << 4,
  PIECE_MOVE_DISABLES_CASTLING_QUEEN  = 0b1 << 5,
  PIECE_MOVE_IS_CASTLING              = 0b1 << 6,
  PIECE_MOVE_IMPLIES_PROMOTION        = 0b1 << 7
} PieceMoveFlags;

typedef struct {
  Tuple2 from;
  Tuple2 to;
  PieceMoveFlags flags;
} PieceMove;

bool compare_piece_move(PieceMove m1, PieceMove m2);

void submit_piece_move(PieceSide actor, PieceMove move, State *state);
