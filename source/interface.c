#include "../include/interface.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

static TTF_Font* font;
static SDL_Renderer* renderer;
static SDL_Surface* coordinateSurface;
static SDL_Texture* coordinateTexture;
static SDL_Color* color;
static char* text;
static SDL_Rect* destination;
static unsigned char* object;
static unsigned char* amount;
static SDL_Surface* objectAmountSurface;
static SDL_Texture* objectAmountTexture;

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
    object = (unsigned char*)calloc(5, sizeof(unsigned char));
    amount = (unsigned char*)calloc(5, sizeof(unsigned char));
}

void renderCoordinates(float x, float y)
{
    sprintf(text, "x: %d   y: %d", (int)round(x), (int)round(y));
    SDL_RenderCopy(renderer, coordinateTexture, NULL, destination);
    coordinateSurface = TTF_RenderText_Solid(font, text, *color);
    destination->w = coordinateSurface->w;
    destination->h = coordinateSurface->h;
    coordinateTexture = SDL_CreateTextureFromSurface(renderer, coordinateSurface);
    SDL_FreeSurface(coordinateSurface);
    SDL_RenderCopy(renderer, coordinateTexture, NULL, destination);
}

void renderMinimap(float x, float y)
{
    int c0 = (int)floor(x)-64;
    int r0 = (int)floor(y)-64;
    for(int r = 0; r < 128; r++)
    {
        for(int c = 0; c < 128; c++)
        {
            if(getTile(c0+c, r0+r)||c==0||c==127||r==0||r==127)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
                SDL_RenderDrawPoint(renderer, 12+c, 32+r);
            }
            if((c-64)*(c-64)+(r-64)*(r-64)<16)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawPoint(renderer, 12+c, 32+r);
            }
        }
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void addObject(unsigned char objectID)
{
    int firstWithObject = INT_MAX;
    int firstEmpty = INT_MAX;
    for(int i = 4; i >= 0; i--) 
    {
        if(object[i]==objectID&&amount[i]<255) firstWithObject = i;
        if(object[i]==0) firstEmpty = i;
    }

    if(firstWithObject<5)
    {
        amount[firstWithObject]++;
        return;
    }

    if(firstEmpty<5)
    {
        object[firstEmpty] = objectID;
        amount[firstEmpty] = 1;
        return;
    }
}

void renderBar()
{
    SDL_Rect background;
    background.x = 24;
    background.y = 192;
    background.w = 2*UNIT_INT;
    background.h = 2*UNIT_INT;
    SDL_Rect number;
    number.x = 24+UNIT_INT;
    number.y = 192+UNIT_INT;
    number.w = UNIT_INT;
    number.h = UNIT_INT;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);

    for(int i = 0; i < 5; i++)
    {
        SDL_RenderFillRect(renderer, &background);
        if(object[i]==1) renderTextureAbsolute(TXT_LOG, background.x, background.y);
        if(object[i]==2) renderTextureAbsolute(TXT_STONE, background.x, background.y);
        if(object[i]==3) renderTextureAbsolute(TXT_WEED, background.x, background.y);

        if(object[i]!=0)
        {
            sprintf(text, "%d", amount[i]);
            objectAmountSurface = TTF_RenderText_Solid(font, text, *color);
            objectAmountTexture = SDL_CreateTextureFromSurface(renderer, objectAmountSurface);
            number.y = background.y;
            SDL_RenderCopy(renderer, objectAmountTexture, NULL, &number);
        }

        background.y += 100;
    }
}
