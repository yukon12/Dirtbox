#include <camera.h>

SDL_FPoint* camera;

void loadCamera()
{
    camera = (SDL_FPoint*)malloc(sizeof(SDL_FPoint));
    camera->x = 1280.0f/2.0f;
    camera->y = 720.0f/2.0f;
}

float getCameraX()
{
    return camera->x;
}

float getCameraY()
{
    return camera->y;
}

void shiftCamera(float x, float y)
{
    camera->x += x;
    camera->y += y;
}
