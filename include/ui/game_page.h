#pragma once

#include <raylib.h>

#include "chess/state.h"
#include "chess/utils/tuple.h"

# define NOT_DRAGGING t2(-1, -1)

typedef struct {
  Texture2D *sprite;
  Color black_square_color;
  Color white_square_color;
  State *state;
  Tuple2 move_source;
} GamePage;

void update_game_page(GamePage *game_page);
void render_game_page(GamePage *game_page);
