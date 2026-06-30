#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "chess/state.h"

typedef struct {
  size_t from;
  size_t to;
} PieceMove;

void submit_piece_move(PieceMove move, State *state);
