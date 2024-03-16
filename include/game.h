#ifndef GAME
#define GAME
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "header.h"
#include "map.h"
#include "texture.h"
#include "perlin.h"

void run();
void load();
void loop();
void input();
void update();
void draw();
void quit();

#endif
