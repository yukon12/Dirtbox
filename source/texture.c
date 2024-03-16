#include "../include/texture.h"

static SDL_Renderer* renderer;
static SDL_Texture** texture;

void loadTexture(SDL_Renderer* gameRenderer)
{
    renderer = gameRenderer; 
    texture = (SDL_Texture**)malloc(2*sizeof(SDL_Texture*));
    texture[0] = IMG_LoadTexture(renderer, "../assets/water_tile.png");
    texture[1] = IMG_LoadTexture(renderer, "../assets/grass_tile.png");
}

void drawTexture(int x, int y, int id)
{
    SDL_Rect* destination = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    destination->x = x-(int)getCameraX();
    destination->y = y-(int)getCameraY();
    destination->w = UNIT;
    destination->h = UNIT;
    SDL_RenderCopy(renderer, texture[id], NULL, destination);
}
