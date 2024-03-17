#include "../include/game.h"

#include <stdio.h>

static void load();
static void loop();
static void input();
static void update();
static void render();
static void quit();

static bool running;
static float deltaTime;
static SDL_Window* window;
static SDL_Renderer* renderer;

void run()
{
    load();
    loop();
    quit();
}

void load()
{
    srand(time(NULL));

    assert(SDL_Init(SDL_INIT_EVERYTHING)==0);

    window = SDL_CreateWindow("Dirtbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    assert(window!=NULL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(window!=NULL);

    SDL_Texture** texture = (SDL_Texture**)malloc(2*sizeof(SDL_Texture*));
    texture[0] = IMG_LoadTexture(renderer, "../assets/water_tile.png");
    texture[1] = IMG_LoadTexture(renderer, "../assets/grass_tile.png");
    texture[2] = IMG_LoadTexture(renderer, "../assets/player.png");

    loadCamera(renderer, texture);
    loadPlayer();
    loadMap(renderer);
}

void loop()
{
    running = true;
    unsigned int time = SDL_GetTicks();
    while(running)
    {
        input();
        update();
        render();
        if(SDL_GetTicks()-time<16) SDL_Delay(16-SDL_GetTicks()+time);
        deltaTime = ((float)(SDL_GetTicks()-time))/1000.0f;
        time = SDL_GetTicks();
    }
}

void input()
{
    const unsigned char* keyboardState = SDL_GetKeyboardState(NULL);
    if(keyboardState[SDL_SCANCODE_ESCAPE]) running = false;
    if(keyboardState[SDL_SCANCODE_A]) movePlayerX(-1.0f*deltaTime*PLAYER_SPEED);
    if(keyboardState[SDL_SCANCODE_D]) movePlayerX(1.0f*deltaTime*PLAYER_SPEED);
    if(keyboardState[SDL_SCANCODE_W]) movePlayerY(-1.0f*deltaTime*PLAYER_SPEED);
    if(keyboardState[SDL_SCANCODE_S]) movePlayerY(1.0f*deltaTime*PLAYER_SPEED);
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
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    drawMap();
    renderPlayer();
    SDL_RenderPresent(renderer);
}

void quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
