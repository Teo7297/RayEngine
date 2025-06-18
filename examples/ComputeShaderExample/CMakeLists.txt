# File: examples/ComputeShaderExample/CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(ComputeShaderExample)

# Set source files
set(SOURCES main.cpp)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link with RayEngine target
target_link_libraries(${PROJECT_NAME} PRIVATE RayEngine)

# Set output directory for the executable to match the DLL location
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
)

# If you need to copy resources when building
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/resources")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "${CMAKE_BINARY_DIR}/bin/examples/resources"
    )
endif()