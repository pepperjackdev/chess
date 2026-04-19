#include "page.h"
#include <raylib.h>

void update_board_page(BoardPage *board_page) {
  int col = GetMouseX() / (GetScreenWidth() / 8);
  int row = GetMouseY() / (GetScreenHeight() / 8);
  
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if ((*board_page->board)[row * 8 + col] != 0) {
      board_page->drag_start_index = row * 8 + col;
    }
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    Piece piece = (*board_page->board)[board_page->drag_start_index];
    (*board_page->board)[board_page->drag_start_index] = 0;
    (*board_page->board)[row * 8 + col] = piece;
    board_page->drag_start_index = -1;
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

void draw_board_page(BoardPage *board_page) {
  float squareWidth = GetScreenWidth() / 8.0f;
  float squareHeight = GetScreenHeight() / 8.0f;

  // Drawing pieces on the board
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      // Squares
      DrawRectangle(
          col * squareWidth,
          row * squareHeight,
          squareWidth,
          squareHeight, 
          ((row + col) % 2 == 0) ? 
            board_page->black_square_color : 
            board_page->white_square_color
      );

      // Pieces
      Piece piece = (*board_page->board)[row * 8 + col];
      if (piece == 0) continue;
      if (board_page->drag_start_index != (row * 8 + col)) {
        DrawTexturePro(
          *board_page->sprite, 
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

  // Drawing pieces over the boardd
  if (board_page->drag_start_index != -1) {
    DrawTexturePro(
      *board_page->sprite, 
      get_piece_sprite((*board_page->board)[board_page->drag_start_index]),
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

void update_page(Page page) {
  switch (page.page_type) {
    case BOARD:
      update_board_page(page.page_data);
      break;
  }
}

void draw_page(Page page) {
  switch (page.page_type) {
    case BOARD:
      draw_board_page((BoardPage*)page.page_data);
      break;
  }
}

