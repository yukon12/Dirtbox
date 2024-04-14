#include "game.h"

static void load();
static void loop();
static void input();
static void update();
static void render();
static void quit();

static unsigned char running;
static float deltaTime;
static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Surface *spriteSheetSurface;
static TTF_Font *font;
static SDL_Rect **quad;

void run()
{
	load();
	loop();
	quit();
}

static void load()
{
	srand(time(NULL));
	
	int _sdlInit = SDL_Init(SDL_INIT_EVERYTHING);
	int _imgInit = IMG_Init(IMG_INIT_PNG);
	int _ttfInit = TTF_Init();
	
	running = 1;
	deltaTime = 0.0f;
	window = SDL_CreateWindow("Dirtbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	spriteSheetSurface = IMG_Load("../assets/spritesheet.png"); // Path to be fixed.
	font = TTF_OpenFont("../assets/silkscreen.ttf", 32);
	quad = createQuad();
	
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	loadWorld(renderer, spriteSheetSurface, quad);
	loadCamera(renderer, spriteSheetSurface);
	loadPlayer(quad, font);
	loadMap(renderer, font);
	loadInventory(renderer, font, quad);
	
	assert(_sdlInit==0);
	assert(_imgInit==IMG_INIT_PNG);
	assert(_ttfInit==0);
	assert(window!=NULL);
	assert(renderer!=NULL);
	assert(spriteSheetSurface!=NULL);
	assert(font!=NULL);
}

static void loop()
{
	while(running)
	{
		unsigned int _start = SDL_GetTicks();
		
		input();
		update();
		render();
		
		unsigned int _stop = SDL_GetTicks();
		unsigned int _frameDuration = _stop-_start;
		if(_frameDuration<16) SDL_Delay(16-_frameDuration);
		
		_stop = SDL_GetTicks();
		_frameDuration = _stop-_start;
		deltaTime = 0.001f*_frameDuration;
	}
}

static void input()
{
	SDL_Event _event;
	while(SDL_PollEvent(&_event))
		if(_event.type == SDL_QUIT) running = 0;
	
	const unsigned char* _keyboardState = SDL_GetKeyboardState(NULL);
	if(_keyboardState[SDL_SCANCODE_ESCAPE])
		running = 0;
	// Add arrow support.
	if(_keyboardState[SDL_SCANCODE_W])
		movePlayer(DIR_BACK);
	if(_keyboardState[SDL_SCANCODE_S])
		movePlayer(DIR_FRONT);
	if(_keyboardState[SDL_SCANCODE_A])
		movePlayer(DIR_LEFT);
	if(_keyboardState[SDL_SCANCODE_D])
		movePlayer(DIR_RIGHT);
	if(_keyboardState[SDL_SCANCODE_E])
		pickUpObject(floor(getPlayerX()+0.5f), floor(getPlayerY()+0.5f));
	if(_keyboardState[SDL_SCANCODE_Q])
		dropObject(floor(getPlayerX()+0.5f), floor(getPlayerY()+0.5f));
	if(_keyboardState[SDL_SCANCODE_1])
		chooseSlot(0);
	if(_keyboardState[SDL_SCANCODE_2])
		chooseSlot(1);
	if(_keyboardState[SDL_SCANCODE_3])
		chooseSlot(2);
	if(_keyboardState[SDL_SCANCODE_4])
		chooseSlot(3);
	if(_keyboardState[SDL_SCANCODE_5])
		chooseSlot(4);
}

static void update()
{
	updatePlayer(deltaTime);
	// Move to one function.
	setCameraX(getPlayerX()-CAMERA_OFFSET_X);
	setCameraY(getPlayerY()-CAMERA_OFFSET_Y);
	updateWorldFragmentTextures(getCameraX(), getCameraY());
	updateMap(getPlayerX(), getPlayerY());
}

static void render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	renderWorld();
	renderPlayer();
	renderMap();
	renderInventory();
	
	SDL_RenderPresent(renderer);
}

static void quit()
{
	// To be written.
}