#pragma once

#include <stdint.h>

#include "chess/move/piece_move.h"
#include "chess/utils/tuple.h"

#define MOVE_LIST_LENGTH 256

typedef Tuple2 Direction;

extern const size_t STANDARD_DIRECTIONS_COUNT;
extern const Direction STANDARD_DIRECTIONS[16];

typedef enum : uint16_t {
    N   = 0b1 << 0,
    NNE = 0b1 << 1,
    NE  = 0b1 << 2,
    ENE = 0b1 << 3,
    E   = 0b1 << 4,
    ESE = 0b1 << 5,
    SE  = 0b1 << 6,
    SSE = 0b1 << 7,
    S   = 0b1 << 8,
    SSW = 0b1 << 9,
    SW  = 0b1 << 10,
    WSW = 0b1 << 11,
    W   = 0b1 << 12,
    WNW = 0b1 << 13,
    NW  = 0b1 << 14,
    NNW = 0b1 << 15
} Directions;

typedef enum : uint8_t {
    SQUARE_EMPTY            = 0b1 << 0,
    SQUARE_ENEMY            = 0b1 << 1,
    SQUARE_EMPTY_OR_ENEMY   = 0b1 << 2,
    SQUARE_EN_PASSANT       = 0b1 << 3,
    PIECE_NEVER_MOVED       = 0b1 << 4,
} Conditions;

typedef struct {
    Directions directions;
    int squares_per_step;
    int steps;
    Conditions conditions;
} Pattern;

typedef struct {
    const Pattern *patterns;
    size_t count;
} PatternSet;

#define DEF_PATTERN_SET(NAME, ...) \
    static const Pattern NAME##_PATTERN_SET_ARRAY[] = { \
        __VA_ARGS__ \
    }; \
    static const PatternSet NAME##_PATTERN_SET = { \
        NAME##_PATTERN_SET_ARRAY, \
        sizeof(NAME##_PATTERN_SET_ARRAY) / sizeof(NAME##_PATTERN_SET_ARRAY[0]) \
    };

DEF_PATTERN_SET(EMPTY, );

int generate_legal_moves(State *state, PieceMove *move_list);
