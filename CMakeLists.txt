cmake_minimum_required(VERSION 3.14)

# Check if building with Emscripten
if(EMSCRIPTEN)
    message(STATUS "Building for Web platform with size optimization")
    
    # Define platform-specific compiler definitions
    add_compile_definitions(PLATFORM_WEB GRAPHICS_API_OPENGL_ES2)
    
    # Set output to HTML files
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    
    # Add Emscripten-specific compiler and linker flags with -Os for size optimization
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Os -s ASYNCIFY -s EXPORTED_RUNTIME_METHODS=ccall")
    
    # Web-specific build options
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)  # Force static for web
else()
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF) # This affects only raylib, RayEngine will still be shared for desktop platforms
endif()

project(RayEngine VERSION 1.0.0 LANGUAGES C CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform-specific settings
if(UNIX AND NOT EMSCRIPTEN)
    # Linux-specific settings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
endif()

# Include FetchContent module
include(FetchContent)

# Fetch raylib - special handling for Emscripten
if(EMSCRIPTEN)
    # Force Web platform and OpenGL ES 2.0 for raylib
    set(PLATFORM "Web" CACHE STRING "Platform" FORCE)
    set(GRAPHICS "OpenGL_ES_2.0" CACHE STRING "Graphics API" FORCE)
    
    # Additional raylib-specific settings
    set(SUPPORT_GESTURES_SYSTEM ON CACHE BOOL "" FORCE)
endif()

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)

# Don't build raylib examples 
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Fetch and make raylib available
FetchContent_MakeAvailable(raylib)

# Set include and source directories
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add include directory
include_directories(${INCLUDE_DIR})

# Find all source files in src directory
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

# Create library - static for Emscripten, shared for other platforms
if(EMSCRIPTEN)
    add_library(${PROJECT_NAME} STATIC ${SOURCES})  # Static lib for web
else()
    add_library(${PROJECT_NAME} SHARED ${SOURCES})  # DLL/SO for desktop
endif()

# Link with raylib
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

# Define RAYENGINE_EXPORTS when building the library
if(NOT EMSCRIPTEN)
    target_compile_definitions(${PROJECT_NAME} PRIVATE RAYENGINE_EXPORTS)
endif()

# Set the output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Conditionally build examples
option(BUILD_RAYENGINE_EXAMPLES "Build the RayEngine examples" ON)
if(BUILD_RAYENGINE_EXAMPLES)
    add_subdirectory(examples)
endif()