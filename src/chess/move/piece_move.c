#include "chess/move/piece_move.h"

#include "chess/piece.h"
#include "chess/state.h"

bool compare_piece_move(PieceMove m1, PieceMove m2) {
    return m1.source == m2.source && m1.target == m2.target;
}

void apply_piece_move(PieceMove move, State *state) {
    Piece moving = state->placement[move.source];
    state->placement[move.source] = 0;
    state->placement[move.target] = moving | FLAG_MOVED;
    state->active_side = (state->active_side == SIDE_WHITE) ? SIDE_BLACK : SIDE_WHITE;
}

bool is_piece_move_pseudo_legal(PieceMove move, State *state) {
    return true;
}

bool there_is_check(PieceSide side, State *state) {
    //  PieceMove move = {.source = 0};
    //  // locating king (target)
    //  for (int i = 0; i < 64; i++) {
    //      Piece current = state->placement[i];
    //      if (type_of(current) == TYPE_KING && side_of(current) == side) {
    //          move.target = i;
    //      }
    //  }
    //  // looking for checks
    //  for (; move.source < 64; move.source++) {
    //      Piece moving = state->placement[move.source];
    //      if (side_of(moving) == side) continue;
    //      if (is_piece_move_pseudo_legal(move, state)) return true;
    //  }
    //  return false;

    // FIXME: provide effective implementation
    return false;
}

bool is_piece_move_legal(PieceMove move, State *state) {
    if (!is_piece_move_pseudo_legal(move, state)) return false;
    State future_state = *state;
    apply_piece_move(move, &future_state);
    return !there_is_check(state->active_side, &future_state);
}

void submit_piece_move(PieceMove move, State *state) {
    if (is_piece_move_legal(move, state)) {
        apply_piece_move(move, state);
    }
}
