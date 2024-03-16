#ifndef PERLIN
#define PERLIN
//#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

typedef struct {
    float x, y;
} Vector;

float** generateNoise(int n, int m);
static Vector** generateGrid(int m);
static float perlin(float x, float y, Vector** grid, int m);
static float interpolate(float a0, float a1, float w);

#endif
