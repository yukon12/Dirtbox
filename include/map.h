#ifndef MAP
#define MAP
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL_image.h>
#include "header.h"
#include "texture.h"
#include "perlin.h"

void loadMap(SDL_Renderer* renderer);
static void addOctave(float** noise, int m);
void drawMap();
unsigned char getTile(int c, int r);
unsigned char getObject(int c, int r);

#endif
