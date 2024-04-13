#include "quad.h"

SDL_Rect **createQuad()
{
	SDL_Rect **_quad = (SDL_Rect **)malloc(24*sizeof(SDL_Rect *));
	
	for(int _i = 0; _i < 24; _i++)
	{
		_quad[_i] = (SDL_Rect *)malloc(sizeof(SDL_Rect));
		_quad[_i]->x = 16*(_i/4);
		_quad[_i]->y = 16*(_i%4);
		_quad[_i]->w = 16;
		_quad[_i]->h = 16;
	}
	
	return _quad;
}