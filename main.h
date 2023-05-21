#ifndef _MAIN_H_
#define _MAIN_H_

#include "raylib.h"

#define WIDTH 800
#define HEIGHT 800
#define DEFAULT_SPEED 100.0f;
#define DEFAULT_SPEED_MODIFIER 4.0f;

typedef struct CircleStruct
{
	int x;
	int y;
	int radius;
	Color color;
} Circle;

typedef struct AxeStruct
{
	int posX;
	int posY;
	int width;
	int height;
	int speed;
	Color color;
} Axe;

typedef struct AxeArrayStruct
{
	int maxSize;
	int size;
	Axe **axes;
} AxeArray;

typedef struct GameStruct
{
	size_t score;
	size_t highScore;
} Game;

AxeArray *initAxeArray(int maxSize);

Axe *createNewAxe();
Circle *createNewCircle();

void AddAxe(AxeArray *axeArray, Axe *axe);
void AddAxe(AxeArray *axeArray);

bool CheckCollision(Circle *circle, Axe *axe);
bool CheckCollisionForAxes(Circle *circle, AxeArray *axeArray);

void UpdateAxes(Game *game, float *delta, AxeArray *axeArray);
void UpdateAxe(Game *game, float *delta, Axe *axe);
void updateAllAxesXPosition(AxeArray *axeArray, bool modifySpeed);
void updateAxeXPosition(Axe *axe);
void UpdateCircle(float *delta, Circle *circle);

void drawAxes(AxeArray *axeArray);
void drawAxe(Axe *axe);
/**
 * @brief Draw a circle
 */
void drawCircle(Circle *circle, Color color);

void freeAxeArray(AxeArray *axeArray);

void resetGame(Game *game, Circle *circle, AxeArray *axeArray);

Game *initGame();

void DrawStats(char *strbuffer, Game *game, AxeArray *axeArray);

#endif // _MAIN_H_
