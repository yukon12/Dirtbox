#include "../include/map.h"
void addOctave(float** noise, int m);

unsigned char** tile;
unsigned char** object;

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

    int v = 0;
    for(int r = 0; r < MAP_SIZE; r++)
    {
        for(int c = 0; c < MAP_SIZE; c++)
        {
            v = rand()%64;
            if(tile[c][r]&&v<3) object[c][r] = v+1;
        }
    }
}

void addOctave(float** noise, int m)
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
    int c0 = floor(getCameraX());
    int r0 = floor(getCameraY());
    unsigned char frame = (SDL_GetTicks()/500)%2;

    for(int j = 0; j < 16; j++)
    {
        for(int i = 0; i < 28; i++)
        {
            int c = (c0+i)%MAP_SIZE;
            int r = (r0+j)%MAP_SIZE;
            renderTexture(2*tile[c][r]+frame, (float)c, (float)r);
            if(object[c][r]!=0) renderTexture(OBJECT+object[c][r]-1, (float)c, (float)r);
        }
    }
}

unsigned char getTile(int c, int r)
{
    c = (c+MAP_SIZE)%MAP_SIZE;
    r = (r+MAP_SIZE)%MAP_SIZE;
    return tile[c][r];
}

unsigned char getObject(int c, int r)
{
    c = (c+MAP_SIZE)%MAP_SIZE;
    r = (r+MAP_SIZE)%MAP_SIZE;
    return object[c][r];
}
