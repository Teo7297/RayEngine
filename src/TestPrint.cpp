#include "RayEngine/TestPrint.h"

#include <string>
#include <iostream>
#include "raylib.h"


void TestWindow(const std::string& title)
{
    // Initialize the window
    InitWindow(800, 600, title.c_str());

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, RayEngine WITH NO EMSCRIPTED SHIT AROUND LMAO!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    // Close the window
    CloseWindow();
}