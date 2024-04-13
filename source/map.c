#include "map.h"

#define MAP_FRAGMENT_SIZE 128
#define GAP 8
#define MAP_OPACITY 255

static SDL_Texture *createFragment(int _x, int _y);
static void shiftFragmentTableHorizontally(int _shift);
static void shiftFragmentTableVertically(int _shift);

static SDL_Renderer *renderer;
static TTF_Font *font;

// Change name.
static int cornerX;
static int cornerY;
static int fragmentX;
static int fragmentY;
static SDL_Color *textColor;
static SDL_Texture **fragment;
static SDL_Texture *coordinatePrefixX;
static SDL_Texture *coordinatePrefixY;
static SDL_Texture *coordinateValueX;
static SDL_Texture *coordinateValueY;

void loadMap(SDL_Renderer *_renderer, TTF_Font *_font)
{
	renderer = _renderer;
	font = _font;
	
	cornerX = 0;
	cornerY = 0;
	fragmentX = 0;
	fragmentY = 0;
	textColor = (SDL_Color *)malloc(sizeof(SDL_Color));
	textColor->r = 255;
	textColor->g = 255;
	textColor->b = 255;
	textColor->a = 255;
	fragment = (SDL_Texture **)malloc(4*sizeof(SDL_Texture *));
	fragment[0] = createFragment(0, 0);
	fragment[1] = createFragment(0, 1);
	fragment[2] = createFragment(1, 0);
	fragment[3] = createFragment(1, 1);
	// Unreadable code. Replace with _temporarySurface.
	SDL_Surface *_cpfxSurface = TTF_RenderText_Solid(font, "x: ", *textColor);
	coordinatePrefixX = SDL_CreateTextureFromSurface(renderer, _cpfxSurface);
	SDL_FreeSurface(_cpfxSurface);
	SDL_Surface *_cpfySurface = TTF_RenderText_Solid(font, "y: ", *textColor);
	coordinatePrefixY = SDL_CreateTextureFromSurface(renderer, _cpfySurface);
	SDL_FreeSurface(_cpfySurface);
	SDL_Surface *_cvfxSurface = TTF_RenderText_Solid(font, "32", *textColor);
	coordinateValueX = SDL_CreateTextureFromSurface(renderer, _cvfxSurface);
	SDL_FreeSurface(_cvfxSurface);
	SDL_Surface *_cvfySurface = TTF_RenderText_Solid(font, "32", *textColor);
	coordinateValueY = SDL_CreateTextureFromSurface(renderer, _cvfySurface);
	SDL_FreeSurface(_cvfySurface);
}

// Possible improvements.
static SDL_Texture *createFragment(int _x, int _y)
{
	SDL_Surface *_fragmentSurface = SDL_CreateRGBSurface(0, MAP_FRAGMENT_SIZE, MAP_FRAGMENT_SIZE, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	
	int _sX = (MAP_FRAGMENT_SIZE*_x+WORLD_SIZE)%WORLD_SIZE;
	int _sY = (MAP_FRAGMENT_SIZE*_y+WORLD_SIZE)%WORLD_SIZE;
	
	SDL_LockSurface(_fragmentSurface);
	
	unsigned char *_pixels = (unsigned char *)_fragmentSurface->pixels;
	
	for(int _dY = 0; _dY < MAP_FRAGMENT_SIZE; _dY++)
	{
		for(int _dX = 0; _dX < MAP_FRAGMENT_SIZE; _dX++)
		{
			int _pixelIndex = 4*MAP_FRAGMENT_SIZE*_dY+4*_dX;
			_pixels[_pixelIndex] = 0;
			_pixels[_pixelIndex+1] = 255;
			_pixels[_pixelIndex+2] = 255;
			_pixels[_pixelIndex+3] = 255;
			if(getWorldTile(_sX+_dX, _sY+_dY))
				_pixels[_pixelIndex] = MAP_OPACITY;
		}
	}
	
	SDL_UnlockSurface(_fragmentSurface);
	
	SDL_Texture* _fragment = SDL_CreateTextureFromSurface(renderer, _fragmentSurface);
	SDL_FreeSurface(_fragmentSurface);
	
	return _fragment;
}

void updateMap(float _x, float _y)
{
	if(cornerX != floor(_x)-64)
	{
		char _text[4];
		sprintf(_text, "%d", (int)floor(_x));
		SDL_Surface *_cvfxSurface = TTF_RenderText_Solid(font, _text, *textColor);
		coordinateValueX = SDL_CreateTextureFromSurface(renderer, _cvfxSurface);
		SDL_FreeSurface(_cvfxSurface);
	}
	
	if(cornerY != floor(_y)-64)
	{
		char _text[4];
		sprintf(_text, "%d", (int)floor(_y));
		SDL_Surface *_cvfySurface = TTF_RenderText_Solid(font, _text, *textColor);
		coordinateValueY = SDL_CreateTextureFromSurface(renderer, _cvfySurface);
		SDL_FreeSurface(_cvfySurface);
	}
	
	cornerX = floor(_x)-64;
	cornerY = floor(_y)-64;
	int _newFragmentX = floor(cornerX/((float)MAP_FRAGMENT_SIZE));
	int _newFragmentY = floor(cornerY/((float)MAP_FRAGMENT_SIZE));
	
	int _horizontalShift = _newFragmentX - fragmentX;
	int _verticalShift = _newFragmentY - fragmentY;
	
	shiftFragmentTableHorizontally(_horizontalShift);
	shiftFragmentTableVertically(_verticalShift);
}

static void shiftFragmentTableHorizontally(int _shift)
{
	if(_shift == 0)
		return;
	
	fragmentX += _shift;
	
	if(_shift == -1)
	{
		fragment[2] = fragment[0];
		fragment[3] = fragment[1];
		fragment[0] = createFragment(fragmentX, fragmentY);
		fragment[1] = createFragment(fragmentX, fragmentY+1);
		return;
	}
	
	if(_shift == 1)
	{
		fragment[0] = fragment[2];
		fragment[1] = fragment[3];
		fragment[2] = createFragment(fragmentX+1, fragmentY);
		fragment[3] = createFragment(fragmentX+1, fragmentY+1);
		return;
	}
	
	fragment[0] = createFragment(fragmentX, fragmentY);
	fragment[1] = createFragment(fragmentX, fragmentY+1);
	fragment[2] = createFragment(fragmentX+1, fragmentY);
	fragment[3] = createFragment(fragmentX+1, fragmentY+1);
}

static void shiftFragmentTableVertically(int _shift)
{
	if(_shift == 0)
		return;
	
	fragmentY += _shift;
	
	if(_shift == -1)
	{
		fragment[1] = fragment[0];
		fragment[3] = fragment[2];
		fragment[0] = createFragment(fragmentX, fragmentY);
		fragment[2] = createFragment(fragmentX+1, fragmentY);
		return;
	}
	
	if(_shift == 1)
	{
		fragment[0] = fragment[1];
		fragment[2] = fragment[3];
		fragment[1] = createFragment(fragmentX, fragmentY+1);
		fragment[3] = createFragment(fragmentX+1, fragmentY+1);
		return;
	}
	
	fragment[0] = createFragment(fragmentX, fragmentY);
	fragment[1] = createFragment(fragmentX, fragmentY+1);
	fragment[2] = createFragment(fragmentX+1, fragmentY);
	fragment[3] = createFragment(fragmentX+1, fragmentY+1);
}

void renderMap()
{	
	int _mapX = cornerX-MAP_FRAGMENT_SIZE*fragmentX;
	int _mapY = cornerY-MAP_FRAGMENT_SIZE*fragmentY;
	
	SDL_Rect *_source = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	
	_source->x = _mapX;
	_source->y = _mapY;
	_source->w = MAP_FRAGMENT_SIZE-_mapX;
	_source->h = MAP_FRAGMENT_SIZE-_mapY;
	renderTextureOnTheWindow(fragment[0], _source, GAP, GAP, 1.0f);
	
	_source->x = _mapX;
	_source->y = 0;
	_source->w = MAP_FRAGMENT_SIZE-_mapX;
	_source->h = _mapY;
	renderTextureOnTheWindow(fragment[1], _source, GAP, GAP+MAP_FRAGMENT_SIZE-_mapY, 1.0f);
	
	_source->x = 0;
	_source->y = _mapY;
	_source->w = _mapX;
	_source->h = MAP_FRAGMENT_SIZE-_mapY;
	renderTextureOnTheWindow(fragment[2], _source, GAP+MAP_FRAGMENT_SIZE-_mapX, GAP, 1.0f);
	
	_source->x = 0;
	_source->y = 0;
	_source->w = _mapX;
	_source->h = _mapY;
	renderTextureOnTheWindow(fragment[3], _source, GAP+MAP_FRAGMENT_SIZE-_mapX, GAP+MAP_FRAGMENT_SIZE-_mapY, 1.0f);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, MAP_OPACITY);
	
	SDL_Rect *_bound = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	_bound->x = GAP;
	_bound->y = GAP;
	_bound->w = 128;
	_bound->h = 128;
	SDL_RenderDrawRect(renderer, _bound);
	
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, MAP_OPACITY);
	
	SDL_RenderDrawPoint(renderer, GAP+63, GAP+63);
	SDL_RenderDrawPoint(renderer, GAP+63, GAP+64);
	SDL_RenderDrawPoint(renderer, GAP+64, GAP+63);
	SDL_RenderDrawPoint(renderer, GAP+64, GAP+64);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	renderTextureOnTheWindow(coordinatePrefixX, NULL, GAP, 2*GAP+MAP_FRAGMENT_SIZE, 1.0f);
	renderTextureOnTheWindow(coordinatePrefixY, NULL, GAP, 2*GAP+MAP_FRAGMENT_SIZE+32, 1.0f);
	renderTextureOnTheWindow(coordinateValueX, NULL, GAP+48, 2*GAP+MAP_FRAGMENT_SIZE, 1.0f);
	renderTextureOnTheWindow(coordinateValueY, NULL, GAP+48, 2*GAP+MAP_FRAGMENT_SIZE+32, 1.0f);
}