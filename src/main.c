#include <raylib.h>

#include "ui/page.h"
#include "ui/game_page.h"

#include "io/fen.h"

int main() {
  SetTargetFPS(60);
  InitWindow(960, 960, "Chess");

  Image sprite_image = LoadImage("assets/sprites/chess_pieces_sprite.png");
  Texture2D sprite_texture = LoadTextureFromImage(sprite_image);
  UnloadImage(sprite_image);

  State state;
  parse_fen_into_state(
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 
    &state
  );

  GamePage game_page = {
    &sprite_texture,
    (Color){0xDA, 0xD7, 0xCD, 0xFF},
    (Color){0xA1, 0x87, 0x68, 0xFF},
    &state,
    -1 // NOT DRAGGING
  };

  Page page = {
    GAME,
    &game_page
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
