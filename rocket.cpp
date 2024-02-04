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
    Vector2 rPos, rVel, dir;
    dir.x = 1;
    dir.y = 1;
    int xrocket, yrocket, dist, objective;
    bool inEarth;
    objective = 0;
    int screenWidth = 960;
    int screenHeight = 540;
    float grav = 9.8f;
    Image rRestImg = LoadImage ("assets/rocket-rest2.png");
    Image rImg = LoadImage ("assets/rocket.png");
    rPos.x = 460;
    rPos.y = 350;

    Camera2D cam = {{480, 270}, {0, 0}, 0.0f, 2.0f}; 
    cam.target = (Vector2){ rPos.x + 20, rPos.y + 20};
    cam.offset = (Vector2){ 0, 0 };
    cam.target = (Vector2){ 400, 200 };
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    Rectangle floor;
    floor.x = 0;
    floor.y = 520;
    floor.width = 960;
    floor.height = 20;
    
    Rectangle collRocket;
    collRocket.width = 40;
    collRocket.height = 50;

    InitWindow(screenWidth, screenHeight, "RockinSpace!");
    SetTargetFPS(120);

    //image fixing
    Image* point_rRestImg = &rRestImg;
    Image* point_rImg = &rImg;
    Texture2D rRestTexture;
    Texture2D rTexture;
    ImageResizeNN(point_rRestImg, 40, 50);
    ImageResizeNN(point_rImg, 40, 50);

    rRestTexture = LoadTextureFromImage(rRestImg);
    rTexture = LoadTextureFromImage(rImg);

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
        DrawRectangleRec(floor, GREEN);
        DrawRectangleRec(collRocket, DARKBLUE);
        DrawTexture(rRestTexture, rPos.x, rPos.y,WHITE);
        DrawFPS(0,0); // fps
        //DrawText(TextFormat("X: %d", xrocket), 12, 40, 20, GREEN); // X coords
        //DrawText(TextFormat("Y: %d", yrocket), 12, 70, 20, GREEN); // Y coords

        //checking if obj complete
        if (dist > 31){
            //erasing previous text
            DrawText("Escaped Earth!", 400, 270, 20, GREEN);
            objective = 1;//telling game to close 
        }
        else if (CheckCollisionRecs(collRocket, floor)){
            //erasing previous text

            DrawText("Mission Failed", 390, 270, 20, RED);
            objective = 1; //telling game to close 
        }

        if (objective == 0){
            DrawText(TextFormat("Distance from Planet: %d", dist), 0, 40, 20, PURPLE);
            DrawText("Escape Earth's gravity by reaching distance 30+", 200, 270, 20, PURPLE);
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
        BeginMode2D (cam);

        //applying grav
        rVel.y += grav * delta;
            
        //calculating cVelocity and position
        rVel.y += dir.y * delta;
        rPos.y += rVel.y * delta;

        cam.target = (Vector2){rPos.x + 20, rPos.y + 20};
        cam.offset = (Vector2){0, rVel.y};

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
