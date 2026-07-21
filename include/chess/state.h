#pragma once

#include <stdint.h>

#include "chess/placement.h"
#include "chess/castling.h"

typedef struct {
  Placement placement;
  PieceSide active_side;
  Castling castling;
  int en_passant_index;
  int halfmove_clock;
  int fullmove_clock;
} State;
