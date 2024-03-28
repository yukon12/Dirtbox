#include "../include/game.h"
#include <SDL2/SDL_scancode.h>
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
    assert(IMG_Init(IMG_INIT_PNG)!=0);
    assert(TTF_Init()==0);

    window = SDL_CreateWindow("Dirtbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    assert(window!=NULL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(window!=NULL);

    SDL_Texture* spritesheet = IMG_LoadTexture(renderer, ASSETS_DIR"/spritesheet.png");

    TTF_Font* font = TTF_OpenFont(ASSETS_DIR"/silkscreen.ttf", 24);

    loadCamera(renderer, spritesheet);
    loadPlayer();
    loadMap(renderer);
    loadInterface(renderer, font);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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
    resetOrientation();
    const unsigned char* keyboardState = SDL_GetKeyboardState(NULL);
    if(keyboardState[SDL_SCANCODE_ESCAPE]) running = false;
    if(keyboardState[SDL_SCANCODE_W]) playerGoUp(deltaTime);
    if(keyboardState[SDL_SCANCODE_S]) playerGoDown(deltaTime);
    if(keyboardState[SDL_SCANCODE_A]) playerGoLeft(deltaTime);
    if(keyboardState[SDL_SCANCODE_D]) playerGoRight(deltaTime);
    if(keyboardState[SDL_SCANCODE_E])
    {
        int c = floor(getPlayerX()+0.5f);
        int r = floor(getPlayerY()+0.5f);
        addObject(getObject(c, r));
        setObject(c, r, 0);
    }
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
    drawMap();
    renderPlayer();
    renderCoordinates(getPlayerX(), getPlayerY());
    renderMinimap(getPlayerX(), getPlayerY());
    renderBar();
    SDL_RenderPresent(renderer);
}

void quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
