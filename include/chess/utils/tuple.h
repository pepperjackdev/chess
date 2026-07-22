#pragma once

typedef struct { int x; int y; } Tuple2;

Tuple2 index_to_tuple2(int index);
int tuple2_to_index(Tuple2 t);
Tuple2 tuple2_add(Tuple2 t1, Tuple2 t2);
Tuple2 tuple2_scale(Tuple2 t1, int scale);
bool tuple2_in_range(Tuple2 min, Tuple2 t, Tuple2 max);