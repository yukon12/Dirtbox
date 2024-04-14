#include "inventory.h"

#define OBJ_NOTHING 0
#define OBJ_LOG 1
#define OBJ_STONE 2
#define OBJ_WEED 3

static SDL_Texture *createAmountTexture(int _index);

static SDL_Renderer *renderer;
static TTF_Font *font;
static SDL_Rect **quad;

static SDL_Texture **amountTexture;
static SDL_Color *textColor;
static unsigned char *objectTexture;
static unsigned char *object;
static int *amount;
static int chosenSlot;

void loadInventory(SDL_Renderer *_renderer, TTF_Font *_font, SDL_Rect **_quad)
{
	renderer = _renderer;
	font = _font;
	quad = _quad;
	
	amountTexture = (SDL_Texture **)malloc(5*sizeof(SDL_Texture *));
	textColor = (SDL_Color *)malloc(sizeof(SDL_Color));
	textColor->r = 255;
	textColor->g = 255;
	textColor->b = 255;
	textColor->a = 255;
	objectTexture = (unsigned char *)malloc(3*sizeof(unsigned char));
	objectTexture[0] = TXT_LOG;
	objectTexture[1] = TXT_STONE;
	objectTexture[2] = TXT_WEED;
	object = (unsigned char *)calloc(5, sizeof(unsigned char));
	amount = (int *)calloc(5, sizeof(int));
	chosenSlot = 0;
}

static SDL_Texture *createAmountTexture(int _index)
{
	if(amount[_index]==0)
		return NULL;
	
	char _text[3];
	sprintf(_text, "%d", amount[_index]);
	SDL_Surface *_surface = TTF_RenderText_Solid(font, _text, *textColor);
	SDL_Texture *_texture = SDL_CreateTextureFromSurface(renderer, _surface);
	SDL_FreeSurface(_surface);
	return _texture;
}

void renderInventory()
{
	SDL_Rect *_slot = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	_slot->x = 8;
	_slot->y = 160;
	_slot->w = 64;
	_slot->h = 64;
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
	
	for(int _i = 0; _i < 5; _i++)
	{
		_slot->y += 72;
		if(_i==chosenSlot)
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 196);
		SDL_RenderFillRect(renderer, _slot);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
		if(object[_i])
		{
			renderTextureOnTheWindow(NULL, quad[objectTexture[object[_i]-1]], _slot->x, _slot->y, 4.0f);
			renderTextureOnTheWindow(amountTexture[_i], NULL, _slot->x, _slot->y+48, 0.5f);
		}
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void pickUpObject(int _x, int _y)
{
	unsigned char _object = getWorldObject(_x, _y);
	
	if(_object==OBJ_NOTHING)
		return;
	
	setWorldObject(_x, _y, OBJ_NOTHING);
	
	int _firstMatchingSlot = -1;
	for(int _i = 0; _i < 5; _i++)
	{
		if(object[_i] == _object)
		{
			_firstMatchingSlot = _i;
			break;
		}
	}
	
	if(_firstMatchingSlot == -1)
	{
		for(int _i = 0; _i < 5; _i++)
		{
			if(object[_i] == OBJ_NOTHING)
			{
				_firstMatchingSlot = _i;
				break;
			}
		}
	}
	
	if(_firstMatchingSlot == -1)
		return;
	
	object[_firstMatchingSlot] = _object;
	amount[_firstMatchingSlot]++;
	amountTexture[_firstMatchingSlot] = createAmountTexture(_firstMatchingSlot);
}

void dropObject(int _x, int _y)
{
	unsigned char _objectOnTheGround = getWorldObject(_x, _y);
	unsigned char _object = object[chosenSlot];
	
	if(_objectOnTheGround!=OBJ_NOTHING||_object==OBJ_NOTHING)
		return;
	
	setWorldObject(_x, _y, _object);
	
	amount[chosenSlot]--;
	if(amount[chosenSlot]==0)
		object[chosenSlot]=OBJ_NOTHING;
	amountTexture[chosenSlot] = createAmountTexture(chosenSlot);
}

void chooseSlot(int _index)
{
	chosenSlot = _index;	
}