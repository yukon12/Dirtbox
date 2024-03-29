#include "../include/perlin.h"

static SDL_FPoint** generateGrid(int m);
static float perlin(float x, float y, SDL_FPoint** grid, int m);
static float interpolate(float a0, float a1, float w);

float** generateNoise(int n, int m)
{
    float** noise = (float**)malloc(n*sizeof(float*));
    for(int c = 0; c < n; c++) noise[c] = (float*)malloc(n*sizeof(float));
    
    SDL_FPoint** grid = generateGrid(m);
    float fieldSize = ((float)n)/((float)m);

    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < n; c++)
        {
            float x = ((float)c)/((float)fieldSize);
            float y = ((float)r)/((float)fieldSize);
            noise[c][r] = perlin(x, y, grid, m);
        }
    }

    return noise;
}

static SDL_FPoint** generateGrid(int m)
{
    SDL_FPoint** grid = (SDL_FPoint**)malloc(m*sizeof(float*));
    for(int c = 0; c < m; c++) grid[c] = (SDL_FPoint*)malloc(m*sizeof(SDL_FPoint));

    for(int r = 0; r < m; r++)
    {
        for(int c = 0; c < m; c++)
        {
            float angle = (float)(rand()%360);
            angle *= 0.0175f;
            grid[c][r].x = cos(angle);
            grid[c][r].y = sin(angle);
        }
    }

    return grid;
}

static float perlin(float x, float y, SDL_FPoint** grid, int m)
{
    int x0 = (int)x;
    int x1 = (x0+1)%m;
    int y0 = (int)y;
    int y1 = (y0+1)%m;

    float px = x-(float)x0;
    float py = y-(float)y0;

    float tl, tr, bl, br, t, b, e;
    tl = (px)*(grid[x0][y0].x)+(py)*(grid[x0][y0].y);
    tr = (px-1.0f)*(grid[x1][y0].x)+(py)*(grid[x1][y0].y);
    bl = (px)*(grid[x0][y1].x)+(py-1.0f)*(grid[x0][y1].y);
    br = (px-1.0f)*(grid[x1][y1].x)+(py-1.0f)*(grid[x1][y1].y);
    t = interpolate(tl, tr, px);
    b = interpolate(bl, br, px);
    e = interpolate(t, b, py);
    return e;
}

static float interpolate(float a0, float a1, float w)
{
    return (a1-a0)*((w*(w*6.0f-15.0f)+10.0f)*w*w*w)+a0;
}
