#include "chess/move/piece_move_generator.h"

#include "chess/move/piece_move.h"
#include "chess/move/patterns/standard_chess_patterns.h"
#include "chess/piece.h"
#include "chess/placement.h"
#include "chess/utils/tuple.h"

bool evaluate_conditions(
    State *state, 
    PieceMove piece_move, 
    Conditions conditions
) {
    return true; // FIXME
}

const size_t STANDARD_DIRECTIONS_COUNT = 16;
const Direction STANDARD_DIRECTIONS[] = {
    (Direction){0, 1},      // N
    (Direction){1, 2},      // NNE
    (Direction){1, 1},      // NE
    (Direction){2, 1},      // ENE
    (Direction){1, 0},      // E
    (Direction){2, -1},     // ESE
    (Direction){1, -1},     // SE
    (Direction){1, -2},     // SSE
    (Direction){0, -1},     // S
    (Direction){-1, -2},    // SSW
    (Direction){-1, -1},    // SW
    (Direction){-2, -1},    // WSW
    (Direction){-1, 0},     // W
    (Direction){-2, 1},     // WNW
    (Direction){-1, 1},     // NW
    (Direction){-1, 2},     // NNW
};

PatternSet get_piece_pattern_set(PieceType piece_type) {
    PatternSet pattern_set;
    switch (piece_type) {
        case PIECE_TYPE_PAWN: pattern_set = PAWN_PATTERN_SET; break;
        default:
            pattern_set = EMPTY_PATTERN_SET;
    }
    return pattern_set;
}

int generate_pseudo_legal_moves(State *state, PieceMove *move_list) {
    int move_list_count = 0;
    for (int i = 0; i < 64; i++) {
        Piece piece = placement_get_piece(&state->placement, i);
        if (piece != NULL_PIECE && piece_get_side(piece) == state->active_side) {
            PatternSet pattern_set = get_piece_pattern_set(piece_get_type(piece));
            for (int j = 0; j < pattern_set.count; j++) {
                Pattern pattern = pattern_set.patterns[j];
                for (int k = 0; k < STANDARD_DIRECTIONS_COUNT; k++) {
                    if (!((0b1 << k) & pattern.directions)) continue;
                    Direction direction = STANDARD_DIRECTIONS[k];
                    Tuple2 target = index_to_tuple2(i);
                    for (int s = 1; s <= pattern.steps; s++) {
                        target = tuple2_add(target, tuple2_scale(direction, pattern.squares_per_step));
                        if (!tuple2_in_range((Tuple2){0, 0}, target, (Tuple2){7, 7})) continue;
                        PieceMove piece_move = {i, tuple2_to_index(target)};
                        if (!evaluate_conditions(state, piece_move, pattern.conditions)) break;
                        move_list[move_list_count++] = piece_move;
                    }
                }
            }
        }
    }
    return move_list_count;
}

int generate_legal_moves(State *state, PieceMove *move_list) {
    return generate_pseudo_legal_moves(state, move_list);
}