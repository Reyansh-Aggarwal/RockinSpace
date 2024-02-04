#include <raylib.h>

void clampi (float &cl, int min, int max){
  if (cl > max){
    cl = max;
  } 
  else if(cl < min){
    cl = min;
  }
}

int main() {
  //intializing 
  Vector2 rPos, rVel, dir, camPos;
  dir.x = 1;
  dir.y = 1;
  int xrocket, yrocket, dist, objective;
  bool inEarth;
  objective = 0;
  int screenWidth = 960;
  int screenHeight = 540;
  float grav = 0.98f;
  Image rRestImg = LoadImage ("assets/rocket-rest2.png");
  Image rImg = LoadImage ("assets/rocket.png");
  Image cloudImg = LoadImage("assets/cloud.png");
  rPos.x = 460;
  rPos.y = 350;
  camPos.x = rPos.x;
  camPos.y = rPos.y;

  Camera2D cam = { 0 }; 
  cam.target = {camPos.x, camPos.y};
  cam.offset = {camPos.x , camPos.y};
  cam.rotation = 0.0f;
  cam.zoom = 1.0f;

  Rectangle floor;
  floor.x = 0;
  floor.y = 520;
  floor.width = 960;
  floor.height = 100;
    
  Rectangle collRocket;
  collRocket.width = 40;
  collRocket.height = 50;

  InitWindow(screenWidth, screenHeight, "RockinSpace!");
  SetTargetFPS(120);

  //image fixing
  Image* point_rRestImg = &rRestImg;
  Image* point_rImg = &rImg;
  Image* point_cloud = &cloudImg;
  Texture2D rRestTexture;
  Texture2D rTexture;
  Texture2D cloudTexture;

  ImageResizeNN(point_rRestImg, 40, 50);
  ImageResizeNN(point_rImg, 40, 50);
  ImageResizeNN(point_cloud, 104, 44);

  rRestTexture = LoadTextureFromImage(rRestImg);
  rTexture = LoadTextureFromImage(rImg);
  cloudTexture = LoadTextureFromImage(cloudImg);

  while (!WindowShouldClose()){

    //setting values before drawing
    xrocket = int(rPos.x);
    yrocket = int(rPos.y);
    dist = (floor.y - rPos.y - 40)/10;
    float delta = GetFrameTime();
    inEarth = dist < 30;
    collRocket.x = rPos.x;
    collRocket.y = rPos.y;

    //clamping
    clampi (rVel.x, -50, 50);
    clampi (rVel.y, -50, 50);

    //draw
    BeginDrawing();
    ClearBackground(DARKBLUE);
    BeginMode2D(cam);

    DrawRectangleRec(floor, GREEN);
    DrawTexture(rRestTexture, rPos.x, rPos.y,WHITE);
    DrawTexture(cloudTexture, 100, 0, WHITE);

    if (objective == 0){

      DrawText("Escape Earth's gravity by reaching distance 30+", 220, 270, 20, PURPLE);

      if (rPos.y < 320){
        DrawText(TextFormat("Distance from Planet: %d", dist), (rPos.x -460), (rPos.y - 250) + 20, 20, PURPLE);
        // DrawText(TextFormat("Y: %d", yrocket), 0, (rPos.y - 270), 20, GREEN);
        DrawFPS(rPos.x -460, rPos.y - 250); // fps
      } 
      else{
        DrawText(TextFormat("Distance from Planet: %d", dist), (rPos.x -460), 90, 20, PURPLE);
        // DrawText(TextFormat("Y: %d", yrocket), 0, 50, 20, GREEN);
        DrawFPS(0, 70); // fps
      }  

    }

    //checking if obj complete
    // if (dist > 31){
    //   //erasing previous text
    //   DrawText("Escaped Earth!", 400, 270, 20, GREEN);
    //   objective = 1;//telling game to close 
    // }
    if (CheckCollisionRecs(collRocket, floor)){
 

      DrawText("Mission Failed", 390, 270, 20, RED);
      objective = 1; //telling game to close 
    }

    if (IsKeyDown(KEY_W)){
      dir.y = -1; 
      rVel.y -= 11;
      DrawTexture(rTexture, rPos.x, rPos.y, WHITE);
    } else {
      dir.y = 1;
    }

    //applying grav
    if (inEarth){
      rVel.y += grav;
    }

    //applying grav
    rVel.y += grav * delta;
            
    //calculating cVelocity and position
    rVel.y += dir.y * delta;
    rPos.y += rVel.y * delta;

  if (rPos.y < 320){
    cam.target = {camPos.x, rPos.y};
  } else if (rPos.y > 320){
    cam.target = {camPos.x, 320};
  }
  cam.offset = {rPos.x , (float)screenHeight/2};
    
    if (objective == 1) {
      BeginDrawing();
      DrawText("Closing window  in 2s",380, 70, 20, RED);
      EndDrawing();
      WaitTime (2);
      break;
    }

    EndMode2D();
    
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
