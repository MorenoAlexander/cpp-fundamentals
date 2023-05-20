#include "raylib.h"
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 800


int main() {

  InitWindow(WIDTH, HEIGHT, "Stephen's Window");

  while (!WindowShouldClose()) {
    BeginDrawing();


    ClearBackground(WHITE);

    DrawCircle(WIDTH/2, HEIGHT/2, 200, PURPLE);




    EndDrawing();
  }


  return 0;
}


