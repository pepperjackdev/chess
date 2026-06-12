#include "chess/move.h"
#include "chess/piece_move_generator.h"

bool compare_piece_moves(PieceMove m1, PieceMove m2) {
    return m1.source == m2.source && m1.target == m2.target;
}

void submit_piece_move(PieceMove move, State *state) {
    if (state->legal_moves_cache.length == 0) {
        generate_legal_piece_moves(&state->legal_moves_cache, state);
    };
    
    for (int i = 0; i < state->legal_moves_cache.length; i++) {
        if (compare_piece_moves(move, ((PieceMove*)state->legal_moves_cache.array)[i])) {
            Piece piece = state->placement[move.source];
            state->placement[move.source] = 0;
            state->placement[move.target] = piece | FLAG_MOVED;
            state->active_side ^= SIDE_BLACK;
            generate_legal_piece_moves(&state->legal_moves_cache, state);
            return;
        }
    }
}

void submit_move(Move move, State *state) {
    switch (move.move_type) {
        case PIECE_MOVE: submit_piece_move(move.move_data.piece_move,  state); break;
    }
}