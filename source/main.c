#include "platform/platform.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    platform_init();

    while (platform_process_events()) {
        platform_draw_start();

        platform_draw_clear(0x000000);
        platform_draw_pixel(50, 50, 0xFFFFFF);

        platform_draw_fini();
    }

    platform_printf("Hello, world!\n");

    platform_fini();

    return 0;
}