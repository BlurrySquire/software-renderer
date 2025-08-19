#ifdef PLATFORM_X11

#include "platform.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>

Display* display = NULL;
Window window = 0;
GC graphics = 0;
Atom wm_delete_window = 0;
Pixmap back_buffer = 0;

uint32_t width = 800;
uint32_t height = 600;

void platform_init() {
    display = XOpenDisplay(NULL);
    window = XCreateSimpleWindow(
        display, DefaultRootWindow(display), 0, 0,
        width, height, 0,
        CopyFromParent, CopyFromParent
    );

    XStoreName(display, window, "Software Renderer");

    wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wm_delete_window, 1);

    XSelectInput(display, window, KeyPressMask | StructureNotifyMask);

    XMapWindow(display, window);

    graphics = XCreateGC(display, window, 0, NULL);
    back_buffer = XCreatePixmap(display, window, width, height, DefaultDepth(display, DefaultScreen(display)));

    for(;;) {
	    XEvent event;
	    XNextEvent(display, &event);
	    if (event.type == MapNotify) {
            break;
        }
    }

    XFlush(display);
}

void platform_fini() {
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

bool platform_process_events() {
    while (XPending(display)) {
        XEvent event;
        XNextEvent(display, &event);

        if (event.type == ClientMessage) {
            if ((Atom)event.xclient.data.l[0] == wm_delete_window) {
                return false;
            }
        }
    }

    return true;
}

void platform_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    vprintf(fmt, args);

    va_end(args);
}

void* platform_alloc(size_t size) {
    return malloc(size);
}

void platform_free(void* data) {
    free(data);
}

bool platform_get_keypress([[maybe_unused]] char key) {
    return true;
}

uint32_t platform_get_width() {
    return width;
}

uint32_t platform_get_height() {
    return height;
}

void platform_draw_start() {
    // Doesn't do anything for X11 but might be needed on other platforms
}

void platform_draw_fini() {
    XCopyArea(display, back_buffer, window, graphics, 0, 0, width, height, 0, 0);
    XFlush(display);
}

void platform_draw_pixel(uint32_t x, uint32_t y, uint32_t colour) {
    XSetForeground(display, graphics, colour);
    XDrawPoint(display, back_buffer, graphics, x, y);
}

void platform_draw_clear(uint32_t colour) {
    XSetForeground(display, graphics, colour);
    XFillRectangle(display, back_buffer, graphics, 0, 0, width, height);
}

#endif