// WAGE v0.1 2023 lili

#include <iostream>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.hh"
#include "render/x.cc"

int main(int argc, char** argv) {
    XINIT();
    XLOOP();
    XCLOSE();
}
