#include "player.h"

// To be moved to "header.h".
#define FRAME_TIME 250

static void renderInventory();

static SDL_Rect **playerQuad;

static float playerX;
static float playerY;
static unsigned int playerMovement; // Name issue.
static unsigned char playerDirection;

void loadPlayer(SDL_Rect **_quad)
{
	playerQuad = (SDL_Rect **)malloc(10*sizeof(SDL_Rect *));
	playerQuad[0] = _quad[TXT_PLAYER_IDLE];
	playerQuad[1] = _quad[TXT_PLAYER_BACK_1];
	playerQuad[2] = _quad[TXT_PLAYER_FRONT_1];
	playerQuad[3] = _quad[TXT_PLAYER_LEFT_1];
	playerQuad[4] = _quad[TXT_PLAYER_RIGHT_1];
	playerQuad[5] = _quad[TXT_PLAYER_IDLE];
	playerQuad[6] = _quad[TXT_PLAYER_BACK_2];
	playerQuad[7] = _quad[TXT_PLAYER_FRONT_2];
	playerQuad[8] = _quad[TXT_PLAYER_LEFT_2];
	playerQuad[9] = _quad[TXT_PLAYER_RIGHT_2];
	
	playerX = 0;
	playerY = 0;
	playerMovement = 0;
	playerDirection = 0;
}

void updatePlayer(float _deltaTime)
{
	playerDirection = 0;
	
	if((playerMovement&(1<<DIR_BACK))&&(playerMovement&(1<<DIR_FRONT)))
		playerMovement &= ((1<<DIR_LEFT)&(1<<DIR_RIGHT));
	
	if((playerMovement&(1<<DIR_LEFT))&&(playerMovement&(1<<DIR_RIGHT)))
		playerMovement &= ((1<<DIR_BACK)&(1<<DIR_FRONT));
	
	if(playerMovement&(1<<DIR_BACK))
	{
		playerY -= _deltaTime*PLAYER_SPEED;
		// These functions could be more readable.
		if(!isOnTheGround(playerX+0.5f, playerY+1.0f)) playerY = ceil(playerY);
		playerDirection = DIR_BACK;
	}
	
	if(playerMovement&(1<<DIR_FRONT))
	{
		playerY += _deltaTime*PLAYER_SPEED;
		if(!isOnTheGround(playerX+0.5f, playerY+1.0f)) playerY = floor(playerY);
		playerDirection = DIR_FRONT;
	}
		
	if(playerMovement&(1<<DIR_LEFT))
	{
		playerX -= _deltaTime*PLAYER_SPEED;
		if(!isOnTheGround(playerX+0.0625f, playerY+1.0f)) playerX = ceil(playerX)+0.0625f;
		playerDirection = DIR_LEFT;
	}
		
	if(playerMovement&(1<<DIR_RIGHT))
	{
		playerX += _deltaTime*PLAYER_SPEED;
		if(!isOnTheGround(playerX+0.9375f, playerY+1.0f)) playerX = floor(playerX)-0.0625f;
		playerDirection = DIR_RIGHT;
	}
		
	playerMovement = 0;
	
	if(playerX < 0.0f) playerX += ((float)WORLD_SIZE);
	if(playerY < 0.0f) playerY += ((float)WORLD_SIZE);
	if(playerX > ((float)WORLD_SIZE)) playerX -= ((float)WORLD_SIZE);
	if(playerY > ((float)WORLD_SIZE)) playerY -= ((float)WORLD_SIZE);
}

void renderPlayer()
{
	unsigned char _frame = (SDL_GetTicks()/FRAME_TIME)%2;
	renderTextureOnTheWorld(NULL, playerQuad[5*_frame+playerDirection], playerX, playerY);
}

void movePlayer(unsigned char _direction)
{
	playerMovement |= (1<<_direction);
}

float getPlayerX()
{
	return playerX;	
}

float getPlayerY()
{
	return playerY;
}