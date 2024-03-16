#ifndef TEXTURE
#define TEXTURE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "header.h"
#include "camera.h"

void loadTexture(SDL_Renderer* renderer);
void drawTexture(int x, int y, int id);

#endif
