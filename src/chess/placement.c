#include "chess/placement.h"

Piece placement_get_piece(Placement *placement, size_t index) {
    return (*placement)[index];
}

void placement_set_piece(Placement *placement, size_t index, Piece piece) {
    (*placement)[index] = piece;
}