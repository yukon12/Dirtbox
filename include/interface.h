#ifndef INTERFACE
#define INTERFACE

#include <limits.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "map.h"
#include "header.h"

void loadInterface(SDL_Renderer* gameRenderer, TTF_Font* gameFont);
void renderCoordinates(float x, float y);
void renderMinimap(float x, float y);
void addObject(unsigned char objectID);
void renderBar();

#endif
