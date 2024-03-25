#include "../include/game.h"
#include <SDL2/SDL_image.h>

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

    SDL_Texture** texture = (SDL_Texture**)malloc(13*sizeof(SDL_Texture*));
    texture[0] = IMG_LoadTexture(renderer, FILE_WATER_TILE_1);
    texture[1] = IMG_LoadTexture(renderer, FILE_WATER_TILE_2);
    texture[2] = IMG_LoadTexture(renderer, FILE_GRASS_TILE_1);
    texture[3] = IMG_LoadTexture(renderer, FILE_GRASS_TILE_2);
    texture[4] = IMG_LoadTexture(renderer, FILE_PLAYER_IDLE);
    //texture[5]
    texture[6] = IMG_LoadTexture(renderer, FILE_PLAYER_LEFT_1);
    texture[7] = IMG_LoadTexture(renderer, FILE_PLAYER_LEFT_2);
    texture[8] = IMG_LoadTexture(renderer, FILE_PLAYER_RIGHT_1);
    texture[9] = IMG_LoadTexture(renderer, FILE_PLAYER_RIGHT_2);
    texture[10] = IMG_LoadTexture(renderer, FILE_LOG);
    texture[11] = IMG_LoadTexture(renderer, FILE_STONE);
    texture[12] = IMG_LoadTexture(renderer, FILE_WEED);

    TTF_Font* font = TTF_OpenFont("../assets/silkscreen.ttf", 24);

    loadCamera(renderer, texture);
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
    if(keyboardState[SDL_SCANCODE_A]) playerGoLeft(deltaTime);
    if(keyboardState[SDL_SCANCODE_D]) playerGoRight(deltaTime);
    if(keyboardState[SDL_SCANCODE_W]) playerGoUp(deltaTime);
    if(keyboardState[SDL_SCANCODE_S]) playerGoDown(deltaTime);
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
    renderCoordinates(getPlayerX(), getPlayerY());
    renderMinimap(getPlayerX(), getPlayerY());
    SDL_RenderPresent(renderer);
}

void quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
