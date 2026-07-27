#include "chess/move/piece_move_generator.h"

#include "chess/castling.h"
#include "chess/move/piece_move.h"
#include "chess/move/patterns/standard_chess_patterns.h"
#include "chess/piece.h"
#include "chess/placement.h"
#include "chess/state.h"
#include "chess/utils/tuple.h"

ConditionFlag compute_conditions(
    State *state, 
    PieceMove piece_move,
    ConditionFlag to_compute
) {
    ConditionFlag conditions = 0;
    Piece moving_piece = placement_get_piece(&state->placement, piece_move.from);
    Piece target_piece = placement_get_piece(&state->placement, piece_move.to);
    if (to_compute & SQUARE_EMPTY && target_piece == NULL_PIECE) conditions |= SQUARE_EMPTY;
    if (to_compute & SQUARE_ENEMY && target_piece != NULL_PIECE && piece_get_side(target_piece) != state->active_side) conditions |= SQUARE_ENEMY;
    if (to_compute & SQUARE_NOT_ALLY && target_piece == NULL_PIECE || piece_get_side(target_piece) != state->active_side) conditions |= SQUARE_NOT_ALLY;
    if (to_compute & SQUARE_EN_PASSANT && t2cmp(piece_move.to, state->enpassant)) conditions |= SQUARE_EN_PASSANT;
    if (to_compute & PIECE_NEVER_MOVED && moving_piece != NULL_PIECE && !(moving_piece & PIECE_FLAG_MOVED)) conditions |= PIECE_NEVER_MOVED;
    if (to_compute & CASTLING_KING_SIDE_ALLOWED && state->castling & ((state->active_side == PIECE_SIDE_WHITE) ? CASTLING_WHITE_KING_SIDE : CASTLING_BLACK_KING_SIDE)) conditions |= CASTLING_KING_SIDE_ALLOWED;
    if (to_compute & CASTLING_QUEEN_SIDE_ALLOWED && state->castling & ((state->active_side == PIECE_SIDE_WHITE) ? CASTLING_WHITE_QUEEN_SIDE : CASTLING_BLACK_QUEEN_SIDE)) conditions |= CASTLING_QUEEN_SIDE_ALLOWED;
    if (to_compute & CASTLING_PATH_IS_CLEAR) {
        bool path_is_clear = true;
        
        if (conditions & CASTLING_KING_SIDE_ALLOWED) {
            for (int i = 1; i <= 2; i++) {
                Tuple2 position = t2add(piece_move.from, t2(i, 0));
                if (placement_get_piece(&state->placement, position) != NULL_PIECE) path_is_clear = false;
            }
        }

        if (conditions & CASTLING_QUEEN_SIDE_ALLOWED) {
            for (int i = 1; i <= 3; i++) {
                Tuple2 position = t2sub(piece_move.from, t2(i, 0));
                if (placement_get_piece(&state->placement, position) != NULL_PIECE) path_is_clear = false;
            }
        }

        if (path_is_clear) conditions |= CASTLING_PATH_IS_CLEAR;
    }
    return conditions;
}


bool evaluate_conditions(
    State *state, 
    PieceMove piece_move,
    ConditionFlag conditions
) {
    return (conditions & compute_conditions(state, piece_move, conditions)) == conditions;
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

void generate_pseudo_legal_piece_moves(
    State *state, 
    PieceMove *move_list,
    int *move_list_count,
    Tuple2 position) 
{
    Piece piece = placement_get_piece(&state->placement, position);
    PatternSet set = get_piece_pattern_set(piece_get_type(piece));
    for (int j = 0; j < set.count; j++) {
        Pattern pattern = set.patterns[j];
        for (int k = 0; k < STANDARD_DIRECTIONS_COUNT; k++) {
            if (!((0b1 << k) & pattern.directions)) continue;
            Direction direction = STANDARD_DIRECTIONS[k];
            Tuple2 target = position;
            for (int s = 1; s <= pattern.steps | pattern.steps == PATTERN_STEPS_UNLIMITED; s++) {
                int direction_coefficient = (pattern.is_direction_relative &&
                    piece_get_side(piece) == PIECE_SIDE_BLACK) ? 1 : -1;
                target = t2add(target, t2scale(direction, 
                    pattern.squares_per_step * direction_coefficient));
                if (!t2range((Tuple2){0, 0}, target, (Tuple2){7, 7})) break;
                PieceMove piece_move = {position, target, pattern.piece_move_static_flags};
                if (!evaluate_conditions(state, piece_move, pattern.conditions)) break;
                move_list[(*move_list_count)++] = piece_move;
                if (placement_get_piece(&state->placement, piece_move.to) != NULL_PIECE) break;
            }
        }
    }
}

int generate_pseudo_legal_moves(State *state, PieceMove *move_list) {
    int move_list_count = 0;
    int king_index = 0;
    for (int i = 0; i < 64; i++) {
        Piece piece = placement_get_piece(&state->placement, itot2(i));
        if (piece == NULL_PIECE || piece_get_side(piece) != state->active_side) continue;
        if (piece == piece_new(PIECE_TYPE_KING, state->active_side)) { king_index = i; continue; }
        generate_pseudo_legal_piece_moves(state, move_list, &move_list_count, itot2(i));
    }
    generate_pseudo_legal_piece_moves(state, move_list, &move_list_count, itot2(king_index));
    return move_list_count;
}

int generate_legal_moves(State *state, PieceMove *move_list) {
    return generate_pseudo_legal_moves(state, move_list);
}