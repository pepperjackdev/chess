#pragma once

#include "chess/state.h"

#include "utils/array.h"
#include <stdint.h>

#define CHESS_MAX_NUMBER_OF_MOVES 256

typedef struct {
  int file;
  int rank;
} Index;

typedef struct {
  int file;
  int rank;
} Direction;

#define RANK(index) (index / 8)
#define FILE(index) (index % 8)
#define INDEX(position) (position.rank * 8 + position.file)

#define NORTH            (Direction){0, -1}
#define NORTH_NORTH_EAST (Direction){1, -2}
#define NORTH_EAST       (Direction){1, -1}
#define EAST_NORTH_EAST  (Direction){2, -1}
#define EAST             (Direction){1, 0}
#define EAST_SOUTH_EAST  (Direction){2, 1}
#define SOUTH_EAST       (Direction){1, 1}
#define SOUTH_SOUTH_EAST (Direction){1, 2}
#define SOUTH            (Direction){0, 1}
#define SOUTH_SOUTH_WEST (Direction){-1, 2}
#define SOUTH_WEST       (Direction){-1, 1}
#define WEST_SOUTH_WEST  (Direction){-2, 1}
#define WEST             (Direction){-1, 0}
#define WEST_NORTH_WEST  (Direction){-2, -1}
#define NORTH_WEST       (Direction){-1, -1}
#define NORTH_NORTH_WEST (Direction){-1, -2}

typedef enum : uint8_t {
  SQUARE_EMPTY          = 0b00000001,
  SQUARE_OCCUPIED_ALLY  = 0b00000010,
  SQUARE_OCCUPIED_ENEMY = 0b00000100,
  SQUARE_EN_PASSANT     = 0b00001000,
  PIECE_NEVER_MOVED     = 0b00010000
} PieceMoveCondition;

bool compare_move_conditions(PieceMoveCondition m1, PieceMoveCondition m2);

typedef struct {
  Array directions;
  int squares_per_step;
  int max_number_of_steps;
  PieceMoveCondition condition;
} PieceMovePattern;

#define MOVE_PATTERN(NAME, squares_per_step, max_number_of_steps, condition, ...) \
  static Direction NAME##_PIECE_MOVE_DIRECTIONS[] = {__VA_ARGS__}; \
  static PieceMovePattern NAME##_PIECE_MOVE_PATTERN = (PieceMovePattern){ \
    ARRAY_FROM_C_ARRAY(NAME##_PIECE_MOVE_DIRECTIONS), \
    squares_per_step, \
    max_number_of_steps, \
    condition \
  }

#define REGISTER_PIECE_MOVE_PATTERNS(NAME, ...) \
  static PieceMovePattern *NAME##_PIECE_MOVE_PATTERNS[] = { \
    __VA_ARGS__ \
  }

// KING
MOVE_PATTERN(KING, 1, 1, SQUARE_EMPTY | SQUARE_OCCUPIED_ENEMY,
  NORTH, NORTH_EAST, 
  EAST, SOUTH_EAST, 
  SOUTH, SOUTH_WEST, 
  WEST, NORTH_WEST,
);

REGISTER_PIECE_MOVE_PATTERNS(KING, &KING_PIECE_MOVE_PATTERN);

// QUEEN
MOVE_PATTERN(QUEEN, 1, -1, SQUARE_EMPTY | SQUARE_OCCUPIED_ENEMY,
  NORTH, NORTH_EAST, 
  EAST, SOUTH_EAST, 
  SOUTH, SOUTH_WEST, 
  WEST, NORTH_WEST,
);

REGISTER_PIECE_MOVE_PATTERNS(QUEEN, &QUEEN_PIECE_MOVE_PATTERN);

// BISHOP
MOVE_PATTERN(BISHOP, 1, -1, SQUARE_EMPTY | SQUARE_OCCUPIED_ENEMY, 
  NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST
);

REGISTER_PIECE_MOVE_PATTERNS(BISHOP, &BISHOP_PIECE_MOVE_PATTERN);

// KNIGHT
MOVE_PATTERN(KNIGHT,1, 1, SQUARE_EMPTY | SQUARE_OCCUPIED_ENEMY, 
  NORTH_NORTH_EAST, EAST_NORTH_EAST,
  EAST_SOUTH_EAST, SOUTH_SOUTH_EAST,
  SOUTH_SOUTH_WEST, WEST_SOUTH_WEST,
  WEST_NORTH_WEST, NORTH_NORTH_WEST,
);

REGISTER_PIECE_MOVE_PATTERNS(KNIGHT, &KNIGHT_PIECE_MOVE_PATTERN);

// ROOK
MOVE_PATTERN(ROOK, 1, -1, SQUARE_EMPTY | SQUARE_OCCUPIED_ENEMY, 
  NORTH, EAST, SOUTH, WEST
);
 
REGISTER_PIECE_MOVE_PATTERNS(ROOK, &ROOK_PIECE_MOVE_PATTERN);

// PAWN
MOVE_PATTERN(PAWN_FORWARD, 1, 1, SQUARE_EMPTY, 
  NORTH
);

MOVE_PATTERN(PAWN_FORWARD_FIRST, 2, 1, SQUARE_EMPTY | PIECE_NEVER_MOVED,
  NORTH
);

MOVE_PATTERN(PAWN_CAPTURE, 1, 1, SQUARE_OCCUPIED_ENEMY,
  NORTH_EAST, NORTH_WEST
);

MOVE_PATTERN(PAWN_EN_PASSANT, 1, 1, SQUARE_EN_PASSANT,
  NORTH_WEST, NORTH_EAST
);

REGISTER_PIECE_MOVE_PATTERNS(PAWN, 
  &PAWN_FORWARD_PIECE_MOVE_PATTERN,
  &PAWN_FORWARD_FIRST_PIECE_MOVE_PATTERN,
  &PAWN_CAPTURE_PIECE_MOVE_PATTERN,
  &PAWN_EN_PASSANT_PIECE_MOVE_PATTERN
);

void generate_legal_piece_moves(Array *moves, State *state);
