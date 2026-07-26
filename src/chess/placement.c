#include "chess/placement.h"
#include "chess/utils/tuple.h"

Piece placement_get_piece(Placement *placement, Tuple2 position) {
    return (*placement)[t2toi(position)];
}

void placement_set_piece(Placement *placement, Tuple2 position, Piece piece) {
    (*placement)[t2toi(position)] = piece;
}