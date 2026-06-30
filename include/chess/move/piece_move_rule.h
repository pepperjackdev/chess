#pragma once

#include <glib.h>

#include "chess/move/piece_move.h"
#include "chess/state.h"


typedef struct {
    int delta_file;
    int delta_row;
} MoveVector;

typedef uint8_t Condition;

bool compare_conditions(Condition c1, Condition c2);
Condition compute_condition(PieceMove move, State *state);

typedef struct {
    int step_scale;
    int step_limit;
    Condition conditions;
} MovePattern;

typedef MovePattern MoveRule[];