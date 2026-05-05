#include <raylib.h>

#include "chess.h"
#include "page.h"

int main() {
  SetTargetFPS(60);
  InitWindow(960, 960, "Chess");

  Font font = LoadFontEx(
    "assets/fonts/ioskeley_mono_nerd_font_regular.ttf", 
    30, 
    0, 
    0
  );

  Image sprite_image = LoadImage("assets/sprites/chess_pieces_sprite.png");
  Texture2D sprite_texture = LoadTextureFromImage(sprite_image);
  UnloadImage(sprite_image);

  State state;
  load_fen_into_state("1r6/5pp1/R1R4p/1r1pP3/2pkQPP1/7P/1P6/2K5 w - - 0 41", &state);

  BoardPage board_page = {
    &sprite_texture,
    (Color){0xDA, 0xD7, 0xCD, 0xFF},
    (Color){0xA1, 0x87, 0x68, 0xFF},
    &state.piece_placement_data, 
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
      // ----- ----- ----- -----
      // |    DEBUG INFO       |
      // ----- ----- ----- -----
      if (IsKeyDown(KEY_LEFT_SHIFT)) {
        // Background
        DrawRectangle(60, 60, 840, 840, 
          (Color){0x51, 0x51, 0x51, 0xF5});

        // State
        DrawTextEx(
          font,
          TextFormat(
            "State:\n"
            "\t Placement: [Shown]\n"
            "\t Active Color: %s\n"
            "\t Castling Availability: %#b\n"
            "\t En Passant Target Square: %d\n"
            "\t Halfmove clock: %d\n"
            "\t Fullmove clock: %d\n",
            (state.active_color) ? "White" : "Black",
            state.castling_availability,
            state.en_passant_target_square,
            state.halfmove_clock,
            state.fullmove_clock
          ),
          (Vector2){120, 120}, 
          40,
          0,
          WHITE
        );
      }
      // ----- ----- ----- -----
    EndDrawing();
  }

  CloseWindow();
}

