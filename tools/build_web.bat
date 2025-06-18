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

REM Build
emmake make