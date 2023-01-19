// WAGE renderer for X11

#pragma once
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include "../defs.hh"
#include "render.cc"

Display *d; // display
Window w;   // window
XEvent e;   // current event
GC gc;      // graphics context
int s;      // screen number

Colormap cmap;

SHAPE testShape;


void XRENDER_SHAPE(SHAPE shape) {
    if(shape.PRIM = PRIM_RECT) {
        XAllocColor(d, cmap, &shape.color);
        XSetForeground(d, gc, shape.color.pixel);
        XFillRectangle(d, w, gc, shape.x, shape.y, shape.w, shape.h);
    }
}

void XINIT() {

    testShape.PRIM = PRIM_RECT;
    testShape.x = 50;
    testShape.y = 50;
    testShape.w = 100;
    testShape.h = 100;
    XColor tmpColor;
    tmpColor.red = 0xFFFF; tmpColor.green = 0xFFFF; tmpColor.blue = 0xFFFF;
    tmpColor.flags = DoRed | DoGreen | DoBlue;
    testShape.color = tmpColor;

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

    gc = XCreateGC(d, w, 0, 0);
    XSetBackground(d, gc, WhitePixel(d, s));
	XSetForeground(d, gc, BlackPixel(d, s));

    cmap = DefaultColormap(d, DefaultScreen(d));
}

void XLOOP() {
    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            // XFillRectangle(d, w, gc, 20, 20, 10, 10);
            // XColor xcolour;

            // I guess XParseColor will work here
            // xcolour.red = 0x0; xcolour.green = 0xFFFF; xcolour.blue = 0x0;
            // xcolour.flags = DoRed | DoGreen | DoBlue;
            // XAllocColor(d, cmap, &xcolour);

            // XSetForeground(d, gc, xcolour.pixel);
            // XFillRectangle(d, w, gc, 0, 0, 30, 30);
            // XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));

            XRENDER_SHAPE(testShape);
        }
        if (e.type == KeyPress)
            break;
    }
}

void XCLOSE() {
    XCloseDisplay(d);
    XFreeGC(d, gc);
    exit(0);
}