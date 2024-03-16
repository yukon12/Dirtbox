#include "../include/map.h"
#include <stdio.h>

static unsigned char** tile;
static unsigned char** object;

void loadMap(SDL_Renderer* renderer)
{
    tile = (unsigned char**)malloc(MAP_SIZE*sizeof(unsigned char*));
    object = (unsigned char**)malloc(MAP_SIZE*sizeof(unsigned char*));
    for(int i = 0; i < MAP_SIZE; i++)
    {
        tile[i] = (unsigned char*)calloc(MAP_SIZE, sizeof(unsigned char));
        object[i] = (unsigned char*)calloc(MAP_SIZE, sizeof(unsigned char));
    }

    float** noise = (float**)malloc(MAP_SIZE*sizeof(float*));
    for(int c = 0; c < MAP_SIZE; c++) noise[c] = (float*)malloc(MAP_SIZE*sizeof(float));
    addOctave(noise, 64);     
    addOctave(noise, 32);     
    addOctave(noise, 16);     

    for(int r = 0; r < MAP_SIZE; r++)
    {
        for(int c = 0; c < MAP_SIZE; c++)
        {
            tile[c][r] = WATER;
            if(noise[c][r]>=0.0f) tile[c][r] = GRASS;
        }
    }
}

static void addOctave(float** noise, int m)
{
    float** octave = generateNoise(MAP_SIZE, m);
    for(int r = 0; r < MAP_SIZE; r++)
    {
        for(int c = 0; c < MAP_SIZE; c++)
        {
            noise[c][r] += octave[c][r];
        }
    }
}

void drawMap()
{
    int c0 = (getCameraX()/UNIT);
    int c1 = c0+(WINDOW_WIDTH/UNIT)+1;
    int r0 = (getCameraY()/UNIT);
    int r1 = r0+(WINDOW_HEIGHT/UNIT)+1;

    if(c0<0) c0 = 0;
    if(c1>=MAP_SIZE) c1 = MAP_SIZE-1;
    if(r0<0) r0 = 0;
    if(r1>MAP_SIZE) r1 = MAP_SIZE-1;

    for(int r = r0; r <= r1; r++)
    {
        for(int c = c0; c <= c1; c++)
        {
            drawTexture(c*UNIT, r*UNIT, tile[c][r]);
        }
    }
}

unsigned char getTile(int c, int r)
{
    return tile[c][r];
}

unsigned char getObject(int c, int r)
{
    return object[c][r];
}
