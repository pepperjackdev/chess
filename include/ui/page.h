#pragma once

#include <raylib.h>

typedef enum {
  GAME,
} PageType;

typedef struct {
  PageType page_type;
  void *page_data;
} Page;

void draw_page(Page page);
void update_page(Page page);
