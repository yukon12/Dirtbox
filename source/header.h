#ifndef HEADER
#define HEADER

// To be ordered.

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WORLD_SIZE 1024
#define TEXTURE_SIZE 16
#define PIXEL_SIZE 3
#define UNIT (PIXEL_SIZE*TEXTURE_SIZE)
#define WORLD_WINDOW_SIZE (UNIT*WORLD_SIZE)

#define CAMERA_OFFSET_X (((float)WINDOW_WIDTH-1.0f)/(2.0f*((float)UNIT)))
#define CAMERA_OFFSET_Y (((float)WINDOW_HEIGHT-1.0f)/(2.0f*((float)UNIT)))

#define PLAYER_SPEED 15.0f

#define DIR_BACK 1
#define DIR_FRONT 2
#define DIR_LEFT 3
#define DIR_RIGHT 4

#endif