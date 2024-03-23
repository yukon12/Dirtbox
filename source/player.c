#include "../include/player.h"

SDL_FPoint* player;
SDL_FPoint* offset;

void loadPlayer()
{
    player = (SDL_FPoint*)malloc(sizeof(SDL_FPoint));
    player->x = 0.0f;
    player->y = 0.0f;
    offset = (SDL_FPoint*)malloc(sizeof(SDL_FPoint));
    offset->x = ((float)WINDOW_WIDTH)/(2.0f*UNIT)-0.5f;
    offset->y = ((float)WINDOW_HEIGHT)/(2.0f*UNIT)-0.5f;
    setCameraX(player->x-offset->x);
    setCameraY(player->y-offset->y);
}

float getPlayerX()
{
    return player->x;
}

float getPlayerY()
{
    return player->y;
}

void movePlayerX(float a)
{
    player->x += a;
    setCameraX(player->x-offset->x);
    while((player->x)>((float)MAP_SIZE)) player->x -= ((float)MAP_SIZE);
    while((player->x)<0.0f) player->x += ((float)MAP_SIZE);
}

void movePlayerY(float a)
{
    player->y += a;
    setCameraY(player->y-offset->y);
    while((player->y)>((float)MAP_SIZE)) player->y -= ((float)MAP_SIZE);
    while((player->y)<0.0f) player->y += ((float)MAP_SIZE);
}

void renderPlayer()
{
    renderTexture(2, player->x, player->y);
}
