#ifndef PLAYER
#define PLAYER

#include <SDL2/SDL.h>
#include "quad.h" // To be replaced by "header.h"
#include "header.h"
#include "camera.h"
#include "world.h"

// Load, player, update then others.
void loadPlayer();
void updatePlayer(float _deltaTime);
void renderPlayer();
void movePlayer(unsigned char _direction);
// Use x, y variables instead of vector or SDL_Point.
float getPlayerX();
float getPlayerY();

#endif