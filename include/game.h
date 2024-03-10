#ifndef GAME
#define GAME
#include <stdbool.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <map.h>
#include <camera.h>

void run();
void load();
void loop();
void input();
void update();
void draw();
void quit();

#endif
