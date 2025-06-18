#pragma once

// Define platform-specific export macros
#if defined(EMSCRIPTEN)
    // No exports for Emscripten - everything is statically linked
#define RAYENGINE_API
#elif defined(_WIN32) || defined(_WIN64)
#ifdef RAYENGINE_EXPORTS
    // When building the DLL
#define RAYENGINE_API __declspec(dllexport)
#else
    // When using the DLL
#define RAYENGINE_API __declspec(dllimport)
#endif
#else
    // For Linux/macOS
#ifdef RAYENGINE_EXPORTS
#define RAYENGINE_API __attribute__((visibility("default")))
#else
#define RAYENGINE_API
#endif
#endif

// Version information
#define RAYENGINE_VERSION_MAJOR 1
#define RAYENGINE_VERSION_MINOR 0
#define RAYENGINE_VERSION_PATCH 0

// Export functions declarations
#ifdef __cplusplus
extern "C" {
#endif

    RAYENGINE_API int RayEngine_GetVersionMajor();
    RAYENGINE_API int RayEngine_GetVersionMinor();
    RAYENGINE_API int RayEngine_GetVersionPatch();

#ifdef __cplusplus
}
#endif