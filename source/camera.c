#include "../include/camera.h"

#include <stdio.h>

static SDL_FPoint* camera;
static SDL_Rect* destination;
static SDL_Renderer* renderer;
static SDL_Texture** texture;

void loadCamera(SDL_Renderer* gameRenderer, SDL_Texture** gameTexture)
{
    camera = (SDL_FPoint*)malloc(sizeof(SDL_FPoint));
    destination = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    destination->w = UNIT_INT;
    destination->h = UNIT_INT;
    camera->x = 0.0f;
    camera->y = 0.0f;
    renderer = gameRenderer;
    texture = gameTexture;
}

float getCameraX()
{
    return camera->x;
}

float getCameraY()
{
    return camera->y;
}

void setCameraX(float a)
{
    camera->x = a;
    while((camera->x)>((float)MAP_SIZE)) camera->x -= ((float)MAP_SIZE);
    while((camera->x)<0.0f) camera->x += ((float)MAP_SIZE);
}

void setCameraY(float a)
{
    camera->y = a;
    while((camera->y)>((float)MAP_SIZE)) camera->y -= ((float)MAP_SIZE);
    while((camera->y)<0.0f) camera->y += ((float)MAP_SIZE);
}

void renderTexture(int textureID, float x, float y)
{
    const int mapPixelSize = UNIT_INT*MAP_SIZE;
    float relativeX = x - camera->x;
    float relativeY = y - camera->y;
    int pixelX = round(relativeX*UNIT);
    int pixelY = round(relativeY*UNIT);
    int windowX = (pixelX+UNIT_INT+mapPixelSize)%mapPixelSize-UNIT_INT;
    int windowY = (pixelY+UNIT_INT+mapPixelSize)%mapPixelSize-UNIT_INT;

    if(windowX>=-UNIT_INT&&windowX<mapPixelSize&&windowY>=-UNIT_INT&&windowX<mapPixelSize)
    {
        destination->x = windowX;
        destination->y = windowY;
        SDL_RenderCopy(renderer, texture[textureID], NULL, destination);
    }
}
