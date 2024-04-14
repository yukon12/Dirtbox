#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "quad.h"
#include "camera.h"
#include "world.h"

void loadInventory(SDL_Renderer *_renderer, TTF_Font *_font, SDL_Rect **_quad);
void renderInventory();
void pickUpObject(int _x, int _y);
void dropObject(int _x, int _y);
void chooseSlot(int _index);