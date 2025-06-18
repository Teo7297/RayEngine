@echo off

REM Set the project directory explicitly to the parent of the tools folder
set PROJECT_DIR=%~dp0..
echo Using project directory: %PROJECT_DIR%

REM Call Emscripten environment setup
call C:\emscripten\emsdk\emsdk_env.bat

REM Create build directory if it doesn't exist
if not exist "%PROJECT_DIR%\build_web" mkdir "%PROJECT_DIR%\build_web"

REM Navigate to build directory
cd "%PROJECT_DIR%\build_web"

REM Run CMake with the correct path and required raylib flags for web
echo Running CMake for directory: %PROJECT_DIR%
emcmake cmake "%PROJECT_DIR%" ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DGRAPHICS="OPENGL_ES3" ^
    -DCMAKE_C_FLAGS="-Os -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES3 -s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2" ^
    -DCMAKE_CXX_FLAGS="-Os -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES3 -s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2" ^
    -DCMAKE_EXE_LINKER_FLAGS="-Os -s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s ASYNCIFY -s EXPORTED_RUNTIME_METHODS=ccall -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2" ^
    -DCMAKE_EXECUTABLE_SUFFIX=".html"