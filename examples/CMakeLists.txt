# File: examples/CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(RayEngineExamples)

# Include the main project's include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the SimpleGameExample subdirectory
add_subdirectory(SimpleGameExample)
add_subdirectory(ComputeShaderExample)
add_subdirectory(EngineTesting)
add_subdirectory(PhysicsExample)

# You can add additional examples here
# add_subdirectory(AnotherExample)