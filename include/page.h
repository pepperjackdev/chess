#pragma once

#include <raylib.h>
#include "chess.h"

typedef enum {
  BOARD,
} PageType;

typedef struct {
  PageType page_type;
  void *page_data;
} Page;

typedef struct {
  Texture2D *sprite;
  Color black_square_color;
  Color white_square_color;
  Board *board;
  int drag_start_index;
} BoardPage;

void draw_page(Page page);
void update_page(Page page);
