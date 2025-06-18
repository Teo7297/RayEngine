cmake_minimum_required(VERSION 3.14)

project(RayEngine VERSION 1.0.0 LANGUAGES C CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform-specific settings
if(UNIX)
    # Linux-specific settings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
endif()

# Include FetchContent module
include(FetchContent)

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
add_library(${PROJECT_NAME} SHARED ${SOURCES})  # DLL/SO for desktop

# Link with raylib
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

target_compile_definitions(${PROJECT_NAME} PRIVATE RAYENGINE_EXPORTS)

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