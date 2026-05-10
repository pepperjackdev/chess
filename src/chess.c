#include "chess.h"
#include "utils/array.h"
#include <stdint.h>
#include <stdio.h>

Piece piece_of(PieceType type, PieceSide side) {
    return type | side;
}

PieceType type_of(Piece piece) {
    return piece & 0b00000111;
}

PieceSide side_of(Piece piece) {
    return piece & 0b00001000;
}

bool compare(Move m1, Move m2) {
    return m1.source == m2.source && m1.target == m2.target;
}

Array get_type_move_pattern(PieceType type) {
    switch (type) {
        case TYPE_KING:     return ARRAY_FROM_C_ARRAY(KING_MOVE_PATTERNS);
        case TYPE_QUEEN:    return ARRAY_FROM_C_ARRAY(QUEEN_MOVE_PATTERNS);
        case TYPE_BISHOP:   return ARRAY_FROM_C_ARRAY(BISHOP_MOVE_PATTERNS);
        case TYPE_KNIGHT:   return ARRAY_FROM_C_ARRAY(KNIGHT_MOVE_PATTERNS);
        case TYPE_ROOK:     return ARRAY_FROM_C_ARRAY(ROOK_MOVE_PATTERNS);
        case TYPE_PAWN:     return ARRAY_FROM_C_ARRAY(PAWN_MOVE_PATTERNS);
        default:
            fprintf(stderr, 
                "Cannot find MovePattern for Type %b\n", 
                type
            );
    }

    return (Array){NULL, 0, 0};
}

uint8_t compute_conditions(Move move, State *state) {
    uint8_t condition = 0x00;
    Piece moving = state->placement[move.source];
    Piece target = state->placement[move.target];
    condition |= (target == 0) ? SQUARE_EMPTY : 0x00;
    condition |= (target != 0 && side_of(target) == side_of(moving)) ? SQUARE_OCCUPIED_ALLY : 0x00;
    condition |= (target != 0 && side_of(target) != side_of(moving)) ? SQUARE_OCCUPIED_ENEMY : 0x00;
    condition |= (move.target == state->en_passant_index) ? SQUARE_EN_PASSANT : 0x00;
    condition |= (moving & PIECE_HAS_BEEN_MOVED) ?  0x00 : PIECE_NEVER_MOVED;
    return condition;
}

void generate_piece_legal_moves(Array *moves, int index, State *state) {
    Piece piece = state->placement[index];
    int coefficient = (side_of(piece) == SIDE_WHITE) ? 1 : -1;
    Array move_patterns = get_type_move_pattern(type_of(piece));

    // For each move pattern
    for (int pattern_i = 0; pattern_i < move_patterns.length; pattern_i++) {
        MovePattern *pattern = ((MovePattern**)move_patterns.array)[pattern_i];

        // For each direction in a move pattern
        for (int direction_i = 0; direction_i < pattern->directions.length; direction_i++) {
            MoveDirection direction = ((MoveDirection*)pattern->directions.array)[direction_i];
            int new_index = index;

            // For each square along a direction
            for (int j = 0; j < pattern->limit || pattern->limit == -1; j++) {
                new_index += direction * coefficient;
                if (new_index < 0 || new_index >= 64) break;

                Piece target_piece = state->placement[new_index];

                bool condition = pattern->condition & 
                    compute_conditions((Move){index, new_index}, state);

                if (condition) {
                    ((Move*)moves->array)[moves->length] = (Move){
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

void generate_legal_moves(Array *moves, State *state) {
    moves->length = 0;
    for (int i = 0; i < 64; i++) {
        Piece piece = state->placement[i];
        if (piece == 0) continue;
        if (side_of(piece) != state->active_side) continue;
        generate_piece_legal_moves(moves, i, state);
    }
}

void move(Move move, State *state) {
    LEGAL_MOVES_CACHE.length = 0;
    generate_legal_moves(&LEGAL_MOVES_CACHE, state);
    for (int i = 0; i < LEGAL_MOVES_CACHE.length; i++) {
        if (compare(move, ((Move*)LEGAL_MOVES_CACHE.array)[i])) {
            Piece piece = state->placement[move.source];
            state->placement[move.source] = 0;
            state->placement[move.target] = piece | PIECE_HAS_BEEN_MOVED;
            state->active_side ^= SIDE_BLACK;
            return;
        }
    }
}
