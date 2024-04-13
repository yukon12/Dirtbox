#ifndef CAMERA
#define CAMERA

#include <SDL2/SDL.h>
#include "header.h"

void loadCamera(SDL_Renderer *_renderer, SDL_Surface *_spriteSheetSurface);
float getCameraX();
float getCameraY();
void setCameraX(float _x);
void setCameraY(float _y);
void renderTextureOnTheWorld(SDL_Texture *_texture, SDL_Rect *_source, float _x, float _y);
void renderTextureOnTheWindow(SDL_Texture *_texture, SDL_Rect *_source, int _x, int _y, float _scale);

#endif