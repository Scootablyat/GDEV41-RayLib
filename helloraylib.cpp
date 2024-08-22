#include <raylib.h>
 
/* 
    HOW TO RUN RAYLIB FILES:
    g++ helloraylib.cpp -o out -I raylib/ -L raylib/ -lraylib -lopengl32 -lgdi32 -lwinmm 
    
    replace helloraylib.cpp with .cpp file of choice (obviously)
    replace out with name of file (obviously)

    DrawRectangle(x pos, y pos, width, height);
    - (x, y) is where the rectangle will be draw from and it will act as the upper left point of the rectangle

    ClearBackground(color);
    - changes background color

    ./nameOfFile.exe


    Raylib uses Polling based input (basically always checking a bunch of times a second if a button is being pressed)
*/

int main(){
    InitWindow(800, 600, "Hello Raylib");
    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(PINK);


        EndDrawing();
    }
    CloseWindow();
    return 0;
}