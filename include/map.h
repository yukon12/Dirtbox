#ifndef MAP
#define MAP
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <camera.h>

void loadMap(SDL_Renderer* renderer);
void drawMap(SDL_Renderer* renderer);
unsigned char getTile();
unsigned char getObject();

#endif
