#include "world.h"

// Debug.
#include <assert.h>
#include <stdio.h>

// Frame issue.

// To be moved to "header.h".
// Smaller fragments.
#define FRAGMENT_SIZE 32
#define PERLIN_NOISE_GRID_SIZE 256
#define FRAME_TIME 500

static unsigned char **createTileMatrix();
static unsigned char **createObjectMatrix();
static void shiftFragmentTableHorizontally(int _shift);
static void shiftFragmentTableVertically(int _shift);
static SDL_Texture *createFragment(int _x, int _y, unsigned char _frame);
static unsigned int getTileSprites(int _x, int _y, unsigned char _frame);
static void layerTileSprites(SDL_Surface* _fragmentSurface, int _x, int _y, unsigned int _sprites);

static SDL_Renderer *renderer;
static SDL_Surface *spriteSheetSurface;
static SDL_Rect **quad;

static unsigned char **tileMatrix;
static unsigned char **objectMatrix;
static unsigned int *tileTextureOrder;
static unsigned char *objectTexture;
static int fragmentX;
static int fragmentY;
static SDL_Texture **fragment;


// Move createFragment function higher.
void loadWorld(SDL_Renderer* _renderer, SDL_Surface *_spriteSheetSurface, SDL_Rect **_quad)
{
	renderer = _renderer;
	spriteSheetSurface = _spriteSheetSurface;
	quad = _quad;
	
	tileMatrix = createTileMatrix();
	objectMatrix = createObjectMatrix();
	// If I change spritesheet, this will become obsolete.
	tileTextureOrder = (unsigned int *)malloc(11*sizeof(unsigned int));
	tileTextureOrder[0] = TXT_GRASS_1;
	tileTextureOrder[1] = TXT_GRASS_2;
	tileTextureOrder[2]= TXT_WATER_1;
	tileTextureOrder[3]= TXT_WATER_2;
	tileTextureOrder[4] = TXT_DIRT;
	tileTextureOrder[5] = TXT_GRASS_RIGHT;
	tileTextureOrder[6] = TXT_GRASS_LEFT;
	tileTextureOrder[7] = TXT_GRASS_TOP;
	tileTextureOrder[8] = TXT_GRASS_BOTTOM;
	tileTextureOrder[9] = TXT_GRASS_BOTTOM_RIGHT;
	tileTextureOrder[10] = TXT_GRASS_BOTTOM_LEFT;
	objectTexture = (unsigned char *)malloc(3*sizeof(unsigned char));
	objectTexture[0] = TXT_LOG;
	objectTexture[1] = TXT_STONE;
	objectTexture[2] = TXT_WEED;
	fragmentX = 0;
	fragmentY = 0;
	fragment = (SDL_Texture **)malloc(8*sizeof(SDL_Texture *));
	fragment[0] = createFragment(fragmentX, fragmentY, 0);
	fragment[1] = createFragment(fragmentX, fragmentY+1, 0);
	fragment[2] = createFragment(fragmentX+1, fragmentY, 0);
	fragment[3] = createFragment(fragmentX+1, fragmentY+1, 0);
	fragment[4] = createFragment(fragmentX, fragmentY, 1);
	fragment[5] = createFragment(fragmentX, fragmentY+1, 1);
	fragment[6] = createFragment(fragmentX+1, fragmentY, 1);
	fragment[7] = createFragment(fragmentX+1, fragmentY+1, 1);
}

static unsigned char **createTileMatrix()
{	
	unsigned char **_tileMatrix = (unsigned char **)malloc(WORLD_SIZE*sizeof(_tileMatrix));
	for(int _x = 0; _x < WORLD_SIZE; _x++)
		_tileMatrix[_x] = (unsigned char *)calloc(WORLD_SIZE, sizeof(_tileMatrix));
	
	int _octave[] = { 16, 32, 64 };
	float **_perlinNoise = createPerlinNoise(WORLD_SIZE, _octave, sizeof(_octave)/sizeof(int));
	
	for(int _y = 0; _y < WORLD_SIZE; _y++)
	{
		for(int _x = 0; _x < WORLD_SIZE; _x++)
		{
			// Sea level to be changed.
			if(_perlinNoise[_x][_y]>=0.0f)
				_tileMatrix[_x][_y] = 1;
		}
	}
	
	return _tileMatrix;
}

static unsigned char **createObjectMatrix()
{
	unsigned char **_objectMatrix = (unsigned char **)malloc(WORLD_SIZE*sizeof(_objectMatrix));
	for(int _x = 0; _x < WORLD_SIZE; _x++)
		_objectMatrix[_x] = (unsigned char *)calloc(WORLD_SIZE, sizeof(_objectMatrix));
	
	for(int _y = 0; _y < WORLD_SIZE; _y++)
	{
		for(int _x = 0; _x < WORLD_SIZE; _x++)
		{
			_objectMatrix[_x][_y] = 0;
			int _object = rand()%64;
			if(tileMatrix[_x][_y]&&_object<3)
				_objectMatrix[_x][_y] = _object+1;
		}
	}
	
	return _objectMatrix;
}


// Change the function's name.
void updateWorldFragmentTextures(float _x, float _y)
{	
	int _newFragmentX = floor(_x/((float)FRAGMENT_SIZE));
	int _newFragmentY = floor(_y/((float)FRAGMENT_SIZE));
	
	int _horizontalShift = _newFragmentX - fragmentX;
	int _verticalShift = _newFragmentY - fragmentY;
	
	shiftFragmentTableHorizontally(_horizontalShift);
	shiftFragmentTableVertically(_verticalShift);
}

// Add destroying textures.
static void shiftFragmentTableHorizontally(int _shift)
{	
	if(_shift == 0)
		return;
	
	fragmentX += _shift;
	
	if(_shift == -1)
	{
		fragment[2] = fragment[0];
		fragment[3] = fragment[1];
		fragment[6] = fragment[4];
		fragment[7] = fragment[5];
		fragment[0] = createFragment(fragmentX, fragmentY, 0);
		fragment[1] = createFragment(fragmentX, fragmentY+1, 0);
		fragment[4] = createFragment(fragmentX, fragmentY, 1);
		fragment[5] = createFragment(fragmentX, fragmentY+1, 1);
		return;
	}
	
	if(_shift == 1)
	{
		fragment[0] = fragment[2];
		fragment[1] = fragment[3];
		fragment[4] = fragment[6];
		fragment[5] = fragment[7];
		fragment[2] = createFragment(fragmentX+1, fragmentY, 0);
		fragment[3] = createFragment(fragmentX+1, fragmentY+1, 0);
		fragment[6] = createFragment(fragmentX+1, fragmentY, 1);
		fragment[7] = createFragment(fragmentX+1, fragmentY+1, 1);
		return;
	}
	
	fragment[0] = createFragment(fragmentX, fragmentY, 0);
	fragment[1] = createFragment(fragmentX, fragmentY+1, 0);
	fragment[2] = createFragment(fragmentX+1, fragmentY, 0);
	fragment[3] = createFragment(fragmentX+1, fragmentY+1, 0);
	fragment[4] = createFragment(fragmentX, fragmentY, 1);
	fragment[5] = createFragment(fragmentX, fragmentY+1, 1);
	fragment[6] = createFragment(fragmentX+1, fragmentY, 1);
	fragment[7] = createFragment(fragmentX+1, fragmentY+1, 1);
}

// Add destroying textures.
static void shiftFragmentTableVertically(int _shift)
{
	if(_shift == 0)
		return;
	
	fragmentY += _shift;
	
	if(_shift == -1)
	{
		//SDL_DestroyTexture(fragment[1]);
		//SDL_DestroyTexture(fragment[3]);
		//SDL_DestroyTexture(fragment[5]);
		//SDL_DestroyTexture(fragment[7]);
		fragment[1] = fragment[0];
		fragment[3] = fragment[2];
		fragment[5] = fragment[4];
		fragment[7] = fragment[6];
		fragment[0] = createFragment(fragmentX, fragmentY, 0);
		fragment[2] = createFragment(fragmentX+1, fragmentY, 0);
		fragment[4] = createFragment(fragmentX, fragmentY, 1);
		fragment[6] = createFragment(fragmentX+1, fragmentY, 1);
		return;
	}
	
	if(_shift == 1)
	{
		fragment[0] = fragment[1];
		fragment[2] = fragment[3];
		fragment[4] = fragment[5];
		fragment[6] = fragment[7];
		fragment[1] = createFragment(fragmentX, fragmentY+1, 0);
		fragment[3] = createFragment(fragmentX+1, fragmentY+1, 0);
		fragment[5] = createFragment(fragmentX, fragmentY+1, 1);
		fragment[7] = createFragment(fragmentX+1, fragmentY+1, 1);
		return;
	}
	
	fragment[0] = createFragment(fragmentX, fragmentY, 0);
	fragment[1] = createFragment(fragmentX, fragmentY+1, 0);
	fragment[2] = createFragment(fragmentX+1, fragmentY, 0);
	fragment[3] = createFragment(fragmentX+1, fragmentY+1, 0);
	fragment[4] = createFragment(fragmentX, fragmentY, 0);
	fragment[5] = createFragment(fragmentX, fragmentY+1, 1);
	fragment[6] = createFragment(fragmentX+1, fragmentY, 0);
	fragment[7] = createFragment(fragmentX+1, fragmentY+1, 1);
}

static SDL_Texture *createFragment(int _x, int _y, unsigned char _frame)
{
	// Alpha !!!
	SDL_Surface *_fragmentSurface = SDL_CreateRGBSurface(0, TEXTURE_SIZE*FRAGMENT_SIZE, TEXTURE_SIZE*FRAGMENT_SIZE, 24, 0xFF0000, 0x00FF00, 0x0000FF, 0x000000);
	unsigned int _sprites = 0;
	
	int _sX = (FRAGMENT_SIZE*_x+WORLD_SIZE)%WORLD_SIZE;
	int _sY = (FRAGMENT_SIZE*_y+WORLD_SIZE)%WORLD_SIZE;
	
	for(int _dY = 0; _dY < FRAGMENT_SIZE; _dY++)
	{
		for(int _dX = 0; _dX < FRAGMENT_SIZE; _dX++)
		{
			// Possible issue but not sure.
			int _currentX = _sX+_dX;
			int _currentY = _sY+_dY;
			_sprites = getTileSprites(_currentX, _currentY, _frame);
			layerTileSprites(_fragmentSurface, _dX, _dY, _sprites);
		}
	}
	
	SDL_Texture* _fragment = SDL_CreateTextureFromSurface(renderer, _fragmentSurface);
	SDL_FreeSurface(_fragmentSurface);
	
	return _fragment;
}

static unsigned int getTileSprites(int _x, int _y, unsigned char _frame)
{
	unsigned int _sprites = 0;
	
	if(tileMatrix[_x][_y])
	{
		if(!_frame) 
		{
			_sprites |= (1<<TXT_GRASS_1);
			return _sprites;
		}
		_sprites |= (1<<TXT_GRASS_2);
		return _sprites;
	}
	
	if(!_frame)
		_sprites |= (1<<TXT_WATER_1);
	if(_frame)
		_sprites |= (1<<TXT_WATER_2);
	
	int _topY = (_y-1+WORLD_SIZE)%WORLD_SIZE;
	int _bottomY = (_y+1)%WORLD_SIZE;
	int _leftX = (_x-1+WORLD_SIZE)%WORLD_SIZE;
	int _rightX = (_x+1)%WORLD_SIZE;
	
	if(tileMatrix[_x][_topY])
		_sprites |= ((1<<TXT_DIRT)|(1<<TXT_GRASS_BOTTOM));
	
	if(tileMatrix[_x][_bottomY])
		_sprites |= (1<<TXT_GRASS_TOP);
	
	if(tileMatrix[_leftX][_y])
		_sprites |= (1<<TXT_GRASS_RIGHT);
	
	if(tileMatrix[_rightX][_y])
		_sprites |= (1<<TXT_GRASS_LEFT);
	
	if(tileMatrix[_leftX][_topY]&&(!tileMatrix[_x][_topY])&&(!tileMatrix[_leftX][_topY]))
		_sprites |= (1<<TXT_GRASS_BOTTOM_RIGHT);
	
	if(tileMatrix[_rightX][_topY]&&(!tileMatrix[_x][_topY])&&(!tileMatrix[_rightX][_topY]))
		_sprites |= (1<<TXT_GRASS_BOTTOM_LEFT);
	
	return _sprites;
}

static void layerTileSprites(SDL_Surface* _fragmentSurface, int _x, int _y, unsigned int _sprites)
{
	SDL_Rect *_destination = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	_destination->x = TEXTURE_SIZE*_x;
	_destination->y = TEXTURE_SIZE*_y;
	_destination->w = 16;
	_destination->h = 16;
	
	for(int _i = 0; _i < 11; _i++)
		if(_sprites&(1<<tileTextureOrder[_i]))
			SDL_BlitSurface(spriteSheetSurface, quad[tileTextureOrder[_i]], _fragmentSurface, _destination);
}

void renderWorld()
{
	unsigned char _frame = (SDL_GetTicks()/FRAME_TIME)%2;
	renderTextureOnTheWorld(fragment[4*_frame], NULL, FRAGMENT_SIZE*fragmentX, FRAGMENT_SIZE*fragmentY);
	renderTextureOnTheWorld(fragment[4*_frame+1], NULL, FRAGMENT_SIZE*fragmentX, FRAGMENT_SIZE*(fragmentY+1));
	renderTextureOnTheWorld(fragment[4*_frame+2], NULL, FRAGMENT_SIZE*(fragmentX+1), FRAGMENT_SIZE*fragmentY);
	renderTextureOnTheWorld(fragment[4*_frame+3], NULL, FRAGMENT_SIZE*(fragmentX+1), FRAGMENT_SIZE*(fragmentY+1));
	
	int _sX = FRAGMENT_SIZE*fragmentX;
	int _sY = FRAGMENT_SIZE*fragmentY;
	// 2 to be replaced by a macro.
	// Objects to be included into fragments.
	for(int _dY = 0; _dY < 2*FRAGMENT_SIZE; _dY++)
	{
		for(int _dX = 0; _dX < 2*FRAGMENT_SIZE; _dX++)
		{
			// Should be unnecessary. Something is wrong?
			unsigned char object = objectMatrix[(_sX+_dX+WORLD_SIZE)%WORLD_SIZE][(_sY+_dY+WORLD_SIZE)%WORLD_SIZE];
			if(object)
				renderTextureOnTheWorld(NULL, quad[objectTexture[object-1]], _sX+_dX, _sY+_dY);
		}
	}
}

unsigned char getWorldTile(int _x, int _y)
{
	return tileMatrix[(_x+WORLD_SIZE)%WORLD_SIZE][(_y+WORLD_SIZE)%WORLD_SIZE];
}

unsigned char getWorldObject(int _x, int _y)
{
	return objectMatrix[(_x+WORLD_SIZE)%WORLD_SIZE][(_y+WORLD_SIZE)%WORLD_SIZE];
}

void setWorldObject(int _x, int _y, unsigned char _object)
{
	_x = (_x+WORLD_SIZE)%WORLD_SIZE;
	_y = (_y+WORLD_SIZE)%WORLD_SIZE;
	objectMatrix[_x][_y] = _object;
}

unsigned char isOnTheGround(float _x, float _y)
{
	unsigned char _result = 0;
	_result |= getWorldTile(floor(_x), floor(_y));
	_result |= getWorldTile(floor(_x), ceil(_y)-1);
	_result |= getWorldTile(ceil(_x)-1, floor(_y));
	_result |= getWorldTile(ceil(_x)-1, ceil(_y)-1);
	return _result;
}