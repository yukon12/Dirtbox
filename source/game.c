#include <game.h>
#include <stdio.h>

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
    assert(SDL_Init(SDL_INIT_EVERYTHING)==0);
    window = SDL_CreateWindow("Dirtbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    assert(window!=NULL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(window!=NULL);
    loadCamera();
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
        draw();
        if(SDL_GetTicks()-time<16) SDL_Delay(16-SDL_GetTicks()+time);
        deltaTime = ((float)(SDL_GetTicks()-time))/1000.0f;
        time = SDL_GetTicks();
        printf("%f\n", deltaTime);
    }
}

void input()
{
    const unsigned char* keyboardState = SDL_GetKeyboardState(NULL);
    if(keyboardState[SDL_SCANCODE_ESCAPE]) running = false;
    if(keyboardState[SDL_SCANCODE_A]) shiftCamera(deltaTime*48.0f, 0.0f);
    if(keyboardState[SDL_SCANCODE_D]) shiftCamera(-deltaTime*48.0f, 0.0f);
    if(keyboardState[SDL_SCANCODE_W]) shiftCamera(0.0f, deltaTime*48.0f);
    if(keyboardState[SDL_SCANCODE_S]) shiftCamera(0.0f, -deltaTime*48.0f);
}

void update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_QUIT) running = false;
    }
}

void draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    drawMap(renderer);
    SDL_RenderPresent(renderer);
}

void quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
