# Sunshine

    Sunshine is a rendering engine written in c++ using OpenGL.

## Dependencies

This project is beeing developed on Windows 11 with CMake.
This project currently uses the following libraries:

    - OpenGL
    - glfw3
    - glm
    -glad

To install these preferably use vcpkg as the package manager.

## How to run?

To build and run Sunshine, create a build directory in the root of this project.

`mkdir build && cd build`

Configure cmake in this directory.

`cmake .. -DCMAKE_TOOLCHAIN_FILE={/path/to/vcpkg}/scripts/buildsystems/vcpkg.cmake`

Then you can build the project in release mode.

`cmake --build . --config Release`