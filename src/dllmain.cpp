#include "RayEngine/Export.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

// Windows DLL entry point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch(reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#elif defined(__EMSCRIPTEN__)
// Nothing needed for Emscripten
#else
// Linux/macOS library constructor/destructor
__attribute__((constructor)) void rayengine_initialize()
{
    // Initialization code for Linux/macOS
}

__attribute__((destructor)) void rayengine_cleanup()
{
    // Cleanup code for Linux/macOS
}
#endif

// Export functions implementations
int RayEngine_GetVersionMajor() { return RAYENGINE_VERSION_MAJOR; }
int RayEngine_GetVersionMinor() { return RAYENGINE_VERSION_MINOR; }
int RayEngine_GetVersionPatch() { return RAYENGINE_VERSION_PATCH; }