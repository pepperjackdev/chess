#include "chess/move/piece_move.h"

#include "chess/piece.h"
#include "chess/placement.h"
#include "chess/state.h"

bool compare_piece_move(PieceMove m1, PieceMove m2) {
    return m1.from == m2.from && m1.to == m2.to;
}

void submit_piece_move(PieceSide actor, PieceMove move, State *state) {
    if (actor != state->active_side) return;
    Piece moving = placement_get_piece(&state->placement, move.from);
    placement_set_piece(&state->placement, move.from, NULL_PIECE);
    placement_set_piece(&state->placement, move.to, moving);
    state->active_side = (state->active_side == PIECE_SIDE_WHITE) ? 
        PIECE_SIDE_BLACK : PIECE_SIDE_WHITE;
}
