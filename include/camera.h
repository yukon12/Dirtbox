#ifndef CAMERA
#define CAMERA

#include <SDL2/SDL.h>
#include "header.h"

void loadCamera(SDL_Renderer* gameRenderer, SDL_Texture* gameSpritesheet);
float getCameraX();
float getCameraY();
void setCameraX(float a);
void setCameraY(float a);
void renderTexture(int textureID, float x, float y);
void renderTextureAbsolute(int textureID, int x, int y);

#endif
