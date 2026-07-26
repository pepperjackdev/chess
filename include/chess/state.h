#pragma once

#include <stdint.h>

#include "chess/placement.h"
#include "chess/castling.h"
#include "chess/utils/tuple.h"

typedef struct {
  Placement placement;
  PieceSide active_side;
  Castling castling;
  Tuple2 enpassant;
  int halfmove_clock;
  int fullmove_clock;
} State;
