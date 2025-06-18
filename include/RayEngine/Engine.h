#pragma once

#include "RayEngine/Export.h"

namespace RayEngine
{

    class RAYENGINE_API Engine
    {
    public:
        static Engine& GetInstance();

        Engine(const Engine&) = delete;            // Delete copy constructor
        Engine& operator=(const Engine&) = delete; // Delete copy assignment operator

        void Run(); // Method to start the engine

    private:
        Engine();
        ~Engine();
    };

}