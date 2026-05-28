#include "chess/move.h"

#include <stdio.h>

bool compare_piece_moves(PieceMove m1, PieceMove m2) {
    return m1.source == m2.source && m1.target == m2.target;
}

Array get_type_move_pattern(PieceType type) {
    switch (type) {
        case TYPE_KING:     return ARRAY_FROM_C_ARRAY(KING_PIECE_MOVE_PATTERNS);
        case TYPE_QUEEN:    return ARRAY_FROM_C_ARRAY(QUEEN_PIECE_MOVE_PATTERNS);
        case TYPE_BISHOP:   return ARRAY_FROM_C_ARRAY(BISHOP_PIECE_MOVE_PATTERNS);
        case TYPE_KNIGHT:   return ARRAY_FROM_C_ARRAY(KNIGHT_PIECE_MOVE_PATTERNS);
        case TYPE_ROOK:     return ARRAY_FROM_C_ARRAY(ROOK_PIECE_MOVE_PATTERNS);
        case TYPE_PAWN:     return ARRAY_FROM_C_ARRAY(PAWN_PIECE_MOVE_PATTERNS);
        default:
            fprintf(stderr, 
                "Cannot find MovePattern for Type %b\n", 
                type
            );
    }

    return (Array){NULL, 0, 0};
}

bool compare_move_conditions(PieceMoveCondition m1, PieceMoveCondition m2) {
    return (m1 & m2 & 0b00000111)
        && ((m1 & m2 & 0b11111000) == (m2 & 0b11111000));
}

PieceMoveCondition compute_conditions(PieceMove move, State *state) {
    uint8_t condition = 0x00;
    Piece moving = state->placement[move.source];
    Piece target = state->placement[move.target];
    condition |= (target == 0) ? SQUARE_EMPTY : 0x00;
    condition |= (target != 0x00 && (side_of(target) == side_of(moving))) ? SQUARE_OCCUPIED_ALLY : 0x00;
    condition |= (target != 0x00 && (side_of(target) != side_of(moving))) ? SQUARE_OCCUPIED_ENEMY : 0x00;
    condition |= (move.target == state->en_passant_index) ? SQUARE_EN_PASSANT : 0x00;
    condition |= (moving & FLAG_MOVED) ? 0x00 : PIECE_NEVER_MOVED;
    return condition;
}

void generate_piece_legal_piece_moves(Array *moves, int index, State *state) {
    Piece piece = state->placement[index];
    int coefficient = (side_of(piece) == SIDE_WHITE) ? 1 : -1;
    Array move_patterns = get_type_move_pattern(type_of(piece));

    // For each move pattern
    for (int pattern_i = 0; pattern_i < move_patterns.length; pattern_i++) {
        PieceMovePattern *pattern = ((PieceMovePattern**)move_patterns.array)[pattern_i];

        // For each direction in a move pattern
        for (int direction_i = 0; direction_i < pattern->directions.length; direction_i++) {
            Direction direction = ((Direction*)pattern->directions.array)[direction_i];
            int new_index = index;

            // For each square along a direction
            for (int step = 1; step <= pattern->max_number_of_steps || pattern->max_number_of_steps == -1; step++) {
                int current_rank = RANK(index);
                int current_file = FILE(index);

                current_rank += direction.rank * coefficient * pattern->squares_per_step * step;
                current_file += direction.file * coefficient * pattern->squares_per_step * step;

                if (current_rank < 0 || current_rank >= 8 || current_file < 0 || current_file >= 8) {
                    break;
                }

                new_index = current_rank * 8 + current_file;

                bool is_path_occupied = false;                
                for (int i = 1; i < pattern->squares_per_step; i++) {
                    int new_index = index + i * INDEX(direction) * coefficient;
                    if (new_index < 0 || new_index >= 64) break;
                    if (state->placement[new_index] != 0) {
                        is_path_occupied = true;
                        break;
                    };
                }
                if (is_path_occupied) break;

                Piece target_piece = state->placement[new_index];

                PieceMoveCondition computed_condition = compute_conditions(
                    (PieceMove){index, new_index}, 
                    state
                );

                if (compare_move_conditions(computed_condition, pattern->condition)) {
                    ((PieceMove*)moves->array)[moves->length] = (PieceMove){
                        index, 
                        new_index
                    };
                    moves->length++;
                }

                if (target_piece != 0) break;
            }
        }
    }
}

void generate_pseudo_legal_moves(Array *moves, State *state) {
    moves->length = 0;
    for (int i = 0; i < 64; i++) {
        Piece piece = state->placement[i];
        if (piece == 0) continue;
        if (side_of(piece) != state->active_side) continue;
        generate_piece_legal_piece_moves(moves, i, state);
    }
}

void generate_legal_piece_moves(Array *moves, State *state) {
    generate_pseudo_legal_moves(moves,  state);
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