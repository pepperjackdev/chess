#include <raylib.h>

int main() {
  SetTargetFPS(60);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(900, 900, "Chess");

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
}
