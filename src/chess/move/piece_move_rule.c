#include "chess/move/piece_move_rule.h"

bool compare_conditions(Condition c1, Condition c2) {
    return c1 & c2 & 0b00001111 != 0;
}