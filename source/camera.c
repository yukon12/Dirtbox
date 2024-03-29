#include "../include/camera.h"
#include <SDL2/SDL_render.h>

static SDL_Renderer* renderer;
static SDL_Texture* spriteSheet;
static SDL_FPoint* cameraPosition;
static SDL_Rect* source;
static SDL_Rect* destination;

void loadCamera(SDL_Renderer* _renderer, SDL_Texture* _spriteSheet)
{
    renderer = _renderer;

    spriteSheet = _spriteSheet;

    cameraPosition = (SDL_FPoint*)malloc(sizeof(SDL_FPoint));
    cameraPosition->x = 0.0f;
    cameraPosition->y = 0.0f;

    destination = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    destination->x = 0;
    destination->y = 0;
    destination->w = UNIT;
    destination->h = UNIT;

    source = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    source->x = 0;
    source->y = 0;
    source->w = 16;
    source->h = 16;
}

void quitCamera()
{
    SDL_DestroyTexture(spriteSheet);
}

float getCameraX()
{
    return cameraPosition->x;
}

float getCameraY()
{
    return cameraPosition->y;
}

void setCameraX(float _a)
{
    cameraPosition->x = _a;
    while((cameraPosition->x)>((float)MAP_SIZE)) cameraPosition->x -= ((float)MAP_SIZE);
    while((cameraPosition->x)<0.0f) cameraPosition->x += ((float)MAP_SIZE);
}

void setCameraY(float _a)
{
    cameraPosition->y = _a;
    while((cameraPosition->y)>((float)MAP_SIZE)) cameraPosition->y -= ((float)MAP_SIZE);
    while((cameraPosition->y)<0.0f) cameraPosition->y += ((float)MAP_SIZE);
}

void renderTextureOnTheMap(int _textureID, float _x, float _y)
{
    float relativeX = _x - cameraPosition->x;
    float relativeY = _y - cameraPosition->y;
    int windowX = round(relativeX*UNIT_FLOAT);
    int windowY = round(relativeY*UNIT_FLOAT);
    windowX = (windowX+UNIT+MAP_WINDOW_SIZE)%MAP_WINDOW_SIZE-UNIT;
    windowY = (windowY+UNIT+MAP_WINDOW_SIZE)%MAP_WINDOW_SIZE-UNIT;

    if(windowX>=-UNIT&&windowX<WINDOW_WIDTH&&windowY>=-UNIT&&windowY<WINDOW_HEIGHT)
    {
        source->x = ((int)floor(((float)_textureID)/4.0f))*16;
        source->y = (_textureID%4)*16;

        destination->x = windowX;
        destination->y = windowY;

        SDL_RenderCopy(renderer, spriteSheet, source, destination);
    }
}

void renderTextureOnTheWindow(int _textureID, int _x, int _y)
{
    source->x = ((int)floor(((float)_textureID)/4.0f))*16;
    source->y = (_textureID%4)*16;
    destination->x = _x;
    destination->y = _y;
    SDL_RenderCopy(renderer, spriteSheet, source, destination);
}
