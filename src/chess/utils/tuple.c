#include "chess/utils/tuple.h"

Tuple2 index_to_tuple2(int index) {
    return (Tuple2){index / 8, index % 8};
}

int tuple2_to_index(Tuple2 t) {
    return t.y * 8 + t.x;
}

Tuple2 tuple2_add(Tuple2 t1, Tuple2 t2) {
    return (Tuple2){t1.x + t2.x, t2.y + t2.y};
}

Tuple2 tuple2_scale(Tuple2 t, int scale) {
    return (Tuple2){t.x * scale, t.y * scale};
}

bool tuple2_in_range(
    Tuple2 min, 
    Tuple2 t, 
    Tuple2 max
) {
    return t.x >= min.x && t.x <= max.x 
        && t.y >= min.y && t.y <= max.y;
}