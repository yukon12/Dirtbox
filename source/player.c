#include "../include/player.h"

#define IDLE 0
#define LEFT 1
#define RIGHT 2
#define BACK 3
#define FRONT 4

static SDL_FPoint* player;
static SDL_FPoint* offset;
static unsigned char orientation;

void loadPlayer()
{
    player = (SDL_FPoint*)malloc(sizeof(SDL_FPoint));
    player->x = 0.0f;
    player->y = 0.0f;
    offset = (SDL_FPoint*)malloc(sizeof(SDL_FPoint));
    offset->x = ((float)WINDOW_WIDTH)/(2.0f*UNIT)-0.5f;
    offset->y = ((float)WINDOW_HEIGHT)/(2.0f*UNIT)-0.5f;
    orientation = 0;
    setCameraX(player->x-offset->x);
    setCameraY(player->y-offset->y);
}

float getPlayerX()
{
    return player->x;
}

float getPlayerY()
{
    return player->y;
}

void resetOrientation()
{
    orientation = IDLE;
}

unsigned char leftFoot()
{
    unsigned char result = 0;
    result |= getTile((int)floor(player->x+0.0625f), (int)floor(player->y+1.0f)); 
    result |= getTile((int)ceil(player->x+0.0625f)-1, (int)floor(player->y+1.0f)); 
    result |= getTile((int)floor(player->x+0.0625f), (int)ceil(player->y+1.0f)-1); 
    result |= getTile((int)ceil(player->x+0.0625f)-1, (int)ceil(player->y+1.0f)-1); 
    return result;
}

unsigned char rightFoot()
{
    unsigned char result = 0;
    result |= getTile((int)floor(player->x+0.9375f), (int)floor(player->y+1.0f)); 
    result |= getTile((int)ceil(player->x+0.9375f)-1, (int)floor(player->y+1.0f)); 
    result |= getTile((int)floor(player->x+0.9375f), (int)ceil(player->y+1.0f)-1); 
    result |= getTile((int)ceil(player->x+0.9375f)-1, (int)ceil(player->y+1.0f)-1); 
    return result;
}

void playerGoLeft(float deltaTime)
{
    movePlayerX(-1.0f*deltaTime*PLAYER_SPEED);
    if(leftFoot()==0) player->x = ceil(player->x)-0.0625f;
    setCameraX(player->x-offset->x);
    orientation = LEFT;
}

void playerGoRight(float deltaTime)
{
    movePlayerX(1.0f*deltaTime*PLAYER_SPEED);
    if(rightFoot()==0) player->x = floor(player->x)+0.0625f;
    setCameraX(player->x-offset->x);
    orientation = RIGHT;
}

void playerGoUp(float deltaTime)
{
    movePlayerY(-1.0f*deltaTime*PLAYER_SPEED);
    if(leftFoot()==0||rightFoot()==0) player->y = ceil(player->y);
    setCameraY(player->y-offset->y);
    orientation = BACK;
}

void playerGoDown(float deltaTime)
{
    movePlayerY(1.0f*deltaTime*PLAYER_SPEED);
    if(leftFoot()==0||rightFoot()==0) player->y = floor(player->y);
    setCameraY(player->y-offset->y);
    orientation = FRONT;
}

void movePlayerX(float a)
{
    player->x += a;
    while((player->x)>((float)MAP_SIZE)) player->x -= ((float)MAP_SIZE);
    while((player->x)<0.0f) player->x += ((float)MAP_SIZE);
}

void movePlayerY(float a)
{
    player->y += a;
    while((player->y)>((float)MAP_SIZE)) player->y -= ((float)MAP_SIZE);
    while((player->y)<0.0f) player->y += ((float)MAP_SIZE);
}

void renderPlayer()
{
    unsigned char textureID = TXT_PLAYER_IDLE;
    if((SDL_GetTicks()/250)%2)
    {
        if(orientation==LEFT) textureID = TXT_PLAYER_LEFT_1;
        else if(orientation==RIGHT) textureID = TXT_PLAYER_RIGHT_1;
        else if(orientation==BACK) textureID = TXT_PLAYER_BACK_1;
        else if(orientation==FRONT) textureID = TXT_PLAYER_FRONT_1;
    }
    else
    {
        if(orientation==LEFT) textureID = TXT_PLAYER_LEFT_2;
        else if(orientation==RIGHT) textureID = TXT_PLAYER_RIGHT_2;
        else if(orientation==BACK) textureID = TXT_PLAYER_BACK_2;
        else if(orientation==FRONT) textureID = TXT_PLAYER_FRONT_2;
    }
    renderTextureOnTheMap(textureID, player->x, player->y);
}
