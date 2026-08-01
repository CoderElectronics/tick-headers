#pragma once

#ifdef MIRROR_APP
#include <stdint_target.h>
#endif

#ifdef MIRROR_HOST
#include <stdint.h>
#endif

// Syscall IDs (The O(1) indices)
typedef enum {
    SYS_YIELD       = 0, // Maps to UVM32_SYSCALL_YIELD
    SYS_PUTC        = 1, // Maps to UVM32_SYSCALL_PUTC
    SYS_PRINTLN     = 2, // Maps to UVM32_SYSCALL_PRINTLN
    SYS_DRAW_PIXEL  = 3,
    SYS_DRAW_LINE   = 4,

    SYS_MAX_FUNCTIONS
} mixel_syscall_id_t;

// Mixel LCD Commands
typedef struct {
    int16_t x;
    int16_t y;
    uint16_t color;
} mixel_pixel_cmd_t;

typedef struct {
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
    uint16_t color;
} mixel_line_cmd_t;
