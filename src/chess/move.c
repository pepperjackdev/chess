#include "chess/move.h"

#include "chess/state.h"

void submit_move(Move move, State *state) {
    switch (move.move_type) {
        case PIECE_MOVE: submit_piece_move(move.move_data.piece_move, state); break;
    }
}