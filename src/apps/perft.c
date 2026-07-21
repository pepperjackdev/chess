#include <stdint.h>
#include <stdio.h>

#include "chess/state.h"
#include "chess/move/piece_move.h"
#include "chess/move/piece_move_generator.h"

uint64_t perft(State *state, int depth) {
    if (depth == 0) return 1;
    
    PieceMove move_list[256];
    int move_list_length = generate_legal_moves(state, move_list);

    uint64_t nodes = 0;
    for (int i = 0; i < move_list_length; i++) {
        // Make move
        nodes += perft(state, depth - 1);
        // Unmake move
    }

    return nodes;
}

int main() {
    printf("Hello, World!\n");
}
