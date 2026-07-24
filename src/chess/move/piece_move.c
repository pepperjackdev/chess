#include "chess/move/piece_move.h"

#include "chess/piece.h"
#include "chess/state.h"
#include "chess/placement.h"
#include "chess/move/piece_move_generator.h"
#include "chess/utils/tuple.h"

bool compare_piece_move(PieceMove m1, PieceMove m2) {
    return m1.from == m2.from && m1.to == m2.to;
}

void make_piece_move(PieceMove move, State *state) {
    Piece moving = placement_get_piece(&state->placement, move.from) | PIECE_FLAG_MOVED;
    placement_set_piece(&state->placement, move.from, NULL_PIECE);
    placement_set_piece(&state->placement, move.to, moving);
    if (move.flags & PIECE_MOVE_IS_REVERSIBLE) state->halfmove_clock++;
    if (move.flags & PIECE_MOVE_IS_NOT_REVERSIBLE) {
        state->fullmove_clock += 1;
        state->halfmove_clock = 0;
    };
    if (move.flags & PIECE_MOVE_ENABLES_ENPASSANT) {
        state->en_passant_index = tuple2_to_index(
            tuple2_add(index_to_tuple2(move.from),
                tuple2_scale(STANDARD_DIRECTIONS[N], state->active_side == PIECE_SIDE_WHITE ? -1 : 1)
            )
        );
    }
    state->active_side = (state->active_side == PIECE_SIDE_WHITE) ? 
        PIECE_SIDE_BLACK : PIECE_SIDE_WHITE;
}

void submit_piece_move(PieceSide actor, PieceMove move, State *state) {
    if (actor != state->active_side) return;
    PieceMove move_list[MOVE_LIST_LENGTH];
    int count = generate_legal_moves(state, move_list);
    for (int i = 0; i < count; i++) {
        if (compare_piece_move(move, move_list[i])) {
            make_piece_move(move, state);
            break;
        };
    }
}
