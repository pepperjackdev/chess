#include "chess/state.h"

#include "chess/io/fen.h"

void state_create(State *state, char *fen) {
    parse_fen_into_state(fen, state);
    state->legal_moves_cache = array_create(sizeof(PieceMove) * CHESS_MAX_NUMBER_OF_MOVES);
}

void state_delete(State *state) {
    array_delete(&state->legal_moves_cache);
}