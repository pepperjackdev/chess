#include <raylib.h>
#include <stdint.h>

// Pages

typedef enum {
  CHESSBOARD = 0,
} Page;

// Piece

typedef enum {
  TYPE_PAWN   = 0b00000001,
  TYPE_ROOK   = 0b00000010,
  TYPE_KNIGHT = 0b00000011,
  TYPE_BISHOP = 0b00000100,
  TYPE_QUEEN  = 0b00000101,
  TYPE_KING   = 0b00000111
} Type;

typedef enum {
  SIDE_WHITE = 0b00000000,
  SIDE_BLACK = 0b00001000
} Side;

typedef uint8_t Piece;

Piece piece_of(Type type, Side side) {
  return type | side;
}

Type type_of(Piece piece) {
  return piece & 0b00000111;
}

Side side_of(Piece piece) {
  return piece & 0b00001000;
}

// Assets

typedef struct {
  Texture chess_pieces_sprite;
} Assets;

// Board

typedef uint8_t Board[64];

void draw_chessboard_page(Assets *assets, Board *board) {
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
      if (*board[rank * 8 + file] == 0) {
        continue;
      }


      int row, col;
      
      if (side_of(*board[rank * 8 + file]) == SIDE_WHITE) {
        row = 0;
      } else {
        row = 1;
      }

      switch (type_of(*board[rank * 8 + file])) {
        case TYPE_KING:
          col = 0;
          break;
        default:
          col = 5;
      }

      DrawTexturePro(assets->chess_pieces_sprite, 
        (Rectangle){row * 320, col * 320, 320, 320}, 
        (Rectangle){
          (float)file * GetScreenWidth() / 8.0f, 
          (float)rank * GetScreenHeight() / 8.0f, 
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

void draw_page(Page page, Assets *assets, Board *board) {
  switch (page) {
    case CHESSBOARD:
        draw_chessboard_page(assets, board);
        break;
    default:
        break;
  }
}

int main() {
  SetTargetFPS(60);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(900, 900, "Chess");

  Image sprite_image = LoadImage("assets/sprites/chess_pieces_sprite.png");
  Texture sprite_texture = LoadTextureFromImage(sprite_image);

  Board board = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
  }; 

  Assets assets = (Assets) {
    sprite_texture
  };

  Page current_page = CHESSBOARD;

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(RAYWHITE);
      draw_page(CHESSBOARD, &assets, &board);
    EndDrawing();
  }

  CloseWindow();
}

