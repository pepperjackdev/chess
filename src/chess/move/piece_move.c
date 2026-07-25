#include "chess/move/piece_move.h"

#include "chess/castling.h"
#include "chess/piece.h"
#include "chess/state.h"
#include "chess/placement.h"
#include "chess/move/piece_move_generator.h"
#include "chess/utils/tuple.h"
#include <stdlib.h>

bool compare_piece_move(PieceMove m1, PieceMove m2) {
    return m1.from == m2.from && m1.to == m2.to;
}

PieceMoveFlags compute_dynamic_piece_move_flags(PieceMove piece_move, State *state) {
    Piece moving = placement_get_piece(&state->placement, piece_move.from);
    Piece target = placement_get_piece(&state->placement, piece_move.to);

    PieceMoveFlags flags = 0;

    if (piece_get_type(moving) == PIECE_TYPE_PAWN || target != NULL_PIECE) flags |= PIECE_MOVE_IS_NOT_REVERSIBLE;
    else flags |= PIECE_MOVE_IS_REVERSIBLE;
    
    if (piece_get_type(moving) == PIECE_TYPE_PAWN && 
        abs(t2sub(itot2(piece_move.to), itot2(piece_move.from)).y) == 2) 
    {
        flags |= PIECE_MOVE_ENABLES_EN_PASSANT;    
    }

    return flags;
}

void make_piece_move(PieceMove move, State *state) {
    Piece moving = placement_get_piece(&state->placement, move.from) | PIECE_FLAG_MOVED;
    PieceMoveFlags flags = move.flags | compute_dynamic_piece_move_flags(move, state);

    placement_set_piece(&state->placement, move.from, NULL_PIECE);
    placement_set_piece(&state->placement, move.to, moving);

    state->en_passant_index = -1;

    if (flags & PIECE_MOVE_IS_REVERSIBLE) state->halfmove_clock += 1;
    if (flags & PIECE_MOVE_IS_NOT_REVERSIBLE) {
        state->halfmove_clock = 0;
        state->fullmove_clock += 1;
    }
    
    if (flags & PIECE_MOVE_ENABLES_EN_PASSANT) {
        state->en_passant_index = t2toi(t2sub(itot2(move.to), 
            t2scale(((Tuple2){0, 1}), piece_get_side(moving) == PIECE_SIDE_WHITE ? -1 : 1)
        ));
    }

    if (flags & PIECE_MOVE_IS_EN_PASSANT) {
        placement_set_piece(&state->placement, 
            t2toi(t2sub(itot2(move.to),t2scale(((Tuple2){0, 1}), piece_get_side(moving) == PIECE_SIDE_WHITE ? -1 : 1))), 
            NULL_PIECE);
    }

    if (flags & PIECE_MOVE_DISABLES_CASTLING_KING) {
        state->castling &= state->castling ^ (state->active_side == PIECE_SIDE_WHITE) ? 
            CASTLING_WHITE_KING_SIDE : CASTLING_BLACK_KING_SIDE;
    }

    if (flags & PIECE_MOVE_DISABLES_CASTLING_QUEEN) {
        state->castling &= state->castling ^ (state->active_side == PIECE_SIDE_WHITE) ? 
            CASTLING_WHITE_QUEEN_SIDE : CASTLING_BLACK_QUEEN_SIDE;
    }

    if (flags & PIECE_MOVE_IMPLIES_PROMOTION) {
        // TODO
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
            make_piece_move(move_list[i], state);
            break;
        };
    }
}
