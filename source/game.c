#include <game.h>
#include <stdbool.h>
#include <assert.h>
#include <SDL2/SDL.h>

bool running;
SDL_Window* window;
SDL_Renderer* renderer;

void run()
{
    load();
    loop();
    quit();
}

void load()
{
    assert(SDL_Init(SDL_INIT_EVERYTHING)==0);
    window = SDL_CreateWindow("Dirtbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    assert(window!=NULL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(window!=NULL);
}

void loop()
{
    running = true;
    while(running)
    {
        input();
        update();
        render();
    }
}

void input()
{
    const unsigned char* keyboardState = SDL_GetKeyboardState(NULL);
    if(keyboardState[SDL_SCANCODE_ESCAPE]) running = false;
}

void update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_QUIT) running = false;
    }
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
