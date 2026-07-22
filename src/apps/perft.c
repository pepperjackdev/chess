#include <stdio.h>
#include <stdint.h>

#include "chess/state.h"
#include "chess/move/piece_move.h"
#include "chess/move/piece_move_generator.h"
#include "chess/io/fen.h"

uint64_t perft(State *state, int depth) {
    if (depth == 0) return 1;
    
    PieceMove move_list[256];
    int move_list_length = generate_legal_moves(state, move_list);

    State mock_state = *state;

    uint64_t nodes = 0;
    for (int i = 0; i < move_list_length; i++) {
        PieceMove move = move_list[i];
        submit_piece_move(mock_state.active_side, move, &mock_state);
        nodes += perft(&mock_state, depth - 1);
    }

    return nodes;
}

int main(int argc, char** argv) {
    // FIXME: perform perft as test
    State state;
    parse_fen_into_state("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", &state);
    printf("Perft: %lu\n", perft(&state, 6));
}
