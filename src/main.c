#include <raylib.h>

typedef enum {
  BOARD,
} PageType;

typedef union {
  PageType pageType;
  void *pageData;
} Page;

typedef struct {
  Texture2D sprite;
  Color blackSquaresColor;
  Color whiteSquaresColor;
} BoardPage;

void draw_board_page(BoardPage *boardPage) {
  float squareWidth = GetScreenWidth() / 8.0f;
  float squareHeight = GetScreenHeight() / 8.0f;

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      // Squares
      DrawRectangle(
          col * squareWidth,
          row * squareHeight,
          squareWidth,
          squareHeight,
          ((row + col) % 2 == 0) ? boardPage->blackSquaresColor : boardPage->whiteSquaresColor
      );
    }
  }
}

void draw_page(Page *page) {
  switch (page->pageType) {
    case BOARD:
      draw_board_page((BoardPage*)page->pageData);
      break;
  }
}

int main() {
  SetTargetFPS(60);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(960, 960, "Chess");

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
}

