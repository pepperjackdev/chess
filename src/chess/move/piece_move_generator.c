#include "chess/move/piece_move_generator.h"

#include "chess/move/piece_move.h"
#include "chess/move/patterns/standard_chess_patterns.h"
#include "chess/piece.h"
#include "chess/placement.h"
#include "chess/state.h"
#include "chess/utils/tuple.h"

ConditionFlag compute_conditions(
    State *state, 
    PieceMove piece_move
) {
    ConditionFlag conditions = 0;
    Piece moving_piece = placement_get_piece(&state->placement, piece_move.from);
    Piece target_piece = placement_get_piece(&state->placement, piece_move.to);
    if (target_piece == NULL_PIECE) conditions |= SQUARE_EMPTY;
    if (target_piece != NULL_PIECE && piece_get_side(target_piece) != state->active_side) conditions |= SQUARE_ENEMY;
    if (target_piece == NULL_PIECE || piece_get_side(target_piece) != state->active_side) conditions |= SQUARE_NOT_ALLY;
    if (piece_move.to == state->en_passant_index) conditions |= SQUARE_EN_PASSANT;
    if (moving_piece != NULL_PIECE && !(moving_piece & PIECE_FLAG_MOVED)) conditions |= PIECE_NEVER_MOVED;
    return conditions;
}


bool evaluate_conditions(
    State *state, 
    PieceMove piece_move, 
    ConditionFlag conditions
) {
    return (conditions & compute_conditions(state, piece_move)) == conditions;
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
        case PIECE_TYPE_PAWN:   pattern_set = PAWN_PATTERN_SET;     break;
        case PIECE_TYPE_KNIGHT: pattern_set = KNIGHT_PATTERN_SET;   break;
        case PIECE_TYPE_BISHOP: pattern_set = BISHOP_PATTERN_SET;   break;
        case PIECE_TYPE_ROOK:   pattern_set = ROOK_PATTERN_SET;     break;
        case PIECE_TYPE_QUEEN:  pattern_set = QUEEN_PATTERN_SET;    break;
        case PIECE_TYPE_KING:   pattern_set = KING_PATTERN_SET;     break;
        default:
            pattern_set = EMPTY_PATTERN_SET;
    }
    return pattern_set;
}

PieceMoveFlag compute_piece_move_flags(State *state, PieceMove piece_move) {
    PieceMoveFlag flags;
    Piece moving = placement_get_piece(&state->placement, piece_move.from);
    Piece target = placement_get_piece(&state->placement, piece_move.to);
    if (target == NULL_PIECE && piece_get_type(moving) != PIECE_TYPE_PAWN) flags |= PIECE_MOVE_IS_REVERSIBLE;
    else flags |= PIECE_MOVE_IS_NOT_REVERSIBLE;
    if (piece_get_type(moving) == PIECE_TYPE_KING) flags |= PIECE_MOVE_DISABLES_CASTLING_KING | PIECE_MOVE_DISABLES_CASTLING_QUEEN;
    if (piece_get_type(moving) == PIECE_TYPE_ROOK) {
        if (piece_move.from == 0 || piece_move.from == 56) flags |= PIECE_MOVE_DISABLES_CASTLING_QUEEN;
        if (piece_move.from == 7 || piece_move.from == 63) flags |= PIECE_MOVE_DISABLES_CASTLING_KING;
    }
    if (piece_get_type(moving) == PIECE_TYPE_PAWN) {
        Tuple2 target_position = index_to_tuple2(piece_move.to);
        if (target_position.y == 0 || target_position.y == 7) flags |= PIECE_MOVE_IMPLIES_PROMOTION;
    }
    return flags;
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
                    for (int s = 1; s <= pattern.steps | pattern.steps == PATTERN_STEPS_UNLIMITED; s++) {
                        int direction_coefficient = (piece_get_side(piece) == PIECE_SIDE_BLACK) ? 1 : -1;
                        target = tuple2_add(target, tuple2_scale(direction, 
                            pattern.squares_per_step * direction_coefficient));
                        if (!tuple2_in_range((Tuple2){0, 0}, target, (Tuple2){7, 7})) break;
                        PieceMove piece_move = {i, tuple2_to_index(target), pattern.piece_move_flags};
                        piece_move.flags |= compute_piece_move_flags(state, piece_move);
                        if (!evaluate_conditions(state, piece_move, pattern.conditions)) break;
                        move_list[move_list_count++] = piece_move;
                        if (placement_get_piece(&state->placement, piece_move.to) != NULL_PIECE) break;
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