#include "RayEngine/Engine.h"

#include "raylib.h"

namespace RayEngine
{
    Engine& Engine::GetInstance()
    {
        static Engine instance; // Guaranteed to be destroyed.
        return instance;         // Instantiated on first use.
    }

    void Engine::Run()
    {
        // This should start the scene game loop
        while(!WindowShouldClose())    // Detect window close button or ESC key
        {
            BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("ENGINE IS RUNNING!", 190, 200, 20, LIGHTGRAY);

            EndDrawing();
        }
    }

    Engine::Engine()
    {
        InitWindow(640, 480, "RAYENGINE");
    }

    Engine::~Engine()
    {

    }

} // namespace RayEngine