#include "camera.h"

static int convertX(float _x, int _textureWidth);
static int convertY(float _y, int _textureHeight);

static SDL_Renderer *renderer;
static SDL_Texture *spriteSheetTexture;

static float cameraX;
static float cameraY;

void loadCamera(SDL_Renderer *_renderer, SDL_Surface *_spriteSheetSurface)
{
	renderer = _renderer;
	spriteSheetTexture = SDL_CreateTextureFromSurface(renderer, _spriteSheetSurface);
	
	cameraX = 0;
	cameraY = 0;
}

float getCameraX()
{
	return cameraX;	
}

float getCameraY()
{
	return cameraY;
}

void setCameraX(float _x)
{
	cameraX = _x;	
}

void setCameraY(float _y)
{
	cameraY = _y;
}

/*
void renderTextureOnTheWorld(SDL_Texture *_texture, SDL_Rect *_source, float _x, float _y)
{
	if(_texture == NULL)
		_texture = spriteSheetTexture;
	
	int _textureWidth = 0;
	int _textureHeight = 0;
	SDL_QueryTexture(_texture, NULL, NULL, &_textureWidth, &_textureHeight);

	int _windowX = convertX(_x, _textureWidth);
	int _windowY = convertY(_y, _textureHeight);
	
	if(_source == NULL)
	{
		_source = (SDL_Rect *)malloc(sizeof(SDL_Rect));
		_source->x = 0;
		_source->y = 0;
		_source->w = _textureWidth;
		_source->h = _textureHeight;
	}
	
	SDL_Rect *_destination = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	_destination->x = _windowX;
	_destination->y = _windowY;
	_destination->w = PIXEL_SIZE*_source->w;
	_destination->h = PIXEL_SIZE*_source->h;
	
	SDL_RenderCopy(renderer, _texture, _source, _destination);
}
*/

void renderTextureOnTheWorld(SDL_Texture *_texture, SDL_Rect *_source, float _x, float _y)
{
	if(_texture == NULL)
		_texture = spriteSheetTexture;
	
	int _textureWidth = 0;
	int _textureHeight = 0;
	SDL_QueryTexture(_texture, NULL, NULL, &_textureWidth, &_textureHeight);
	
	int _windowX = convertX(_x, _textureWidth);
	int _windowY = convertY(_y, _textureHeight);
	
	renderTextureOnTheWindow(_texture, _source, _windowX, _windowY, PIXEL_SIZE);
}

static int convertX(float _x, int _textureWidth)
{
	// Issue.
	/*
	_x -= cameraX;
	int _result = floor(((float)UNIT)*_x);
	_result = (_result+(PIXEL_SIZE*_textureWidth)+WORLD_WINDOW_SIZE)%WORLD_WINDOW_SIZE-(PIXEL_SIZE*_textureWidth);
	return _result;
	*/
	return (((int)(UNIT*(_x-cameraX)))+WORLD_WINDOW_SIZE+(PIXEL_SIZE*_textureWidth))%WORLD_WINDOW_SIZE-(PIXEL_SIZE*_textureWidth);
}

static int convertY(float _y, int _textureHeight)
{
	// Issue.
	/*
	_y -= cameraY;
	int _result = floor(((float)UNIT)*_y);
	_result = (_result+(PIXEL_SIZE*_textureHeight)+WORLD_WINDOW_SIZE)%WORLD_WINDOW_SIZE-(PIXEL_SIZE*_textureHeight);
	return _result;
	*/
	return (((int)(UNIT*(_y-cameraY)))+WORLD_WINDOW_SIZE+(PIXEL_SIZE*_textureHeight))%WORLD_WINDOW_SIZE-(PIXEL_SIZE*_textureHeight);
}

// Extract common part of both functions to another function.
void renderTextureOnTheWindow(SDL_Texture *_texture, SDL_Rect *_source, int _x, int _y, float _scale)
{
	if(_texture == NULL)
		_texture = spriteSheetTexture;
	
	int _textureWidth = 0;
	int _textureHeight = 0;
	SDL_QueryTexture(_texture, NULL, NULL, &_textureWidth, &_textureHeight);
	
	if(_source == NULL)
	{
		_source = (SDL_Rect *)malloc(sizeof(SDL_Rect));
		_source->x = 0;
		_source->y = 0;
		_source->w = _textureWidth;
		_source->h = _textureHeight;
	}
	
	SDL_Rect *_destination = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	_destination->x = _x;
	_destination->y = _y;
	_destination->w = round(_scale*_source->w);
	_destination->h = round(_scale*_source->h);
	
	SDL_RenderCopy(renderer, _texture, _source, _destination);
}