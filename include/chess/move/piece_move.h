#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "chess/state.h"

typedef struct {
  size_t source;
  size_t target;
} PieceMove;

bool compare_piece_move(PieceMove m1, PieceMove m2);

typedef struct {
  int delta_file;
  int delta_rank;
} MoveVector;

enum MoveVectorsIndex: size_t {
  NORTH,
  NORTH_NORTH_EAST,
  NORTH_EAST,
  EAST_NORTH_EAST,
  EAST,
  EAST_SOUTH_EAST,
  SOUTH_EAST,
  SOUTH_SOUTH_EAST,
  SOUTH,
  SOUTH_SOUTH_WEST,
  SOUTH_WEST,
  WEST_SOUTH_WEST,
  WEST,
  WEST_NORTH_WEST,
  NORTH_WEST,
  NORTH_NORTH_WEST
};

static MoveVector MOVE_VECTORS[] = {
  [NORTH]            = {0, -1},
  [NORTH_NORTH_EAST] = {1, -2},
  [NORTH_EAST]       = {1, -1},
  [EAST_NORTH_EAST]  = {2, -1},
  [EAST]             = {1, 0},
  [EAST_SOUTH_EAST]  = {2, 1},
  [SOUTH_EAST]       = {1, 1},
  [SOUTH_SOUTH_EAST] = {1, 2},
  [SOUTH]            = {0, 1},
  [SOUTH_SOUTH_WEST] = {-1, 2},
  [SOUTH_WEST]       = {-1, 1},
  [WEST_SOUTH_WEST]  = {-2, 1},
  [WEST]             = {-1, 0},
  [WEST_NORTH_WEST]  = {-2, -1},
  [NORTH_WEST]       = {-1, -1},
  [NORTH_NORTH_WEST] = {-1, -2},
};

typedef struct {
  uint8_t move_vector_bitmap;
  int squares_per_step;
  int max_steps;
  void *conditions; // FIXME: how should conditions be handled?
} MovePattern;

bool is_side_under_check(PieceSide side, State *state);
bool is_side_under_checkmate(PieceSide side, State *state);

bool is_piece_move_pseudo_legal(PieceMove move, State *state);
bool is_piece_move_legal(PieceMove move, State *state);

void submit_piece_move(PieceMove move, State *state);
