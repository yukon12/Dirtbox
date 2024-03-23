#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void loadInterface(SDL_Renderer* gameRenderer, TTF_Font* gameFont);
void renderCoordinates(float x, float y);

#endif
