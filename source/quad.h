#ifndef QUAD
#define QUAD

#include <SDL2/SDL.h>

// To be moved to "header.h".
#define TXT_DIRT 0
#define TXT_GRASS_LEFT 1
#define TXT_GRASS_BOTTOM_LEFT 2
#define TXT_LOG 3
#define TXT_GRASS_TOP 4
#define TXT_GRASS_1 5
#define TXT_GRASS_BOTTOM 6
#define TXT_STONE 7
#define TXT_GRASS_2 8
#define TXT_GRASS_RIGHT 9
#define TXT_GRASS_BOTTOM_RIGHT 10
#define TXT_WEED 11
#define TXT_PLAYER_IDLE 12
#define TXT_DIRTBOX 13
#define TXT_WATER_1 14
#define TXT_WATER_2 15
#define TXT_PLAYER_FRONT_1 16
#define TXT_PLAYER_BACK_1 17
#define TXT_PLAYER_LEFT_1 18
#define TXT_PLAYER_RIGHT_1 19
#define TXT_PLAYER_FRONT_2 20
#define TXT_PLAYER_BACK_2 21
#define TXT_PLAYER_LEFT_2 22
#define TXT_PLAYER_RIGHT_2 23

SDL_Rect** createQuad();

#endif