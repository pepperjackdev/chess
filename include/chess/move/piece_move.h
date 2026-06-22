#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "chess/state.h"
#include "utils/array.h"

typedef struct {
  size_t source;
  size_t target;
} PieceMove;

typedef struct {
  int delta_file;
  int delta_rank;
} Direction;

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

typedef enum : uint8_t { _ } PieceMoveCondition;

typedef struct {
  Array directions;
  int max_squares;
  int squares_per_step;
  int max_steps;

} PieceMovePattern;

bool compare_piece_move(PieceMove m1, PieceMove m2);

bool there_is_check(PieceSide side, State *state);
bool there_is_checkmate(PieceSide side, State *state);

bool piece_move_matches_pattern(PieceMove move, PieceMovePattern pattern);

void submit_piece_move(PieceMove move, State *state);