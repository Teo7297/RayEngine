#include "raylib.h"
#include "rlgl.h"
#include <iostream>
#include <string>

int main(int argc, char const* argv[])
{

    InitWindow(800, 600, "Compute Shader Example");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw some text
        DrawText("Compute Shader Example", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    return 0;
}
