#include "RayEngine/Engine.h"

int main(int argc, char const* argv[])
{
    RayEngine::Engine* engine = &RayEngine::Engine::GetInstance();
    engine->Run();

    return 0;
}
