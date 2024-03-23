#include "../include/interface.h"

static TTF_Font* font;
static SDL_Renderer* renderer;
static SDL_Surface* surface;
static SDL_Texture* texture;
static SDL_Color* color;
static char* text;
static SDL_Rect* destination;

void loadInterface(SDL_Renderer* gameRenderer, TTF_Font* gameFont)
{ 
    renderer = gameRenderer;
    font = gameFont;
    color = (SDL_Color*)malloc(sizeof(SDL_Color));
    color->r = 220;
    color->g = 20;
    color->b = 60;
    color->a = 255;
    destination = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    destination->x = 0;
    destination->y = 0;
    text = (char*)malloc(12*sizeof(char));
}

void renderCoordinates(float x, float y)
{
    sprintf(text, "x: %d   y: %d", (int)round(x), (int)round(y));
    SDL_RenderCopy(renderer, texture, NULL, destination);
    surface = TTF_RenderText_Solid(font, text, *color);
    destination->w = surface->w;
    destination->h = surface->h;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, destination);
}
