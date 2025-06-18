#include "RayEngine/TestPrint.h"

#include <iostream>

int main(int argc, char const* argv[])
{
    std::cout << "Welcome to RayEngine!" << std::endl;
    std::cout << "RayEngine Version: "
        << RayEngine_GetVersionMajor() << "."
        << RayEngine_GetVersionMinor() << "."
        << RayEngine_GetVersionPatch() << std::endl;
    std::cout << "Now trying to call a DLL function!" << std::endl;
    TestWindow("Hello, RayEngine!");
    return 0;
}
