// WAGE renderer for X11

#pragma once
#include "../defs.hh"
#include "render.cc"

Display *d; // display
Window w;   // window
XEvent e;   // current event
int s;      // screen number

void XINIT() {

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Could not connect to X11 Display!");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 500, 500, 1, BlackPixel(d, s), WhitePixel(d, s));
    XStoreName(d, w, WAGE_WINDOW_NAME); // window title

    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);
}

void XLOOP() {
    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
            // XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
        }
        if (e.type == KeyPress)
            break;
    }
}

void XCLOSE() {
    XCloseDisplay(d);
    exit(0);
}