#pragma once

#include <stddef.h>

#include "chess/piece.h"

typedef Piece Placement[64];

Piece placement_get_piece(Placement *placement, size_t index);
void placement_set_piece(Placement *placement, size_t index, Piece piece);