#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "types.h"

void platform_init();
void platform_fini();

bool platform_process_events();

void platform_printf(const char* fmt, ...);

void* platform_alloc(size_t size);
void platform_free(void* data);

bool platform_get_keypress(char key);

uint32_t platform_get_width();
uint32_t platform_get_height();

void platform_draw_start();
void platform_draw_fini();

void platform_draw_pixel(uint32_t x, uint32_t y, uint32_t colour);
void platform_draw_clear(uint32_t colour);

#endif