# Zinot Project
Simple 3D game engine (not usable yet), some utility classes (for engine and textures tool) 
and compressed (DXT1/3/5) textures binary format for OpenGL with converting tool.

## Used software
- Qt5Core - strings processing, JSON reading, data containers
- SFML - window and OpenGL context
- GLLoadGen - OpenGL 3.3 loader
- libsquish - compressing textures
- FreeImage - loading PNG
- FreeType2 - fonts
- GLM - math
- Google Test - unit tests
- CMake - building execs

## Building
### On Microsoft Windows
- You must get and compile third party libraries.
- Open `Libraries.cmake` in text editor and edit paths below `elseif (WIN32)` statement to your paths of third party libraries.
- Change variable `LIB_QT_HOME` in `Libraries.cmake` file. It is path with pattern `<Qt_installation_dir>/<Qt_version/<compiler_type>`.
- Make `build` directory in root directory and `cd` into it.
- Run `cmake -G "MinGW Makefiles" ..` command in build directory.
- Run `make` command
- If everything has gone ok building is done!

### On Linux
- You must get necessary third party packages from your distro's repository.
- Open Libraries.cmake in text editor and change `LIB_QT_HOME` (placed below `if (CMAKE_SYSTEM_NAME MATCHES "Linux")`) variable to your value. It is path with pattern `<Qt_installation_dir>/<Qt_version/<compiler_type>`.
- Make `build` directory in root directory and `cd` into it.
- Run `cmake ..` command in build directory.
- Run `make` command
- If everything has gone ok building is done!