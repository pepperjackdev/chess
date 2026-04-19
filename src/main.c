#include <raylib.h>
#include "chess.h"

typedef enum {
  BOARD,
} PageType;

typedef struct {
  PageType pageType;
  void *pageData;
} Page;

typedef struct {
  Texture2D *sprite;
  Color blackSquaresColor;
  Color whiteSquaresColor;
  Board *board;
} BoardPage;

Rectangle get_piece_sprite(Piece piece) {
  int row = (side_of(piece) == SIDE_WHITE) ? 0 : 1;
  int col = type_of(piece) - 1;
  return (Rectangle){
    col * 320,
    row * 320,
    320,
    320,
  };
};

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
          ((row + col) % 2 == 0) ? 
            boardPage->blackSquaresColor : 
            boardPage->whiteSquaresColor
      );

      // Pieces
      Piece piece = (*boardPage->board)[row * 8 + col];
      if (piece == 0) continue;

      DrawTexturePro(
        *boardPage->sprite, 
        get_piece_sprite(piece), 
        (Rectangle){
          col * squareWidth,
          row * squareHeight,
          squareWidth,
          squareHeight
        },
        (Vector2){0, 0}, 
        0.0f, 
        RAYWHITE
      );
    }
  }
}

void draw_page(Page page) {
  switch (page.pageType) {
    case BOARD:
      draw_board_page((BoardPage*)page.pageData);
      break;
  }
}

int main() {
  SetTargetFPS(60);
  InitWindow(960, 960, "Chess");

  Image spriteImage = LoadImage("assets/sprites/chess_pieces_sprite.png");
  Texture2D spriteTexture = LoadTextureFromImage(spriteImage);
  UnloadImage(spriteImage);

  Board board;
  load_fen_into_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", &board);

  BoardPage boardPage = {
    &spriteTexture,
    (Color){0xDA, 0xD7, 0xCD, 0xFF},
    (Color){0xA1, 0x87, 0x68, 0xFF},
    &board
  };

  Page page = {
    BOARD,
    &boardPage
  };

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(RAYWHITE);
      draw_page(page);
    EndDrawing();
  }

  CloseWindow();
}

