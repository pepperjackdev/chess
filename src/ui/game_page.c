#include "ui/game_page.h"

#include "chess/move/piece_move_generator.h"
#include "chess/piece.h"
#include "chess/placement.h"
#include "chess/state.h"
#include "chess/move.h"
#include "chess/utils/tuple.h"

#include <raylib.h>

void update_game_page(GamePage *game_page) {
  int col = GetMouseX() / (GetScreenWidth() / 8);
  int row = GetMouseY() / (GetScreenHeight() / 8);
  
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (placement_get_piece(&game_page->state->placement, row * 8 + col) != 0) {
      game_page->move_source_index = row * 8 + col;
    }
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    if (game_page->move_source_index == NOT_DRAGGING) return;
    submit_move(
      (Move){
        game_page->state->active_side,
        PIECE_MOVE, 
        (PieceMove){game_page->move_source_index, row * 8 + col}
      },
      game_page->state
    );
    game_page->move_source_index = NOT_DRAGGING;
  }
}

Rectangle get_piece_sprite(Piece piece) {
  int row = (piece_get_side(piece) == PIECE_SIDE_WHITE) ? 0 : 1;
  int col = piece_get_type(piece) - 1;
  return (Rectangle){
    col * 320,
    row * 320,
    320,
    320,
  };
};

void render_game_page(GamePage *game_page) {
  float squareWidth = GetScreenWidth() / 8.0f;
  float squareHeight = GetScreenHeight() / 8.0f;

  PieceMove move_list[256];
  int move_list_count = generate_legal_moves(game_page->state, move_list);

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      bool red_flag = false;
      if (game_page->move_source_index != NOT_DRAGGING) {
        for (int i = 0; i < move_list_count; i++) {
          if (move_list[i].to == t2toi((Tuple2){col, row}) && 
            move_list[i].from == game_page->move_source_index) {
            red_flag = true;
          }
        }
      }
      // Squares
      DrawRectangle(
          col * squareWidth,
          row * squareHeight,
          squareWidth,
          squareHeight, 
          (red_flag) ? RED : ((row + col) % 2 == 0) ? 
            game_page->black_square_color : 
            game_page->white_square_color
      );

      DrawText(
        TextFormat("%d", t2toi((Tuple2){col, row})),
        col * squareWidth,
        row * squareHeight,
        20,
        BLACK
      );

      // Pieces
      Piece piece = placement_get_piece(&game_page->state->placement, row * 8 + col);
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

  // Drawing pieces over the board
  if (game_page->move_source_index != NOT_DRAGGING) {
    DrawTexturePro(
      *game_page->sprite, 
      get_piece_sprite(placement_get_piece(
        &game_page->state->placement, 
        game_page->move_source_index)
      ),
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

  // State Info
  if (IsKeyDown(KEY_LEFT_SHIFT)) {
    DrawRectangle(100, 100, 760, 760, GRAY);
    DrawText(TextFormat("Active color: %s", 
      game_page->state->active_side == PIECE_SIDE_WHITE ? "white" : "black"), 200, 200, 30, WHITE);
    DrawText(TextFormat("Castling: %b",
      game_page->state->castling), 200, 250, 30, WHITE);
    DrawText(TextFormat("En passant target: %d",
      game_page->state->en_passant_index), 200, 300, 30, WHITE);
    DrawText(TextFormat("Halfm. clock: %d",
      game_page->state->halfmove_clock), 200, 350, 30, WHITE);
    DrawText(TextFormat("Fullm. clock: %d",
      game_page->state->fullmove_clock), 200, 400, 30, WHITE);
  }
}