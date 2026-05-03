#include <raylib.h>

#include "chess.h"
#include "page.h"

int main() {
  SetTargetFPS(60);
  InitWindow(960, 960, "Chess");

  Image sprite_image = LoadImage("assets/sprites/chess_pieces_sprite.png");
  Texture2D sprite_texture = LoadTextureFromImage(sprite_image);
  UnloadImage(sprite_image);

  Board board;

  BoardPage board_page = {
    &sprite_texture,
    (Color){0xDA, 0xD7, 0xCD, 0xFF},
    (Color){0xA1, 0x87, 0x68, 0xFF},
    &board, 
    -1 // Not Dragging
  };

  Page page = {
    BOARD,
    &board_page
  };

  while (!WindowShouldClose()) {
    update_page(page);
    BeginDrawing();
      ClearBackground(RAYWHITE);
      draw_page(page);
    EndDrawing();
  }

  CloseWindow();
}

