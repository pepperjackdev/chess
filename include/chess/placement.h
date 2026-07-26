#pragma once

#include <stddef.h>

#include "chess/piece.h"
#include "chess/utils/tuple.h"

typedef Piece Placement[64]; 

Piece placement_get_piece(Placement *placement, Tuple2 position);
void placement_set_piece(Placement *placement, Tuple2 position, Piece piece);