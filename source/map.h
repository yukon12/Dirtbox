#ifndef MAP
#define MAP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "header.h"
#include "camera.h"
#include "world.h"

void loadMap(SDL_Renderer *_renderer, TTF_Font *font);
void updateMap(float _x, float _y);
void renderMap();

#endif