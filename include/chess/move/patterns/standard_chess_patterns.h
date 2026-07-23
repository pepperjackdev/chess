#pragma once

#include "chess/move/piece_move_generator.h"

DEF_PATTERN_SET(PAWN, 
    {N, 1, 1, SQUARE_EMPTY},
    {NE | NW, 1, 1, SQUARE_ENEMY},
    {N, 2, 1, SQUARE_EMPTY | PIECE_NEVER_MOVED}
);

DEF_PATTERN_SET(KNIGHT,
    {NNE | ENE | ESE | SSE | SSW | WSW | WNW | NNW, 1, 1, SQUARE_NOT_ALLY}
);

DEF_PATTERN_SET(BISHOP, 
    {NE | SE | SW | NW, 1, -1, SQUARE_NOT_ALLY}
);

DEF_PATTERN_SET(ROOK, 
    {N | E | S | W, 1, -1, SQUARE_NOT_ALLY}
);

DEF_PATTERN_SET(QUEEN, 
    {N | NE | E | SE | S | SW | W | NW, 1, -1, SQUARE_NOT_ALLY}
);

DEF_PATTERN_SET(KING, 
    {N | NE | E | SE | S | SW | W | NW, 1, 1, SQUARE_NOT_ALLY}
);