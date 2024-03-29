#include "../include/map.h"

static void addOctave(float** noise, int m);

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
            tile[c][r] = 0;
            if(noise[c][r]>=0.0f) tile[c][r] = 1;
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

void renderWater(int c, int r, int frame)
{
    if(tile[c][r]!=0) return;
    if(!frame)
    {
        renderTextureOnTheMap(TXT_WATER_1, c, r);
        return;
    }
    renderTextureOnTheMap(TXT_WATER_2, c, r);
}

void renderDirt(int c, int r, int frame)
{
    if(tile[c][r]==0&&r>0&&tile[c][r-1]==1) renderTextureOnTheMap(TXT_DIRT, c, r);
}

void renderGrass(int c, int r, int frame)
{
    if(tile[c][r]==1)
    {
        if(!frame)
        {
            renderTextureOnTheMap(TXT_GRASS_1, c, r);
            return;
        }
        renderTextureOnTheMap(TXT_GRASS_2, c, r);
        return;
    }

    if(tile[(c+MAP_SIZE-1)%MAP_SIZE][r])
    {
        renderTextureOnTheMap(TXT_GRASS_RIGHT, c, r);
    }

    if(tile[(c+1)%MAP_SIZE][r])
    {
        renderTextureOnTheMap(TXT_GRASS_LEFT, c, r);
    }

    if(tile[c][(r+MAP_SIZE-1)%MAP_SIZE])
    {
        renderTextureOnTheMap(TXT_GRASS_BOTTOM, c, r);
    }
    
    if(tile[c][(r+1)%MAP_SIZE])
    {
        renderTextureOnTheMap(TXT_GRASS_TOP, c, r);
    }

    if(tile[(c+MAP_SIZE-1)%MAP_SIZE][(r+MAP_SIZE-1)%MAP_SIZE])
    {
        renderTextureOnTheMap(TXT_GRASS_BOTTOM_RIGHT, c, r);
    }

    if(tile[(c+1)%MAP_SIZE][(r+MAP_SIZE-1)%MAP_SIZE])
    {
        renderTextureOnTheMap(TXT_GRASS_BOTTOM_LEFT, c, r);
    }
}

void renderTile(int c, int r, int frame)
{
    renderWater(c, r, frame);
    renderDirt(c, r, frame);
    renderGrass(c, r, frame);
}

void renderObject(int c, int r, int frame)
{
    if(object[c][r]==0) return;
    if(object[c][r]==1) 
    {
        renderTextureOnTheMap(TXT_LOG, c, r);
        return;
    }
    if(object[c][r]==2) 
    {
        renderTextureOnTheMap(TXT_STONE, c, r);
        return;
    }
    if(object[c][r]==3) 
    {
        renderTextureOnTheMap(TXT_WEED, c, r);
        return;
    }
}

void renderMap()
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
            renderTile(c, r, frame);
            if(object[c][r]!=0) renderObject(c, r, frame);
        }
    }
}

void setObject(int c, int r, unsigned char objectID)
{
    c = (c+MAP_SIZE)%MAP_SIZE;
    r = (r+MAP_SIZE)%MAP_SIZE;
    object[c][r] = objectID;
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
