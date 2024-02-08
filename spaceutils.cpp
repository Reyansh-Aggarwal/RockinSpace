#include <raylib.h>
#include <cstdlib>
Texture loadTexture( const char* ImgPath, int width, int height){ 

  Image img = LoadImage(ImgPath);

  if (!width == 0 && !height == 0){
  Image* point_img = &img;
  ImageResizeNN(point_img, width, height);
  }

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

int cloudX (){
  int posx =rand() % (856 + 1 - 0) + 0;
  return posx;
}