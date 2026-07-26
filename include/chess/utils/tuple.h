#pragma once

typedef struct { int x; int y; } Tuple2;

Tuple2 t2(int x, int y);
bool t2cmp(Tuple2 t1, Tuple2 t2);
Tuple2 itot2(int index);
int t2toi(Tuple2 t);
Tuple2 t2add(Tuple2 t1, Tuple2 t2);
Tuple2 t2sub(Tuple2 t1, Tuple2 t2);
Tuple2 t2scale(Tuple2 t1, int scale);
bool t2range(Tuple2 min, Tuple2 t, Tuple2 max);