#pragma once

#include <raylib.h>

#include "chess.h"

typedef struct {
  Texture2D *sprite;
  Color black_square_color;
  Color white_square_color;
  State *state;
  int move_source_index;
} GamePage;

void update_game_page(GamePage *game_page);
void draw_game_page(GamePage *game_page);