#include <raylib.h>
#include <stdint.h>

#define TYPE_PAWN   0b00000000
#define TYPE_BISHOP 0b00000001
#define TYPE_KNIGHT 0b00000010
#define TYPE_ROOK   0b00000011
#define TYPE_QUEEN  0b00000100
#define TYPE_KING   0b00000101

#define SIDE_WHITE  0b00000000
#define SIDE_BLACK  0b00001000

typedef enum {
  CHESSBOARD = 0,
} Page;

typedef struct {
  Texture chess_pieces_sprite;
} Assets;

typedef uint8_t Board[64];

uint8_t make_piece(uint8_t type, uint8_t side) {
  return type | side;
}

void load_fen_into_board(char *fen, Board *board) {
}

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
        (Rectangle){
          0, 
          0, 
          (float)GetScreenWidth() / 8.0f, 
          (float)GetScreenHeight() / 8.0f
        },
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

  Board board = {}; 

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

