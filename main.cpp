#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <math.h>
#include <random>
#include "main.h"

const float speed = DEFAULT_SPEED;

Axe *createNewAxe()
{

  int randomX = rand() % WIDTH;

  Axe *axe = (Axe *)malloc(sizeof(Axe));
  axe->height = 50;
  axe->width = 50;
  axe->posX = randomX;
  axe->posY = 0;
  axe->color = RED;
  axe->speed = -1;

  return axe;
}

Circle *createNewCircle()
{
  Circle *circle = (Circle *)malloc(sizeof(Circle));
  circle->x = WIDTH / 2;
  circle->y = HEIGHT / 2;
  circle->radius = 50;
  circle->color = PURPLE;

  return circle;
}

void drawCircle(Circle *circle, Color color)
{
  DrawCircle(circle->x, circle->y, circle->radius, color);
}

void drawAxe(Axe *axe)
{
  DrawRectangle(axe->posX, axe->posY, axe->width, axe->height, axe->color);
}

void drawAxes(AxeArray *axeArray)
{
  printf("size: %d\n", axeArray->size);
  for (int i = 0; i < axeArray->size; i++)
  {
    printf("drawing axe: %d\n", i);
    drawAxe(axeArray->axes[i]);
  }
}

void UpdateCircle(float *delta, Circle *circle)
{
  int movement = floor(speed * (*delta));
  if (IsKeyDown(KEY_D) && (circle->x + circle->radius) < WIDTH)
  {
    circle->x += movement;
  }

  if (IsKeyDown(KEY_A) && (circle->x - circle->radius) > 0)
  {
    circle->x -= movement;
  }

  if (IsKeyDown(KEY_W) && (circle->y - circle->radius) > 0)
  {
    circle->y -= movement;
  }

  if (IsKeyDown(KEY_S) && (circle->y + circle->radius) < HEIGHT)
  {
    circle->y += movement;
  }
}

void updateAllAxesXPosition(AxeArray *axeArray, bool modifySpeed)
{
  for (int i = 0; i < axeArray->size; i++)
  {
    if (modifySpeed)
    {
      axeArray->axes[i]->speed = 0;
    }
    updateAxeXPosition(axeArray->axes[i]);
  }
}

void updateAxeXPosition(Axe *axe)
{
  axe->posY = 0;
  axe->posX = rand() % WIDTH;
}

void UpdateAxe(Game *game, float *delta, Axe *axe)
{

  int movement = speed * (*delta) + axe->speed;
  axe->posY += movement;

  if (axe->posY + axe->height > HEIGHT)
  {
    axe->speed += 1;
    updateAxeXPosition(axe);
    game->score += 1;
  }
}

void UpdateAxes(Game *game, float *delta, AxeArray *axeArray)
{
  for (int i = 0; i < axeArray->size; i++)
  {
    UpdateAxe(game, delta, axeArray->axes[i]);
  }
}

bool CheckCollision(Circle *circle, Axe *axe)
{
  return circle->x + circle->radius > axe->posX && circle->x - circle->radius < axe->posX + axe->width &&
         circle->y + circle->radius > axe->posY && circle->y - circle->radius < axe->posY + axe->height;
}

bool CheckCollisionForAxes(Circle *circle, AxeArray *axeArray)
{
  for (int i = 0; i < axeArray->size; i++)
  {
    if (CheckCollision(circle, axeArray->axes[i]))
    {
      return true;
    }
  }
  return false;
}

AxeArray *initAxeArray(int maxSize)
{
  AxeArray *axeArray = (AxeArray *)malloc(sizeof(AxeArray));
  axeArray->maxSize = maxSize;
  axeArray->size = 0;
  axeArray->axes = (Axe **)malloc(sizeof(Axe *) * maxSize);

  return axeArray;
}

void AddAxe(AxeArray *axeArray, Axe *axe)
{
  axeArray->axes[axeArray->size++] = axe;
}

void AddAxe(AxeArray *axeArray)
{
  if (axeArray->size == axeArray->maxSize)
  {
    return;
  }

  Axe *axe = createNewAxe();
  axeArray->axes[axeArray->size++] = axe;
}

void freeAxeArray(AxeArray *axeArray)
{
  for (size_t i = 0; i < axeArray->size; i++)
  {
    free(axeArray->axes[i]);
  }
  free(axeArray->axes);
  free(axeArray);
}

void resetGame(Game *game, Circle *circle, AxeArray *axeArray)
{

  // reset score
  game->score = 0;

  // reset circle
  circle->x = WIDTH / 2;
  circle->y = HEIGHT / 2;

  // reset axes

  axeArray->size = 1;

  for (int i = 1; i < axeArray->size; i++)
  {
    free(axeArray->axes[i]);
  }

  updateAllAxesXPosition(axeArray, true);
}

Game *initGame()
{
  Game *game = (Game *)malloc(sizeof(Game));
  game->score = 0;
  game->highScore = 0;

  return game;
}

void DrawStats(char *strbuffer, Game *game, AxeArray *axeArray)
{
  snprintf(strbuffer, 50, "Score: %d", game->score);
  DrawText(strbuffer, 10, 10, 20, BLACK);

  snprintf(strbuffer, 50, "High score: %d", game->highScore);
  DrawText(strbuffer, 10, 40, 20, BLACK);

  snprintf(strbuffer, 50, "Axes: %d", axeArray->size);
  DrawText(strbuffer, 10, 70, 20, BLACK);
}

int main()
{
  char *stringbuffer = (char *)malloc(sizeof(char) * 50);
  srand(time(NULL));
  InitWindow(WIDTH, HEIGHT, "Axe Game");
  float prevTime = 0.0f;
  float currentTime = 0.0f;
  float speedModifier = DEFAULT_SPEED_MODIFIER;

  Game *game = initGame();

  Circle *circle = createNewCircle();

  AxeArray *axeArray = initAxeArray(10);

  AddAxe(axeArray);

  SetTargetFPS(60);

  printf("Press A to move left: %d\n", HEIGHT);

  size_t gameStart = time(NULL);

  bool collision_with_player = false;
  while (!WindowShouldClose())
  {
    prevTime = currentTime;
    currentTime = GetTime();
    float delta = abs(currentTime - prevTime) * speedModifier;

    collision_with_player = CheckCollisionForAxes(circle, axeArray);

    BeginDrawing();

    ClearBackground(WHITE);

    DrawStats(stringbuffer, game, axeArray);

    if (!collision_with_player)
    {
      drawCircle(circle, PURPLE);
      drawAxes(axeArray);

      UpdateAxes(game, &delta, axeArray);

      UpdateCircle(&delta, circle);

      size_t newTime = time(NULL);
      size_t timeElapsed = newTime - gameStart;

      // printf("time elapsed: %d, %s\n", timeElapsed, timeElapsed % 60 == 0 ? "true" : "false");

      if (timeElapsed == 25)
      {
        AddAxe(axeArray);
        gameStart = newTime;
      }

      if (game->score > game->highScore)
      {
        game->highScore = game->score;
      }
    }
    else
    {
      DrawText("Game Over", WIDTH / 2, HEIGHT / 2, 48, BLACK);
      DrawText("Press Space to restart", WIDTH / 2, HEIGHT / 2 + 50, 24, BLACK);

      if (IsKeyDown(KEY_SPACE))
      {
        collision_with_player = false;
        resetGame(game, circle, axeArray);
        gameStart = time(NULL);
      }
    }

    EndDrawing();
  }

  free(circle);
  freeAxeArray(axeArray);
  free(game);
  free(stringbuffer);

  return 0;
}
