#include "../include/perlin.h"

float** generateNoise(int n, int m)
{
    float** noise = (float**)malloc(n*sizeof(float*));
    for(int c = 0; c < n; c++) noise[c] = (float*)malloc(n*sizeof(float));
    
    Vector** grid = generateGrid(m);
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

static Vector** generateGrid(int m)
{
    Vector** grid = (Vector**)malloc(m*sizeof(float*));
    for(int c = 0; c < m; c++) grid[c] = (Vector*)malloc(m*sizeof(Vector));

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

static float perlin(float x, float y, Vector** grid, int m)
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

// Copied from https://en.wikipedia.org/wiki/Perlin_noise.
static float interpolate(float a0, float a1, float w)
{
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}
