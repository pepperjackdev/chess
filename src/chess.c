#include "chess.h"
#include "utils/array.h"
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
        case TYPE_NULL:     return (Array){NULL, 0, 0};
        case TYPE_KING:     return (Array){NULL, 0, 0};
        case TYPE_QUEEN:    return (Array){NULL, 0, 0};
        case TYPE_BISHOP:   return (Array){NULL, 0, 0};
        case TYPE_KNIGHT:   return (Array){NULL, 0, 0};
        case TYPE_ROOK:     return ARRAY_FROM_C_ARRAY(ROOK_MOVE_PATTERNS);
        case TYPE_PAWN:     return (Array){NULL, 0, 0};
        default:
            fprintf(stderr, 
                "Cannot fint MovePattern for Type %b", 
                type
            );
    }
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
            for (int j = 0; j < pattern->limit; j++) {
                new_index += direction * coefficient;
                if (new_index < 0 || new_index >= 64) break;

                bool status_match;
                Piece target_piece = state->placement[new_index];
                switch (pattern->status) {
                    case SQUARE_EMPTY: 
                        status_match = target_piece == 0;
                        break;
                    case SQUARE_OCCUPIED_ALLY: 
                        status_match = target_piece != 0 &&
                            side_of(target_piece) == side_of(piece); 
                        break;
                    case SQUARE_OCCUPIED_ENEMY:
                        status_match = target_piece != 0 &&
                            side_of(target_piece) != side_of(piece); 
                        break;
                    case SQUARE_EMPTY_OR_OCCUPIED_BY_ENEMY:
                        status_match = target_piece == 0 ||
                            side_of(target_piece) != side_of(piece); 
                        break;
                }

                if (status_match) {
                    ((Move*)moves->array)[moves->length] = (Move){index, new_index};   
                    moves->length++;
                }
            }
        }
    }
}

void generate_legal_moves(Array *moves, State *state) {
    moves->length = 0;
    for (int i = 0; i < 64; i++) {
        Piece piece = state->placement[i];
        if (side_of(piece) != state->active_side) continue;
        generate_piece_legal_moves(moves, i, state);
    }
}

void move(Move move, State *state) {
    LEGAL_MOVES_CACHE.length = 0;

    generate_legal_moves(&LEGAL_MOVES_CACHE, state);

    printf("Generated moves: %d\n", LEGAL_MOVES_CACHE.length);

    for (int i = 0; i < LEGAL_MOVES_CACHE.length; i++) {
        printf("Move %d -> %d\n",
            LEGAL_MOVES_CACHE_C_ARRAY[i].source,
            LEGAL_MOVES_CACHE_C_ARRAY[i].target
        );
    }

    for (int i = 0; i < LEGAL_MOVES_CACHE.length; i++) {
        if (compare(move, ((Move*)LEGAL_MOVES_CACHE.array)[i])) {
            Piece piece = state->placement[move.source];

            state->placement[move.source] = 0;
            state->placement[move.target] = piece;

            return;
        }
    }
}
