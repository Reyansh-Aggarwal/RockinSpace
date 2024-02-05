#ifndef SPACEUTILS
#define SPACEUTILS
#include <raylib.h>

Texture loadTexture( const char* ImgPath, int width, int height); //taking img path, width and height if you wish to resize
void clampi (float &cl, int min, int max);

#endif