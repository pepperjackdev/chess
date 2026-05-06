#include "ui/game_page.h"

#include <raylib.h>

void update_game_page(GamePage *game_page) {
  int col = GetMouseX() / (GetScreenWidth() / 8);
  int row = GetMouseY() / (GetScreenHeight() / 8);
  
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (game_page->state->placement[row * 8 + col] != 0) {
      game_page->move_source_index = row * 8 + col;
    }
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    move(
      (Move){
        game_page->move_source_index,
        row * 8 + col
      }, 
      game_page->state
    );
    game_page->move_source_index = -1;
  }
}

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

void draw_game_page(GamePage *game_page) {
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
            game_page->black_square_color : 
            game_page->white_square_color
      );

      // Pieces
      Piece piece = game_page->state->placement[row * 8 + col];
      if (piece == 0) continue;
      DrawTexturePro(
        *game_page->sprite, 
        get_piece_sprite(piece), 
        (Rectangle){
          col * squareWidth,
          row * squareHeight,
          squareWidth,
          squareHeight
        },
        (Vector2){0, 0}, 
        0.0f, 
        game_page->move_source_index != (row * 8 + col) ? 
          RAYWHITE : (Color){0xA0, 0xA0, 0xA0, 0x80} 
      );
    }
  }

  // Drawing pieces over the boardd
  if (game_page->move_source_index != -1) {
    DrawTexturePro(
      *game_page->sprite, 
      get_piece_sprite(game_page->state->placement[game_page->move_source_index]),
      (Rectangle){
        GetMouseX() - squareWidth / 2,
        GetMouseY() - squareHeight / 2,
        squareWidth,
        squareHeight
      },
      (Vector2){0, 0}, 
      0.0f, 
      RAYWHITE
    );
  }
}