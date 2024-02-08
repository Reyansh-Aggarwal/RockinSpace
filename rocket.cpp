#include "raylib.h"
#include"spaceutils.h"
#include <cstdlib>
#include <unistd.h>
int main() {    

  //intializing 
  Color lightBlue = Color{0, 118, 248, 255};
  Color spaceBlue = Color{32, 40, 46, 255};
  Vector2 rPos, rVel, dir, camPos, cloudPos, sliderPos, tracker;
  dir.x = 1;
  dir.y = 1;
  int dist, objective;
  bool inEarth;
  objective = 0;
  int screenWidth = 960;
  int screenHeight = 540;
  float grav = 0.98f;
  tracker.x = 892;
  tracker.y = 470;
  rPos.x = 460;
  rPos.y = 350;     //rPos.y = 270 acc to cam
  camPos.x = rPos.x;
  camPos.y = rPos.y;
  cloudPos.x = cloudX();
  cloudPos.y = 0;

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
  SetTargetFPS(165);

  //loading textures
  Texture2D rRestTexture = loadTexture("assets/rocket-rest.png", 39, 53);
  Texture2D rTexture = loadTexture("assets/rocket-motion.png", 39, 53);
  Texture2D cloudTexture = loadTexture("assets/cloud.png", 104, 44);
  Texture2D sliderTexture = loadTexture("assets/slider1.png", 80, 500);
  Texture2D trackerTexture = loadTexture("assets/tracker.png", 29, 37);

  while (!WindowShouldClose()){

    //setting values before drawing
    dist = (floor.y - rPos.y - 40)/10;
    float delta = GetFrameTime();
    inEarth = dist < 1601;
    collRocket.x = rPos.x;
    collRocket.y = rPos.y; 


    //clamping
    clampi (rVel.x, -50, 50);
    clampi (rVel.y, -50, 50);
    clampi (tracker.y, 30, 470);

    //draw
    BeginDrawing();

    if (!inEarth){
      ClearBackground(spaceBlue);
    }
    else{
      ClearBackground(DARKBLUE);
    }
    
    //drawing slider
    BeginMode2D(cam);

    DrawRectangleRec(floor, GREEN);

    //drawing cloud
    if (cloudPos.y > rPos.y - 310 && cloudPos.y < rPos.y + 300){  //only draws cloud when on screen
    DrawTexture(cloudTexture, cloudPos.x, cloudPos.y, WHITE);
    }

    /*if (rPos.y > 320){
      DrawTexture(sliderTexture, 866, 70, WHITE);
      DrawText(TextFormat("Distance from Planet: %d%s", dist, "m"),0, 60, 20, PURPLE);
      DrawFPS(0, 80);
    } */

    //drawing text

    if (CheckCollisionRecs(collRocket, floor)){

      DrawText("Mission Failed", 390, 270, 20, RED);
      objective = 1; //telling game to close 
    }

    if (objective == 0){
      DrawText("Escape Earth's gravity by reaching distance 30+", 220, 270, 20, lightBlue);
      DrawText("Press W OR Right Back Trigger/Up Arrow on Gamepad to Go UP", 150, 240, 20, lightBlue);
      } 

    //drawing sprite
    DrawTexture(rRestTexture, rPos.x, rPos.y,WHITE);



    //moving cloud(s)
    cloudPos.x += 20 * delta;

    //checking if obj complete
    // if (dist > 31){
    //   //erasing previous text
    //   DrawText("Escaped Earth!", 400, 270, 20, GREEN);
    //   objective = 1;//telling game to close 
    // }

    if (IsKeyDown(KEY_W) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)){
      dir.y = -1; 
      rVel.y -= 11;
      DrawTexture(rTexture, rPos.x, rPos.y, WHITE);
    } else {
      dir.y = 1;
    }

    //applying grav
    if (inEarth){
      rVel.y += grav * delta;
    }

    //applying grav
    //rVel.y += grav * delta;
            
    //calculating cVelocity and position
    rVel.y += dir.y * delta;
    rPos.y += rVel.y * delta;

    if (rPos.y < 320){
      cam.target = {camPos.x, rPos.y};
    } else if (rPos.y > 320){
      cam.target = {camPos.x, 320};
    }
  

    cam.offset = {rPos.x , (float)screenHeight/2};
    
    float distPercent = dist/80 * 100;
    float pixelPercent = 1/100 * 440;
    tracker.y -= (distPercent * pixelPercent);

    if (objective == 1) {
      BeginDrawing();
      DrawText("Closing window  in 2s",380, 70, 20, RED);
      EndDrawing();
      WaitTime (2);
      break;
    }
    EndMode2D();

    //calculating tracker pos
    DrawText(TextFormat("tracker.y =  %f %s", tracker.y, "for debugging only (line 166)"),0, 100, 20, PURPLE); //debugging

    //drawing gui
    DrawFPS(0, 30);
    DrawTexture(sliderTexture, 866, 20, WHITE);
    DrawTexture(trackerTexture, tracker.x , tracker.y, WHITE);  // y = 470 - lowest, y = 30 - highest, 4 px = 1%
    
    

    if (inEarth){
      DrawText(TextFormat("Distance from Planet: %d%s", dist, "m"),0, 10, 20, PURPLE);
    }
    else if (!inEarth){
      DrawText(TextFormat("Distance from Saturn: %d%s", (8000 - dist), "m"),0, 10, 20, PURPLE);
    }
  

    EndDrawing();
  }

  UnloadTexture(rTexture);
  UnloadTexture(rRestTexture);
  UnloadTexture(cloudTexture);
  UnloadTexture(sliderTexture);
  UnloadTexture(trackerTexture);

  CloseWindow();
  return 0;
}
