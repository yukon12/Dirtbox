#ifndef PLAYER
#define PLAYER

#include <SDL2/SDL.h>
#include "camera.h"
#include "map.h"

void loadPlayer();
float getPlayerX();
float getPlayerY();
void resetOrientation();
void playerGoLeft(float deltaTime);
void playerGoRight(float deltaTime);
void playerGoUp(float deltaTime);
void playerGoDown(float deltaTime);
void movePlayerX(float a);
void movePlayerY(float a);
void renderPlayer();

#endif
