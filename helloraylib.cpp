#include <raylib.h>
 
/* 
    HOW TO RUN RAYLIB FILES:
    g++ helloraylib.cpp -o out -I raylib/ -L raylib/ -lraylib -lopengl32 -lgdi32 -lwinmm 
    
    replace helloraylib.cpp with .cpp file of choice (obviously)
    replace out with name of file (obviously)

    ./nameOfFile.exe
*/
int main(){
    InitWindow(800, 600, "Hello Raylib");
    while(!WindowShouldClose()){
        BeginDrawing();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}