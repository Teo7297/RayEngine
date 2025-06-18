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

# Fetch raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)

# Fetch Bullet Physics
FetchContent_Declare(
    bullet
    GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
    GIT_TAG master
)

# Configure Bullet build options
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET3 OFF CACHE BOOL "" FORCE)
set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # Static linking for Bullet

# Don't build raylib examples 
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Fetch and make libraries available
FetchContent_MakeAvailable(raylib bullet)

# Set include and source directories
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add include directories
include_directories(
    ${INCLUDE_DIR}
    ${bullet_SOURCE_DIR}/src
)

# Find all source files in src directory
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

# Create library - shared for desktop
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Link with raylib and Bullet libraries
target_link_libraries(${PROJECT_NAME} PUBLIC 
    raylib
    LinearMath
    Bullet3Common
    BulletCollision
    BulletDynamics
    BulletInverseDynamics
    BulletSoftBody
)

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