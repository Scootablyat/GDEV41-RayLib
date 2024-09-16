#include <raylib.h>
#include <iostream>
 

int main(){
    float speed = 4;
    float xSpeed = speed;
    float ySpeed = speed;
    float x = 50;
    float y = 50;
    float width = 800;
    float height = 600;
    float rectWidth = 100;
    float rectHeight = 50;
    InitWindow(width, height, "Exercise 2");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        
        if(x+rectWidth >= 800 || x+rectWidth <=0 || x >=800 || x <=0){
            xSpeed*=-1;
        }
        if(y+rectHeight >= 600  || y+rectHeight <=0 || y >=600 || y <=0){
            ySpeed*=-1;
        }
        x+=xSpeed; 
        y+=ySpeed;
        DrawRectangle(x, y, rectWidth, rectHeight, PINK);
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}