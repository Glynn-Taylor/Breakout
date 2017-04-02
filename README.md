# Overview
A breakout game with several engine features such as state handling, an entity-component system, and examples of sprite rendering and collision components.

# Building

## Windows 7
1.  Install [Visual Studio 2015](https://www.visualstudio.com)
2.	Open Visual Studio and Reconfigure additional include and library directories
3. 	You may need to install libpng, either through [vcpkg](https://github.com/Microsoft/vcpkg) or by building zlib and libpng 
4.  Build and run the project

## Linux
1.  Get a copy of the source code, either by cloning this repository, or by
    downloading an
    [archive](https://github.com/google/guetzli/archive/master.zip) and
    unpacking it.
2.  Install [libpng](http://www.libpng.org/pub/png/libpng.html).
    If using your operating system
    package manager, install development versions of the packages if the
    distinction exists.
    *   On Ubuntu, do `apt-get install libpng-dev`.
    *   On Fedora, do `dnf install libpng-devel`. 
    *   On Arch Linux, do `pacman -S libpng`.
    *   On Alpine Linux, do `apk add libpng-dev`.
3.  Run `make` and expect the binary to be created in `bin/Release/guetzli`.