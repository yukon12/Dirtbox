#ifndef WORLD
#define WORLD

#include <SDL2/SDL.h>
#include "perlin.h"
#include "quad.h" // To be replaced by "header.h".
#include "camera.h"
#include "header.h"

void loadWorld(SDL_Renderer* _renderer, SDL_Surface *_spriteSheetSurface, SDL_Rect **_quad);
void updateWorldFragmentTextures(float _x, float _y);
void renderWorld();
unsigned char getWorldTile(int _x, int _y);
unsigned char getWorldObject(int _x, int _y);
void setWorldObject(int _x, int _y, unsigned char _object);
unsigned char isOnTheGround(float _x, float _y);

#endif