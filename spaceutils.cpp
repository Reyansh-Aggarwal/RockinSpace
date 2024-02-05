#include <raylib.h>

Texture loadTexture( const char* ImgPath, int width, int height){ 
  Image img = LoadImage(ImgPath);
  Image* point_img = &img;
  ImageResizeNN(point_img, width, height);
  Texture texture = LoadTextureFromImage(img);
  return texture;
}

void clampi (float &cl, int min, int max){
  if (cl > max){
    cl = max;
  } 
  else if(cl < min){
    cl = min;
  }
}