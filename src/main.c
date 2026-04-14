#include <raylib.h>

typedef enum {
  CHESSBOARD = 0,
} Page;

typedef struct {
  Texture chess_pieces_sprite;
} Assets;

void draw_chessboard_page(Assets assets) {
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      // drawing the squares
      if ((rank + file) % 2 == 0) {
        DrawRectangle(
          file * GetScreenWidth() / 8,
          rank * GetScreenHeight() / 8,
          GetScreenWidth() / 8,
          GetScreenHeight() / 8,
          BLACK
        );
      }
      // drawing the pieces
      DrawTexturePro(assets.chess_pieces_sprite, 
        (Rectangle){0, 0, 320, 320}, 
        (Rectangle){0, 0, 100, 100},
        (Vector2){0, 0},
        0,
        RAYWHITE
      );
    }
  }
}

void draw_page(Page page, Assets assets) {
  switch (page) {
    case CHESSBOARD:
        draw_chessboard_page(assets);
        break;
  }
}

int main() {
  SetTargetFPS(60);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(900, 900, "Chess");

  Image sprite_image = LoadImage("assets/sprites/chess_pieces_sprite.png");
  Texture sprite_texture = LoadTextureFromImage(sprite_image);

  Assets assets = (Assets) {
    sprite_texture
  };

  Page current_page = CHESSBOARD;

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(RAYWHITE);
      draw_page(CHESSBOARD, assets);
    EndDrawing();
  }

  CloseWindow();
}

