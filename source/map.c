#include <map.h>
#define MAP_SIZE 1024
#define SCALE 4

static unsigned char** tile;
static unsigned char** object;
static SDL_Texture** tileTexture;

void loadMap(SDL_Renderer* renderer)
{
    tile = (unsigned char**)malloc(MAP_SIZE*sizeof(unsigned char*));
    object = (unsigned char**)malloc(MAP_SIZE*sizeof(unsigned char*));
    for(int i = 0; i < MAP_SIZE; i++)
    {
        tile[i] = (unsigned char*)calloc(MAP_SIZE, sizeof(unsigned char));
        object[i] = (unsigned char*)calloc(MAP_SIZE, sizeof(unsigned char));
    }

    tileTexture = (SDL_Texture**)malloc(2*sizeof(SDL_Texture*));
    tileTexture[0] = IMG_LoadTexture(renderer, "../assets/water_tile.png");
    tileTexture[1] = IMG_LoadTexture(renderer, "../assets/grass_tile.png");
}

void drawMap(SDL_Renderer* renderer)
{
    SDL_Rect* destination = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    destination->w = SCALE*16;
    destination->h = SCALE*16;
    for(int c = 0; c < MAP_SIZE; c++)
    {
        for(int r = 0; r < MAP_SIZE; r++)
        {
            destination->x = SCALE*16*c+(int)getCameraX();
            destination->y = SCALE*16*r+(int)getCameraY();
            SDL_RenderCopy(renderer, tileTexture[tile[c][r]], NULL, destination);
        }
    }
}

unsigned char getTile(int c, int r)
{
    return tile[c][r];
}

unsigned char getObject(int c, int r)
{
    return tile[c][r];
}
