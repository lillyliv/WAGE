// WAGE v0.1 2023 lili

#include <iostream>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WAGE_WINDOW_NAME "WAGE V0.1 By LILI"
#define WAGE_VERSION_INT 0 // version zero, increments by one for every stable release

int main(int argc, char** argv) {
    Display *d; // display
    Window w;   // window
    XEvent e;   // current event
    int s;      // screen number

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

    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
            // XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
        }
        if (e.type == KeyPress)
            break;
    }

    XCloseDisplay(d);
    return 0;
}