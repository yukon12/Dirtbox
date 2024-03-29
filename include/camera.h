#ifndef CAMERA
#define CAMERA

#include <SDL2/SDL.h>
#include "header.h"

void loadCamera(SDL_Renderer* _renderer, SDL_Texture* _spritesheet);
void quitCamera();
float getCameraX();
float getCameraY();
void setCameraX(float _a);
void setCameraY(float _a);
void renderTextureOnTheMap(int _textureID, float _x, float _y);
void renderTextureOnTheWindow(int _textureID, int _x, int _y);

#endif
