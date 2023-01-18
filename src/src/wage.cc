// WAGE v0.1 2023 lili

#include <iostream>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>

#include "defs.hh"
#include "render/render.cc"

#ifdef USE_X_SERVER // dont include files we dont need to reduce binary sizes on some compilers
    #include "render/x.cc"
#endif

#ifdef USE_WAYLAND
    #include "render/way.cc"
#endif

int main(int argc, char** argv) {

    #ifdef USE_X_SERVER
        XINIT();
        XLOOP();
        XCLOSE();
    #endif

    #ifdef USE_WAYLAND

    #endif

    exit(0);
}
