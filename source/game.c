#include "../include/game.h"

static void load();
static void loop();
static void input();
static void update();
static void render();
static void quit();

static unsigned char running;
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

    SDL_Surface* surface = IMG_Load(ASSETS_DIR"/spritesheet.png");
    SDL_Texture* spriteSheet = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect* iconSource = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    iconSource->x = 3*16;
    iconSource->y = 1*16;
    iconSource->w = 16;
    iconSource->h = 16;
    SDL_Rect* iconDestination = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    iconDestination->x = 0;
    iconDestination->y = 0;
    iconDestination->w = 64;
    iconDestination->h = 64;
    SDL_Surface* icon = SDL_CreateRGBSurface(0, 64, 64, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_BlitScaled(surface, iconSource, icon, iconDestination);
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(icon);
    free(iconSource);
    free(iconDestination);

    TTF_Font* font = TTF_OpenFont(ASSETS_DIR"/silkscreen.ttf", 24);

    loadCamera(renderer, spriteSheet);
    loadPlayer();
    loadMap(renderer);
    loadInterface(renderer, font);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

}

void loop()
{
    running = 1;
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
    if(keyboardState[SDL_SCANCODE_ESCAPE]) running = 0;
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
    if(keyboardState[SDL_SCANCODE_Q])
    {
        int c = floor(getPlayerX()+0.5f);
        int r = floor(getPlayerY()+0.5f);
        unsigned char o = popObject();
        if(o!=0) addObject(getObject(c, r));
        setObject(c, r, o);
    }
    if(keyboardState[SDL_SCANCODE_1]) setChosen(0);
    if(keyboardState[SDL_SCANCODE_2]) setChosen(1);
    if(keyboardState[SDL_SCANCODE_3]) setChosen(2);
    if(keyboardState[SDL_SCANCODE_4]) setChosen(3);
    if(keyboardState[SDL_SCANCODE_5]) setChosen(4);

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_QUIT) running = 0;
    }
}

void update()
{

}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderMap();
    renderPlayer();
    renderCoordinates(getPlayerX(), getPlayerY());
    renderMinimap(getPlayerX(), getPlayerY());
    renderBar();
    SDL_RenderPresent(renderer);
}

void quit()
{
    quitCamera();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
