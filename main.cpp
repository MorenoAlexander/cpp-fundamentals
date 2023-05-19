#include "raylib.h"
#include <stdio.h>

int main() {
  // InitWindow(300, 600, "hello, world");
  //
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(300,300, "hELLO, WORLD!");
  printf("Hello,World!");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
  }


  CloseWindow();
  return 0;
}


