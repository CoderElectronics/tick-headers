#pragma once

#include "mirror_target.h"
#include "mirror_shared.h"

#ifdef MIRROR_APP

static inline void mixel_draw_pixel(int16_t x, int16_t y, uint16_t color) {
    static mixel_pixel_cmd_t cmd;
    cmd.x = x;
    cmd.y = y;
    cmd.color = color;
    syscall((uint32_t)SYS_DRAW_PIXEL, (uint32_t)&cmd, 0);
}

static inline void mixel_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    static mixel_line_cmd_t cmd;
    cmd.x0 = x0;
    cmd.y0 = y0;
    cmd.x1 = x1;
    cmd.y1 = y1;
    cmd.color = color;
    syscall((uint32_t)SYS_DRAW_LINE, (uint32_t)&cmd, 0);
}

#endif

#ifdef MIRROR_HOST

#endif
