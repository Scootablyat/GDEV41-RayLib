#include <raylib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


/*
Using Raylib, create a scene such that you have three circles, each with a different color.

Pressing the Tab key cycles between the three shapes to choose which one you can control.

Pressing the Space key switches between keyboard and mouse mode.

Keyboard Mode allows the player to control the active circle via WASD AND Arrow Keys.
Mouse Mode makes the active circle follow the mouse cursor.
Make sure that the movement of the circles are Framerate-Independent, meaning that no matter the FPS, movement remains the same. (Only applies to Keyboard Mode)

Bonus: Create a config.ini file where you can reconfigure the key bindings of the movement (Just make it so WASD can be changed, arrow keys can remain constant).

Format of Submission is Surname_Main.cpp and config.ini

Submit JUST the .cpp file. No need for CoA.

DUE: September 6, 2024 (Friday)


NOTE TO SIR: The currently selected circle is highlighted with the pink color.
*/

int GetKeyCode(std::string x){
    char y = x[0];
    return y - '0' + 48;
}

int getSettings(std::string setting)
{
    std::fstream settingsFile;
    settingsFile.open("config.ini", std::ios::in);
    std::string line;
    if (settingsFile.is_open())
    {
        while (std::getline(settingsFile, line)){
            // std::cout << line << std::endl;
            if (line.find("moveUpward") == 0 && setting == "moveUpward"){
                return GetKeyCode(line.erase(0, 16));
            }
            if (line.find("moveDownward") == 0 && setting == "moveDownward"){
                return GetKeyCode(line.erase(0, 16));
            }
            if (line.find("moveRightward") == 0 && setting == "moveRightward"){
                return GetKeyCode(line.erase(0, 16));
            }
            if (line.find("moveLeftward") == 0 && setting == "moveLeftward"){
                return GetKeyCode(line.erase(0, 16));
            }
        }
    }
    return 0;
}


int switchCircles(int currentlySelectedCircle){
    if(currentlySelectedCircle >= 3){
        return 1;
    }
    return currentlySelectedCircle+=1;
}
int switchMovement(int currentMovementMode){
    if(currentMovementMode >= 2){
        return 1;
    }
    return currentMovementMode+=1;
}

void movement(int up, int down, int right, int left, float speed, Vector2& circle){
    if(IsKeyDown(up)){
        circle.y -= speed*GetFrameTime();
    }
    if(IsKeyDown(down)){
        circle.y += speed*GetFrameTime();
    }
    if(IsKeyDown(right)){
        circle.x += speed*GetFrameTime();
    }
        if(IsKeyDown(left)){
        circle.x -= speed*GetFrameTime();
    }
}

void mouseMovement(Vector2& circle){
    circle = GetMousePosition();
}

int main(){
    int cycleCircles = KEY_TAB;
    int cycleMovementMode = KEY_SPACE;
    int moveUpward = KEY_UP;
    int moveDownward = KEY_DOWN;
    int moveRightward = KEY_RIGHT;
    int moveLeftward = KEY_LEFT;
    int altMoveUpward = getSettings("moveUpward");
    int altMoveDownward = getSettings("moveDownward");
    int altMoveRightward = getSettings("moveRightward");
    int altMoveLeftward = getSettings("moveLeftward");
    int currentlySelectedCircle = 1;
    float speed = 120;

    Color circle1 = BLUE;
    Vector2 circle1vect = (Vector2){100, 100};
    Color circle2 = DARKGREEN;
    Vector2 circle2vect = (Vector2){700, 500};
    Color circle3 = LIGHTGRAY;
    Vector2 circle3vect = (Vector2){500, 300};

    int currentMovementMode = 1;
    

    InitWindow(800, 600, "Tamano - Exercise 3");
    double prevTime = GetTime();
    while(!WindowShouldClose()){
        double currentTime = GetTime();
        if(IsKeyPressed(cycleCircles)){
            currentMovementMode = 1;
            currentlySelectedCircle = switchCircles(currentlySelectedCircle);
            std::cout << "Key Pressed: " << cycleCircles << std::endl;
            std::cout << "Currently Selected Circle: " << currentlySelectedCircle << std::endl;
        }
        if(IsKeyPressed(cycleMovementMode)){
            currentMovementMode = switchMovement(currentMovementMode);
            std::cout << "Current Movement Mode: " << currentMovementMode << std::endl;
        }
        if(currentlySelectedCircle == 1){
            circle1 = PINK;
            circle2 = DARKGREEN;
            circle3 = LIGHTGRAY;
            if(currentMovementMode == 1){
                movement(moveUpward, moveDownward, moveRightward, moveLeftward, speed, circle1vect);
                movement(altMoveUpward, altMoveDownward, altMoveRightward, altMoveLeftward, speed, circle1vect);
            }
            if(currentMovementMode == 2){
                mouseMovement(circle1vect);
            }
        }
        if(currentlySelectedCircle == 2){
            circle1 = BLUE;
            circle2 = PINK;
            circle3 = LIGHTGRAY;
            if(currentMovementMode == 1){
                movement(moveUpward, moveDownward, moveRightward, moveLeftward, speed, circle2vect);
                movement(altMoveUpward, altMoveDownward, altMoveRightward, altMoveLeftward, speed, circle2vect);
            }
            if(currentMovementMode == 2){
                mouseMovement(circle2vect);
            }
        }
        if(currentlySelectedCircle == 3){
            circle1 = BLUE;
            circle2 = DARKGREEN;
            circle3 = PINK;
            if(currentMovementMode == 1){
                movement(moveUpward, moveDownward, moveRightward, moveLeftward, speed, circle3vect);
                movement(altMoveUpward, altMoveDownward, altMoveRightward, altMoveLeftward, speed, circle3vect);
            }
            if(currentMovementMode == 2){
                mouseMovement(circle3vect);
            }
        }
        // calculations ^^^^
        BeginDrawing();
        ClearBackground(BLACK);
        
        
        
        DrawCircle(circle1vect.x, circle1vect.y, 50, circle1);
        DrawCircle(circle2vect.x, circle2vect.y, 50, circle2);
        DrawCircle(circle3vect.x, circle3vect.y, 50, circle3);
        

        EndDrawing();
    }
    CloseWindow();
    return 0;
}